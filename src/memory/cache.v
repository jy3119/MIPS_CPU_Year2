`include "src/memory/util.v"
/*
  I've done [weird amount] of cache presently however this is easy to change.
  I need to look more into what an optimal amount is.
  
  Block: Tag: 18 bits, word: 32 bits
  Set:   4 blocks
  Cache: 4096 Sets
*/

module cache (
    /* Standard signals */
    input logic clk,
    input logic reset,
    output logic active,
    output logic[31:0] register_v0,

    /* Avalon memory mapped bus controller (master) */
    output logic[31:0] address,
    output logic write,
    output logic read,
    input logic waitrequest,
    output logic[31:0] writedata,
    // As I've not got this from the CPU I'm assuming it's always all bytes?
    output logic[3:0] byteenable = 4'b1111,
    input logic[31:0] readdata
  );

  //  Cache signals //
  logic miss = 0;
  logic[3:0][49:0] cache[4095:0]; // We can change size easily enough, size is weird because tag...
  logic[11:0] cache_address;
  logic [1:0] offset;
  logic[17:0] tag;

  // Signals from CPU interface //
  logic cpu_write, cpu_read, cpu_wait;
  // Signals to CPU //
  logic[31:0] cpu_readdata;
  // Any more to add?

  assign offset = address[1:0];
  assign cache_address = address[13:2]; // address % 12 ignoring offset
  assign tag = address[31:14];

  // Do I need to be more explicit with time here? (ie are we assuming cache is instant?)

  always @(posedge cpu_write) `do (
    cpu_wait <= 1;
    write <= 1;
    cache[cache_address][3] <= cache[cache_address][2];
    cache[cache_address][2] <= cache[cache_address][1];
    cache[cache_address][1] <= cache[cache_address][0];
    cache[cache_address][0] <= {tag, writedata};
    // I assume it's ok to stop the waitrequest even though we haven't written
    // to memory yet as the data will be in the cache?
    cpu_wait <= 0;
    @(negedge waitrequest);
    write <= 0;
  )

  // It's probably wise to change this from a ternary to a MUX
  // Z (high impedance) is synthesisable but I don't think it's best practise?

  always @(posedge read) `do (
    waitrequest <= 1;
    cpu_readdata <= cache[cache_address][0][49:32] == tag?
      cache[cache_address][0][31:0] : cache[cache_address][1][49:32] == tag?
      cache[cache_address][1][31:0] : cache[cache_address][2][49:32] == tag?
      cache[cache_address][2][31:0] : cache[cache_address][3][49:32] == tag?
      cache[cache_address][0][31:0] : 50'hz;
    miss <= cpu_readdata == 50'hz;
    waitrequest <= miss;
  )
  
  always @(posedge miss) `do (
    read <= 1;
    // Is this preferable to @(readdata)?(
    @(negedge waitrequest);
    cpu_readdata <= readdata;
    read <= 0;
    // Is it ok to disable waitrequest before we write the cache as it's speedy?
    cpu_wait <= 0;
    // Will this just clog the cache up with instructions?
    cache[cache_address][3] <= cache[cache_address][2];
    cache[cache_address][2] <= cache[cache_address][1];
    cache[cache_address][1] <= cache[cache_address][0];
    cache[cache_address][0] <= {tag, readdata};
  )
endmodule