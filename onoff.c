
#include <pic.h>
#include <htc.h>
#include <pic12lf1822.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ  4000000    // delay�p(�N���b�N�WMHz�œ��쎞)

// �R���t�B�M�����[�V�����P�̐ݒ�
// CLKOUT��݂�RA4��݂Ŏg�p����(CLKOUTEN_OFF)�F�����ۯ��g�p����(INTIO)
// �O���ۯ��Ď����Ȃ�(FCMEN_OFF)�F�O���E�����ۯ��̐ؑւ��ł̋N���͂Ȃ�(IESO_OFF)
// �d���d���~���펞�Ď��@�\ON(BOREN_ON)�F�d��ON����64ms�����۸��т��J�n����(PWRTEN_ON)
// �����ޯ����ϰ����(WDTE_OFF)�F
// �O��ؾ�ĐM���͎g�p�������޼��ٓ���(RA3)��݂Ƃ���(MCLRE_OFF)
// ��۸�����ذ��ی삵�Ȃ�(CP_OFF)�F�ް���ذ��ی삵�Ȃ�(CPD_OFF)
__CONFIG(CLKOUTEN_OFF & FOSC_INTOSC & FCMEN_OFF & IESO_OFF & BOREN_ON &
         PWRTE_ON & WDTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF);
// �R���t�B�M�����[�V�����Q�̐ݒ�
// ����N���b�N��32MHz�ł͓��삳���Ȃ�(PLLEN_OFF)
// �X�^�b�N���I�[�o�t���[��A���_�[�t���[�����烊�Z�b�g������(STVREN_ON)
// ��d���v���O���~���O�@�\�g�p���Ȃ�(LVP_OFF)
// Flash��ذ��ی삵�Ȃ�(WRT_OFF)�F�d���d���~���펞�Ď��d��(2.5V)�ݒ�(BORV_HI)
__CONFIG(PLLEN_OFF & STVREN_ON & WRT_OFF & BORV_HI & LVP_OFF);

#define LED        LATA2

//******************* �v���g�^�C�v *************************************
void FlashLED(char);
void ErrorInd(void);

// ******************* main ******************************************
void main() {
    char RxData;
    OSCCON = 0b01101010;                 //  �����N���b�N4Mhz
    PORTA  = 0x00;
    APFCONbits.RXDTSEL = 1;             //Rx��RA5���g�p����
    TRISA  = 0b11111011;                 //RA2:�o�� ���͓���
    ANSELA = 0x00;                       //���ׂăf�W�^��
    WPUA   = 0b00011111;                 // RA5�ȊO��v���A�b�v
    nWPUEN = 0;

    // UART�֘A���W�X�^�ݒ�
    RCSTA   = 0b10010000;                // 8 bit �A����M
    TXSTA   = 0b00000100;                // �񓯊���M High Baud Rate�I��
    BAUDCON = 0b00001000;                // 16 bit SPBRG
    SPBRGH  = 0;                         // 9600bps
    SPBRGL  = 103;
    while(1){
        while (!RCIF);                   // ��M����܂ő҂�
        if(RCSTAbits.OERR){              // Overrun�G���[�Ȃ�
            RCSTAbits.CREN=0;            // �G���[���N���A
            RCSTAbits.CREN=1;            // �ċN��
            RxData = RCREG;              // ��ǂ�
            continue;                    // �Ď�M
        }
        RxData = RCREG;                  // ��M�f�[�^����荞��
        switch(RxData){                  // �f�[�^���e��
            case '1':FlashLED(1);break;  // '1'�Ȃ�_�� 1 ��
            case '2':FlashLED(2);break;  // '2'�Ȃ�_�� 2 ��
            case '3':FlashLED(3);break;  // '3'�Ȃ�_�� 3 ��
            case '4':FlashLED(4);break;  // '4'�Ȃ�_�� 4 ��
            default :ErrorInd() ;break;  // ���͒Z�_�� 2 ��
        }
    }
}
// �w��� LED ��_�ł��� *******************************************
void FlashLED(char i){
    while(i--){
        LED = 1; __delay_ms(250);
        LED = 0; __delay_ms(250);
    }
}
// �G���[�\���̂��ߒZ�� 2 ��_�� **************************************
void ErrorInd(void){
    LED = 1; __delay_ms(50);
    LED = 0; __delay_ms(50);
    LED = 1; __delay_ms(50);
    LED = 0; __delay_ms(50);
}