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
  all(false);
}

//ライトボリュームの設定
//volume:値(0〜1までの少数)
void setLightVolume(float volume){
  gLightVolume = volume;
}

/*---ブロック一覧-----------------------------------------------------------*/
/*---xyz指定-----------------------------------------------------------*/
  //all(true);(つける)

/*---xy指定×z指定------------------------------------------------------------------*/
/*---xy指定基礎-----------------------------------------------------------*/  
  //planePoint(0,0,true);(x軸,y軸,つける)
  //planeLine(sX,sY,eX,eY,true);
  //planeAll(true);

/*--z指定基礎-----------------------------------------------------------*/  
  //height(4, true);(z軸,つける)
  //heightRandom(300,true,5);(時間,残す,繰り返し回数)：未着手
  //heightsRandom(2,300,true,3);(同時出力点の個数,時間,残す,繰り返し回数)：未着手
  //heights(0,0,0,0,0, true);：未着手
  //heightAll(true);

/*--z指定一次改変-----------------------------------------------------------*/
  //fromTopToBottom(300,false);(時間,残さない)
  //fromBottomToTop(300,false);

/*--z指定二次改変-----------------------------------------------------------*/
  //heightRotatePointOfSquareTrajectory(right);(時計回り)：未着手

  //expansionZ(2,false);(中心点のz座標,残さない):未着手
  //zoomOutZ(2,false);(中心点のz座標,残さない):未着手

  
/*---xy指定一次改変-----------------------------------------------------------*/
  //pointX_RandomX(0,300,true,5);(y軸,時間,残す,繰り返し回数)：未完,シード値に現在時刻を使いたい
  //pointX_RandomY(0,300,true,5);(x軸,時間,残す,繰り返し回数)：未完,シード値に現在時刻を使いたい
  //planePointRandom(300,true,25);(時間,残す,繰り返し回数)：未完,シード値に現在時刻を使いたい
  //planePointsRandom(5,300,true,5);(同時出力点の個数,時間,残す,繰り返し回数)：未完,シード値に現在時刻を使いたい

  //planeSixToThity(300);

  //fromFrontToBack(0,300,false);(x軸,時間,残さない)
  //fromFrontToBackRandom(300,false,5);(時間,残さない,回数)：未着手
  //fromFrontToBacks(0,0,0,0,0,300,true);(x[0]off,x[1]off,x[2]off,x[3]off,x[4]off,時間,残す)：未着手
  //fromFrontToBackAll(300,false);
  
  //fromBackToFront(0,300,false);
  //fromBackToFrontRandom(300,false,5);：未着手
  //fromBackToFronts(0,0,0,0,0,300,true);：未着手
  //fromBackToFrontAll(300,false);
  
  //fromLeftToRight(0,300,false);(y軸,時間,残さない)
  //fromLeftToRightRandom(300,false,5);：未着手
  //fromLeftToRights(0,0,0,0,0,300,true);：未着手
  //fromLeftToRightAll(300,false);
  
  //fromRightToLeft(0,300,false);
  //fromRightToLeftRandom(300,false,5);：未着手
  //fromRightToLefts(0,0,0,0,0,300,true);：未着手
  //fromRightToLeftAll(300,false);
  
/*---xy指定二次改変-----------------------------------------------------------*/
  //planeCircle(2,2,2,true);(中心点のx座標,中心点のy座標,半径,残す):未完
  //planeSquare(2,2,2,true);(中心点のx座標,中心点のy座標,半径,残す):未完
  //planeRotatePointOfSquareTrajectory(right);(時計回り)：未着手
  //planeRotateTwoPointsOfSquareTrajectory(right);(時計回り)：未着手
  //planeRotateBoxOfSquareTrajectory(right);(時計回り)：未着手
  //planeRotateTwoBoxesOfSquareTrajectory(right);(時計回り)：未着手
  
  //expansionX(2,2,false);(中心点のx座標,中心点のy座標,残さない):未着手
  //expansionY(2,2,false);(中心点のx座標,中心点のy座標,残さない):未着手
  //expansionXY(2,2,false);(中心点のx座標,中心点のy座標,残さない):未着手

  //zoomOutX(2,2,false);(中心点のx座標,中心点のy座標,残さない):未着手
  //zoomOutY(2,2,false);(中心点のx座標,中心点のy座標,残さない):未着手
  //zoomOutXY(2,2,false);(中心点のx座標,中心点のy座標,残さない):未着手

