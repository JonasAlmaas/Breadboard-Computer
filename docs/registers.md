## Registers

|     | Name                    | Description |
| :-: | ----------------------- | ----------- |
| A   | Register A              |
| B   | Register B              |
| Σ   | Sum Register            | Sum of the A and B Registers. <br> "SU" determines whether the data format is Two's Compliment.                          |
| O   | Output Register         | Displays it's value in base 10. <br> Unsigned if "SU" is not set and signed with Two's Compliment otherwise.             |
| I   | Instruction Register    | 8-Bit register containing the current Instruction being executed. <br> First 4 Bits is the opcode, the next 4 arguments. |
| M   | Memory Address Register | What address use when interacting with the RAM. |

|     | Name                      | Description |
| :-: | ------------------------- | ----------- |
| PC  | Program Counter           | Keeps track if what instruction to execute.                                                          |
| MC  | Micro Instruction Counter | Keeps track of what cycle we are on within an instruction. <br> Resets automatically after 8 cycles. |
