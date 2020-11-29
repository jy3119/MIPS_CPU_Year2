interface Harvard_Interface;
    input logic clk;
    input logic resetl;
    output logic active;
    output logic [31:0] register_v0;

    /* New clock enable. See below. */
    input logic clk_enable;

    /* Combinatorial read access to instructions */
    output logic[31:0]  instr_address;
    input logic[31:0]   instr_readdata;

    /* Combinatorial read and single-cycle write access to instructions */
    output logic[31:0] data_address;
    output logic data_write;
    output logic data_read;
    output logic[31:0] data_writedata;
    input logic[31:0] data_readdata;
endinterface //Harvard_Interface