/*---xy指定×z指定改変-----------------------------------------------------------*/
  //OneToOneHundredTwentyFive(300);
  //perform_uprain();
  
  //rainOneDrops(50,5,false,true);(時間,回数,残さない,下がる)：未着手
  //rainTwoDrops(50,10,false,false);(時間,回数,残さない,上がる)：未着手

  //waterFall(50,5,false,true);(時間,回数,残さない,下がる)：未着手
  //twoWaterFalls(50,10,true);(時間,回数,下がる)：未着手
  
  //expansionCube(2,2,2,false);(中心点のx座標,中心点のy座標,中心点のz座標,残さない):未着手
  //zoomOutCube(2,2,2,false);(中心点のx座標,中心点のy座標,中心点のz座標,残さない):未着手
  

/*---計算式-----------------------------------------------------------*/
/*---xyz指定-----------------------------------------------------------*/
//all(true);(つける)
//全部
//fg: ONの場合(true), OFFの場合(false)
void all(bool fg){
  for(int i=1; i<=30; i++){
    dmx_master.setChannelValue(i, fg ? MAX_LIGHT_VOLUME : 0);
  }
}


/*---xy指定×z指定------------------------------------------------------------------*/
/*---xy指定基礎-----------------------------------------------------------*/  
//planePoint(0,0,true);(x軸,y軸,つける)
//点の描画
//x,y:描画する位置(0〜4)
//fg: ONの場合(true), OFFの場合(false)
void planePoint(int x, int y,bool fg){
  if(x<0 || 4<x || y<0 || 4<y){
    sprintf(BUF, "Input value is out of range %d %d", x, y);
    Serial.println(BUF);
  }

  int ch = 6+x+5*y;
  int val = int(gLightVolume*MAX_LIGHT_VOLUME);
  sprintf(BUF, "planePoint x[%d] y[%d] ch[%d] val[%d]", x, y, ch, val);
  Serial.println(BUF);
  dmx_master.setChannelValue(ch, fg?val:0);
}

//planeLine(sX,sY,eX,eY,true);
//線の描画
//sPosX:開始点X
//sPosY:開始点Y
//ePosX:終了点X
//ePosY:終了点Y
void planeLine(int sPosX, int sPosY, int ePosX, int ePosY,bool fg){
  //スタートよりもエンドの方が値が大きいこと
  if(sPosX< ePosX  || sPosY< ePosY){
    sprintf(BUF, "Input value is wrong %d %d %d %d", sPosX, sPosY, ePosX, ePosY);
    Serial.println(BUF);
  }

  //まずは、直線だけを描画
  if(sPosX == ePosX){
     for(int i=sPosY; i<=ePosY; i++){
      planePoint(sPosX, i,fg?true:false);     
     }
  }else if(sPosY == ePosY){
     for(int i=sPosX; i<=ePosX; i++){
      planePoint(i, sPosY,fg?true:false);      
     }
  }else{
      Serial.println("planeLine. not supported");  
  }
}

//planeAll(true);
//平面の描写
//fg: ONの場合(true), OFFの場合(false)
void planeAll(bool fg){
  for(int i=6; i<=30; i++){
    dmx_master.setChannelValue(i,fg ? MAX_LIGHT_VOLUME : 0);
  }
}

/*--z指定基礎-----------------------------------------------------------*/  
//height(4, true);(z軸,つける)
//高さ方向のライトの点灯位置の指定
//height:変更する高さ(0〜4)
//fg: ONの場合(true), OFFの場合(false)
void height(int height, bool fg){ 
  dmx_master.setChannelValue(height+1, fg ? MAX_LIGHT_VOLUME : 0);  
}

//heightsRandom(2,300,true,3);(同時出力点の個数,時間,残す,繰り返し回数)：未着手

