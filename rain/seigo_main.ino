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

//点の描画
//x,y:描画する位置(0〜4)
void drawPoint(int x, int y){
  if(x<0 || 4<x || y<0 || 4<y){
    sprintf(BUF, "Input value is out of range %d %d", x, y);
    Serial.println(BUF);
  }

  int ch = 6+x+5*y;
  int val = int(gLightVolume*MAX_LIGHT_VOLUME);
  sprintf(BUF, "drawPoint x[%d] y[%d] ch[%d] val[%d]", x, y, ch, val);
  Serial.println(BUF);
  dmx_master.setChannelValue(ch, val);
}

//円の描画
//x, y:中心
//radius:半径
//fillFg:円の内側を塗りつぶす場合(true), 塗りつぶさない場合(false)

void drawCircle(int x, int y, float radius, bool fillFg){
  float dist;
  //x, yを起点にして、radiusの範囲を走査して、半径の内側に入っているかを確認する
  for(int i=x-radius/2; i<x+radius/2; i++){
    for(int j=y-radius/2; j<y+radius/2; j++){
      dist = (i-x)*(i-x)+(i-y)*(i-y);
      if(dist <= radius*radius){
        drawPoint(i, j);
      }
    } 
  }
}

//四角の描画
//x, y:中心
//四角:半径
//fillFg:四角の内側を塗りつぶす場合(true), 塗りつぶさない場合(false)
void drawBox(int x, int y, float radius, bool fillFg){
  float dist;
  //中を埋める場合
  if(fillFg){ 
    for(int i=x-radius/2; i<x+radius/2; i++){
      for(int j=y-radius/2; j<y+radius/2; j++){
          drawPoint(i, j);
      } 
    }
  }else{
  //中を埋めない場合
    for(int i=x-radius/2; i<x+radius/2; i++){
      drawPoint(i, y-radius/2);
      drawPoint(i, y+radius/2);      
    }
    for(int i=y-radius/2; i<y+radius/2; i++){
      drawPoint(x-radius/2, i);
      drawPoint(y+radius/2, i);      
    }
  }
}

