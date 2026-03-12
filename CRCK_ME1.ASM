.model tiny
.286 

.data

input_buffer            db 228, 0, 6 dup (0dh), 0
correct_pwd             db "SYGTV["

.code
org 100h

key             equ 2h
pwd_len         equ 6
video_seg       equ 0b800h
centre_offset   equ 5 * 160 + 80 - 14
end_sym         equ 24h

Start:

                mov dx, offset input_buffer
                mov ah, 0ah
                int 21h


                mov bx, offset input_buffer + 2
                call TestPwd

                mov ax, 4c00h
                int 21h

;------------------------------------------------------------------------
; Сверяет введенный пароль с настоящим
; Принимает:  bx - адрес на начало пароля
; Возвращает: -
; Портит: bx, si
;------------------------------------------------------------------------
TestPwd         proc

                push cx
                push ax

                mov si, offset correct_pwd
                mov cx, pwd_len
                
loop_check_pwd:
                cmp cx, 0
                je end_of_pwd

                mov ah, [si]
                sub ah, key

                cmp byte ptr [bx], ah
                jne not_equal_pwd

                inc bx
                inc si
                dec cx

                jmp loop_check_pwd

end_of_pwd:
                mov bx, offset mes_correct
                mov ah, 8ah
                call PrintWord

                pop ax
                pop cx

                ret

not_equal_pwd:
                mov bx, offset mes_incorrect
                mov ah, 8ch
                call PrintWord

                pop ax
                pop cx

                ret
                endp


;------------------------------------------------------------------------
; Выводит слово по адресу ax на экран,слово должно оканчиваться символом '$'
; Принимает:  bx - адрес начала строки для вывода
;             ah - цвет символа
; Возвращает: -
; Портит: bx, es, di
;------------------------------------------------------------------------
PrintWord       proc

                mov di, video_seg
                mov es, di

                mov di, centre_offset

loop_print_word:
                cmp byte ptr [bx], end_sym
                je end_print_word

                mov al, [bx]
                mov word ptr es:[di], ax

                add di, 2
                inc bx

                jmp loop_print_word

end_print_word:
                ret
                endp

mes_correct     db "ACCESS GRANTED$"
mes_incorrect   db "ACCESS DENIED$"

end Start