//heights(0,0,0,0,0, true);：未着手
//高さ方向のライトの点灯位置の指定(複数指定)←間違い
//height:変更する高さ.要素が4つの配列で指定する
//ex. 全部クリア：height=[0,0,0,0,0]
//    全部点灯：height=[1,1,1,1,1]
//　　１段目だけ点灯：height=[1,0,0,0]
void heights(int *height){
  for(int i=0; i<5; i++){
    dmx_master.setChannelValue(i+1, (height[0]==1) ?  MAX_LIGHT_VOLUME : 0);  
  }
}

//heightAll(true);
//高さ方向全て
void heightAll(bool fg){
  for(int i=1; i<=5; i++){
    dmx_master.setChannelValue(i, fg ? MAX_LIGHT_VOLUME : 0);
  }
}
//heightRandom(300,true,5);(時間,残す,繰り返し回数)：未着手
//高さ方向ランダム

/*--z指定一次改変-----------------------------------------------------------*/
//fromTopToBottom(300,false);(時間,残さない)
//上から下への描写
//fg:残す場合(true), 残さない場合(false)
//time:delayの時間
void fromTopToBottom(int t,bool fg){
  for(int z=4;z>=0;z--){
    height(z, true);
    delay(t);
    height(z,fg ? true : false);
    delay(t);
  }
  heightAll(false);
}

//fromBottomToTop(300,false);
//下から上への描写
//fg:残す場合(true), 残さない場合(false)
//time:delayの時間
void fromBottomToTop(int t,bool fg){
  for(int z=0;z<=4;z++){
    height(z, true);
    delay(t);
    height(z,fg ? true : false);
    delay(t);
  }
  heightAll(false);
}

/*--z指定二次改変-----------------------------------------------------------*/
//heightRotatePointOfSquareTrajectory(right);(時計回り)：未着手
//高さ方向に点を動かす。四角の軌跡

//expansionZ(2,false);(中心点のz座標,残さない):未着手
//高さ方向に拡大

//zoomOutZ(2,false);(中心点のz座標,残さない):未着手
//高さ方向に縮小


/*---xy指定一次改変-----------------------------------------------------------*/
//pointY_RandomX(0,300,true,5);(y軸,時間,残す,繰り返し回数)：未完,シード値に現在時刻を使いたい
//y軸指定,ランダムなx値の選定
void pointY_RandomX(int y,int t){
  int val = int(gLightVolume*MAX_LIGHT_VOLUME);
  int x=random(0,5);
  int ch = 6+x+5*y;
  dmx_master.setChannelValue ( ch, val );
  delay(t);
  dmx_master.setChannelValue ( ch, 0 );
  delay(t);
}  

//pointX_RandomY(0,300,true,5);(x軸,時間,残す,繰り返し回数)：未完,シード値に現在時刻を使いたい
//x軸指定,ランダムなy値の選定
void pointX_RandomY(int x,int t){
  int val = int(gLightVolume*MAX_LIGHT_VOLUME);
  int y=random(0,5);
  int ch = 6+x+5*y;
  dmx_master.setChannelValue ( ch, val );
  delay(t);
  dmx_master.setChannelValue ( ch, 0 );
  delay(t);
  
}

//planePointRandom(300,true,25);(時間,残す,繰り返し回数)：未完,シード値に現在時刻を使いたい
//ランダムな点の描写
void planePointRandom(int t){
  int val = int(gLightVolume*MAX_LIGHT_VOLUME);
  dmx_master.setChannelValue ( random(6,31), val );
  delay(t);
  dmx_master.setChannelValue ( random(6,31), 0 );
  delay(t);
}

//planePointsRandom(5,300,true,5);(同時出力点の個数,時間,残す,繰り返し回数)：未完,シード値に現在時刻を使いたい
//ランダムな複数の点の描写

//planeSixToThity(300);
//6から30までを打つ。(1段目のライトを、個別に光らせる)
void planeSixToThity(int t){

  for(int i=0; i<5; i++){
    for(int j=0; j<5; j++){
      planePoint(i,j,true);
      delay(t);
      planeAll(false);
    }   
  }
}

