
#include <pic.h>
#include <htc.h>
#include <pic12lf1822.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ  1000000    // delay用(クロック1MHzで動作時)

// コンフィギュレーション１の設定
// CLKOUTﾋﾟﾝをRA4ﾋﾟﾝで使用する(CLKOUTEN_OFF)：内部ｸﾛｯｸ使用する(INTIO)
// 外部ｸﾛｯｸ監視しない(FCMEN_OFF)：外部・内部ｸﾛｯｸの切替えでの起動はなし(IESO_OFF)
// 電源電圧降下常時監視機能ON(BOREN_ON)：電源ONから64ms後にﾌﾟﾛｸﾞﾗﾑを開始する(PWRTEN_ON)
// ｳｵｯﾁﾄﾞｯｸﾞﾀｲﾏｰ無し(WDTE_OFF)：
// 外部ﾘｾｯﾄ信号は使用せずにﾃﾞｼﾞﾀﾙ入力(RA3)ﾋﾟﾝとする(MCLRE_OFF)
// ﾌﾟﾛｸﾞﾗﾑﾒﾓﾘｰを保護しない(CP_OFF)：ﾃﾞｰﾀﾒﾓﾘｰを保護しない(CPD_OFF)
__CONFIG(CLKOUTEN_OFF & FOSC_INTOSC & FCMEN_OFF & IESO_OFF & BOREN_ON &
         PWRTE_ON & WDTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF) ;
// コンフィギュレーション２の設定
// 動作クロックを32MHzでは動作させない(PLLEN_OFF)
// スタックがオーバフローやアンダーフローしたらリセットをする(STVREN_ON)
// 低電圧プログラミング機能使用しない(LVP_OFF)
// Flashﾒﾓﾘｰを保護しない(WRT_OFF)：電源電圧降下常時監視電圧(2.5V)設定(BORV_HI)
__CONFIG(PLLEN_OFF & STVREN_ON & WRT_OFF & BORV_HI & LVP_OFF);

// 指定した時間(num x 10ms)だけウエイトを行う処理関数
void Wait(unsigned int num)
{
     int i ;

     // numで指定した回数だけ繰り返す
     for (i=0 ; i < num ; i++) {
          __delay_ms(10) ;     // 10msプログラムの一時停止
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
          while(TXIF==0) ;     // 送信可能になるまで待つ    *1)
          TXREG = i ;          // 送信する
          // 送信データを作成する(モニターに表示しやすい用に文字データを作成)
          i++ ;
          if (i > 0x7b) i=0x30 ;

          Wait(100) ;          // １秒後に処理を繰り返す
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

// メインの処理
void main()
{
     char i ;

     OSCCON = 0b01011010 ;     // 内部クロックは1ＭＨｚとする
     ANSELA = 0b00000000 ;     // no use analog（すべてデジタルI/Oに割当てる）
     TRISA  = 0b00001000 ;     // ピンは全て出力に割当てる(RA3 is INPUT only)
     PORTA  = 0b00000000 ;     // reset OUTPUT pin(all LOW)
     // ＵＳＡＲＴ機能の設定を行う
     RXDTSEL = 1 ;             // 2番ピン(RA5)をＲＸ受信ピンとする
     TXCKSEL = 1 ;             // 3番ピン(RA4)をＴＸ送信ピンとする
 	 BRG16 = 1;                // baud rate 　set bit
     TXSTA  = 0b00100100 ;     // 送信情報設定：非同期モード　８ビット・ノンパリティ
     RCSTA  = 0b10010000 ;     // 受信情報設定
     SPBRG  = 25 ;             // ボーレートを９６００(高速モード)に設定
RCIF = 0;
RCIE = 1 ;                // ＵＳＡＲＴ割込み受信を有効にする
//TMR0IE = 1;              // タイマー0割込み(T0IE)を許可する
PEIE = 1 ;                // 周辺装置割込みを有効にする
GIE  = 1 ;                // 全割込み処理を許可する

     Wait(500) ;               // ５秒後に開始する
     i = 0x30 ;

     while(1) {
/*          while(TXIF==0) ;     // 送信可能になるまで待つ    *1)
          TXREG = i ;          // 送信する
          // 送信データを作成する(モニターに表示しやすい用に文字データを作成)
          i++ ;
          if (i > 0x7b) i=0x30 ;

          Wait(100) ;          // １秒後に処理を繰り返す
 */    }
}