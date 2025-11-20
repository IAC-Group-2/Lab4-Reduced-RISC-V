/* verilator lint_off UNUSED */
module sign_extend #(
    parameter DATA_WIDTH = 32
)(
    input  logic                  imm_src, // 0 = I type, 1 = B type
    input  logic [DATA_WIDTH-1:0] imm_instr,
    output logic [DATA_WIDTH-1:0] imm_ext
);

always_comb begin
    case (imm_src)
        // I type: imm[31:20]
        1'b0: imm_ext = {{20{imm_instr[31]}}, imm_instr[31:20]};

        // B type: immediate values are scattered in the instruction
        1'b1: imm_ext = {
                        {19{imm_instr[31]}},     // sign extend
                        imm_instr[31],           // imm[12]
                        imm_instr[7],            // imm[11]
                        imm_instr[30:25],        // imm[10:5]
                        imm_instr[11:8],         // imm[4:1]
                        1'b0                     // imm[0] = 0 is implicit
                        };
    endcase
end

endmodule
/* verilator lint_on UNUSED */

