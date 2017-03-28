/** I N C L U D E S ************************************************/
#include <pic.h>
#include <htc.h>
#include <pic12f675.h>
static void pic_set();
int adcon();
/*** Configuration *******/
__CONFIG(UNPROTECT & MCLRDIS & BOREN & PWRTEN & WDTDIS & INTIO) ;

/* �O���[�o���֐� */
static int counter = 0;		//���荞�݃J�E���^
static int sec = 0;			//1�b�J�E���^
static int flg = 0;			//ONOFF_flag
//static void Delay_ms(unsigned char ms);
//static void Delay_1ms();		//1m_sDaly

/*********** ���荞�ݏ����@************/
static void interrupt intr(void) {
	T0IF = 0;		//TMR0���荞�݃N���A
	TMR0 = 6;		//TMR0�Đݒ�
  
	if(++counter >= 496){		//1�b�o�߂�����(500+�␳�l5)
		counter = 0;
		sec++;
		if(flg==0){

			if(sec>=30 || GPIO0==1){		//360 5���o�߂�����(5[min]*60=300[sec])
			//if(sec>=10){     //����m�F�p 10�b�v��
				GPIO5=0;
				flg=1;
			}
				
		}else {
		    //if(sec>=10){     //����m�F�p 10�b�v��
			if(sec >=3240){		//12���Ԍo�߂�����(�J�����p)(12[hour]*60*60=43200[sec])
								//1���Ԍo�߂�����(���K�[�p)(1[hour]*60*60=3600[sec]	3300
				GPIO5=1;
				sec=0;
				flg=0;
			}
		}
	}
}

/**********�@���C���֐��@**********/
main() {
	int value;
	pic_set();		//pic�̏����ݒ�
	while(1){
/*
		value = adcon();
		if(value <= 50) {
			INTCON=0x20;
		}else if(value > 50) {
			INTCON=0xA0;
		}
*/
	}
}

/********** PIC�̏����� **********/
static void pic_set() {
	ANSEL=0x00;			//analogPin  doc.p44
	TRISIO=0x01;		//GP0�̂�INPUT,�c���OUTPUT  	doc.p20	Note: TRISIO<3> always reads 1
	GPIO=0x20;			//GP5���o�� doc.p19
	CMCON=0x07;			//�R���p���[�^���g�p
	//ADCON0=0b10000001;	//AN0��A/D�ϊ��s���Ƃ��Ďg�p����
	OPTION_REG=0x02;	//TMR0�v���X�P�[��1:4(1�J�E���g1��s)
	TMR0=6;				//TMR0�����l(max�J�E���g250��s)
	INTCON=0xA0;
	//_delay_us(20);
}
/*�d������(���g�p)
int adcon() {
	unsigned int volt;

	ADCON0bits.GO = 1;
	while(GO);
	volt = ( volt << 8 ) | ADRESH;
	volt = ADRESL;
	return volt;
}
*/
/********* �P���r�~ms �E�F�C�g���[�`�� *************/
/*
static void Delay_ms(unsigned char ms) {
	unsigned char c;
	for (c=ms ; c>0 ; c--) {
		Delay_1ms();
	}
}
*/
/********* �P���r�E�F�C�g���[�`�� *****************/
/*
static void Delay_1ms() {
	unsigned int cnt;
	unsigned int i;
	cnt = 76;

	for	(i=0 ; i<cnt ; i++) {
		NOP();
	}
}
*/