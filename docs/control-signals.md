# Control Signals

| Code | Name                            | Description                                                                                    |
| ---- | ------------------------------- | ---------------------------------------------------------------------------------------------- |
| HLT  | Halt Execution                  | Stop the clock.                                                                                |
| MI   | Memory Address Register In      | Load the Memory Address Register from the Bus.                                                 |
| RI   | RAM In                          | Load value into RAM from the Bus. <br> Address is determined by the Memory Address Register.   |
| RO   | RAM Out                         | Output value from RAM onto the Bus. <br> Address is determined by the Memory Address Register. |
| IO   | Instruction Out                 | Output the Instruction Register onto the Bus.                                                  |
| II   | Instruction In                  | Load the Instruction Register from the Bus.                                                    |
| AI   | A Register In                   | Load Register A from the Bus.                                                                  |
| AO   | A Register Out                  | Output the A Register onto the Bus.                                                            |
| ΣO   | Sum Out                         | Output the Sum Register onto the Bus.                                                          |
| SU   | Subtract                        | Whether To Subtract Register A and B or not.                                                   |
| BI   | B Register In                   | Load Register B from the Bus.                                                                  |
| OI   | Output Register In              | Load the Output Register from the Bus.                                                         |
| PCE  | Program Counter Enable          | Advance the Program Counter on the next cycle.                                                 |
| PCO  | Program Counter Out             | Output the Program counter onto the Bus.                                                       |
| JMP  | Jump                            | Load the Program Counter from the Bus?                                                         |
| MCR  | Micro Instruction Counter Reset | Resets the Micro Instruction Counter.                                                          |
| SFI  | Status Flag Register In         | Update the Status Flag Register.                                                               |
