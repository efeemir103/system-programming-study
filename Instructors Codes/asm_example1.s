.cpu cortex-m0plus
.thumb

.global main

main:

  MOV R0, #0x12
  MOV R1, #0x2
  MOV R2, #0x4
  ADD R1, R0, #0x4

END: B END
.end
