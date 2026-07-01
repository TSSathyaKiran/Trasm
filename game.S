.section .data

W: .quad 21
A: .quad 8
S: .quad 9
D: .quad 10

X_cord: .quad 393
Y_cord: .quad 278
player_w:   .quad 15
player_h:   .quad 45

is_running: .quad 1

.section .text
.global game_handle_event
.global game_update

game_handle_event:

    adr x3, W
    ldr x1, [x3]
    cmp x0, x1
    beq event_w

    adr x3, A
    ldr x1, [x3]
    cmp x0, x1
    beq event_a

    adr x3, S
    ldr x1, [x3]
    cmp x0, x1
    beq event_s

    adr x3, D
    ldr x1, [x3]
    cmp x0, x1
    beq event_d

    ret

event_w:

    adr x3, Y_cord
    ldr x2, [x3]
    sub x2, x2, #5
    str x2, [x3]
    adr x3, player_w
    ldr s2, [x3]
    mov x2, #15
    str x2, [x3]
    adr x3, player_h
    ldr x2, [x3]
    mov x2, #45
    str x2, [x3]
    ret

event_a:

    adr x3, X_cord
    ldr x2, [x3]
    sub x2, x2, #5
    str x2, [x3]
    adr x3, player_w
    ldr s2, [x3]
    mov x2, #45
    str x2, [x3]
    adr x3, player_h
    ldr x2, [x3]
    mov x2, #15
    str x2, [x3]
    ret

event_s:

    adr x3, Y_cord
    ldr x2, [x3]
    add x2, x2, #5
    str x2, [x3]
    adr x3, player_w
    ldr s2, [x3]
    mov x2, #15
    str x2, [x3]
    adr x3, player_h
    ldr x2, [x3]
    mov x2, #45
    str x2, [x3]
    ret

event_d:

    adr x3, X_cord
    ldr x2, [x3]
    add x2, x2, #5
    str x2, [x3]
    adr x3, player_w
    ldr s2, [x3]
    mov x2, #45
    str x2, [x3]
    adr x3, player_h
    ldr x2, [x3]
    mov x2, #15
    str x2, [x3]
    ret


game_running:
    adr x3, is_running
    ldr x0, [x3]
    ret

game_set:
    adr x3, is_running
    str x0, [x3]
    ret
    
    