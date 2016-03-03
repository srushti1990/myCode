// ASSIGNMENT - Implement a unidirectional bus architecture

`timescale 1ns/10ps

module top_level_module(clock);
    
    input clock;
    
    wire [31:0] Wdata_Mas1_to_Mux3;
    wire [31:0] Wdata_Mas2_to_Mux3;
    wire [31:0] Wdata_Mux3_to_SL;
    wire Control_Mas1_to_Mux1;
    wire Control_Mas2_to_Mux1;
    wire Control_Mux1_to_SL;
    wire [31:0] Rdata;
    wire [31:0] Rdata_SL1_to_Mux_SL;
    wire [31:0] Rdata_SL2_to_Mux_SL;
    wire [31:0] Rdata_SL3_to_Mux_SL;
    wire [31:0] Rdata_SL4_to_Mux_SL;
    wire [31:0] Addr_Mas1_to_Mux2;
    wire [31:0] Addr_Mas2_to_Mux2;
    wire [31:0] Addr_Mux2_to_SL_DEC; 
    wire Ready_SL1_to_Mux_SL;
    wire Ready_SL2_to_Mux_SL;
    wire Ready_SL3_to_Mux_SL;
    wire Ready_SL4_to_Mux_SL;
    wire Ready;
    wire [1:0] Req;
    wire [1:0] Ack;
    wire [3:0] EN;
    
    wire [1:0] Status_Mas1_to_Mux1;
    wire [1:0] Size_Mas1_to_Mux1;
    wire [3:0] Burst_Mas1_to_Mux1;
    
    wire [1:0] Status_Mas2_to_Mux1;
    wire [1:0] Size_Mas2_to_Mux1;
    wire [3:0] Burst_Mas2_to_Mux1;
    
    wire [1:0] Status_Mux1_to_SL;
    wire [1:0] Size_Mux1_to_SL;
    wire [3:0] Burst_Mux1_to_SL;
    
    Master_1 DUT1(.Wdata_Mas1(Wdata_Mas1_to_Mux3), .Addr_Mas1(Addr_Mas1_to_Mux2), .Control_Mas1(Control_Mas1_to_Mux1), .Req_Mas1(Req), .Ready_Mas1(Ready), .Ack_Mas1(Ack), .Rdata_Mas1(Rdata), .clock_Mas1(clock), .Status_Mas1(Status_Mas1_to_Mux1), .Size_Mas1(Size_Mas1_to_Mux1), .Burst_Mas1(Burst_Mas1_to_Mux1));
    Master_2 DUT2(.Wdata_Mas2(Wdata_Mas2_to_Mux3), .Addr_Mas2(Addr_Mas2_to_Mux2), .Control_Mas2(Control_Mas2_to_Mux1), .Req_Mas2(Req), .Ready_Mas2(Ready), .Ack_Mas2(Ack), .Rdata_Mas2(Rdata), .clock_Mas2(clock), .Status_Mas2(Status_Mas2_to_Mux1), .Size_Mas2(Size_Mas2_to_Mux1), .Burst_Mas2(Burst_Mas2_to_Mux1));
    Slave_1 DUT3(.Rdata_SL1(Rdata_SL1_to_Mux_SL), .Ready_SL1(Ready_SL1_to_Mux_SL), .Wdata_SL1(Wdata_Mux3_to_SL), .Addr_SL1(Addr_Mux2_to_SL_DEC), .Control_SL1(Control_Mux1_to_SL), .EN_SL1(EN), .clock_SL1(clock), .Status_SL1(Status_Mux1_to_SL), .Size_SL1(Size_Mux1_to_SL), .Burst_SL1(Burst_Mux1_to_SL));
    Slave_2 DUT4(.Rdata_SL2(Rdata_SL2_to_Mux_SL), .Ready_SL2(Ready_SL2_to_Mux_SL), .Wdata_SL2(Wdata_Mux3_to_SL), .Addr_SL2(Addr_Mux2_to_SL_DEC), .Control_SL2(Control_Mux1_to_SL), .EN_SL2(EN), .clock_SL2(clock));
    Slave_3 DUT5(.Rdata_SL3(Rdata_SL3_to_Mux_SL), .Ready_SL3(Ready_SL3_to_Mux_SL), .Wdata_SL3(Wdata_Mux3_to_SL), .Addr_SL3(Addr_Mux2_to_SL_DEC), .Control_SL3(Control_Mux1_to_SL), .EN_SL3(EN), .clock_SL3(clock));
    Slave_4 DUT6(.Rdata_SL4(Rdata_SL4_to_Mux_SL), .Ready_SL4(Ready_SL4_to_Mux_SL), .Wdata_SL4(Wdata_Mux3_to_SL), .Addr_SL4(Addr_Mux2_to_SL_DEC), .Control_SL4(Control_Mux1_to_SL), .EN_SL4(EN), .clock_SL4(clock));
    Decoder DUT7(.EN_Dec_SL(EN), .Addr_Mas_Dec(Addr_Mux2_to_SL_DEC));
    MUX_SL DUT8(.Rdata_Mux_SL(Rdata),.Mux_Sel_Dec(EN),.Rdata_SL1(Rdata_SL1_to_Mux_SL),.Rdata_SL2(Rdata_SL2_to_Mux_SL),.Rdata_SL3(Rdata_SL3_to_Mux_SL),.Rdata_SL4(Rdata_SL4_to_Mux_SL),.Ready_SL1(Ready_SL1_to_Mux_SL),.Ready_SL2(Ready_SL2_to_Mux_SL),.Ready_SL3(Ready_SL3_to_Mux_SL),.Ready_SL4(Ready_SL4_to_Mux_SL),.Ready_Mux_SL(Ready));
    MUX1 DUT9(.Control_SL_Mux1(Control_Mux1_to_SL), .Control_Mas1_Mux1(Control_Mas1_to_Mux1), .Control_Mas2_Mux1(Control_Mas2_to_Mux1), .Ack_Arb_Mux1(Ack), .Status_Mas1_Mux1(Status_Mas1_to_Mux1), .Status_Mas2_Mux1(Status_Mas2_to_Mux1), .Size_Mas1_Mux1(Size_Mas1_to_Mux1), .Size_Mas2_Mux1(Size_Mas2_to_Mux1), .Burst_Mas1_Mux1(Burst_Mas1_to_Mux1), .Burst_Mas2_Mux1(Burst_Mas2_to_Mux1), .Status_SL_Mux1(Status_Mux1_to_SL), .Size_SL_Mux1(Size_Mux1_to_SL), .Burst_SL_Mux1(Burst_Mux1_to_SL));
    MUX2 DUT10(.Addr_Mux2_Dec_EN(Addr_Mux2_to_SL_DEC), .Addr_Mas1_Mux2(Addr_Mas1_to_Mux2), .Addr_Mas2_Mux2(Addr_Mas2_to_Mux2), .Ack_Arb_Mux2(Ack));
    MUX3 DUT11(.Wdata_SL_Mux3(Wdata_Mux3_to_SL), .Wdata_Mas1_Mux3(Wdata_Mas1_to_Mux3), .Wdata_Mas2_Mux3(Wdata_Mas2_to_Mux3), .Ack_Arb_Mux3(Ack));
    Arbiter DUT12(.clock_Arb(clock), .Req_Arb(Req), .Ack_Arb(Ack));
    
endmodule

module Master_1(Wdata_Mas1, Addr_Mas1, Control_Mas1, Req_Mas1, Ready_Mas1, Ack_Mas1, Rdata_Mas1, clock_Mas1, Status_Mas1, Size_Mas1, Burst_Mas1);
  
  output [1:0] Status_Mas1;
  output [1:0] Size_Mas1;
  output [3:0] Burst_Mas1;
  
  output [31:0] Wdata_Mas1;
  output Control_Mas1;
  output [1:0] Req_Mas1;
  output [31:0] Addr_Mas1;
  input [31:0] Rdata_Mas1;
  input Ready_Mas1;
  input [1:0] Ack_Mas1;
  input clock_Mas1;
  
  reg [31:0] Wdata_Mas1;
  reg Control_Mas1;
  reg [1:0] Req_Mas1;
  reg [31:0] Addr_Mas1;
  
  wire [31:0] Rdata_Mas1;
  wire Ready;
  wire [1:0] Ack_Mas1;
  
  reg [1:0] Status_Mas1;
  reg [1:0] Size_Mas1;
  reg [3:0] Burst_Mas1;
  
 	initial
	begin
	   Control_Mas1 <= 1'b0;
	   Req_Mas1 <= 2'b00;
	end

  always @ (posedge clock_Mas1)
  begin
    Req_Mas1 <= #2 2'b10;
    if(Ack_Mas1)
    begin
      Status_Mas1 <= #2 2'b00;
      Size_Mas1 <= #2 2'b00;
      Burst_Mas1 <= #2 4'b0000;
      
      Addr_Mas1 <= #2 32'h00000001;
      Control_Mas1 <= #2 1'b1;
      if(Ready_Mas1)
      begin
        Wdata_Mas1 <= #2 32'h00001111;
      end
    end
  end

endmodule

module Master_2(Wdata_Mas2, Addr_Mas2, Control_Mas2, Req_Mas2, Ready_Mas2, Ack_Mas2, Rdata_Mas2, clock_Mas2, Status_Mas2,Size_Mas2, Burst_Mas2);
  
  output [1:0] Status_Mas2;
  output [1:0] Size_Mas2;
  output [3:0] Burst_Mas2;
  
  output [31:0] Wdata_Mas2;
  output Control_Mas2;
  output [1:0] Req_Mas2;
  output [31:0] Addr_Mas2;
  input [31:0] Rdata_Mas2;
  input Ready_Mas2;
  input [1:0] Ack_Mas2;
  input clock_Mas2;
  
  reg [31:0] Wdata_Mas2;
  reg Control_Mas2;
  reg [1:0] Req_Mas2;
  reg [31:0] Addr_Mas2;
  
  wire [31:0] Rdata_Mas1;
  wire Ready;
  wire [1:0] Ack_Mas1;
  
  always @ (posedge clock_Mas2)
  begin
    Req_Mas2=2'b10;
    
  end
  
endmodule

module Slave_1(Rdata_SL1, Ready_SL1, Wdata_SL1, Addr_SL1, Control_SL1, EN_SL1, clock_SL1, Status_SL1, Size_SL1, Burst_SL1);

  input [31:0] Wdata_SL1;
  input [31:0] Addr_SL1;
  input Control_SL1;
  input [3:0] EN_SL1;
  input clock_SL1;
  input [1:0] Status_SL1;
  input [1:0] Size_SL1;
  input [3:0] Burst_SL1;
  
  output [31:0] Rdata_SL1;
  output Ready_SL1;
  
  reg [31:0] Rdata_SL1;
  reg Ready_SL1;
  
  assign EN_Read_Write = 1'b0;
  
  reg [31:0] memoryA [3:0];
  
  always @ (posedge clock_SL1)
  begin
    if(Control_SL1 == 1)
    begin
     Ready_SL1 <= #6 1'b1;
    end
    if(Control_SL1 == 0)
    begin
      Ready_SL1 <= #6 1'b1;
    end
  end
  
  always @ (posedge clock_SL1 && Control_SL1 == 1 && EN_SL1[0] == 1'b1)
  begin
    memoryA[Addr_SL1] <= Wdata_SL1;
  end
  
  always @ (posedge clock_SL1 && Control_SL1 == 0 && EN_SL1[0] == 1'b1)
  begin
    Rdata_SL1 <= memoryA[Addr_SL1];
  end
  
endmodule

module Slave_2(Rdata_SL2, Ready_SL2, Wdata_SL2, Addr_SL2, Control_SL2, EN_SL2, clock_SL2);

  input [31:0] Wdata_SL2;
  input [31:0] Addr_SL2;
  input Control_SL2;
  input [3:0] EN_SL2;
  input clock_SL2;
  
  output [31:0] Rdata_SL2;
  output Ready_SL2;
  
  reg [31:0] Rdata_SL2;
  reg Ready_SL2;
  
  reg [31:0] memoryB [3:0];
  
    always @ (posedge clock_SL2)
  begin
    if(Control_SL2 == 1)
    begin
     Ready_SL2 <= #2 1'b1;
    end
    if(Control_SL2 == 0)
    begin
      Ready_SL2 <= #2 1'b1;
    end
  end
  
endmodule

module Slave_3(Rdata_SL3, Ready_SL3, Wdata_SL3, Addr_SL3, Control_SL3, EN_SL3, clock_SL3);

  input [31:0] Wdata_SL3;
  input [31:0] Addr_SL3;
  input Control_SL3;
  input [3:0] EN_SL3;
  input clock_SL3;
  
  output [31:0] Rdata_SL3;
  output Ready_SL3;

  reg [31:0] Rdata_SL3;
  reg Ready_SL3;
  
  reg [31:0] memoryC [3:0];
  
    always @ (posedge clock_SL3)
  begin
    if(Control_SL3 == 1)
    begin
     Ready_SL3 <= #2 1'b1;
    end
    if(Control_SL3 == 0)
    begin
      Ready_SL3 <= #2 1'b1;
    end
  end
  
endmodule

module Slave_4(Rdata_SL4, Ready_SL4, Wdata_SL4, Addr_SL4, Control_SL4, EN_SL4, clock_SL4);

  input [31:0] Wdata_SL4;
  input [31:0]Addr_SL4;
  input Control_SL4;
  input [3:0] EN_SL4;
  input clock_SL4;
  
  output [31:0] Rdata_SL4;
  output Ready_SL4;
  
  reg [31:0] Rdata_SL4;
  reg Ready_SL4;
  
  reg [31:0] memoryD [3:0];
  
    always @ (posedge clock_SL4)
  begin
    if(Control_SL4 == 1)
    begin
     Ready_SL4 <= #2 1'b1;
    end
    if(Control_SL4 == 0)
    begin
      Ready_SL4 <= #2 1'b1;
    end
  end
  
endmodule
  
module Arbiter(clock_Arb, Req_Arb, Ack_Arb);
  
  input clock_Arb;
  input Req_Arb;
  output Ack_Arb;
  
  wire [1:0] Req_Arb;
  reg [1:0] Ack_Arb;
  
  always @ (posedge clock_Arb)
  begin
 		case(Req_Arb)
			2'b00:begin #2 Ack_Arb <= 2'b00;end
			2'b01:begin #2 Ack_Arb <= 2'b01;end
			2'b1x:begin #2 Ack_Arb <= 2'b10;end
			2'bx1:begin #2 Ack_Arb <= 2'b01;end
			2'b10:begin #2 Ack_Arb <= 2'b10;end
			2'b11:begin #2 Ack_Arb <= 2'b01;end
		endcase
  end
  
endmodule

module Decoder(EN_Dec_SL, Addr_Mas_Dec);
    
  input [31:0] Addr_Mas_Dec;
  output [3:0] EN_Dec_SL;
  reg [3:0] EN_Dec_SL;
  
 always @ (*)
 begin
  case(Addr_Mas_Dec[31:30])
    2'b00: begin EN_Dec_SL<=4'b0001;end
    2'b01: begin EN_Dec_SL<=4'b0010;end
    2'b10: begin EN_Dec_SL<=4'b0100;end
    2'b10: begin EN_Dec_SL<=4'b1000;end
  endcase
  end
endmodule
  
module MUX_SL(Rdata_Mux_SL, Mux_Sel_Dec,Rdata_SL1, Rdata_SL2, Rdata_SL3, Rdata_SL4, Ready_SL1, Ready_SL2, Ready_SL3, Ready_SL4, Ready_Mux_SL);
  
  input Ready_SL1;
  input Ready_SL2;
  input Ready_SL3;
  input Ready_SL4;
  input [31:0] Rdata_SL1;
  input [31:0] Rdata_SL2;
  input [31:0] Rdata_SL3;
  input [31:0] Rdata_SL4;
  input [3:0] Mux_Sel_Dec;
  
  output [31:0] Rdata_Mux_SL;
  reg [31:0] Rdata_Mux_SL;
  
  output Ready_Mux_SL;
  reg Ready_Mux_SL;
  
  always @ (*)
  begin
    case(Mux_Sel_Dec)
    4'b0001:begin Rdata_Mux_SL <= Rdata_SL1;Ready_Mux_SL <= Ready_SL1; end
    4'b0010:begin Rdata_Mux_SL <= Rdata_SL2;Ready_Mux_SL <= Ready_SL2; end
    4'b0100:begin Rdata_Mux_SL <= Rdata_SL3;Ready_Mux_SL <= Ready_SL3; end
    4'b1000:begin Rdata_Mux_SL <= Rdata_SL4;Ready_Mux_SL <= Ready_SL4; end
    endcase
  end
endmodule

module MUX1(Control_SL_Mux1, Control_Mas1_Mux1, Control_Mas2_Mux1, Ack_Arb_Mux1, Status_Mas1_Mux1, Status_Mas2_Mux1, Size_Mas1_Mux1, Size_Mas2_Mux1, Burst_Mas1_Mux1, Burst_Mas2_Mux1, Status_SL_Mux1, Size_SL_Mux1, Burst_SL_Mux1);
  
  input Control_Mas1_Mux1;
  input Control_Mas2_Mux1;
  input [1:0] Status_Mas1_Mux1;
  input [1:0] Status_Mas2_Mux1;
  input [1:0] Size_Mas1_Mux1;
  input [1:0] Size_Mas2_Mux1;
  input [3:0] Burst_Mas1_Mux1;
  input [3:0] Burst_Mas2_Mux1;
  
  
  input [1:0] Ack_Arb_Mux1;
  
  output Control_SL_Mux1;
  output [1:0] Status_SL_Mux1;
  output [1:0] Size_SL_Mux1;
  output [3:0] Burst_SL_Mux1;
  
  reg [1:0] Status_SL_Mux1;
  reg [1:0] Size_SL_Mux1;
  reg [3:0] Burst_SL_Mux1;
  reg Control_SL_Mux1;
  
  always @ (*)
  begin
  case(Ack_Arb_Mux1)
    2'b10: begin 
                Control_SL_Mux1 <= Control_Mas1_Mux1;  
                Status_SL_Mux1 <= Status_Mas1_Mux1;
                Size_SL_Mux1 <= Size_Mas1_Mux1;
                Burst_SL_Mux1 <= Burst_Mas1_Mux1;
           end
    2'b01: begin 
                Control_SL_Mux1 <= Control_Mas2_Mux1;
                Status_SL_Mux1 <= Status_Mas2_Mux1;
                Size_SL_Mux1 <= Size_Mas2_Mux1;
                Burst_SL_Mux1 <= Burst_Mas2_Mux1;
           end
  endcase
  end
  
endmodule

module MUX2(Addr_Mux2_Dec_EN, Addr_Mas1_Mux2, Addr_Mas2_Mux2, Ack_Arb_Mux2);
  
  input [31:0] Addr_Mas1_Mux2;
  input [31:0] Addr_Mas2_Mux2;
  input [1:0] Ack_Arb_Mux2;
  
  output [31:0] Addr_Mux2_Dec_EN;
  reg [31:0] Addr_Mux2_Dec_EN;
  
  always @ (*)
  begin
  case(Ack_Arb_Mux2)
    2'b10: Addr_Mux2_Dec_EN <= Addr_Mas1_Mux2;
    2'b01: Addr_Mux2_Dec_EN <= Addr_Mas2_Mux2;
  endcase
  end
endmodule

module MUX3(Wdata_SL_Mux3, Wdata_Mas1_Mux3, Wdata_Mas2_Mux3, Ack_Arb_Mux3);
  
  input [31:0] Wdata_Mas1_Mux3;
  input [31:0] Wdata_Mas2_Mux3;
  input [1:0] Ack_Arb_Mux3;
  
  output [31:0] Wdata_SL_Mux3;
  reg [31:0] Wdata_SL_Mux3;
  
  always @ (*)
  begin
  case(Ack_Arb_Mux3)
    2'b10: begin Wdata_SL_Mux3 <= Wdata_Mas1_Mux3; end
    2'b01: begin Wdata_SL_Mux3 <= Wdata_Mas2_Mux3; end
  endcase  
  end
endmodule