//fromFrontToBack(0,300,false);(x軸,時間,残さない)
//手前から奥への描写(ひとつの軸)
//fg:残す場合(true), 残さない場合(false)
//time:delayの時間
void fromFrontToBack(int x,int t,bool fg){
  for(int y=0;y<=4;y++){
    int ch = 6+x+5*y;
    int val = int(gLightVolume*MAX_LIGHT_VOLUME);
    dmx_master.setChannelValue(ch, val);
    delay(t);
    dmx_master.setChannelValue(ch, fg?val:0); 
    delay(t);
  }
  planeAll(false);
}

//fromFrontToBackRandom(300,false,5);(時間,残さない,回数)：未着手
//手前から奥へのランダムな描写

//fromFrontToBacks(0,0,0,0,0,300,true);(x[0]off,x[1]off,x[2]off,x[3]off,x[4]off,時間,残す)：未着手
//手前から奥への複数個同時の描写

//fromFrontToBackAll(300,false);
//手前から奥への描写(全ての点)
//fg:残す場合(true), 残さない場合(false)
//time:delayの時間
void fromFrontToBackAll(int t,bool fg){
  for(int y=0;y<=4;y++){
    planeLine(0,y,4,y,true);
    delay(t);
    planeLine(0,y,4,y,fg?true : false);
    delay(t);
  }
  planeAll(false);
}

//fromBackToFront(0,300,false);
//奥から手前への描写(ひとつの軸)
//fg:残す場合(true), 残さない場合(false)
//time:delayの時間
void fromBackToFront(int x,int t,bool fg){
  for(int y=4;y>=0;y--){
    int ch = 6+x+5*y;
    int val = int(gLightVolume*MAX_LIGHT_VOLUME);
    dmx_master.setChannelValue(ch, val);
    delay(t);
    dmx_master.setChannelValue(ch, fg?val:0); 
    delay(t);
  }
  planeAll(false);
  
}

//fromBackToFrontRandom(300,false,5);：未着手
//奥から手前へのランダムな描写

//fromBackToFronts(0,0,0,0,0,300,true);：未着手
//奥から手前への複数個同時の描写

//fromBackToFrontAll(300,false);
//奥から手前への描写(全ての点)
//fg:残す場合(true), 残さない場合(false)
//time:delayの時間
void fromBackToFrontAll(int t,bool fg){
  for(int y=4;y>=0;y--){
    planeLine(0,y,4,y,true);
    delay(t);
    planeLine(0,y,4,y,fg?true:false);
    delay(t);
  }
  planeAll(false);
}

//fromLeftToRight(0,300,false);(y軸,時間,残さない)
//左から右への描写(ひとつの軸)
//fg:残す場合(true), 残さない場合(false)
//time:delayの時間
void fromLeftToRight(int y,int t,bool fg){
  for(int x=0;x<=4;x++){
    int ch = 6+x+5*y;
    int val = int(gLightVolume*MAX_LIGHT_VOLUME);
    dmx_master.setChannelValue(ch, val);
    delay(t);
    dmx_master.setChannelValue(ch, fg?val:0); 
    delay(t);
  }
  planeAll(false);
}

//fromLeftToRightRandom(300,false,5);：未着手
//左から右へのランダムな描写

//fromLeftToRights(0,0,0,0,0,300,true);：未着手
//左から右への複数個同時の描写

//fromLeftToRightAll(300,false);
//左から右への描写(全ての点)
//fg:残す場合(true), 残さない場合(false)
//time:delayの時間
void fromLeftToRightAll(int t,bool fg){
  for(int x=0;x<=4;x++){
    planeLine(x,0,x,4,true);
    delay(t);
    planeLine(x,0,x,4,fg?true:false);
    delay(t);
  }
  planeAll(false);
}

//fromRightToLeft(0,300,false);
//右から左への描写(ひとつの軸)
//fg:残す場合(true), 残さない場合(false)
//time:delayの時間
void fromRightToLeft(int y,int t,bool fg){
  for(int x=4;x>=0;x--){
    int ch = 6+x+5*y;
    int val = int(gLightVolume*MAX_LIGHT_VOLUME);
    dmx_master.setChannelValue(ch, val);
    delay(t);
    dmx_master.setChannelValue(ch, fg?val:0); 
    delay(t);
  }
  planeAll(false);
}

