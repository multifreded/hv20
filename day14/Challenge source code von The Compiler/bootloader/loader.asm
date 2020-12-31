;;  (Re)sources:
;;  https://www.joe-bergeron.com/posts/Writing%20a%20Tiny%20x86%20Bootloader/
;;  http://www.ctyme.com/intr/int.htm
;;  https://github.com/tanmayv25/x86-bootloader
;;  https://wiki.osdev.org/Text_Mode_Cursor
;;  https://en.wikipedia.org/wiki/INT_10H

%define conwidth 80
%define conheight 25

%define qrwidth 25
%define qrheight 13

bits 16    ; The CPU powers up with 16 bit mode only
org 0x7c00 ; jump to 0x7c00 to output data.

;;; GIF
;;; http://www.matthewflickinger.com/lab/whatsinagif/bits_and_bytes.asp

;; Header
; GIF89a
db 0x47, 0x49, 0x46, 0x38, 0x39, 0x61

;; Logical screen descriptor
; width 128
db 0x80, 0x00
; height 16
db 0x10, 0x00
; flags
;  global   color res    sort     color table size (2^(N+1))
;  true     4px          false    2^2 = 4
db 1 << 7 | 0b010 << 4 | 0 << 3 | 0b001
; background color index
db 0x03
; pixel aspect ratio
db 0x00

;; color table
db 0x00, 0x00, 0x00   ; black
db 0xfe, 0x00, 0x00   ; red
db 0x9d, 0x9d, 0x9d   ; gray
db 0xfd, 0xfd, 0xfd   ; white

db 0x21, 0xfe, (after_jmp - $ - 4)
db 0x00  ; alignment for asm "21 03" instruction
jmp boot
db 0x00  ; end of data block for GIF

after_jmp:
;; GIF comment for rest
db 0x21, 0xfe, (gifdata - $ - 3)

;;;
;;; Init
;;;
boot:
    ;; Show hidden flag
    xor bx, bx
    mov ah, 0x0e
.hidden:
    mov al, [hiddendata+bx]
    mov cl, [qrdata+bx]

    test al, al
    jz .blank

    xor al, cl
    int 0x10

    inc bx
    jmp .hidden

.blank:
    ; hlt
    ;; Blank display
    ; http://www.ctyme.com/intr/rb-0097.htm
    mov ax, (0x07 << 8) | 0x00  ; scroll down window, clear entire window
    mov bh, 0xf0  ; white on black
    xor cx, cx    ; top left: (0,0)
    mov dx, (conheight << 8) | conwidth ; bottom right
    int 0x10

    ;; Move cursor
    ;; https://wiki.osdev.org/Text_Mode_Cursor#Moving_the_Cursor
    ;; http://www.ctyme.com/intr/rb-0087.htm
    mov ah, 0x02  ; set cursor position
    mov bh, 0x00  ; page 0 - doesn't matter, we're not using double-buffering
    mov dx, ((conheight - qrheight) / 2) << 8 | 0x00 ; row, column
    int 0x10

    ;; dx = 0x3 used as mask
    mov dx, 0x3

;;;
;;; Print QR code
;;;
;;; si, di are used as loop counters,
;;; [abcd]x and bp as generic data registers

    ;; si: loop counter "i" (--> 0)
    mov si, (qrwidth * qrheight) - 1
    ;; di: width counter (--> 0)
    ;; set to 0 instead of qrwidth here so we show a prefix immediately
    xor di, di

;;; Loop over each character (double-pixel)
.loop:
    ;; Show prefix if needed (needs ax, dx)
    test di, di
    jnz .afterprefix

    ;; "BUG"
    cmp si, (qrwidth * (qrheight-4)) - 1
    jne .prefix
    cli
    hlt

.prefix:

    ;; print character: CR
    mov ax, 0x0e << 8 | 0x0d
    int 0x10
    ;; LF
    mov al, 0x0a
    int 0x10

    ;; Output 'cx' spaces
    mov cx, (conwidth - qrwidth) / 2
.prefixloop:
    mov al, 0x20
    int 0x10
    dec cx
    jnz .prefixloop

    mov di, qrwidth

;;; Show actual QR data
.afterprefix:
    ;; cx: bitoffset = 2 * (i % 4)
    mov cx, si
    and cx, dx
    add cx, cx

    ;; bx: index = i / 4;
    mov bx, si
    shr bx, 0x2

    ;; bp: value = qrdata[si]
    mov bp, [qrdata+bx]         ; BX, BP, SI, DI

    ;; bp: value = bp >> bitoffset (cl) & mask (dx, 0b11)
    shr bp, cl                  ; CL only
    and bp, dx

    ;; Display character
    mov al, [qrlut+bp]          ; BX, BP, SI, DI
    ; mov ah, 0x0e (already set above for prefix)
    int 0x10

    ;; Move to next character
    dec di
    dec si
    jnz .loop

halt:
    ;; Disable cursor
    ;; http://www.ctyme.com/intr/rb-0086.htm
    ;; https://wiki.osdev.org/Text_Mode_Cursor#Disabling_the_Cursor
    mov ah, 0x01
    mov ch, 0x3f
    int 0x10

    ;; Clear interrupt flag and halt
    cli                         ; FIXME might be unneeded?
    hlt

qrdata:
%include "qrdata.asm"

qrlut:
    db 0xDB   ; empty
    db 0xDF   ; bottom
    db 0xDC   ; top
    db 0x20   ; full

hiddendata:
    %include "hiddendata.asm"

gifdata:
    db 0x00  ; end comment block
    db 0x2C  ; image separator
    db 0x00, 0x00  ; x position 0
    db 0x00, 0x00  ; y position 0
    db 0x80, 0x00  ; width 128
    db 0x10, 0x00  ; height 16
    db 0x00  ; flags
%include "gifdata.asm"

db 0x21, 0xfe, (padding - $ - 5)
;db "[::::::]=|>=###)"
db "uvag:--xrrc-tbvat"
db 0
db 0x3b  ; GIF trailer

;; Zero-pad up to 512 bytes
padding:
times 508 - ($-$$) db 0

;; BIOS expects the last double words to be this value
dw 0
dw 0xaa55

%assign thesize padding-$$+4
%assign thefree 512-thesize
%assign theqrsize padding-qrdata
%warning size: thesize/512 (thefree free), QR theqrsize
