opt subtitle "HI-TECH Software Omniscient Code Generator (Lite mode) build 10920"

opt pagewidth 120

	opt lm

	processor	12F675
clrc	macro
	bcf	3,0
	endm
clrz	macro
	bcf	3,2
	endm
setc	macro
	bsf	3,0
	endm
setz	macro
	bsf	3,2
	endm
skipc	macro
	btfss	3,0
	endm
skipz	macro
	btfss	3,2
	endm
skipnc	macro
	btfsc	3,0
	endm
skipnz	macro
	btfsc	3,2
	endm
indf	equ	0
indf0	equ	0
pc	equ	2
pcl	equ	2
status	equ	3
fsr	equ	4
fsr0	equ	4
c	equ	1
z	equ	0
pclath	equ	10
# 8 "C:\Users\sodelab\Documents\PIC\ONOFF_12V\onoff.c"
	psect config,class=CONFIG,delta=2 ;#
# 8 "C:\Users\sodelab\Documents\PIC\ONOFF_12V\onoff.c"
	dw 0x3FFF & 0x3FDF & 0x3FFF & 0x3FEF & 0x3FF7 & 0x3FFC ;#
	FNCALL	_main,_pic_set
	FNROOT	_main
	FNCALL	intlevel1,_intr
	global	intlevel1
	FNROOT	intlevel1
	global	_counter
	global	_flg
	global	_sec
	global	_CMCON
psect	text153,local,class=CODE,delta=2
global __ptext153
__ptext153:
_CMCON	set	25
	global	_GPIO
_GPIO	set	5
	global	_INTCON
_INTCON	set	11
	global	_TMR0
_TMR0	set	1
	global	_CARRY
_CARRY	set	24
	global	_GIE
_GIE	set	95
	global	_GPIO5
_GPIO5	set	45
	global	_T0IF
_T0IF	set	90
	global	_ANSEL
_ANSEL	set	159
	global	_EEADR
_EEADR	set	155
	global	_EECON1
_EECON1	set	156
	global	_EECON2
_EECON2	set	157
	global	_EEDATA
_EEDATA	set	154
	global	_OPTION_REG
_OPTION_REG	set	129
	global	_TRISIO
_TRISIO	set	133
	global	_RD
_RD	set	1248
	global	_WR
_WR	set	1249
	global	_WREN
_WREN	set	1250
	file	"onoff_12V.as"
	line	#
psect cinit,class=CODE,delta=2
global start_initialization
start_initialization:

psect	bssBANK0,class=BANK0,space=1
global __pbssBANK0
__pbssBANK0:
_counter:
       ds      2

_flg:
       ds      2

_sec:
       ds      2

; Clear objects allocated to BANK0
psect cinit,class=CODE,delta=2
	clrf	((__pbssBANK0)+0)&07Fh
	clrf	((__pbssBANK0)+1)&07Fh
	clrf	((__pbssBANK0)+2)&07Fh
	clrf	((__pbssBANK0)+3)&07Fh
	clrf	((__pbssBANK0)+4)&07Fh
	clrf	((__pbssBANK0)+5)&07Fh
psect cinit,class=CODE,delta=2
global end_of_initialization

;End of C runtime variable initialization code

end_of_initialization:
clrf status
ljmp _main	;jump to C main() function
psect	cstackCOMMON,class=COMMON,space=1
global __pcstackCOMMON
__pcstackCOMMON:
	global	??_pic_set
??_pic_set:	; 0 bytes @ 0x0
	global	??_main
??_main:	; 0 bytes @ 0x0
psect	cstackBANK0,class=BANK0,space=1
global __pcstackBANK0
__pcstackBANK0:
	global	?_pic_set
?_pic_set:	; 0 bytes @ 0x0
	global	?_intr
?_intr:	; 0 bytes @ 0x0
	global	??_intr
??_intr:	; 0 bytes @ 0x0
	global	?_main
?_main:	; 2 bytes @ 0x0
	ds	4
;;Data sizes: Strings 0, constant 0, data 0, bss 6, persistent 0 stack 0
;;Auto spaces:   Size  Autos    Used
;; COMMON           0      0       0
;; BANK0           62      4      10

;;
;; Pointer list with targets:



;;
;; Critical Paths under _main in COMMON
;;
;;   None.
;;
;; Critical Paths under _intr in COMMON
;;
;;   None.
;;
;; Critical Paths under _main in BANK0
;;
;;   None.
;;
;; Critical Paths under _intr in BANK0
;;
;;   None.

;;
;;Main: autosize = 0, tempsize = 0, incstack = 0, save=0
;;

;;
;;Call Graph Tables:
;;
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (0) _main                                                 2     2      0       0
;;                            _pic_set
;; ---------------------------------------------------------------------------------
;; (1) _pic_set                                              0     0      0       0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 1
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (2) _intr                                                 4     4      0       0
;;                                              0 BANK0      4     4      0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 2
;; ---------------------------------------------------------------------------------

;; Call Graph Graphs:

;; _main (ROOT)
;;   _pic_set
;;
;; _intr (ROOT)
;;

