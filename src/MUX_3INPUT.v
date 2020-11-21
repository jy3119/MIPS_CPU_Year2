module MUX_3
#(
	parameter BUS_WIDTH = 1	//BUS_WIDTH can be changed in module instantiation
)
(
	input logic [1:0]			control,
	input logic [BUS_WIDTH:0] 	input_0,
	input logic [BUS_WIDTH:0] 	input_1,
	input logic [BUS_WIDTH:0] 	input_2,

	output logic [BUS_WIDTH:0] resolved
);

	always_comb begin
		case(control)
			2'b00 	:	resolved = input_0;
			2'b01	:	resolved = input_1;
			2'b10	:	resolved = input_2;
			2'b11	:	resolved = 0; //Something has gone wrong if this case has been reached
		endcase
	end

endmodule