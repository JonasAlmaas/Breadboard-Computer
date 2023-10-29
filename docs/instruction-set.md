# Instruction Set

|      | Description           |
| ---- | --------------------- |
| r    | Source Memory address |
| x    | Irrelevant            |

| ASM | Opcode       | Cycles | Function                                                                                                |
|-----|------------- | :----: |-------------------------------------------------------------------------------------------------------- |
| NOP | **0000**xxxx | 3      | No operation.                                                                                           |
| LDA | **0001**rrrr | 4      | Load Value From Memory Into Register A.                                                                 |
| ADD | **0010**rrrr | 5      | Load Value From Memory Into Register B. <br> Add Register A and B and Write the Sum back to Register A. |
| OUT | **1110**xxxx | 3      | Load Output Register With Register A.                                                                   |
| HLT | **1111**xxxx | 3      | Halt Execution.                                                                                         |
