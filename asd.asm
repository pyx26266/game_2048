mov ax,data 

mov ds,ax

mov ax,stack 

mov ss,ax

mov sp,stacktop %define encoderkey 'hello' %strlen enkey encoderkey main1: 

mov ah,00

int 16h 

mov dl,al

cmp al, 'q' 

jz done 

mov ah,enkey 

add dl, ah

mov ah,2

int 0x21 

jmp main1 done: 

mov ax,0x4c00 

int 0x21 segment data segment stack stack 

resb 64 stacktop: 

Let me explain a bit. 

The commands... 

mov ah,00

int 16h 

...instruct the program to wait for a key input from the user (this is what interrupt 16h does when 0x00 is stored in AH register). The key entered is stored in DL register with the command: 

mov dl,al.

The command... 

cmp al, 'q' 

jz done 

...checks the value of the key pressed and if user pressed ‘q’ then the program jumps to the command which terminated it (see below). 

Commands... 

mov ax,0x4c00 

int 0x21 

...are the ones which terminate the program (this is what interrupt 0x21 does with 0 in AX register). 

If the user has entered a character different than ‘q’, then the program alters the value stored in DL by adding the value of 

5 to it (it actually transfers the length of the enkey variable, which is 5 – this I did just for my own experimenting purposes): 

mov ah,enkey 

add dl, ah

and then it shows the resulting new character value in the screen: 

mov ah,2

int 0x21 