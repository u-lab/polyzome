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
//int x=2;
//int y=2;
//float radius=2;
//bool fillFg=true;
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
            radius        : 半径
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
//height[i]に変更ひなた先輩チェックお願いします
void setLightHeights(int *height){
  for(int i=0; i<5; i++){
    dmx_master.setChannelValue(i+1, (height[i]==1) ?  MAX_LIGHT_VOLUME : 0);  
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
  setLightVolume(1);
   if(All_clear){
    drawPoint(x, y);
    setLightHeight(z, true);
    delay(delay_time); 
    clearAll();
   }
   
   else{
    drawPoint(x, y);
    setLightHeight(z, true);
    delay(delay_time); 
   }
}
  /* 作成者 :澤井
  ** 関数名 : handler_sawai_part3
  ** 引数 : int x          :表示させる点のx座標
            int y          :表示させる点のy座標
            int z          :表示させる点のz座標
            int delay_time :点灯させ続ける時間
            bool All_clear :点の座標情報のクリア
            float lightVol :光の光量を調節
  ** 関数の機能 : 点の表示に特化した関数です。
                 新規：あいはらさんの新規で作ってくださった関数を中に組み込んでいます
                 x,y,z座標を入力することで簡単に光る位置を設定できることができます。
                **この関数は削除対象です。
  */
void handler_sawai_part3(int x,int y, int z, int delay_time , bool All_clear,float lightVol){
   if(All_clear){
    drawPoint(x, y,lightVol);
    setLightHeight(z, true);
    delay(30);
    delay(delay_time); 
    clearAll();
   }
   
   else{
    drawPoint(x, y,lightVol);
    setLightHeight(z, true);
    delay(delay_time); 
   }
}



/*
** 関数名 : surge
** 引数 : なし
** 関数の機能 : handrersawaiの文がすごく長かったので行を少なくすむように調整
**              後ろで点の描写を行っているため最初に配置   int boxnum[][]={{0,3,2},{2,4,4},{0,3,2},{0,4,1},{1,0,2},{2,0,2},{4,1,3},{3,1,2},{3,0,2},{1,2,4},
                  {3,4,0},{1,2,1},{3,4,2},{2,0,2},{4,1,4},{3,0,3},{3,1,1},{3,0,0},{1,2,4},{3,3,3},{3,4,2},
                 };
** 作者: 澤井
** 日付: 2021/9/28
*/ 
//void surge(int box[][3]){
 
 // for(int i=0;i<21;i++){
   // handler_sawai_part3(boxnum[i][0],boxnum[i][1],boxnum[i][2],50,true);
//  }
//}

/*
  ** 関数名 : all_trye
  ** 引数 : なし
  ** 関数の機能 : フェードin なかったので作ったフェードアウトと組み合わせて使うと良き
  ** 注意；高さの指定をしてくれ 
  ** 作者: 澤井
  ** 日付: 9/23
  */
void all_trye(){
    for(float i=0;i<=1;i+=0.1){
    float plane[][5]={
      {i,i,i,i,i},
      {i,i,i,i,i},
      {i,i,i,i,i},
      {i,i,i,i,i},
      {i,i,i,i,i}
    };
    drawPoints(plane);
    delay(20);
  }

}

  /*
  ** 関数名 : fade_light
  ** 引数 : なし
  ** 関数の機能 : フェードout なかったので作った.フェードinと組み合わせて使うと良き
  ** 注意；高さの指定をしてくれ 
  ** 作者: 澤井
  ** 日付: 9/23
  */
void  fade_light(){
   
      for(float i=1;i>=0;i-=0.01){
       float plane[][5]={
        {i,i,i,i,i},
        {i,i,i,i,i},
        {i,i,i,i,i},
        {i,i,i,i,i},
        {i,i,i,i,i}
       };
       drawPoints(plane);
       delay(20);
      }
}
/*

/*
** 関数名 : grow_in_de_creace
** 引数 : なし
** 関数の機能 :成長の1つ目、すべてのライトがつく、消えるをウェーブのように行う
** 作者: 澤井
** 日付: 2021/9/24
*/  
int grow_in_de_creace(){  
  for( int i=0;i<30;i++){
     dmx_master.setChannelValue(i, MAX_LIGHT_VOLUME);
     delay(50);
  }
  for( int i=30;i>5;i--){
     dmx_master.setChannelValue(i, 0);
     delay(50);
 }
}  

/*
** 関数名 : grow_spredingcircle
** 引数 :    int height :光らせる高さ(1～5)
** 関数の機能 : 成長の表現二つ目,サークルが中心から広がっていく
** 作者: 澤井
** 日付: 2021/9/24
*/
int grow_spredingcircle( int height){
 
  
  dmx_master.setChannelValue(height, MAX_LIGHT_VOLUME);
  drawPoint(2,2,1);
  delay(400);
  for(float i=0;i<=1;i+=0.01){  
    float plane2[][5]={
     {0,0,0,0,0},
     {0,i,i,i,0},
     {0,i,i,i,0},
     {0,i,i,i,0},
     {0,0,0,0,0}
    }; 
    drawPoints(plane2);
    delay(20);
  }   


  for(float i=0;i<=1;i+=0.01){
        float plane2[][5]={
     {i,i,i,i,i},
     {i,i,i,i,i},
     {i,i,i,i,i},
     {i,i,i,i,i},
     {i,i,i,i,i}
    }; 
  
    drawPoints(plane2);
    delay(20);
  }   
  delay(300);
}  

/*
** 関数名 : grow_lightbox
** 引数 : int delaytime:光量maxまで行った後、減らすまでのフェーズに移る待機時間
** 関数の機能 : 成長の表現3つ目,3*3のboxが光量が上がっていって最後まで行くと消えていく
** 作者: 澤井
** 日付: 2021/9/24
*/
int grow_lightbox(int delaytime){

  int takasa[]={0,1,1,1,0};
  setLightHeights(takasa);
  for(float i=0;i<=1;i+=0.01){  
    float plane[][5]={
      {0,0,0,0,0},
      {0,i,i,i,0},
      {0,i,i,i,0},
      {0,i,i,i,0},
      {0,0,0,0,0}
    };
    drawPoints(plane);
    delay(50);
  }
  delay(delaytime);
  for(float i=1;i>=0;i-=0.01){
    float plane[][5]={
      {0,0,0,0,0},
      {0,i,i,i,0},
      {0,i,i,i,0},
      {0,i,i,i,0},
      {0,0,0,0,0}
    };
    drawPoints(plane);
    delay(50);
  }
}    


/*
** 関数名 : growkamo_fireworks
** 引数 : 今のところなし
** 関数の機能 : はなび
** 作者: 澤井
** 日付: 2021/9/24
*/  
/*                                
void growkamo_fireworks(){
int launch_spots[]={22,8,15,29,24,13,6,25,14,16,18};  
  for(int i=0;i<=10;i++){
    for(int k=0;k<=4;k++){
      setLightHeight(k, true); 
      dmx_master.setChannelValue(launch_spots[i], 90+k*7);
      delay(30+k*3);
      setLightHeight(k, false);
    }
   //clearPlaneAll();
  }
  for(int k=0;k<=2;k++){
    dmx_master.setChannelValue(launch_spots[k], 90+k*7);
    setLightHeight(k, true); 
    delay(70+k*10);
    if(k!=2){setLightHeight(k, false);} 
    if(k==2){
      drawPoint(2,2,0.8);
      delay(500);
    }
  }  
  //高さ2は消えてないはず  
  for(float i=0.8;i>=0;i-=0.01){
    drawPoint(2,2,i);
    delay(50);
  }
  //grow_lightbox(0);

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
  delay(100);
 
 clearAll();
delay(100);
 drawPoints(plane);

delay(200);

//clearAll();
}                                

*/
/*
** 関数名 : growkamo_fireworks2
** 引数 : 今のところなし
** 関数の機能 : はなび
** 作者: 澤井
** 日付: 2021/9/24
*/  
                               
void growkamo_fireworks2(){
int launch_spots[]={22,8,15,29,24,13,6,25,14,16,18};  
  for(int i=0;i<=11;i++){
    for(int k=0;k<=4;k++){
      setLightHeight(k, true); 
      dmx_master.setChannelValue(launch_spots[i], 90+k*7);
      delay(300+k*4);
      dmx_master.setChannelValue(launch_spots[i], 0);
      setLightHeight(k, false);
      //clearPlaneAll();
    }
   
  }
  delay(200);
  
     handler_sawai_part3(3,3,0,300,true);
      handler_sawai_part3(3,3,1,300,true);
       handler_sawai_part3(3,3,2,300,true);
        for(float i=1;i>=0;i-=0.01){
        setLightVolume(i);
        setLightHeight(3,true);
        drawPoint(3,3);
        // setLightVolume(i);delay(50);
        }
       
     delay(400);
     
     
     
  
  

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
  delay(700);
 
  clearAll();
  delay(300);
  drawPoints(plane);

  delay(400);
  clearAll();
//cleaall入れたのでかくにんしてみて
}  

/*
** 関数名 : uu
** 引数 : bool clearPlane :clearplaneを途中に入れます
          bool clearAll   :clearallを入れます
** 関数の機能 : 発生の表現一個目、たららんっと光が横に流れていく slack参照
** 作者: 澤井
** 日付: 2021/9/24
*/ 

int uu(bool clearPlane,bool clear_All ){

  setLightVolume(1);
int takasa[]={1,1,1,1,1};
 setLightHeights(takasa);
  for(int i=0; i<5; i++){
    for(int j=0; j<5; j+=2){
      drawPoint(i,j);
      sprintf(BUF, "%d %d", i, j);
      Serial.println(BUF);
      delay(50);
      if(clearPlane)clearPlaneAll();
    }
  }
 if(clear_All)clearAll();
}


void osero(){
 float i=1,k=1;

 //for(float i=0;i<=1;i+=0.01){
      float plane[][5]={
      {i,0,i,0,i},
      {0,i,0,i,0},
      {i,0,i,0,i},
      {0,i,0,i,0},
      {i,0,i,0,i}
    };
    drawPoints(plane);
    //delay(40);
// }
 //delay(500);
// for(float k=0;k<=1;k+=0.01){
    float plane7[][5]={
        {0,k,0,k,0},
        {k,0,k,0,k},
        {0,k,0,k,0},
        {k,0,k,0,k},
        {0,k,0,k,0}
    };
    drawPoints(plane7);
    //delay(40);
 //  }

 
/*
** 関数名 : ossero2
** 引数 : nasi
** 関数の機能 : オセロっぽいものの改変
** 作者: 澤井
** 日付: 2021/9/24
*/  
}
void osero2(){
 int i=1,k=1;
 int feights[]={1,1,1,1,1};
 setLightHeights(feights);
 //for(float i=0;i<=1;i+=0.01){
      float plane[][5]={
      {i,0,i,0,i},
      {0,i,0,i,0},
      {i,0,i,0,i},
      {0,i,0,i,0},
      {i,0,i,0,i}
    };
    drawPoints(plane);
    //delay(20);
//}
 //delay(500);
//for(float k=0;k<=1;k+=0.01){
    float plane7[][5]={
        {0,k,0,k,0},
        {k,0,k,0,k},
        {0,k,0,k,0},
        {k,0,k,0,k},
        {0,k,0,k,0}
    };
    drawPoints(plane7);
   // delay(20);
 // }

  
}

void hanahubuki(){
  uu(true,true); 
  uu(true,true);
  uu(true,true);
  for(int i;i<5;i++){
    for(float j=0.04;j<=1;j+=0.1){
     setLightHeight(i,true);

     float lights4[][5]={
              {j,0,j,0,j},
              {0,j,0,j,0},
              {j,0,j,0,j},
              {0,j,0,j,0},
              {j,0,j,0,j}
              };

     drawPoints(lights4);
       delay(20);
   }
   clearAll();    

  }
}
//うまくいかなそうなので廃止予定
void light_run(){
  for(int i=1;i<=5;i++){
     dmx_master.setChannelValue(i, MAX_LIGHT_VOLUME);
      for(int j=6;j<=10;i++){
       dmx_master.setChannelValue(i,MAX_LIGHT_VOLUME);
       delay(50);
       
      }
      for(int j=10;j<=30;j+=5){
       dmx_master.setChannelValue(i,MAX_LIGHT_VOLUME);
       delay(50);clearAll();
       
      }
      for(int j=30;j<=26;j-=1){
       dmx_master.setChannelValue(i,MAX_LIGHT_VOLUME);
       delay(50);clearAll();
      }
      for(int j=26;j<=6;j-=5){
       dmx_master.setChannelValue(i,MAX_LIGHT_VOLUME);
       delay(50);clearAll();
      }  
      clearPlaneAll();
      delay(100);
    }
  int heights[5]={1,1,1,1,1};
      setLightHeights(heights);
  fade_light();
}

void Theater_of_life(){
   for(int i=1;i<=5;i++){
     dmx_master.setChannelValue(i,MAX_LIGHT_VOLUME);
  all_trye();
  for(float i=1;i>=0;i-=0.01){
    float plane[][5]={
        {i,i,i,i,i},
        {i,1,i,1,i},
        {1,i,i,i,1},
        {i,1,i,1,i},
        {i,i,i,i,i}
    };
    drawPoints(plane);
    //delay(20);
 
  }  
 } 
} 

void mode2(int *finish){
 clearAll();
  for(int i=0;i<6;i++){
    if(finish[i]!=0){
    dmx_master.setChannelValue(finish[i],MAX_LIGHT_VOLUME);
     int heights[5]={1,1,1,1,1};
    setLightHeights(heights);
    }
  }
} 



void What_do_you_thINK(){
  int dimax[]={12,16,22,24,20,14};
  int owari[6];
  int conti[5]={0,0,0,0,0};
  //dmx_master.setChannelValue(1,MAX_LIGHT_VOLUME);
  for(int i=0;i<6;i++){
    dmx_master.setChannelValue(dimax[i],MAX_LIGHT_VOLUME);
    for(int k=0;k<=5;k++){  
     
     conti[k]=1;  
     setLightHeights(conti); 
     
    
      mode2(owari);
      
   
      if(k=5){
        owari[i]=dimax[i];
      }
    }   
  }
//clearAll();
}

/*
** 関数名 : serge：うねり
** 引数 : box:　二次元配列を使って3つの値x,y,zを入れる　
* 　　　　number:要素数を入れてください
** 関数の機能 : handrersawaiの分がすごく長かったので行を少なくすむように調整
** 作者: 澤井
** 日付: 2021/9/28
*/ 

  void surge(int box[][3],int number){
 
  for(int i=0;i<number;i++){
    handler_sawai_part3(box[i][0],box[i][1],box[i][2],90,true);
 }
}


/*
** 関数名 : blood:血行
** 関数の機能 : 作りたかったラウンドを作った。雑ですいません
** 作者: 澤井
** 日付: 2021/9/28
*/ 
void blood(){
  int cells[][3]={{4,2,0},{3,2,0},{2,2,0},{1,2,0},{1,3,0},{2,3,0},{3,3,0},{4,3,0},{4,4,0},{3,4,0},{2,4,0},{1,4,0},{1,4,1},{1,3,1},{1,2,1},{1,1,1},{2,1,1},{3,1,1},{4,1,1},{4,2,1},{4,3,1},{4,4,1},{3,4,1},{2,4,1},{1,4,1},{1,3,2},{1,2,2},{1,1,2},{2,1,2},{3,1,2},{4,1,2},{4,2,2}
  ,{4,3,2},{4,4,2},{3,4,2},{2,4,2},{1,4,1},{1,3,3},{1,2,3},{1,1,3},{2,1,3},{3,1,3},{4,1,3},{4,2,3},{4,3,3},{4,4,3},{3,4,3},{2,4,3},{1,4,3},{1,3,4},{1,2,4},{1,1,4},{2,1,4},{3,1,4},{4,1,4},{4,2,4},{4,3,4},{4,4,4},{3,4,4},{2,4,4},{1,4,4},{1,3,4},{1,2,4},{1,1,4},{2,1,4},{3,1,4},{4,1,4}};

  surge(cells,59);

}






void grow_part1_3(){
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
  setLightVolume(0.05);
  setLightHeight(1, true);
  drawLine(3,2,4,4);
  setLightHeight(1,false);
  setLightHeight(2, true);
  drawLine(0, 2, 4, 2);
  setLightHeight(2, false);
  setLightVolume(0.5);
  setLightHeight(4, true);
  drawLine(3,2,4,4);
  setLightHeight(4, false);
  setLightVolume(0.05);
  setLightHeight(0, true);
  drawLine(1, 1, 3, 3);
  setLightHeight(0, false);
  setLightVolume(1);
  setLightHeight(1, true);
  drawLine(3,2,4,4);

  //上のものはテストように追加
  //part3 点をだんだん増やす作業
  all_trye();

  //setLightVolume(1);     
  


 

  handler_sawai_part3(0,3,0,300,true);
  handler_sawai_part3(2,4,1,300,true);
  handler_sawai_part3(0,3,2,400,true);
  handler_sawai_part3(0,4,3,300,true);
  handler_sawai_part3(1,0,4,300,true);
  handler_sawai_part3(2,0,0,400,true);
  handler_sawai_part3(4,1,3,350,true);
  handler_sawai_part3(3,1,2,400,true);
  handler_sawai_part3(3,0,4,500,true);
  handler_sawai_part3(1,2,1,300,true);
  handler_sawai_part3(3,4,3,400,true);
  handler_sawai_part3(1,2,4,300,true);
  handler_sawai_part3(3,4,4,300,true);

  


  float lights[][5]={
                    {0,0,1,0,0},
                    {0,1,0,1,0},
                    {1,0,0,0,1},
                    {0,1,0,1,0},
                    {0,0,1,0,0}
                    };

  for(int i=0;i<5;i++){
    setLightHeight(i,true);
    delay(300);
    drawPoints(lights);
    
  }
  clearAll();

  float lights2[][5]={
          {0,0,1,0,0},
          {0,1,0,1,0},
          {1,0,0,0,1},
          {0,1,0,1,0},
          {0,0,1,0,0}
  };

  for(int i=0;i<5;i++){
    setLightHeight(i,true);
    delay(200);
    drawPoints(lights2);
    
  }
    float lights3[][5]={
             {1,1,1,1,1},
             {1,1,0,1,1},
             {1,0,0,0,1},
             {1,1,0,1,1},
             {1,1,1,1,1}
                       };

  for(int i=0;i<5;i++){
    setLightHeight(i,true);
    delay(200);
    drawPoints(lights3);
    
  }

 all_trye();
 fade_light();
}



void saisyo(){
  //円が広がっていく表現明日の作業でうまくいくようならここは削除
  handler_sawai_part3(2,2,2,300,false,1);delay(100);
  for(int i=12;i<24;i++){
    if(!(i==15||i==16||i==20||i==21)){
      dmx_master.setChannelValue(i, MAX_LIGHT_VOLUME);
      dmx_master.setChannelValue(3, MAX_LIGHT_VOLUME);
   }
  }
  delay(100);
  for(int i=6;i<30;i++){
     dmx_master.setChannelValue(i, MAX_LIGHT_VOLUME);
     dmx_master.setChannelValue(3, MAX_LIGHT_VOLUME);
  }
  delay(400);
  for(int i=12;i<24;i++){
   if(!(i==15||i==16||i==20||i==21)){
      dmx_master.setChannelValue(i, MAX_LIGHT_VOLUME);
     dmx_master.setChannelValue(2, MAX_LIGHT_VOLUME);
     dmx_master.setChannelValue(3, MAX_LIGHT_VOLUME);
     dmx_master.setChannelValue(4, MAX_LIGHT_VOLUME);
    }
  }
}


//メインループ
void loop(){
 
 //grow_spredingcircle(3);
 //saisyo();
  
  //grow_in_de_creace();
  //grow_lightbox(500);
  
  growkamo_fireworks2();
  grow_in_de_creace();
  uu(false,true);
  uu(true,false);
  grow_part1_3();
  osero2();
  osero2();
  osero2();
  hanahubuki();
  
   
  Theater_of_life();
  Theater_of_life();
  clearAll();
  Theater_of_life();
  clearAll();
  Theater_of_life();
  What_do_you_thINK(); 

//ここコンボで二つ固定して
uu(true,false);
   int boxnum[][3]={{0,3,2},{2,4,4},{0,3,2},{0,4,1},{1,0,2},{2,0,2},{4,1,3},{3,1,2},{3,0,2},{1,2,4},
                  {3,4,0},{1,2,1},{3,4,2},{2,0,2},{4,1,4},{3,0,3},{3,1,1},{3,0,0},{1,2,4},{3,3,3},{3,4,2},
                  {2,2,2},{3,4,4},{1,3,3},{2,4,4},{1,0,0},{1,2,0}};
surge(boxnum,27); 
blood();
                                                           
                                                    
                                                               
                                                          
 clearAll();
}





 


