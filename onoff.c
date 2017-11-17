
#include <pic.h>
#include <htc.h>
#include <pic12lf1822.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ  4000000    // delay用(クロック８MHzで動作時)

// コンフィギュレーション１の設定
// CLKOUTﾋﾟﾝをRA4ﾋﾟﾝで使用する(CLKOUTEN_OFF)：内部ｸﾛｯｸ使用する(INTIO)
// 外部ｸﾛｯｸ監視しない(FCMEN_OFF)：外部・内部ｸﾛｯｸの切替えでの起動はなし(IESO_OFF)
// 電源電圧降下常時監視機能ON(BOREN_ON)：電源ONから64ms後にﾌﾟﾛｸﾞﾗﾑを開始する(PWRTEN_ON)
// ｳｵｯﾁﾄﾞｯｸﾞﾀｲﾏｰ無し(WDTE_OFF)：
// 外部ﾘｾｯﾄ信号は使用せずにﾃﾞｼﾞﾀﾙ入力(RA3)ﾋﾟﾝとする(MCLRE_OFF)
// ﾌﾟﾛｸﾞﾗﾑﾒﾓﾘｰを保護しない(CP_OFF)：ﾃﾞｰﾀﾒﾓﾘｰを保護しない(CPD_OFF)
__CONFIG(CLKOUTEN_OFF & FOSC_INTOSC & FCMEN_OFF & IESO_OFF & BOREN_ON &
         PWRTE_ON & WDTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF);
// コンフィギュレーション２の設定
// 動作クロックを32MHzでは動作させない(PLLEN_OFF)
// スタックがオーバフローやアンダーフローしたらリセットをする(STVREN_ON)
// 低電圧プログラミング機能使用しない(LVP_OFF)
// Flashﾒﾓﾘｰを保護しない(WRT_OFF)：電源電圧降下常時監視電圧(2.5V)設定(BORV_HI)
__CONFIG(PLLEN_OFF & STVREN_ON & WRT_OFF & BORV_HI & LVP_OFF);

#define LED        LATA2

//******************* プロトタイプ *************************************
void FlashLED(char);
void ErrorInd(void);

// ******************* main ******************************************
void main() {
    char RxData;
    OSCCON = 0b01101010;                 //  内部クロック4Mhz
    PORTA  = 0x00;
    APFCONbits.RXDTSEL = 1;             //RxはRA5を使用する
    TRISA  = 0b11111011;                 //RA2:出力 他は入力
    ANSELA = 0x00;                       //すべてデジタル
    WPUA   = 0b00011111;                 // RA5以外弱プルアップ
    nWPUEN = 0;

    // UART関連レジスタ設定
    RCSTA   = 0b10010000;                // 8 bit 連続受信
    TXSTA   = 0b00000100;                // 非同期受信 High Baud Rate選択
    BAUDCON = 0b00001000;                // 16 bit SPBRG
    SPBRGH  = 0;                         // 9600bps
    SPBRGL  = 103;
    while(1){
        while (!RCIF);                   // 受信するまで待つ
        if(RCSTAbits.OERR){              // Overrunエラーなら
            RCSTAbits.CREN=0;            // エラーをクリア
            RCSTAbits.CREN=1;            // 再起動
            RxData = RCREG;              // 空読み
            continue;                    // 再受信
        }
        RxData = RCREG;                  // 受信データを取り込む
        switch(RxData){                  // データ内容が
            case '1':FlashLED(1);break;  // '1'なら点滅 1 回
            case '2':FlashLED(2);break;  // '2'なら点滅 2 回
            case '3':FlashLED(3);break;  // '3'なら点滅 3 回
            case '4':FlashLED(4);break;  // '4'なら点滅 4 回
            default :ErrorInd() ;break;  // 他は短点滅 2 回
        }
    }
}
// 指定回数 LED を点滅する *******************************************
void FlashLED(char i){
    while(i--){
        LED = 1; __delay_ms(250);
        LED = 0; __delay_ms(250);
    }
}
// エラー表示のため短く 2 回点滅 **************************************
void ErrorInd(void){
    LED = 1; __delay_ms(50);
    LED = 0; __delay_ms(50);
    LED = 1; __delay_ms(50);
    LED = 0; __delay_ms(50);
}