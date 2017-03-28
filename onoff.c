/** I N C L U D E S ************************************************/
#include <pic.h>
#include <htc.h>
#include <pic12f675.h>
static void pic_set();
int adcon();
/*** Configuration *******/
__CONFIG(UNPROTECT & MCLRDIS & BOREN & PWRTEN & WDTDIS & INTIO) ;

/* グローバル関数 */
static int counter = 0;		//割り込みカウンタ
static int sec = 0;			//1秒カウンタ
static int flg = 0;			//ONOFF_flag
//static void Delay_ms(unsigned char ms);
//static void Delay_1ms();		//1m_sDaly

/*********** 割り込み処理　************/
static void interrupt intr(void) {
	T0IF = 0;		//TMR0割り込みクリア
	TMR0 = 6;		//TMR0再設定
  
	if(++counter >= 496){		//1秒経過したら(500+補正値5)
		counter = 0;
		sec++;
		if(flg==0){

			if(sec>=30 || GPIO0==1){		//360 5分経過したら(5[min]*60=300[sec])
			//if(sec>=10){     //動作確認用 10秒計測
				GPIO5=0;
				flg=1;
			}
				
		}else {
		    //if(sec>=10){     //動作確認用 10秒計測
			if(sec >=3240){		//12時間経過したら(カメラ用)(12[hour]*60*60=43200[sec])
								//1時間経過したら(ロガー用)(1[hour]*60*60=3600[sec]	3300
				GPIO5=1;
				sec=0;
				flg=0;
			}
		}
	}
}

/**********　メイン関数　**********/
main() {
	int value;
	pic_set();		//picの初期設定
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

/********** PICの初期化 **********/
static void pic_set() {
	ANSEL=0x00;			//analogPin  doc.p44
	TRISIO=0x01;		//GP0のみINPUT,残りはOUTPUT  	doc.p20	Note: TRISIO<3> always reads 1
	GPIO=0x20;			//GP5を出力 doc.p19
	CMCON=0x07;			//コンパレータ未使用
	//ADCON0=0b10000001;	//AN0をA/D変換ピンとして使用する
	OPTION_REG=0x02;	//TMR0プリスケーラ1:4(1カウント1μs)
	TMR0=6;				//TMR0初期値(maxカウント250μs)
	INTCON=0xA0;
	//_delay_us(20);
}
/*電圧測定(未使用)
int adcon() {
	unsigned int volt;

	ADCON0bits.GO = 1;
	while(GO);
	volt = ( volt << 8 ) | ADRESH;
	volt = ADRESL;
	return volt;
}
*/
/********* １ｍＳ×ms ウェイトルーチン *************/
/*
static void Delay_ms(unsigned char ms) {
	unsigned char c;
	for (c=ms ; c>0 ; c--) {
		Delay_1ms();
	}
}
*/
/********* １ｍＳウェイトルーチン *****************/
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