;; Address spaces:

;;Name               Size   Autos  Total    Cost      Usage
;;BITCOMMON            0      0       0       0        0.0%
;;EEDATA              80      0       0       0        0.0%
;;NULL                 0      0       0       0        0.0%
;;CODE                 0      0       0       0        0.0%
;;BITSFR0              0      0       0       1        0.0%
;;SFR0                 0      0       0       1        0.0%
;;COMMON               0      0       0       1        0.0%
;;BITSFR1              0      0       0       2        0.0%
;;SFR1                 0      0       0       2        0.0%
;;STACK                0      0       1       2        0.0%
;;BITBANK0            3E      0       0       3        0.0%
;;BANK0               3E      4       A       4       16.1%
;;ABS                  0      0       A       5        0.0%
;;DATA                 0      0       B       6        0.0%

	global	_main
psect	maintext,global,class=CODE,delta=2
global __pmaintext
__pmaintext:

;; *************** function _main *****************
;; Defined at:
;;		line 46 in file "C:\Users\sodelab\Documents\PIC\ONOFF_12V\onoff.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  value           2    0        int 
;; Return value:  Size  Location     Type
;;                  2  387[BANK0 ] int 
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 17F/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0
;;      Params:         0       0
;;      Locals:         0       0
;;      Temps:          0       0
;;      Totals:         0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_pic_set
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	maintext
	file	"C:\Users\sodelab\Documents\PIC\ONOFF_12V\onoff.c"
	line	46
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:	
	opt	stack 6
; Regs used in _main: [wreg+status,2+status,0+pclath+cstack]
	line	48
	
l2047:	
;onoff.c: 47: int value;
;onoff.c: 48: pic_set();
	fcall	_pic_set
	goto	l389
	line	49
