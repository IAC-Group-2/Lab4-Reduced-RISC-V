module ALU #(
    DATA_WIDTH = 32
) (
    input   logic [DATA_WIDTH-1:0]  in0,
    input   logic [DATA_WIDTH-1:0]  in1,
    input   logic [2:0]             ctrl,
    output  logic [DATA_WIDTH-1:0]  out,
    output  logic                   eq
);
always_comb begin
    out = 0;
    eq = 0;
    case (ctrl) //codes given in lecture notes
        3'b000: out = in0 + in1; //add
        3'b001: out = in0 - in1; //subtract
        3'b101: eq = in0 < in1; //set less than
        3'b011: out = in0 | in1; //bitwise or
        3'b010: out = in0 & in1; //bitwise and
        default:
            begin
            eq = 0;
            out = 0;
            end
    endcase
end

endmodule