//fromRightToLeftRandom(300,false,5);：未着手
//右から左へのランダムな描写

//fromRightToLefts(0,0,0,0,0,300,true);：未着手
//右から左への複数個同時の描写

//fromRightToLeftAll(300,false);
//右から左への描写(全ての点)
//fg:残す場合(true), 残さない場合(false)
//time:delayの時間
void fromRightToLeftAll(int t,bool fg){
  for(int x=4;x>=0;x--){
    planeLine(x,0,x,4,true);
    delay(t);
    planeLine(x,0,x,4,fg?true:false);
    delay(t);
  }
  planeAll(false);
}

/*---xy指定二次改変-----------------------------------------------------------*/
//planeCircle(2,2,2,true);:未完
//円の描画
//x, y:中心
//radius:半径
//fillFg:円の内側を塗りつぶす場合(true), 塗りつぶさない場合(false)
void planeCircle(int x, int y, float radius, bool fillFg){
  float dist;
  //x, yを起点にして、radiusの範囲を走査して、半径の内側に入っているかを確認する
  for(int i=x-radius/2; i<x+radius/2; i++){
    for(int j=y-radius/2; j<y+radius/2; j++){
      dist = (i-x)*(i-x)+(i-y)*(i-y);
      if(dist <= radius*radius){
        planePoint(0,0,true);
      }
    } 
  }
}

//planeSquare(2,2,2,true);:未完
//四角の描画
//x, y:中心
//四角:半径
//fillFg:四角の内側を塗りつぶす場合(true), 塗りつぶさない場合(false)
void planeSquare(int x, int y, float radius, bool fillFg){
  float dist;
  //中を埋める場合
  if(fillFg){ 
    for(int i=x-radius/2; i<x+radius/2; i++){
      for(int j=y-radius/2; j<y+radius/2; j++){
          planePoint(i, j,true);
      } 
    }
  }else{
  //中を埋めない場合
    for(int i=x-radius/2; i<x+radius/2; i++){
      planePoint(i, y-radius/2,true);
      planePoint(i, y+radius/2,true);      
    }
    for(int i=y-radius/2; i<y+radius/2; i++){
      planePoint(x-radius/2, i,true);
      planePoint(y+radius/2, i,true);      
    }
  }
}

//planeRotatePointOfSquareTrajectory(right);(時計回り)：未着手
//平面方向に点を動かす。四角の軌跡

//planeRotateTwoPointsOfSquareTrajectory(right);(時計回り)：未着手
//平面方向に2点を動かす。四角の軌跡

//planeRotateBoxOfSquareTrajectory(right);(時計回り)：未着手
//平面方向にボックスを動かす。四角の軌跡

//planeRotateTwoBoxesOfSquareTrajectory(right);(時計回り)：未着手
//平面方向に2つのボックスを動かす。四角の軌跡

//expansionX(2,2,false);(中心点のx座標,中心点のy座標,残さない):未着手
//x軸方向に拡大

//expansionY(2,2,false);(中心点のx座標,中心点のy座標,残さない):未着手
//ｙ軸方向に拡大

//expansionXY(2,2,false);(中心点のx座標,中心点のy座標,残さない):未着手
//xｙ軸方向に拡大

//zoomOutX(2,2,false);(中心点のx座標,中心点のy座標,残さない):未着手
//x軸方向に縮小

//zoomOutY(2,2,false);(中心点のx座標,中心点のy座標,残さない):未着手
//y軸方向に縮小

//zoomOutXY(2,2,false);(中心点のx座標,中心点のy座標,残さない):未着手
//xy軸方向に縮小

