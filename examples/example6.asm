;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
; PMODE/W Assembly Example File #1
;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
.386p

_TEXT   segment use32 dword public 'CODE'
        assume  cs:_TEXT,ds:_DATA

start:
        jmp short _main

        db 'WATCOM... What me worry?'   ; The "WATCOM" string is needed in
                                        ; order to run under DOS/4G and WD.

;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
; CODE
;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±

;°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
; Entry To ASM Code (_main)
; In:
;   CS - Code Selector    Base: 00000000h - Limit: 4G
;   DS - Data Selector    Base: 00000000h - Limit: 4G
;   ES - PSP Selector     Base: PSP Seg   - Limit: 100h
;   FS - ?
;   GS - ?
;   SS - Data Selector    Base: 00000000h - Limit: 4G
;   ESP -> STACK segment
;   Direction Flag - ?
;   Interrupt Flag - ?
;
;   All Other Registers Are Undefined!
;°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
_main:
        sti                             ; Set The Interrupt Flag
        cld                             ; Clear The Direction Flag

        mov ah,9                        ; AH=09h - Print DOS Message
        mov edx,offset _msg             ; DS:EDX -> $ Terminated String
        int 21h                         ; DOS INT 21h

        mov ax,4c00h                    ; AH=4Ch - Exit To DOS
        int 21h                         ; DOS INT 21h

_TEXT   ends

_DATA   segment use32 dword public 'DATA'
;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
; DATA
;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
_msg    db 'Hello World From Protected Mode!',10,13,'$'

_DATA   ends

;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
; STACK
;±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±±
stack   segment para stack 'STACK'
        db 1000h dup(?)
stack   ends

        end start