//線の描画
//sPosX:開始点X
//sPosY:開始点Y
//ePosX:終了点X
//ePosY:終了点Y
void drawLine(int sPosX, int sPosY, int ePosX, int ePosY){
  //スタートよりもエンドの方が値が大きいこと
  if(sPosX< ePosX  || sPosY< ePosY){
    sprintf(BUF, "Input value is wrong %d %d %d %d", sPosX, sPosY, ePosX, ePosY);
    Serial.println(BUF);
  }

  //まずは、直線だけを描画
  if(sPosX == ePosX){
     for(int i=sPosY; i<=ePosY; i++){
      drawPoint(sPosX, i);      
     }
  }else if(sPosY == ePosY){
     for(int i=sPosX; i<=ePosX; i++){
      drawPoint(i, sPosY);      
     }
  }else{
      Serial.println("drawLine. not supported");  
  }
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

//高さ方向のライトの点灯位置の指定(複数指定)
//height:変更する高さ.要素が4つの配列で指定する
//ex. 全部クリア：height=[0,0,0,0,0]
//    全部点灯：height=[1,1,1,1,1]
//    １段目だけ点灯：height=[1,0,0,0,0]
void setLightHeights(int *height){
  for(int i=0; i<5; i++){
    dmx_master.setChannelValue(i+1, (height[0]==1) ?  MAX_LIGHT_VOLUME : 0);  
  }
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


//点の描画(複数同時)
//float pos: 各位置の光の強さが入った二次元配列([[0, 0, 0, 0, 0]〜[0, 0, 0, 0, 0])
//int lightFg: 1:点灯、0:消灯
void drawPoints(float lightVol[][5]){
  for(int i=0; i<5; i++){
    for(int j=0; j<5; j++){
      int ch = 6+i+5*j;
      int val = 0;
  
      if(lightVol[i][j] > 0){
        val = int(lightVol[i][j]*MAX_LIGHT_VOLUME);
      }else{
        val = 0;
      }
      Serial.println(BUF);
      dmx_master.setChannelValue(ch, val);
    }
  }
}

/*
** 関数名 : allLighting
** 引数 : なし
** 戻り値 : なし
** 関数の機能 : 全点灯
** 作者: seigo
** 日付: 2021/09/23
*/
void allLighting (){
  int heights[5]={1,1,1,1,1};
  setLightHeights(heights);
  float plane[][5]={
      {1,1,1,1,1},
      {1,1,1,1,1},
      {1,1,1,1,1},
      {1,1,1,1,1},
      {1,1,1,1,1}
    };
  drawPoints(plane);
}

/*
** 関数名 : fadeIn
** 引数 : int fade : フェードインのスピード(基準:20)
** 戻り値 : なし
** 関数の機能 : フェードインで全点灯
** 作者: seigo
** 日付: 2021/09/23
*/
void fadeIn (int fade){
  int heights[5]={1,1,1,1,1};
  setLightHeights(heights);
  for(float i=0; i<=1; i+=0.01){
    float plane[][5]={
      {i,i,i,i,i},
      {i,i,i,i,i},
      {i,i,i,i,i},
      {i,i,i,i,i},
      {i,i,i,i,i}
    };
    drawPoints(plane);
    delay(fade);
  }
}

/*
** 関数名 : deathFirst
** 引数 : int time : ライトが変わるスピード(基準:500)
** 引数 : int type : 表現の種類(0:通常 1:前半のみ 2:後半のみ)
** 戻り値 : なし
** 関数の機能 : 死の表現1つ目、上段から下段に消えていき、上段から下段についていく。
5*5*5の光っている箱と暗い箱が交互に下に押し出され、消えていくイメージ
** 作者: seigo
** 日付: 2021/10/03
*/
void deathFirst(int time, int type){
  //上から一段づつ消す
  for(int i=4; i>=0; i--){
    if (type == 2) break;
    setLightHeight(i, false);
    delay(time);
  }
  //上から一段づつ点ける
  for(int i=4; i>0; i--){
    if (type == 1) break;
    setLightHeight(i, true);
    delay(time);
  }
}

/*
** 関数名 : deathSecond
** 引数 : int time : 柱が消えるスピード(基準:100)
** 引数 : int type : 表現の種類(0:通常 1:前半のみ 2:後半のみ)
** 戻り値 : なし
** 関数の機能 : 死の表現2つ目、柱がランダムに消えていき、ランダムについていく
** 作者: seigo
** 日付: 2021/10/03
*/
void deathSecond(int time, int type){
  int downNumbers[25]={25,16,11,15,28,30,20,14,23,22,26,24,9,12,21,27,7,18,13,8,10,19,17,29,6};
  for(int i=0; i<25; i++){
    if (type == 2) break;
    dmx_master.setChannelValue(downNumbers[i], 0);
    delay(time);
  }
  //柱がランダム(っぽく)ついていく
  int upNumbers[25]={12,16,7,20,30,27,6,22,13,17,18,11,10,9,25,15,8,26,24,19,14,21,23,28,29};
  for(int i=0; i<25; i++){
    if (type == 1) break;
    dmx_master.setChannelValue(upNumbers[i], MAX_LIGHT_VOLUME);
    delay(time);
  }
}

/*
** 関数名 : deathThird
** 引数 : int time : 立方体が消えるスピード(基準:600)
** 引数 : int fade : フェードインのスピード(基準:20)
** 戻り値 : なし
** 関数の機能 : 死の表現3つ目、外側から立方体が消えていき、フェードインで全点灯
** 作者: seigo
** 日付: 2021/09/22
*/
void deathThird(int time, int fade){
  //外側から立方体が消えていく
  //第一段階
  dmx_master.setChannelValue(1, 0);
  dmx_master.setChannelValue(5, 0);
  for(int i=6; i<=30; i++){
    if(! ((i>=12 && i<=14) || (i>=17 && i<=19) || (i>=22 && i<=24))) dmx_master.setChannelValue(i, 0);
  }
  delay(time);
  //第二段階
  dmx_master.setChannelValue(2, 0);
  dmx_master.setChannelValue(4, 0);
  for(int i=12; i<=24; i++){
    if(i!=18) dmx_master.setChannelValue(i, 0);
  }
  delay(time);
  //全消灯
  clearAll();
  delay(time);
  //フェードインで全点灯
  fadeIn(fade);
}

/*
** 関数名 : diffusionThird
** 引数 : int fade : フェードアウト・インのスピード(基準:10)
** 戻り値 : なし
** 関数の機能 : 分解の表現3つ目、全てのライトがフェードアウトし、フェードインで全点灯
** 作者: seigo
** 日付: 2021/09/22
*/
void diffusionThird(int fade){
  int heights[5]={1,1,1,1,1};
  setLightHeights(heights);
  for(float i=1; i>=0; i-=0.01){
    float plane[][5]={
      {i,i,i,i,i},
      {i,i,i,i,i},
      {i,i,i,i,i},
      {i,i,i,i,i},
      {i,i,i,i,i}
    };
    drawPoints(plane);
    delay(fade);
  }
  fadeIn(fade);
}

//メインループ
void loop(){
  //死の表現: 約45s
  //allLighting();
  delay(500);
  //deathFirst(600);
  //deathSecond(200);
  //deathThird(600, 20);
  //diffusionThird(20);

  //clearAll();
}

