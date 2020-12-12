module Decode_Execute_Register
(
	input	logic 	clk,
	input 	logic	clear,
	input	logic	reset,
	//control logic forwarding
	input	logic 			register_write_decode,
	input 	logic			memory_to_register_decode,
	input	logic			memory_write_decode,
	input	logic [1:0]		ALU_src_B_decode,
	input	logic [1:0]		register_destination_decode,
	input	logic			hi_lo_register_write_decode,
	input	logic [5:0]		ALU_function_decode,
	input 	logic [4:0]		Rs_decode,
	input 	logic [4:0]		Rt_decode,
	input	logic [4:0]		Rd_decode,
	input	logic [31:0]	sign_imm_decode,		
	input	logic			program_counter_multiplexer_jump_decode,
	input	logic			register_file_memory_mux_control_decode,

	output	logic 			register_write_execute,
	output 	logic			memory_to_register_execute,
	output	logic			memory_write_execute,
	output	logic [1:0]		ALU_src_B_execute,
	output	logic [1:0]		register_destination_execute,
	output	logic			hi_lo_register_write_execute,
	output	logic [5:0]		ALU_function_execute,		
	output 	logic [4:0]		Rs_execute,
	output	logic [4:0]		Rt_execute,
	output	logic [4:0]		Rd_execute,
	output	logic [31:0]	sign_imm_execute,
	output	logic 			program_counter_multiplexer_jump_execute,
	output	logic			register_file_memory_mux_control_execute,
	//datapath
	input	logic [31:0]	read_data_one_decode,
	input	logic [31:0]	read_data_two_decode,
	input	logic [31:0] 	program_counter_plus_four_decode,

	output	logic [31:0]	read_data_one_execute,
	output	logic [31:0]	read_data_two_execute,
	output	logic [31:0] 	program_counter_plus_four_execute


);

	always_ff @(posedge clk, posedge reset) begin
		if(clear || reset) begin
			register_write_execute <= 0;
			memory_to_register_execute <= 0;
			memory_write_execute <= 0;
			ALU_src_B_execute <= 0;
			register_destination_execute <= 2'b00;
			hi_lo_register_write_execute <= 0;
			ALU_function_execute <= {6{1'b0}};
			Rt_execute <= {5{1'b0}};
			Rd_execute <= {5{1'b0}};
			Rs_execute <= {5{1'b0}};
			sign_imm_execute <= {32{1'b0}};
			program_counter_multiplexer_jump_execute <= 0;
			register_file_memory_mux_control_execute <= 0;

			read_data_one_execute <= {32{1'b0}};
			read_data_two_execute <= {32{1'b0}};
			program_counter_plus_four_execute <= {32{1'b0}};
		end else begin
			register_write_execute <= register_write_decode;
			memory_to_register_execute <= memory_to_register_decode;
			memory_write_execute <= memory_write_decode;
			ALU_src_B_execute <= ALU_src_B_decode;
			register_destination_execute <= register_destination_decode;
			hi_lo_register_write_execute <= hi_lo_register_write_decode;
			ALU_function_execute <= ALU_function_decode;
			Rs_execute <= Rs_decode;
			Rt_execute <= Rt_decode;
			Rd_execute <= Rd_decode;
			sign_imm_execute <= sign_imm_decode;
			program_counter_multiplexer_jump_execute <= program_counter_multiplexer_jump_decode;
			register_file_memory_mux_control_execute <= register_file_memory_mux_control_execute_decode;
;

			read_data_one_execute <= read_data_one_decode;
			read_data_two_execute <= read_data_two_decode;
			program_counter_plus_four_execute <= program_counter_plus_eight_decode;

		end
	end
	

endmodule