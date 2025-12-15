module PROGRAM4 (
	input		CLK, RST,
	input	[1:0]	KEY,
	input		[2:0] SW,
	output	reg [6:0]	HEX0, HEX1, HEX2, HEX3, HEX4, HEX5
);

reg	[25:0] cnt;
wire enlhz = (cnt==26'd49_999_9);
wire		reset, down, up;
BTN_IN BTN_IN(CLK, RST, KEY, {reset, down, up} );

always @( posedge CLK ) begin
	if ( RST )
		cnt <= 26'b0;
	else if ( enlhz )
		cnt <= 26'b0;
	else if(SW==1)
		cnt <= cnt;
	else
		cnt <= cnt + 26'b1;
end

reg [3:0] sec;
reg [3:0] sec10;
reg [3:0] min;
reg [3:0] min10;
reg [3:0] min100;
reg [3:0] min1000;

reg [3:0] i;

always @( posedge CLK ) begin
	if(i==0) begin
		sec <= 4'h0;
		sec10 <= 5'h0;
		min <= 6'h0;
		min10 <= 7'h0;
		min100 <= 8'h1;
		min1000 <= 9'h0;
		i <= i + 4'h1;
	end
	else begin
		if ( RST ) begin
			i <= 4'h0;
			sec <= 4'h0;
			sec10 <= 5'h0;
			min <= 6'h0;
			min10 <= 7'h0;
			min100 <= 8'h0;
			min1000 <= 9'h0;
		end
		else if ( enlhz )begin
			if ( sec==4'h0 )begin //4'h9
				if ( sec10==5'h0 )begin //5'h9
					if ( min==6'h0 )begin //6'h9
						if (min10==7'h0)begin //7'h5
							if(min100==8'h0)begin //8'h9
								if(min1000==9'h0)begin //9'h9
									sec <= 4'h0;
									sec10 <= 5'h0;
									min <= 6'h0;
									min10 <= 7'h0;
									min100 <= 8'h0;
									min1000 <= 9'h0;
								end
								else begin
									sec <= 4'h9;
									sec10 <= 5'h9;
									min <= 6'h9;
									min10 <= 7'h5;
									min100 <= 8'h9;
									min1000 <= min1000 - 9'h1;
								end
							end
							else begin
								sec <= 4'h9;
								sec10 <= 5'h9;
								min <= 6'h9;
								min10 <= 7'h5;
								min100 <= min100 - 8'h1;
							end
						end
						else begin
							sec <= 4'h9;
							sec10 <= 5'h9;
							min <= 6'h9;
							min10 <= min10 - 7'h1;
						end
					end
					else begin
						sec <= 4'h9;
						sec10 <= 5'h9;
						min <= min - 6'h1;
					end
				end
				else begin
					sec <= 4'h9;
					sec10 <= sec10 - 5'h1;
				end
			end
			else
				sec <= sec - 4'h1;
		end
	end
end

//always @( posedge CLK, posedge RST) begin
//	if(RST) begin
//		if(udcnt==9) begin
//			if(up)
//				udcnt <= 4'h0;
//			else if(down)
//				udcnt <= udcnt - 4'h1;
//		end
//		else if(udcnt==0) begin
//			if(up)
//				udcnt <= udcnt + 4'h1;
//			else if(down)
//				udcnt <= 4'h9;
//		end
//		else begin
//			if(up)
//				udcnt <= udcnt + 4'h1;
//			else if(down)
//				udcnt <= udcnt - 4'h1;
//		end
//	end
//end

always @* begin
	
		case ( sec )
			4'h0:		HEX0 = 7'b1000000;
			4'h1:		HEX0 = 7'b1111001;
			4'h2:		HEX0 = 7'b0100100;
			4'h3:		HEX0 = 7'b0110000;
			4'h4:		HEX0 = 7'b0011001;
			4'h5:		HEX0 = 7'b0010010;
			4'h6:		HEX0 = 7'b0000010;
			4'h7:		HEX0 = 7'b1011000;
			4'h8:		HEX0 = 7'b0000000;
			4'h9:		HEX0 = 7'b0010000;
			default:	HEX0 = 7'bxxxxxxx;
		endcase
		
		case ( sec10 )
			5'h0:		HEX1 = 7'b1000000;
			5'h1:		HEX1 = 7'b1111001;
			5'h2:		HEX1 = 7'b0100100;
			5'h3:		HEX1 = 7'b0110000;
			5'h4:		HEX1 = 7'b0011001;
			5'h5:		HEX1 = 7'b0010010;
			5'h6:		HEX1 = 7'b0000010;
			5'h6:		HEX1 = 7'b0000010;
			5'h7:		HEX1 = 7'b1011000;
			5'h8:		HEX1 = 7'b0000000;
			5'h9:		HEX1 = 7'b0010000;
			default:	HEX1 = 7'bxxxxxxx;
		endcase

		case ( min )
			6'h0:		HEX2 = 7'b1000000;
			6'h1:		HEX2 = 7'b1111001;
			6'h2:		HEX2 = 7'b0100100;
			6'h3:		HEX2 = 7'b0110000;
			6'h4:		HEX2 = 7'b0011001;
			6'h5:		HEX2 = 7'b0010010;
			6'h6:		HEX2 = 7'b0000010;
			6'h7:		HEX2 = 7'b1011000;
			6'h8:		HEX2 = 7'b0000000;
			6'h9:		HEX2 = 7'b0010000;
			default:	HEX2 = 7'bxxxxxxx;
		endcase
		
		case ( min10 )
			7'h0:		HEX3 = 7'b1000000;
			7'h1:		HEX3 = 7'b1111001;
			7'h2:		HEX3 = 7'b0100100;
			7'h3:		HEX3 = 7'b0110000;
			7'h4:		HEX3 = 7'b0011001;
			7'h5:		HEX3 = 7'b0010010;
			7'h6:		HEX3 = 7'b0000010;
			7'h7:		HEX3 = 7'b1011000;
			7'h8:		HEX3 = 7'b0000000;
			7'h9:		HEX3 = 7'b0010000;
			default:	HEX3 = 7'bxxxxxxx;
		endcase
		
		case ( min100 )
			8'h0:		HEX4 = 7'b1000000;
			8'h1:		HEX4 = 7'b1111001;
			8'h2:		HEX4 = 7'b0100100;
			8'h3:		HEX4 = 7'b0110000;
			8'h4:		HEX4 = 7'b0011001;
			8'h5:		HEX4 = 7'b0010010;
			8'h6:		HEX4 = 7'b0000010;
			8'h7:		HEX4 = 7'b1011000;
			8'h8:		HEX4 = 7'b0000000;
			8'h9:		HEX4 = 7'b0010000;
			default:	HEX4 = 7'bxxxxxxx;
		endcase
		
		case ( min1000 )
			9'h0:		HEX5 = 7'b1000000;
			9'h1:		HEX5 = 7'b1111001;
			9'h2:		HEX5 = 7'b0100100;
			9'h3:		HEX5 = 7'b0110000;
			9'h4:		HEX5 = 7'b0011001;
			9'h5:		HEX5 = 7'b0010010;
			9'h6:		HEX5 = 7'b0000010;
			9'h7:		HEX5 = 7'b1011000;
			9'h8:		HEX5 = 7'b0000000;
			9'h9:		HEX5 = 7'b0010000;
			default:	HEX5 = 7'bxxxxxxx;
		endcase

end

endmodule
