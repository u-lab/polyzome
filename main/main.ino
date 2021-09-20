#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Conceptinetics.h>

#define _USE_MATH_DEFINES
#define DMX_MASTER_CHANNELS   32  //DMXで使うチャンネル数
#define RXEN_PIN  2 //不明
#define MAX_LIGHT_VOLUME 125  //ライトの最大ボリューム

//DMXコントローラのインスタンス
DMX_Master  dmx_master ( DMX_MASTER_CHANNELS, RXEN_PIN );

char BUF[256]; //シリアル出力文字列用バッファー

//ライトボリューム 0から1の間の調整にします。
float gLightVolume = 0;

//初期設定
void setup() {
  Serial.println("set up start");
   
  //DMXの初期化
  dmx_master.enable ();
  dmx_master.setChannelRange ( 1, DMX_MASTER_CHANNELS, MAX_LIGHT_VOLUME);
 
  //シリアル通信の初期化
  Serial.begin(9600);
  clearAll();
}

/*
** HANLER TEMPLETE **
** 関数名 : handler_<自分の名前>
** 引数 : デフォルト値はなし。自分用に作るのはあり(作った場合はここに要説明)。
** 戻り値 : void
** 関数の機能 : <説明> loopでこの関数呼び出すだけでみんなの処理がまとまるようにしたい。
** 作者: 関数作った人
** 日付: 関数作った日
*/
//  void handler_name(voids)
//  {
//       ここにloop内で行いたい処理を書き込む
//   }

//メインループ
void loop()
{ 
  //sawai_proc();

  //test_drawPoint(); //test OK
  //test_drawPoints(); //test OK
  //test_drawCircle();  //test OK
  //test_drawBox();   //test OK

  /*
  setLightVolume(0.1);
  //実行するものに対して、コメントを外す。そのうち、シリアル経由でパソコンから切り替えられるようにする。
  for (int i=0;i<5;i++)
  {drawPoint(i,4);

setLightHeight(1, true);delay(500);
setLightHeight(1, false);delay(500);
clearAll();
 }*/
 
}
