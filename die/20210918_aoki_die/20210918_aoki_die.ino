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

void fromTopToBottomOut(int t, bool fg) {
  for (int z = 4; z >= 0; z--) {
    height(z, false);
    delay(t);
    height(z, fg ? true : false);
    delay(t);
  }
  heightAll(false);
}
  /* 作成者 :青木
  ** 関数名 : handler_sawai_part3
  ** 引数 : int x          :表示させる点のx座標
            int y          :表示させる点のy座標
            int z          :表示させる点のz座標
            int delay_time :点灯させ続ける時間
            bool All_clear :点の座標情報のクリア
  ** 関数の機能 : 点の表示に特化した関数です。
                 x,y,z座標を入力することで簡単に光る位置を設定できることができます。
                **この関数は削除対象です。
  */


//メインループ
void loop(){
setLightVolume(1); 
all(false);
delay(600);
fromTopToBottomOut(300,false);

}