/*---xy指定×z指定改変-----------------------------------------------------------*/
//OneToOneHundredTwentyFive();
//OneToOneHundredTwentyFive(平面は、順に光らせる。高さ方向は、ランダムでON/OFFを切り替える)
void OneToOneHundredTwentyFive(int t){
  //ライトボリューム調整
  setLightVolume(1);
  
  for(int i=0; i<5; i++){
    for(int j=0; j<5; j++){
      //光らせる高さの指定
      height(0, random(0,2)==1 ? true : false);
      height(1, random(0,2)==1 ? true : false);
      height(2, random(0,2)==1 ? true : false);
      height(3, random(0,2)==1 ? true : false);
      height(4, random(0,2)==1 ? true : false);

      //点で描画する
      planePoint(i,j,true);
      delay(t);
      planeAll(false);
    }   
  }
}

//perform_uprain()*/
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
    height(i, true);
    setLightVolume(1);
    planeCircle(vpos[0], vpos[1], 1, true);
    delay(100);
    all(false);
  }
}

//rainOneDrops(50,5,false,true);(時間,回数,残さない,下がる)：未着手
//一滴ずづ雨を落とす

//rainTwoDrops(50,10,false,false);(時間,回数,残さない,上がる)：未着手
//交互に二滴の雨を落とす

//waterFall(50,5,false,true);(時間,回数,残さない,下がる)：未着手
//滝の描写

//twoWaterFalls(50,10,true);(時間,回数,下がる)：未着手
//滝がひとつ飛ばしにくる描写

//expansionCube(2,2,2,false);(中心点のx座標,中心点のy座標,中心点のz座標,残さない):未着手
//キューブの拡大

//zoomOutCube(2,2,2,false);(中心点のx座標,中心点のy座標,中心点のz座標,残さない):未着手
//キューブの縮小


