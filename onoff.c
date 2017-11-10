
#include <pic.h>
#include <htc.h>
#include <pic12lf1822.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ  1000000    // delay�p(�N���b�N1MHz�œ��쎞)

// �R���t�B�M�����[�V�����P�̐ݒ�
// CLKOUT��݂�RA4��݂Ŏg�p����(CLKOUTEN_OFF)�F�����ۯ��g�p����(INTIO)
// �O���ۯ��Ď����Ȃ�(FCMEN_OFF)�F�O���E�����ۯ��̐ؑւ��ł̋N���͂Ȃ�(IESO_OFF)
// �d���d���~���펞�Ď��@�\ON(BOREN_ON)�F�d��ON����64ms�����۸��т��J�n����(PWRTEN_ON)
// �����ޯ����ϰ����(WDTE_OFF)�F
// �O��ؾ�ĐM���͎g�p�������޼��ٓ���(RA3)��݂Ƃ���(MCLRE_OFF)
// ��۸�����ذ��ی삵�Ȃ�(CP_OFF)�F�ް���ذ��ی삵�Ȃ�(CPD_OFF)
__CONFIG(CLKOUTEN_OFF & FOSC_INTOSC & FCMEN_OFF & IESO_OFF & BOREN_ON &
         PWRTE_ON & WDTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF) ;
// �R���t�B�M�����[�V�����Q�̐ݒ�
// ����N���b�N��32MHz�ł͓��삳���Ȃ�(PLLEN_OFF)
// �X�^�b�N���I�[�o�t���[��A���_�[�t���[�����烊�Z�b�g������(STVREN_ON)
// ��d���v���O���~���O�@�\�g�p���Ȃ�(LVP_OFF)
// Flash��ذ��ی삵�Ȃ�(WRT_OFF)�F�d���d���~���펞�Ď��d��(2.5V)�ݒ�(BORV_HI)
__CONFIG(PLLEN_OFF & STVREN_ON & WRT_OFF & BORV_HI & LVP_OFF);

// �w�肵������(num x 10ms)�����E�G�C�g���s�������֐�
void Wait(unsigned int num)
{
     int i ;

     // num�Ŏw�肵���񐔂����J��Ԃ�
     for (i=0 ; i < num ; i++) {
          __delay_ms(10) ;     // 10ms�v���O�����̈ꎞ��~
     }
}

void interrupt InterReceiver( void )
{
	static char i = 0x30;
	static int debug = 0;
/*	if (RCIF == 1) {          // usart receive interrupt 
		while(TXIF==0) ;      // wait until possible send
          TXREG = RCREG ;     // send
		RCIF = 0;           // reset usart receive interrupt flag
	}
*/
if (RCIF == 1) {
/*
          while(TXIF==0) ;     // ���M�\�ɂȂ�܂ő҂�    *1)
          TXREG = i ;          // ���M����
          // ���M�f�[�^���쐬����(���j�^�[�ɕ\�����₷���p�ɕ����f�[�^���쐬)
          i++ ;
          if (i > 0x7b) i=0x30 ;

          Wait(100) ;          // �P�b��ɏ������J��Ԃ�
*/
	debug = 1-debug;
Wait(500) ;
if(debug){
     RA2 = 1;
      RA1 = 1;
} 
else
{
     RA2 = 0;
      RA1 = 0;
}
}
RCIF = 0;
}

// ���C���̏���
void main()
{
     char i ;

     OSCCON = 0b01011010 ;     // �����N���b�N��1�l�g���Ƃ���
     ANSELA = 0b00000000 ;     // no use analog�i���ׂăf�W�^��I/O�Ɋ����Ă�j
     TRISA  = 0b00001000 ;     // �s���͑S�ďo�͂Ɋ����Ă�(RA3 is INPUT only)
     PORTA  = 0b00000000 ;     // reset OUTPUT pin(all LOW)
     // �t�r�`�q�s�@�\�̐ݒ���s��
     RXDTSEL = 1 ;             // 2�ԃs��(RA5)���q�w��M�s���Ƃ���
     TXCKSEL = 1 ;             // 3�ԃs��(RA4)���s�w���M�s���Ƃ���
 	 BRG16 = 1;                // baud rate �@set bit
     TXSTA  = 0b00100100 ;     // ���M���ݒ�F�񓯊����[�h�@�W�r�b�g�E�m���p���e�B
     RCSTA  = 0b10010000 ;     // ��M���ݒ�
     SPBRG  = 25 ;             // �{�[���[�g���X�U�O�O(�������[�h)�ɐݒ�
RCIF = 0;
RCIE = 1 ;                // �t�r�`�q�s�����ݎ�M��L���ɂ���
//TMR0IE = 1;              // �^�C�}�[0������(T0IE)��������
PEIE = 1 ;                // ���ӑ��u�����݂�L���ɂ���
GIE  = 1 ;                // �S�����ݏ�����������

     Wait(500) ;               // �T�b��ɊJ�n����
     i = 0x30 ;

     while(1) {
/*          while(TXIF==0) ;     // ���M�\�ɂȂ�܂ő҂�    *1)
          TXREG = i ;          // ���M����
          // ���M�f�[�^���쐬����(���j�^�[�ɕ\�����₷���p�ɕ����f�[�^���쐬)
          i++ ;
          if (i > 0x7b) i=0x30 ;

          Wait(100) ;          // �P�b��ɏ������J��Ԃ�
 */    }
}