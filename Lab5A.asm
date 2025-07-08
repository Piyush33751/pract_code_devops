 org 100h
 mov bx, 5678h ;This is how yoyu right a comment in assembly
 mov ax, 0b800h
 xchg ax,bx
 xchg al,bh
 mov cl, 'A'
 mov ch, 11010000b
 mov [1000h], ax
 mov [1002h], bx
 mov [1004h], cl
 mov [1005h], ch
 mov bx, 1000h
 mov [bx], cx
 mov si, 1002h
 xchg [si], cx
 mov ax, [1004h]
ret

