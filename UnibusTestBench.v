// Test bench for the unidirectional bus architecture
`timescale 1ns/10ps

module clkassgin2;
  reg        clk;
  parameter half_clock = 5;

  top_level_module DUT(.clock(clk));

  initial 
    begin 
	   clk =0;
	  end
  always
	 begin
	   #half_clock clk = ~ clk;
	 end
  
  always
   begin
     #200 $stop;
   end

endmodule

