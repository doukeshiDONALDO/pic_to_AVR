
#include <pic.h>
#include <htc.h>
#include <pic12lf1822.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#define _XTAL_FREQ  8000000    // delay用(クロック８MHzで動作時)

/* グローバル関数 */


static void init();

// コンフィギュレーション１の設定
// CLKOUTﾋﾟﾝをRA4ﾋﾟﾝで使用しない(CLKOUTEN_OFF)：内部ｸﾛｯｸ使用する(INTIO)
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


// ＵＳＡＲＴ通信の受信割込み処理
void interrupt InterReceiver( void )
{
static int counter = 0;    //割り込みカウンタ
static int sec = 0;     //1秒カウンタ
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


// メインの処理
void main()
{
 

  init();
  while (1) {
 
  }
}

static void init() {
  OSCCON = 0b01011010 ;     // 内部クロックは1ＭＨｚとする
  ANSELA = 0b00000000 ;     // アナログは使用しない（すべてデジタルI/Oに割当てる）
  TRISA  = 0b00001001 ;     // input RA3 RA0 , output other 
  PORTA  = 0b00000100 ;     // outout pin init , RA2 is high
  // ＵＳＡＲＴ機能の設定を行う
  RXDTSEL = 1 ;             // 2番ピン(RA5)をＲＸ受信ピンとする
  TXCKSEL = 1 ;             // 3番ピン(RA4)をＴＸ送信ピンとする
  BRG16 = 1;       // baud rate 　set bit
  TXSTA  = 0b00100100 ;     // 送信情報設定：非同期モード　８ビット・ノンパリティ
  RCSTA  = 0b10010000 ;     // 受信情報設定
  SPBRG  = 25 ;             // ボーレートを９６００(高速モード)に設定

  RCIF = 0 ;                // ＵＳＡＲＴ割込み受信フラグの初期化
 

  OPTION_REG = 0b00000000; // 内部ｸﾛｯｸでTIMER0を使用、ﾌﾟﾘｽｹｰﾗｶｳﾝﾄ値 1:2
  TMR0   = 141;         // タイマー0の初期化
  TMR0IF = 0;              // タイマー0割込フラグ(T0IF)を0にする



  RCIE = 1 ;                // ＵＳＡＲＴ割込み受信を有効にする
    TMR0IE = 1;              // タイマー0割込み(T0IE)を許可する
  PEIE = 1 ;                // 周辺装置割込みを有効にする
  GIE  = 1 ;                // 全割込み処理を許可する
}

