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

//ライトボリュームの設定
//volume:値(0〜1までの少数)
void setLightVolume(float volume){
  gLightVolume = volume;
}

//全部クリアする
void clearAll(){
  for(int i=1; i<=30; i++){
    dmx_master.setChannelValue(i, 0);
  }
}

//平面を全て消す
void clearPlaneAll(){
  for(int i=6; i<=30; i++){
    dmx_master.setChannelValue(i, 0);
  }
}

//高さ方向を全て消す
void clearHeightAll(){
  for(int i=1; i<=5; i++){
    dmx_master.setChannelValue(i, 0);
  }
}

//高さ方向のライトの点灯位置の指定
//height:変更する高さ(0〜4)
//fg: ONの場合(true), OFFの場合(false)
void setLightHeight(int height, bool fg){ 
  dmx_master.setChannelValue(height+1, fg ? MAX_LIGHT_VOLUME : 0);  
}

//heights(0,0,0,0,0, true);：未着手
//高さ方向のライトの点灯位置の指定(複数指定)←間違い
//height:変更する高さ.要素が4つの配列で指定する
//ex. 全部クリア：height=[0,0,0,0,0]
//    全部点灯：height=[1,1,1,1,1]
//　　１段目だけ点灯：height=[1,0,0,0]
void heights(int *height) {
  for (int i = 0; i < 5; i++) {
    dmx_master.setChannelValue(i + 1, (height[0] == 1) ?  MAX_LIGHT_VOLUME : 0);
  }
}

//all(true);(つける)
//全部
//fg: ONの場合(true), OFFの場合(false)
void all(bool fg) {
  for (int i = 1; i <= 30; i++) {
    dmx_master.setChannelValue(i, fg ? MAX_LIGHT_VOLUME : 0);
  }
}

//height(4, true);(z軸,つける)
//高さ方向のライトの点灯位置の指定
//height:変更する高さ(0〜4)
//fg: ONの場合(true), OFFの場合(false)
void height(int height, bool fg) {
  dmx_master.setChannelValue(height + 1, fg ? MAX_LIGHT_VOLUME : 0);
}

//heightAll(true);
//高さ方向全て
void heightAll(bool fg) {
  for (int i = 1; i <= 5; i++) {
    dmx_master.setChannelValue(i, fg ? MAX_LIGHT_VOLUME : 0);
  }
}

//planeCircle(2,2,2,true);:未完
//円の描画
//x, y:中心
//radius:半径
//fillFg:円の内側を塗りつぶす場合(true), 塗りつぶさない場合(false)
void planeCircle(int x, int y, float radius, bool fillFg) {
  float dist;
  //x, yを起点にして、radiusの範囲を走査して、半径の内側に入っているかを確認する
  for (int i = x - radius / 2; i < x + radius / 2; i++) {
    for (int j = y - radius / 2; j < y + radius / 2; j++) {
      dist = (i - x) * (i - x) + (i - y) * (i - y);
      if (dist <= radius * radius) {
        planePoint(0, 0, true);
      }
    }
  }
}

  /* 作成者 :青木
  ** 関数名 :diffusionFirst
  ** 引数 : int x          :表示させる点のx座標
            int y          :表示させる点のy座標
            int z          :表示させる点のz座標
            int delay_time :点灯させ続ける時間
            bool All_clear :点の座標情報のクリア
  ** 関数の機能 :*中心から外へ円柱(疎)が拡大する
  * //aaaa
  　　　　　　　　*
  */


//メインループ
//test
void loop(){
setLightVolume(1); 
all(false);
planeCircle(2,2,0,false);
delay(600);
}
