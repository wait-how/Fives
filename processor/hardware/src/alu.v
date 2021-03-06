/*
    ALU - async. clear.  Especially simple since no status bits based on results are set.
*/
module alu(input [15:0] reg_a, input [15:0] reg_b, output reg [15:0] out, input [2:0] op);
    
    initial begin
        out <= 16'h00;
    end
    
    
    always @(reg_a, reg_b, op) begin
	   case (op)
		  3'h0: out <= reg_a + reg_b;
		  3'h1: out <= reg_a - reg_b;
		  3'h2: out <= reg_a;
		  3'h3: out <= reg_a & reg_b;
		  3'h4: out <= reg_a | reg_b;
		  3'h5: out <= reg_a ^ reg_b;
		  3'h6: out <= ~reg_a;
		  3'h7: out <= 16'h00;
	   endcase
    end
    
endmodule

module alu_buffer();
    
endmodule