/*---出力-----------------------------------------------------------*/
//メインループ
void loop()
{ 
setLightVolume(0.05);

  //実行するものに対して、コメントを外す。そのうち、シリアル経由でパソコンから切り替えられるようにする。
  
/*---xyz指定-----------------------------------------------------------*/
  //all(true);(つける)

/*---xy指定×z指定------------------------------------------------------------------*/
/*---xy指定基礎-----------------------------------------------------------*/  
  //planePoint(0,0,true);(x軸,y軸,つける)
  //planeLine(sX,sY,eX,eY,true);
  //planeAll(true);

/*--z指定基礎-----------------------------------------------------------*/  
  //height(4, true);(z軸,つける)
  //heightRandom(300,true,5);(時間,残す,繰り返し回数)：未着手
  //heightsRandom(2,300,true,3);(同時出力点の個数,時間,残す,繰り返し回数)：未着手
  //heights(0,0,0,0,0, true);：未着手
  //heightAll(true);

/*--z指定一次改変-----------------------------------------------------------*/
  //fromTopToBottom(300,false);(時間,残さない)
  //fromBottomToTop(300,false);

/*--z指定二次改変-----------------------------------------------------------*/
  //heightRotatePointOfSquareTrajectory(right);(時計回り)：未着手

  //expansionZ(2,false);(中心点のz座標,残さない):未着手
  //zoomOutZ(2,false);(中心点のz座標,残さない):未着手

  
/*---xy指定一次改変-----------------------------------------------------------*/
  //pointX_RandomX(0,300,true,5);(y軸,時間,残す,繰り返し回数)：未完,シード値に現在時刻を使いたい
  //pointX_RandomY(0,300,true,5);(x軸,時間,残す,繰り返し回数)：未完,シード値に現在時刻を使いたい
  //planePointRandom(300,true,25);(時間,残す,繰り返し回数)：未完,シード値に現在時刻を使いたい
  //planePointsRandom(5,300,true,5);(同時出力点の個数,時間,残す,繰り返し回数)：未完,シード値に現在時刻を使いたい

  //planeSixToThity(300);

  //fromFrontToBack(0,300,false);(x軸,時間,残さない)
  //fromFrontToBackRandom(300,false,5);(時間,残さない,回数)：未着手
  //fromFrontToBacks(0,0,0,0,0,300,true);(x[0]off,x[1]off,x[2]off,x[3]off,x[4]off,時間,残す)：未着手
  //fromFrontToBackAll(300,false);
  
  //fromBackToFront(0,300,false);
  //fromBackToFrontRandom(300,false,5);：未着手
  //fromBackToFronts(0,0,0,0,0,300,true);：未着手
  //fromBackToFrontAll(300,false);
  
  //fromLeftToRight(0,300,false);(y軸,時間,残さない)
  //fromLeftToRightRandom(300,false,5);：未着手
  //fromLeftToRights(0,0,0,0,0,300,true);：未着手
  //fromLeftToRightAll(300,false);
  
  //fromRightToLeft(0,300,false);
  //fromRightToLeftRandom(300,false,5);：未着手
  //fromRightToLefts(0,0,0,0,0,300,true);：未着手
  //fromRightToLeftAll(300,false);
  
/*---xy指定二次改変-----------------------------------------------------------*/
  //planeCircle(2,2,2,true);(中心点のx座標,中心点のy座標,半径,残す):未完
  //planeSquare(2,2,2,true);(中心点のx座標,中心点のy座標,半径,残す):未完
  //planeRotatePointOfSquareTrajectory(right);(時計回り)：未着手
  //planeRotateTwoPointsOfSquareTrajectory(right);(時計回り)：未着手
  //planeRotateBoxOfSquareTrajectory(right);(時計回り)：未着手
  //planeRotateTwoBoxesOfSquareTrajectory(right);(時計回り)：未着手
  
  //expansionX(2,2,false);(中心点のx座標,中心点のy座標,残さない):未着手
  //expansionY(2,2,false);(中心点のx座標,中心点のy座標,残さない):未着手
  //expansionXY(2,2,false);(中心点のx座標,中心点のy座標,残さない):未着手

  //zoomOutX(2,2,false);(中心点のx座標,中心点のy座標,残さない):未着手
  //zoomOutY(2,2,false);(中心点のx座標,中心点のy座標,残さない):未着手
  //zoomOutXY(2,2,false);(中心点のx座標,中心点のy座標,残さない):未着手

/*---xy指定×z指定改変-----------------------------------------------------------*/
  //OneToOneHundredTwentyFive(300);
  //perform_uprain();
  
  //rainOneDrops(50,5,false,true);(時間,回数,残さない,下がる)：未完
  //rainTwoDrops(50,10,false,false);(時間,回数,残さない,上がる)：未着手

  //waterFall(50,5,false,true);(時間,回数,残さない,下がる)：未着手
  //twoWaterFalls(50,10,true);(時間,回数,下がる)：未着手
  
  //expansionCube(2,2,2,false);(中心点のx座標,中心点のy座標,中心点のz座標,残さない):未着手
  //zoomOutCube(2,2,2,false);(中心点のx座標,中心点のy座標,中心点のz座標,残さない):未着手
  
/*--------------------------------------------------------------*/

int curHeigt=0,mode=2;
int stats[25]={0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0};
int curPos =0;




while(1){
  for(int curHeight=0; curHeight<5; curHeight++)
  {
      /*if(mode==1)//今伸びている竹を表示するモード
     {*/
        
      /*  curHeigt+=1;
        int height[5] = {0,0,0,0,0};
        for(int i=0; i<curHeight; i++)
        {
          height[i]=1; 
          delay (500);
          
        
      
        planePoint(x, y,true);
        heights(i);
        

        
        }*/
        //ここからがmode1
        /*if(stats[i]==0)
        {
        stats[i]=2;
        }

        
        int x=i%5,y=i/5;
        for(int h=0;h<5;h++)
        {
        planePoint(x, y,true);
        height(h,true);
        delay(1000);
        }*/
        //mode1ここまで
        

        
        if(mode==2)
        {//配列の中を読み込む
          int  i;
          int x=i%5,y=i/5;
          for(int t=0;t<25;t++)
          {       int j=stats[t];
                     Serial.println(j);   
                     if(stats[t]==1)
                     {i=t;
                     
                     
                     }
              
            
          
        //mode2ここから
        for(int s=0;s<25;s++)
        {
        
        
        
         
        }
        for(int h=0;h<5;h++)
        {
        planePoint(x, y,true);
        height(h,true);
        }
        }
          
      
        
       
                                    
                                          
      
  }
  //もし、全部の竹がひかりおわったら、break;


}
}
}
