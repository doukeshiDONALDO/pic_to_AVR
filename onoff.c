
#include <pic.h>
#include <htc.h>
#include <pic12lf1822.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#define _XTAL_FREQ  8000000    // delay�p(�N���b�N�WMHz�œ��쎞)

/* �O���[�o���֐� */


static void init();

// �R���t�B�M�����[�V�����P�̐ݒ�
// CLKOUT��݂�RA4��݂Ŏg�p���Ȃ�(CLKOUTEN_OFF)�F�����ۯ��g�p����(INTIO)
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


// �t�r�`�q�s�ʐM�̎�M�����ݏ���
void interrupt InterReceiver( void )
{
static int counter = 0;    //���荞�݃J�E���^
static int sec = 0;     //1�b�J�E���^
static int flg = 0;     //ONOFF_flag
static int rev_flg = 0;     //ONOFF_flag
static int now_sec = 0;

static int offtime = 300;     
static int offtime_flg = 0;     //flag
static int now_offtime = 0;     

	
	
	
  if (RCIF == 1) {          // usart receive interrupt 
	if ( RCREG == '$') {   // receive start
      sec = now_sec;
      now_sec = 0;
	  offtime = now_offtime;
      now_offtime = 0;
      flg = 0;
      RA2 = 1;
    }
    else if ( RCREG == '_') {   // receive start
      rev_flg = 1;
    }
    else if ( RCREG == '|') {  // receive stop
      rev_flg = 0;
   }
    else if (rev_flg) {
	    now_sec = now_sec * 10 + (RCREG - '0');    
    }
    
    else if ( RCREG == '(') {  
      offtime_flg = 1;
    }
    else if ( RCREG == ')') {  
      offtime_flg = 0;
    }
    else if (offtime_flg) {
	    now_offtime = now_offtime * 10 + (RCREG - '0');    
    }
   RCIF = 0;           // usart receive interrupt flag reset
  }

  if (TMR0IF == 1) {           // timer0 interrupt
    TMR0IF = 0 ;            // timer0 interrupt flag reset
    TMR0 = 141;         // TMR0 reset
    if (++counter >= 1000) {
      counter = 0;
      sec++;
      if (flg == 0) {

        if (sec >= offtime || RA0 == 1) { 
          RA2 = 0;
          flg = 1;
        }

      } else if(flg){
        if (sec >= 3600) { 
          RA2 = 1;
          sec = 0;
          flg = 0;
        }
      }
    }
  }
}


// ���C���̏���
void main()
{
 

  init();
  while (1) {
 
  }
}

static void init() {
  OSCCON = 0b01011010 ;     // �����N���b�N��1�l�g���Ƃ���
  ANSELA = 0b00000000 ;     // �A�i���O�͎g�p���Ȃ��i���ׂăf�W�^��I/O�Ɋ����Ă�j
  TRISA  = 0b00001001 ;     // input RA3 RA0 , output other 
  PORTA  = 0b00000100 ;     // outout pin init , RA2 is high
  // �t�r�`�q�s�@�\�̐ݒ���s��
  RXDTSEL = 1 ;             // 2�ԃs��(RA5)���q�w��M�s���Ƃ���
  TXCKSEL = 1 ;             // 3�ԃs��(RA4)���s�w���M�s���Ƃ���
  BRG16 = 1;       // baud rate �@set bit
  TXSTA  = 0b00100100 ;     // ���M���ݒ�F�񓯊����[�h�@�W�r�b�g�E�m���p���e�B
  RCSTA  = 0b10010000 ;     // ��M���ݒ�
  SPBRG  = 25 ;             // �{�[���[�g���X�U�O�O(�������[�h)�ɐݒ�

  RCIF = 0 ;                // �t�r�`�q�s�����ݎ�M�t���O�̏�����
 

  OPTION_REG = 0b00000000; // �����ۯ���TIMER0���g�p�A��ؽ��׶��Ēl 1:2
  TMR0   = 141;         // �^�C�}�[0�̏�����
  TMR0IF = 0;              // �^�C�}�[0�����t���O(T0IF)��0�ɂ���



  RCIE = 1 ;                // �t�r�`�q�s�����ݎ�M��L���ɂ���
    TMR0IE = 1;              // �^�C�}�[0������(T0IE)��������
  PEIE = 1 ;                // ���ӑ��u�����݂�L���ɂ���
  GIE  = 1 ;                // �S�����ݏ�����������
}

