module instr_mem (
    input  logic [31:0] A,
    output logic [31:0] RD
);

logic [31:0] instr_rom [255:0];

initial begin
    $readmemh("program.hex", instr_rom);
end

assign RD = instr_rom[A[9:2]];

endmodule
