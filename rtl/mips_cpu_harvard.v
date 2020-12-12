
//Harvard bus
//TODO  fix naming of hi, lo modules to HI, LO
//TODO  add support for HI LO moving commands(multiplexers)
module mips_cpu_harvard (
	input logic clk,
	/* verilator lint_off UNUSED */
	input logic reset,
	/* verilator lint_off UNDRIVEN */output logic active,
	output logic [31:0] register_v0,

	/* New clock enable. See below. */
	input logic clk_enable,

	/* Combinatorial read access to instructions */
	output logic[31:0]  instr_address,
	input logic[31:0]   instr_readdata,

	/* Combinatorial read and single-cycle write access to instructions */
	output logic[31:0] data_address,
	output logic data_write,
	output logic data_read,
	output logic[31:0] data_writedata,
	input  logic[31:0] data_readdata
);

	logic internal_clk;
	
	logic HI_LO_output;


	//Fetch control
	logic [31:0] program_counter_prime;
	logic [31:0] program_counter_fetch;
	logic [31:0] program_counter_plus_four_fetch;
	logic [31:0] instruction_fetch;
	logic [31:0] program_counter_mux_1_out;
	logic 		 halt;

	//decode Controls
	logic       program_counter_source_decode;
	logic       register_write_decode;
	logic       memory_to_register_decode;
	logic       memory_write_decode;
	logic [1:0] ALU_src_B_decode;
	logic       register_destination_decode;
	logic       branch_decode;
	logic       hi_lo_register_write_decode;
	logic       equal_decode;
	logic [5:0] ALU_function_decode;
	logic 		program_counter_multiplexer_jump_decode;
	logic		flush_decode_execute_register;
	logic		register_file_memory_mux_control_decode;

	//decode datapath
	//TODO move instruction logic to control
	//TODO consider using alias rather than assign because that's less confusing
	logic [31:0]    program_counter_branch_decode;
	logic [31:0]    instruction_decode;
	logic [31:0]    program_counter_plus_four_decode;
	
	logic [5:0]		op;
		assign op = instruction_decode[31:26];
	logic [4:0]     read_address_1, Rs_decode;
		assign read_address_1 = instruction_decode[25:21];
		assign Rs_decode = instruction_decode[25:21];
	logic [4:0]     read_address_2,Rt_decode;
		assign read_address_2 = instruction_decode[20:16];
		assign Rt_decode = instruction_decode[20:16];
	logic [4:0]     Rd_decode;
		assign Rd_decode = instruction_decode[15:11];
	logic [15:0]    immediate;
		assign immediate = instruction_decode[15:0];
	
	logic [31:0]    shifter_output_decode;
	logic [31:0]    register_file_output_A_decode;
	logic [31:0]    register_file_output_B_decode;
	logic [31:0]    register_file_output_A_resolved_decode;
	logic [31:0]    register_file_output_B_resolved_decode;
	logic [31:0]    sign_imm_decode;

	//Execute Controls
	logic           register_destination_execute;
	logic           memory_to_register_execute;
	logic           memory_write_execute;
	logic [4:0]     write_register_execute;
	logic [1:0]     ALU_src_B_execute;
	logic [5:0]     ALU_function_execute;
	logic           hi_lo_register_write_execute;
	logic           register_write_execute;
	logic 			program_counter_multiplexer_jump_execute;
	logic			register_file_memory_mux_control_execute;

	//Execute Datapath
	logic [31:0]    register_file_output_A_execute;
	logic [31:0]    register_file_output_B_execute;
	logic [31:0]    source_A_ALU_execute;
	logic [31:0]    source_B_ALU_execute;
	logic [31:0]    write_data_execute;
	logic [31:0]    ALU_output_execute;
	logic [31:0]    ALU_HI_output_execute;
	logic [31:0]    ALU_LO_output_execute;
	logic [4:0]     Rs_execute;
	logic [4:0]     Rt_execute;
	logic [4:0]     Rd_execute;
	logic [31:0]    sign_imm_execute;
	logic [31:0]	program_counter_plus_eight_execute;
	logic [31:0]	program_counter_plus_four_execute;
	logic [31:0]	j_program_counter_execute;

	//Memory controls
	logic       register_write_memory;
	logic [4:0] write_register_memory;
	logic       memory_to_register_memory;
	logic       memory_write_memory;
	logic       hi_lo_register_write_memory;
	logic 		program_counter_multiplexer_jump_memory;
	logic		register_file_memory_mux_memory;

	//Memory datapath
	logic [31:0] ALU_output_memory;
	logic [31:0] ALU_HI_output_memory;
	logic [31:0] ALU_LO_output_memory;
	logic [31:0] read_data_memory;
	logic [31:0] write_data_memory;

	//Writeback controls
	logic register_write_writeback;
	logic hi_lo_register_write_writeback;
	logic memory_to_register_writeback;

	//Writeback datapath
	logic [4:0] write_register_writeback;
	logic [31:0] result_writeback;
	logic [31:0] ALU_HI_output_writeback;
	logic [31:0] ALU_LO_output_writeback;
	logic [31:0] ALU_output_writeback;
	logic [31:0] read_data_writeback;

	//Hazard Unit Outputs
	logic       stall_fetch;
	logic       stall_decode;
	logic       forward_A_decode;
	logic       forward_B_decode;
	logic       flush_execute_register;
	logic [1:0] forward_A_execute;
	logic [1:0] forward_B_execute;
	logic 		flush_fetch_decode_register;

	//Data Memory
	assign read_data_memory = data_readdata;
	assign data_address = ALU_output_memory;
	assign data_writedata = write_data_memory;
	assign data_write = memory_write_memory;
	assign data_read = memory_to_register_memory;

	//Instruction memory
	assign instr_address = program_counter_fetch;
	assign instruction_fetch = instr_readdata;

	Register_File register_file(
		.clk(internal_clk),.pipelined(1), 
		.HI_LO_output(HI_LO_output), 
		.write_enable(register_write_writeback), 
		.hi_lo_register_write_enable(hi_lo_register_write_writeback),
		.read_address_1(read_address_1), 
		.read_address_2(read_address_2), 
		.write_address(write_register_writeback), 
		.write_data(result_writeback), 
		.HI_write_data(ALU_HI_output_writeback), 
		.LO_write_data(ALU_LO_output_writeback), 
		.read_data_1(register_file_output_A_decode),
		.read_data_2(register_file_output_B_decode),
		.read_register_2(register_v0)

	);

	Program_Counter pc (
		.clk(internal_clk),
		.address_input(program_counter_prime),
		.reset(reset),
		.enable(stall_fetch),
		.address_output(program_counter_fetch),
		.halt(halt)
	);

	Adder plus_four_adder(
		.a(program_counter_fetch),
		.b({{28{1'b0}},4'b0100}),
		.z(program_counter_plus_four_fetch)
	);

	MUX_2INPUT #(.BUS_WIDTH(32)) program_counter_multiplexer (
		.control(program_counter_source_decode),
		.input_0(program_counter_plus_four_fetch),
		.input_1(program_counter_branch_decode),
		.resolved(program_counter_mux_1_out)
	);

	MUX_2INPUT #(.BUS_WIDTH(32)) program_counter_multiplexer_two (
		.control(program_counter_multiplexer_jump_memory),
		.input_0(program_counter_mux_1_out),
		.input_1(ALU_output_memory_resolved),
		.resolved(program_counter_prime)
	);

	Fetch_Decode_Register fetch_decode_register(
		.clk(internal_clk),
		.reset(reset),
		.enable(stall_decode),
		.clear(program_counter_source_decode),
		.instruction_fetch(instruction_fetch),
		.program_counter_plus_four_fetch(program_counter_plus_four_fetch),
		.instruction_decode(instruction_decode),
		.program_counter_plus_four_decode(program_counter_plus_four_decode)
	);

	Control_Unit control_unit(
		.instruction(instruction_decode),
		.register_write(register_write_decode),
		.memory_to_register(memory_to_register_decode),
		.memory_write(memory_write_decode),
		.ALU_src_B(ALU_src_B_decode),
		.register_destination(register_destination_decode),
		.branch(branch_decode),
		.hi_lo_register_write(hi_lo_register_write_decode),
		.ALU_function(ALU_function_decode),
		.program_counter_multiplexer_jump(program_counter_multiplexer_jump_decode),
		.j_instruction()
	);

	MUX_2INPUT #(.BUS_WIDTH(32)) register_file_output_A_mux 
	(
		.control(forward_A_decode),
		.input_0(register_file_output_A_decode),
		.input_1(ALU_output_memory_resolved),
		.resolved(register_file_output_A_resolved_decode)
	);

	MUX_2INPUT #(.BUS_WIDTH(32))register_file_output_B_mux
	(
		.control(forward_B_decode),
		.input_0(register_file_output_B_decode),
		.input_1(ALU_output_memory_resolved),
		.resolved(register_file_output_B_resolved_decode)
	);

	Comparator reg_output_comparator(
		.op(op),
		.rt(Rt_decode),
		.a(register_file_output_A_resolved_decode),
		.b(register_file_output_B_resolved_decode),
		.c(equal_decode)
	);

	And_Gate program_counter_source_and_gate_decode(
		.input_A(branch_decode),
		.input_B(equal_decode),
		.output_C(program_counter_source_decode)
	);

	Sign_Extension sign_extender_decode(
		.short_input(immediate),
		.extended_output(sign_imm_decode)
	);

	Left_Shift shifter_decode(
		.shift_input(sign_imm_decode),
		.shift_output(shifter_output_decode)
	);

	Adder adder_decode(
		.a(shifter_output_decode),
		.b(program_counter_plus_four_decode),
		.z(program_counter_branch_decode)
	);



	Decode_Execute_Register decode_execute_register(
		.clk(internal_clk),
		.clear(flush_execute_register),
		.reset(reset),
		.register_write_decode(register_write_decode),
		.memory_to_register_decode(memory_to_register_decode),
		.memory_write_decode(memory_write_decode),
		.ALU_src_B_decode(ALU_src_B_decode),
		.register_destination_decode(register_destination_decode),
		.hi_lo_register_write_decode(hi_lo_register_write_decode),
		.ALU_function_decode(ALU_function_decode),
		.Rs_decode(Rs_decode),
		.Rt_decode(Rt_decode),
		.Rd_decode(Rd_decode),
		.sign_imm_decode(sign_imm_decode),
		.program_counter_multiplexer_jump_decode(program_counter_multiplexer_jump_decode),

		.register_write_execute(register_write_execute),
		.memory_to_register_execute(memory_to_register_execute),
		.memory_write_execute(memory_write_execute),
		.ALU_src_B_execute(ALU_src_B_execute),
		.register_destination_execute(register_destination_execute),
		.hi_lo_register_write_execute(hi_lo_register_write_execute),
		.ALU_function_execute(ALU_function_execute),
		.Rs_execute(Rs_execute),
		.Rt_execute(Rt_execute),
		.Rd_execute(Rd_execute),
		.sign_imm_execute(sign_imm_execute),
		.program_counter_multiplexer_jump_execute(program_counter_multiplexer_jump_execute),

		.read_data_one_decode(register_file_output_A_decode),
		.read_data_two_decode(register_file_output_B_decode),
		.program_counter_plus_four_decode(program_counter_plus_four_decode),
		.read_data_one_execute(register_file_output_A_execute),
		.read_data_two_execute(register_file_output_B_execute),
		.program_counter_plus_four_execute(program_counter_plus_four_execute)
	);

	Adder plus_four_adder_execute(
		.a(32'd4),
		.b(program_counter_plus_four_execute),
		.z(program_counter_plus_eight_execute)
	);

	MUX_4INPUT #(.BUS_WIDTH(5)) write_register_execute_mux(
		.control(register_destination_execute),
		.input_0(Rt_execute),
		.input_1(Rd_execute),
		.input_2(5'b11111),
		.input_3(0), //Intentionally left  unconnected.
		.resolved(write_register_execute)
	);

	MUX_4INPUT #(.BUS_WIDTH(32)) register_file_output_A_execute_mux(
		.control(forward_A_execute),
		.input_0(register_file_output_A_execute),
		.input_1(result_writeback),
		.input_2(ALU_output_memory),
		.input_3(ALU_LO_output_writeback),

		.resolved(source_A_ALU_execute)
	);

	MUX_4INPUT #(.BUS_WIDTH(32)) register_file_output_B_execute_mux(
		.control(forward_B_execute),
		.input_0(register_file_output_B_execute),
		.input_1(result_writeback),
		.input_2(ALU_output_memory),
		.input_3(ALU_HI_output_writeback),

		.resolved(write_data_execute)
	);

	MUX_4INPUT #(.BUS_WIDTH(32)) source_B_ALU_mux(
		.control(ALU_src_B_execute),
		.input_0(write_data_execute),
		.input_1(sign_imm_execute),
		.input_2(program_counter_plus_eight_execute),
		.input_3(0), //Intentionally left unconnected

		.resolved(source_B_ALU_execute)
	);

	ALU alu(
		.ALU_operation(ALU_function_execute),
		.input_1(source_A_ALU_execute),
		.input_2(source_B_ALU_execute),

		.ALU_output(ALU_output_execute),
		.ALU_HI_output(ALU_HI_output_execute),
		.ALU_LO_output(ALU_LO_output_execute)
	);
	Region_Branch region_branch(
		.pc_prefix(program_counter_plus_four_execute),
		.offset(jmp_immediate),
		.j_program_counter_execute(j_program_counter_execute)
	);

	Execute_Memory_Register execute_memory_register(
		.clk(internal_clk),
		.reset(reset),
		.register_write_execute(register_write_execute),
		.memory_to_register_execute(memory_to_register_execute),
		.memory_write_execute(memory_write_execute),
		.hi_lo_register_write_execute(hi_lo_register_write_execute),
		.program_counter_multiplexer_jump_execute(program_counter_multiplexer_jump_execute),

		.register_write_memory(register_write_memory),
		.memory_to_register_memory(memory_to_register_memory),
		.memory_write_memory(memory_write_memory),
		.hi_lo_register_write_memory(hi_lo_register_write_memory),
		.program_counter_multiplexer_jump_memory(program_counter_multiplexer_jump_memory),


		.ALU_output_execute(ALU_output_execute),
		.ALU_HI_output_execute(ALU_HI_output_execute),
		.ALU_LO_output_execute(ALU_LO_output_execute),
		.write_data_execute(write_data_execute),
		.write_register_execute(write_register_execute),
		.j_program_counter_execute(j_program_counter_execute),

		.ALU_output_memory(ALU_output_memory),
		.ALU_HI_output_memory(ALU_HI_output_memory),
		.ALU_LO_output_memory(ALU_LO_output_memory),
		.write_data_memory(write_data_memory),
		.write_register_memory(write_register_memory),
		.j_program_counter_memory(j_program_counter_memory)
	);

	MUX_2INPUT #(.BUS_WIDTH(32)) register_file_memory_mux(
		.control(register_file_memory_mux_control_execute),
		.input_0(ALU_output_memory),
		.input_1(j_program_counter_execute),
		.resolved(ALU_output_memory_resolved)
	);

	Memory_Writeback_Register memory_writeback_register(
		.clk(internal_clk),
		.reset(reset),
		.register_write_memory(register_write_memory),
		.memory_to_register_memory(memory_to_register_memory),
		.hi_lo_register_write_memory(hi_lo_register_write_memory),
		.register_write_writeback(register_write_writeback),
		.memory_to_register_writeback(memory_to_register_writeback),
		.hi_lo_register_write_writeback(hi_lo_register_write_writeback),


		.ALU_output_memory(ALU_output_memory),
		.write_register_memory(write_register_memory),
		.ALU_HI_output_memory(ALU_HI_output_memory),
		.ALU_LO_output_memory(ALU_LO_output_memory),
		.read_data_memory(read_data_memory),
		.ALU_output_writeback(ALU_output_writeback),
		.write_register_writeback(write_register_writeback),
		.ALU_HI_output_writeback(ALU_HI_output_writeback),
		.ALU_LO_output_writeback(ALU_LO_output_writeback),
		.read_data_writeback(read_data_writeback)

	);

	MUX_2INPUT #(.BUS_WIDTH(32)) writeback_mux(
		.control(memory_to_register_writeback),
		.input_0(ALU_output_writeback),
		.input_1(read_data_writeback),
		.resolved(result_writeback)
	);
	Hazard_Unit hazard_unit(
		.branch_decode(branch_decode),
		.Rs_decode(Rs_decode),
		.Rt_decode(Rt_decode),
		.Rs_execute(Rs_execute),
		.Rt_execute(Rt_execute),
		.write_register_execute(write_register_execute),
		.memory_to_register_execute(memory_to_register_execute),
		.register_write_execute(register_write_execute),
		.write_register_memory(write_register_memory),
		.memory_to_register_memory(memory_to_register_memory),
		.register_write_memory(register_write_memory),
		.write_register_writeback(write_register_writeback),
		.register_write_writeback(register_write_writeback),
		.program_counter_multiplexer_jump_execute(program_counter_multiplexer_jump_execute),
		.stall_fetch(stall_fetch),
		.stall_decode(stall_decode),
		.forward_register_file_output_1_decode(forward_A_decode),
		.forward_register_file_output_2_decode(forward_B_decode),
		.flush_execute_register(flush_execute_register),
		.forward_register_file_output_1_execute(forward_A_execute),
		.forward_register_file_output_2_execute(forward_B_execute)
	);
	assign internal_clk = clk && clk_enable;
	assign active = !halt;




endmodule