;onoff.c: 49: while(1){
	
l388:	
	line	58
	
l389:	
	line	49
	goto	l389
	
l390:	
	line	59
	
l391:	
	global	start
	ljmp	start
	opt stack 0
GLOBAL	__end_of_main
	__end_of_main:
;; =============== function _main ends ============

	signat	_main,90
	global	_pic_set
psect	text154,local,class=CODE,delta=2
global __ptext154
__ptext154:

;; *************** function _pic_set *****************
;; Defined at:
;;		line 62 in file "C:\Users\sodelab\Documents\PIC\ONOFF_12V\onoff.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0
;;      Params:         0       0
;;      Locals:         0       0
;;      Temps:          0       0
;;      Totals:         0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text154
	file	"C:\Users\sodelab\Documents\PIC\ONOFF_12V\onoff.c"
	line	62
	global	__size_of_pic_set
	__size_of_pic_set	equ	__end_of_pic_set-_pic_set
	
_pic_set:	
	opt	stack 6
; Regs used in _pic_set: [wreg]
	line	63
	
l2045:	
;onoff.c: 63: ANSEL=0x01;
	movlw	(01h)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(159)^080h	;volatile
	line	64
;onoff.c: 64: TRISIO=0x01;
	movlw	(01h)
	movwf	(133)^080h	;volatile
	line	65
;onoff.c: 65: GPIO=0x20;
	movlw	(020h)
	bcf	status, 5	;RP0=0, select bank0
	movwf	(5)	;volatile
	line	66
;onoff.c: 66: CMCON=0x07;
	movlw	(07h)
	movwf	(25)	;volatile
	line	68
;onoff.c: 68: OPTION_REG=0x02;
	movlw	(02h)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(129)^080h	;volatile
	line	69
;onoff.c: 69: TMR0=6;
	movlw	(06h)
	bcf	status, 5	;RP0=0, select bank0
	movwf	(1)	;volatile
	line	70
;onoff.c: 70: INTCON=0xA0;
	movlw	(0A0h)
	movwf	(11)	;volatile
	line	72
	
l394:	
	return
	opt stack 0
GLOBAL	__end_of_pic_set
	__end_of_pic_set:
;; =============== function _pic_set ends ============

	signat	_pic_set,88
	global	_intr
psect	text155,local,class=CODE,delta=2
global __ptext155
__ptext155:

;; *************** function _intr *****************
;; Defined at:
;;		line 18 in file "C:\Users\sodelab\Documents\PIC\ONOFF_12V\onoff.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, btemp+1
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0
;;      Params:         0       0
;;      Locals:         0       0
;;      Temps:          0       4
;;      Totals:         0       4
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		Interrupt level 1
;; This function uses a non-reentrant model
;;
psect	text155
	file	"C:\Users\sodelab\Documents\PIC\ONOFF_12V\onoff.c"
	line	18
	global	__size_of_intr
	__size_of_intr	equ	__end_of_intr-_intr
	
_intr:	
	opt	stack 6
; Regs used in _intr: [wreg+status,2+status,0+btemp+1]
psect	intentry,class=CODE,delta=2
global __pintentry
__pintentry:
global interrupt_function
interrupt_function:
	global saved_w
	saved_w	set	btemp+0
	movwf	saved_w
	swapf	status,w
	bcf	status, 5	;RP0=0, select bank0
	movwf	(??_intr+0)
	movf	fsr0,w
	movwf	(??_intr+1)
	movf	pclath,w
	movwf	(??_intr+2)
	movf	btemp+1,w
	movwf	(??_intr+3)
	ljmp	_intr
psect	text155
	line	19
	
i1l2019:	
;onoff.c: 19: T0IF = 0;
	bcf	(90/8),(90)&7
	line	20
	
i1l2021:	
;onoff.c: 20: TMR0 = 6;
	movlw	(06h)
	movwf	(1)	;volatile
	line	21
;onoff.c: 21: counter++;
	movlw	low(01h)
	addwf	(_counter),f
	skipnc
	incf	(_counter+1),f
	movlw	high(01h)
	addwf	(_counter+1),f
	line	22
;onoff.c: 22: if(counter == 496){
	movlw	high(01F0h)
	xorwf	(_counter+1),w
	skipz
	goto	u227_25
	movlw	low(01F0h)
	xorwf	(_counter),w
u227_25:

	skipz
	goto	u227_21
	goto	u227_20
u227_21:
	goto	i1l385
u227_20:
	line	23
	
i1l2023:	
;onoff.c: 23: counter = 0;
	clrf	(_counter)
	clrf	(_counter+1)
	line	24
	
i1l2025:	
;onoff.c: 24: sec++;
	movlw	low(01h)
	addwf	(_sec),f
	skipnc
	incf	(_sec+1),f
	movlw	high(01h)
	addwf	(_sec+1),f
	line	25
	
i1l2027:	
;onoff.c: 25: if(flg==0){
	movf	((_flg+1)),w
	iorwf	((_flg)),w
	skipz
	goto	u228_21
	goto	u228_20
u228_21:
	goto	i1l2037
u228_20:
	line	27
	
i1l2029:	
;onoff.c: 27: if(sec>=300){
	movf	(_sec+1),w
	xorlw	80h
	movwf	btemp+1
	movlw	(high(012Ch))^80h
	subwf	btemp+1,w
	skipz
	goto	u229_25
	movlw	low(012Ch)
	subwf	(_sec),w
u229_25:

	skipc
	goto	u229_21
	goto	u229_20
u229_21:
	goto	i1l385
u229_20:
	line	29
	
i1l2031:	
;onoff.c: 29: GPIO5=0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	(45/8),(45)&7
	line	30
	
i1l2033:	
;onoff.c: 30: sec=0;
	clrf	(_sec)
	clrf	(_sec+1)
	line	31
	
i1l2035:	
;onoff.c: 31: flg=1;
	movlw	low(01h)
	movwf	(_flg)
	movlw	high(01h)
	movwf	((_flg))+1
	goto	i1l385
	line	32
	
i1l381:	
	line	33
;onoff.c: 32: }
;onoff.c: 33: }else if(flg==1){
	goto	i1l385
	
i1l380:	
	
i1l2037:	
	movlw	01h
	xorwf	(_flg),w
	iorwf	(_flg+1),w
	skipz
	goto	u230_21
	goto	u230_20
u230_21:
	goto	i1l385
u230_20:
	line	35
	
i1l2039:	
;onoff.c: 35: if(sec >=3300){
	movf	(_sec+1),w
	xorlw	80h
	movwf	btemp+1
	movlw	(high(0CE4h))^80h
	subwf	btemp+1,w
	skipz
	goto	u231_25
	movlw	low(0CE4h)
	subwf	(_sec),w
u231_25:

	skipc
	goto	u231_21
	goto	u231_20
u231_21:
	goto	i1l385
u231_20:
	line	37
	
i1l2041:	
;onoff.c: 37: GPIO5=1;
	bcf	status, 5	;RP0=0, select bank0
	bsf	(45/8),(45)&7
	line	38
	
i1l2043:	
;onoff.c: 38: sec=0;
	clrf	(_sec)
	clrf	(_sec+1)
	line	39
;onoff.c: 39: flg=0;
	clrf	(_flg)
	clrf	(_flg+1)
	goto	i1l385
	line	40
	
i1l384:	
	goto	i1l385
	line	41
	
i1l383:	
	goto	i1l385
	line	42
	
i1l382:	
	goto	i1l385
	
i1l379:	
	line	43
	
i1l385:	
	bcf	status, 5	;RP0=0, select bank0
	movf	(??_intr+3),w
	movwf	btemp+1
	movf	(??_intr+2),w
	movwf	pclath
	movf	(??_intr+1),w
	movwf	fsr0
	swapf	(??_intr+0)^00h,w
	movwf	status
	swapf	saved_w,f
	swapf	saved_w,w
	retfie
	opt stack 0
GLOBAL	__end_of_intr
	__end_of_intr:
;; =============== function _intr ends ============

	signat	_intr,88
psect	text156,local,class=CODE,delta=2
global __ptext156
__ptext156:
	global	btemp
	btemp set 05Eh

	DABS	1,94,2	;btemp
	global	wtemp0
	wtemp0 set btemp
	end
