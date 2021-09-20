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
int x=2;
int y=2;
float radius=2;
bool fillFg=true;
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
 

   /*
  ** 作成者 : 澤井
  ** 関数名 : test_drawBox_var2
  ** 引数 : bool fillfg   : boxの中を埋める(true),埋めない(false)
            int delaytime : delaytimeでdelay時間を入力
            int delaytime : delayの時間
            bool delay_on : delay時間がいる場合(delay_on),いらない場合(false)
  ** 関数の機能 : あいはらさんの作ってくださった関数を一部改変し、drawBoxと違いboxが作られる過程を表示できるようにしています。
  */

void test_drawBox_var2(int x, int y, float radius, bool fillFg, int delaytime, bool delay_on){
  float dist;
   //中を埋める場合
  if(fillFg){ 
    for(int i=x-radius/2; i<x+radius/2; i++){
      for(int j=y-radius/2; j<y+radius/2; j++){
          drawPoint(i, j);
         if(delay_on==true)
          delay(delaytime);
      } 
    }
  }
  else{
  //中を埋めない場合
    for(int i=x-radius/2; i<x+radius/2; i++){
      drawPoint(i, y-radius/2);
      drawPoint(i, y+radius/2); 
      if(delay_on==true)
        delay(delaytime);   
    }
    for(int i=y-radius/2; i<y+radius/2; i++){
      drawPoint(x-radius/2, i);
      drawPoint(y+radius/2, i); 
      if(delay_on==true)
        delay(delaytime);   
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
//　　１段目だけ点灯：height=[1,0,0,0]
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
  /* 作成者 :澤井
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
void handler_sawai_part3(int x,int y, int z, int delay_time , bool All_clear){
   if(All_clear)
   {
   drawPoint(x, y);
   setLightHeight(z, true);
   delay(delay_time); 
   clearAll();
   }
   else
   {
   drawPoint(x, y);
   setLightHeight(z, true);
   delay(delay_time); 
   }
}





//メインループ
void loop(){
 
//成長の表現 1 暫定です。実機テストが必要だと思うのでコピペで対応しています 
//clearHeightAll()を使った方がいいのか(後で気づいた)、今のものは使えるのか？チェック待ち
//澤井の完成予想: 光が横に流れていく
setLightVolume(1); 
setLightHeight(2, true);
drawLine(0, 2, 4, 2);
setLightHeight(2, false);
setLightHeight(4, true);
drawLine(3,2,4,4);
setLightHeight(4, true);
setLightHeight(0, true);
drawLine(1, 1, 3, 3);
setLightHeight(0, false);
setLightHeight(1, true);
drawLine(3,2,4,4);
setLightHeight(2, true);
drawLine(0, 2, 4, 2);
setLightHeight(2, false);
setLightHeight(4, true);
drawLine(3,2,4,4);
setLightHeight(4, true);
setLightHeight(0, true);
drawLine(1, 1, 3, 3);
setLightHeight(0, false);
setLightHeight(1, true);
drawLine(3,2,4,4);

//成長の表現part2
setLightHeight(2, true);
drawCircle(2, 2, 2, true);
clearHeightAll();
delay(5000);
for(int i=0.04;i<1;i+=0.04)
{
 setLightVolume(i);
 setLightHeight(2, true);
 drawPoint(0,3);
 drawPoint(3,3);
 drawPoint(4,3);
 drawPoint(3,3);
 delay(50);
 clearAll();
}
setLightHeight(4, true);
drawCircle(4, 4, 3, true);
//この辺の扱いが難しい
//drawCircle(0,false);にするとどうなる？heightだと思うけど？？
clearHeightAll();
setLightHeight(0, true);
drawCircle(0, 0, 4, true);
delay(300);
clearHeightAll();
setLightHeight(2, true);
drawCircle(3, 3, 2, true);
delay(300);
//これぐらいで,追加予定あり

//part3 点をだんだん増やす作業
setLightVolume(0.04);
handler_sawai_part3(2,2,2,300,true);

handler_sawai_part3(3,4,2,300,true);

handler_sawai_part3(0,0,4,400,false);
handler_sawai_part3(0,4,4,300,true);
//TEST 繰り返し構文で setLightVolume上げてぴかぴかさせる？(予定:現状後回し)別の段でしてあげるときれいかも

handler_sawai_part3(1,2,0,400,false);
handler_sawai_part3(3,3,0,200,false);
handler_sawai_part3(0,1,0,400,true);

handler_sawai_part3(2,3,3,400,false);
handler_sawai_part3(2,4,3,200,false);
handler_sawai_part3(0,3,3,400,false);
handler_sawai_part3(0,4,3,400,false);
handler_sawai_part3(1,0,3,300,true);


handler_sawai_part3(2,0,1,400,false);
handler_sawai_part3(4,1,1,200,false);
handler_sawai_part3(3,1,1,400,false);
handler_sawai_part3(3,0,1,400,false);
handler_sawai_part3(1,2,1,200,false);
handler_sawai_part3(3,4,1,400,false);
handler_sawai_part3(1,2,1,200,false);
handler_sawai_part3(3,4,1,300,true);


handler_sawai_part3(0,3,4,400,false);
handler_sawai_part3(2,4,4,200,false);
handler_sawai_part3(0,3,4,400,false);
handler_sawai_part3(0,4,4,400,false);
handler_sawai_part3(1,0,4,300,false);
handler_sawai_part3(2,0,4,400,false);
handler_sawai_part3(4,1,4,200,false);
handler_sawai_part3(3,1,4,400,false);
handler_sawai_part3(3,0,4,400,false);
handler_sawai_part3(1,2,4,200,false);
handler_sawai_part3(3,4,4,400,false);
handler_sawai_part3(1,2,4,200,false);
handler_sawai_part3(3,4,4,300,true);


//part4成長
 //成長してる茎を描く
setLightVolume(0.04);
int takasa[]={1,1,1,1,1};
 setLightHeights(takasa);
 

  for(int i=0; i<5; i++){
    for(int j=0; j<5; j+=2){
      drawPoint(i,j);
      sprintf(BUF, "%d %d", i, j);
      Serial.println(BUF);
      delay(50);
      clearPlaneAll();
    }   
  }

}
