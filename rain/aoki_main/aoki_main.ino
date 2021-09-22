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

//planePoint(0,0,true);(x軸,y軸,つける)
//点の描画
//x,y:描画する位置(0〜4)
//lightVol: 光の強度(0〜1)
void drawPoint(int x, int y, float lightVol){
  if(x<0 || 4<x || y<0 || 4<y){
    sprintf(BUF, "Input value is out of range %d %d", x, y);
    Serial.println(BUF);
  }

  int ch = 6+x+5*y;
  int val=0;
  if(lightVol > 0){
    val = int(lightVol*MAX_LIGHT_VOLUME);
  }else{
    val = 0;
  }
  sprintf(BUF, "drawPoint x[%d] y[%d] ch[%d] val[%d]", x, y, ch, val);
  Serial.println(BUF);
  dmx_master.setChannelValue(ch, val);
}

//planeAll(true);
//平面の描写
//fg: ONの場合(true), OFFの場合(false)
void planeAll(bool fg) {
  for (int i = 6; i <= 30; i++) {
    dmx_master.setChannelValue(i, fg ? MAX_LIGHT_VOLUME : 0);
  }
}

//平面を全て消す
void clearPlaneAll(){
  for(int i=6; i<=30; i++){
    dmx_master.setChannelValue(i, 0);
  }
}

//planeCircle(2,2,2,true);
//円の描画
//x, y:中心
//radius:半径
//fillFg:円の内側を塗りつぶす場合(true), 塗りつぶさない場合(false)
// example : (中心座標(x, y) = (2, 2), 半径r = 2, 塗りつぶし = on)
// int x=2;
// int y=2;
// float radius=2;
// bool fillFg=true;
// float lightVol 光の強度
void drawCircle(int x, int y, float radius, bool fillFg, float lightVol){
  float dist;
  char buf[10];
 
  //x, yを起点にして、radiusの範囲を走査して、半径の内側に入っているかを確認する
  for(int i=x-radius; i<=x+radius; i++){
    for(int j=y-radius; j<=y+radius; j++){
      dist = pow(i-x, 2)+pow(j-y, 2);
      
      /*debug
      dtostrf(radius,10,3,buf);  
      sprintf(BUF, "drawCircle1 %d %d %d %d %s", x, y, i, j, buf);
      Serial.print(BUF);
      dtostrf(dist,10,3,buf);  
      sprintf(BUF, " %s", buf);
      Serial.println(BUF);
      */ 
      //全部埋める場合には、距離で判定する。
      if(fillFg && dist <= radius*radius){
        drawPoint(i, j, lightVol);
      }
      
      //全部埋ない場合には、ある範囲の距離で判定する。
      if(!fillFg && dist <= radius*radius && radius>0 &&  pow(radius-1, 2)+pow(radius-1, 2) <= dist ){
        drawPoint(i, j, lightVol);
      }
    } 
  }

  //中を塗らない場合には、半径を一つ小さくしたものを消す
  //if(fillFg == false && radius>0){
  //  drawCircle(x, y, radius-1, true, 0);
  //}
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

//planeSquare(2,2,2,true);:未完
//四角の描画
//x, y:中心
//四角:半径
//fillFg:四角の内側を塗りつぶす場合(true), 塗りつぶさない場合(false)
void drawBox(int x, int y, float radius, bool fillFg){
  drawBox(x, y, radius, fillFg, gLightVolume);
}

//四角の描画
//x, y:中心
//四角:半径
//fillFg:四角の内側を塗りつぶす場合(true), 塗りつぶさない場合(false)
//lightVol:光の強度(0〜1)
void drawBox(int x, int y, float radius, bool fillFg, float lightVol){
  float dist;
  //中を埋める場合
  if(fillFg){ 
    for(int i=x-radius; i<=x+radius; i++){
      for(int j=y-radius; j<=y+radius; j++){
          drawPoint(i, j, lightVol);
      } 
    }
  }else{
  //中を埋めない場合
    for(int i=x-radius; i<=x+radius; i++){
      drawPoint(i, y-radius, lightVol);
      drawPoint(i, y+radius, lightVol);      
    }
    for(int i=y-radius; i<=y+radius; i++){
      drawPoint(x-radius, i, lightVol);
      drawPoint(x+radius, i, lightVol);      
    }
  }
}
  /* 作成者 :青木
  ** 関数名 :diffusionSecond
  ** 引数 : int x          :表示させる点のx座標
            int y          :表示させる点のy座標
            int z          :表示させる点のz座標
            int delay_time :点灯させ続ける時間
            bool All_clear :点の座標情報のクリア
  ** 関数の機能 :*中心から外へ円柱(疎)が拡大する
  　　　　　　　　*
  */
  
//height(4, true);(z軸,つける)
//高さ方向のライトの点灯位置の指定
//height:変更する高さ(0〜4)
//fg: ONの場合(true), OFFの場合(false)
void height(int height, bool fg) {
  dmx_master.setChannelValue(height + 1, fg ? MAX_LIGHT_VOLUME : 0);
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

//heightAll(true);
//高さ方向全て
void heightAll(bool fg) {
  for (int i = 1; i <= 5; i++) {
    dmx_master.setChannelValue(i, fg ? MAX_LIGHT_VOLUME : 0);
  }
}

//高さ方向を全て消す
void clearHeightAll(){
  for(int i=1; i<=5; i++){
    dmx_master.setChannelValue(i, 0);
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

//全部クリアする
void clearAll(){
  for(int i=1; i<=30; i++){
    dmx_master.setChannelValue(i, 0);
  }
}

//メインループ
//test
void loop(){
//diffusionFirst
setLightVolume(1); 
all(false);
int takasa[]={1,1,1,1,1};
heights(takasa);
drawCircle(2,2,0,true,0.02);
delay(600);
planeAll(false);
drawCircle(2,2,1,false,0.02);
delay(600);
planeAll(false);
drawCircle(2,2,2,false,0.02);
delay(600);
planeAll(false);
drawCircle(2,2,3,false,0.02);
delay(600);
planeAll(false);
drawCircle(2,2,4,false,0.02);
delay(600);
all(false);

//diffusionSecond
setLightVolume(1); 
all(false);
heights(takasa);
drawBox(2,2,0,true,0.02);
delay(600);
planeAll(false);
drawBox(2,2,1,false,0.02);
delay(600);
planeAll(false);
drawBox(2,2,2,false,0.02);
delay(600);
planeAll(false);
drawBox(2,2,3,false,0.02);
delay(600);
all(false);
}
