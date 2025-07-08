.model small
.stack 100h

.data
    prompt      db  'Enter a line:$'
    newline     db  13, 10, '$'
    buffer      db  80          ; max input length
                db  ?           ; actual length typed (filled by DOS)
                db  80 dup(?)   ; space for characters

.code
main:
    mov ax, @data
    mov ds, ax
    mov es, ax

    ; ---- Display prompt ----
    mov ah, 09h
    mov dx, offset prompt
    int 21h

    ; ---- Read string from user ----
    mov ah, 0Ah
    mov dx, offset buffer
    int 21h

    ; ---- Print newline ----
    mov ah, 09h
    mov dx, offset newline
    int 21h

    ; ---- Convert lowercase to uppercase ----
    lea si, buffer + 2          ; SI points to first character
    mov cl, [buffer + 1]        ; number of characters typed
    mov ch, 0                   ; clear upper byte of counter

convert_loop:
    mov al, [si]
    cmp al, 'a'
    jl skip_convert
    cmp al, 'z'
    jg skip_convert
    sub al, 20h                 ; convert to uppercase
    mov [si], al

skip_convert:
    inc si
    loop convert_loop

    ; ---- Print the converted string ----
    mov ah, 09h
    lea dx, buffer + 2
    lea si, buffer + 2
    mov al, [buffer + 1]        ; get length
    add si, ax                  ; point SI to end of string
    mov byte ptr [si], '$'      ; terminate string with $
    int 21h

    ; ---- Exit program ----
    mov ah, 4Ch
    int 21h

end main
