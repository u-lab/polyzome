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
  //DMXの初期化
  dmx_master.enable ();
  dmx_master.setChannelRange ( 1, DMX_MASTER_CHANNELS, MAX_LIGHT_VOLUME);
 
  //シリアル通信の初期化
  Serial.begin(9600);
  clearAll();
}

//テスト1(1段目のライトを、個別に光らせる)
void test1(){
  //ライトボリューム調整
  setLightVolume(1);
  //光らせる高さの指定
  setLightHeight(0, true);
  
  for(int i=0; i<5; i++){
    for(int j=0; j<5; j++){
      drawPoint(i,j);
      delay(100);
      clearPlaneAll();
    }   
  }
}

//テスト2(平面は、順に光らせる。高さ方向は、ランダムでON/OFFを切り替える)
void test2(){
  //ライトボリューム調整
  setLightVolume(1);
  
  for(int i=0; i<5; i++){
    for(int j=0; j<5; j++){
      //光らせる高さの指定
      setLightHeight(0, random(0,2)==1 ? true : false);
      setLightHeight(1, random(0,2)==1 ? true : false);
      setLightHeight(2, random(0,2)==1 ? true : false);
      setLightHeight(3, random(0,2)==1 ? true : false);
      setLightHeight(4, random(0,2)==1 ? true : false);

      //点で描画する
      drawPoint(i,j);
      delay(100);
      clearPlaneAll();
    }   
  }
}

//上に上がっていく雨の表現を行う
//起点を複数指定できる。
//場所に応じて平面の光の大きさを変えることができる。
//関数で一つの光が上に上がっていくまでとする
void perform_uprain(){
  //起点の場所を決める
  int vpos[2] = {2,2};
  int hpos = 0; //hposは、0〜4

  //光の高さをを変えていく
  for(int i=0; i<5; i++){
    //場所に応じて、光の大きさを変える.未対応

    sprintf(BUF, "height %d", i);
    Serial.println(BUF);
    setLightHeight(i, true);

    
    setLightVolume(1);
    drawCircle(vpos[0], vpos[1], 1, true);
    delay(100);
    clearAll();
  }
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
  sawai_proc();
  /*
  setLightVolume(0.1);
  //実行するものに対して、コメントを外す。そのうち、シリアル経由でパソコンから切り替えられるようにする。
  for (int i=0;i<5;i++)
  {drawPoint(i,4);

setLightHeight(1, true);delay(500);
setLightHeight(1, false);delay(500);
clearAll();
 }
 */
}
