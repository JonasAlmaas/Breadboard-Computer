# Instruction Set

|      | Description           |
| ---- | --------------------- |
| K    | Constant Data         |
| k    | Constant Address      |
| x    | Irrelevant            |

| ASM | Name           | Opcode                  | Cycles | Function                                                              |
| :-: | -------------- | ----------------------- | :----: | --------------------------------------------------------------------- |
| NOP | No Operation   | **0000**'xxxx           | 3      |                                                                       |
| LDA | Load A         | **0001**'xxxx'kkkk'kkkk | 4      | Load value from RAM into Register A.                                  |
| ADD | Add            | **0010**'xxxx'kkkk'kkkk | 5      | Load value from RAM into Register B. <br> Add Register B onto A.      |
| SUB | Subtract       | **0011**'xxxx'kkkk'kkkk | 5      | Load value from RAM into Register B. <br> Subtract Register B from A. |
| STA | Store A        | **0100**'xxxx'kkkk'kkkk | 4      | Store value from Register A into RAM.                                 |
| LDI | Load Immediate | **0101**'xxxx'KKKK'KKKK | 3      | Load Immediate into Register A.                                       |
| JMP | Jump           | **0110**'xxxx'kkkk'kkkk | 3      | Jump to address (Set the value of the Program Counter)                |
| JC  | Jump If Carry  | **0111**'xxxx'kkkk'kkkk | 3      | Jump if Carry flag is set.                                            |
| HZ  | Jump If Zero   | **1000**'xxxx'kkkk'kkkk | 3      | Jump if Zero flag is set.                                             |
| OUT | Output         | **1110**'xxxx'          | 3      | Load Output Register With Register A.                                 |
| HLT | Halt           | **1111**'xxxx           | 3      | Halt Execution.                                                       |
