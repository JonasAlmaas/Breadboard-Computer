# Micro Instructions

## Fetch

Every instruction starts by running the fetch sequence.

| Opcode | Cycle         | | HLT | MI  | RI  | RO  | IO  | II  | AI  | AO  | ΣO  | SU  | BI  | OI  | PCE | PCO | JMP | MCR | SFI |
| :----: | :-----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| xxxx   | 0000&nbsp;(0) | |     | X   |     |     |     |     |     |     |     |     |     |     |     | X   |     |     |     |
| xxxx   | 0001&nbsp;(1) | |     |     |     | X   |     | X   |     |     |     |     |     |     | X   |     |     |     |     |

## NOP

| Opcode | Cycle         | | HLT | MI  | RI  | RO  | IO  | II  | AI  | AO  | ΣO  | SU  | BI  | OI  | PCE | PCO | JMP | MCR | SFI |
| :----: | :-----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0000   | 0010&nbsp;(2) | |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     | X   |     |

## LDA

| Opcode  | Cycle         | | HLT | MI  | RI  | RO  | IO  | II  | AI  | AO  | ΣO  | SU  | BI  | OI  | PCE | PCO | JMP | MCR | SFI |
| :-----: | :-----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0001    | 0010&nbsp;(2) | |     | X   |     |     | X   |     |     |     |     |     |     |     |     |     |     |     |     |
| 0001    | 0011&nbsp;(3) | |     |     |     | X   |     |     | X   |     |     |     |     |     |     |     |     | X   |     |


## ADD

| Opcode | Cycle         | | HLT | MI  | RI  | RO  | IO  | II  | AI  | AO  | ΣO  | SU  | BI  | OI  | PCE | PCO | JMP | MCR | SFI |
| :----: | :-----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0010   | 0010&nbsp;(2) | |     | X   |     |     | X   |     |     |     |     |     |     |     |     |     |     |     |     |
| 0010   | 0011&nbsp;(3) | |     |     |     | X   |     |     |     |     |     |     | X   |     |     |     |     |     |     |
| 0010   | 0100&nbsp;(4) | |     |     |     |     |     |     |     |     | X   |     |     |     |     |     |     | X   |     |


## OUT

| Opcode | Cycle         | | HLT | MI  | RI  | RO  | IO  | II  | AI  | AO  | ΣO  | SU  | BI  | OI  | PCE | PCO | JMP | MCR | SFI |
| :----: | :-----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 1110   | 0010&nbsp;(2) | |     |     |     |     |     |     |     | X   |     |     |     | X   |     |     |     | X   |     |


## HLT

| Opcode | Cycle         | | HLT | MI  | RI  | RO  | IO  | II  | AI  | AO  | ΣO  | SU  | BI  | OI  | PCE | PCO | JMP | MCR | SFI |
| :----: | :-----------: |-| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 1111   | 0010&nbsp;(2) | | X   |     |     |     |     |     |     |     |     |     |     |     |     |     |     | X   |     |
