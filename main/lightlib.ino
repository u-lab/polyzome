
//ライトボリュームの設定
//volume:値(0〜1までの少数)
void setLightVolume(float volume){
  gLightVolume = volume;
}

//点の描画
//x,y:描画する位置(0〜4)
void drawPoint(int x, int y){
  drawPoint(x, y, gLightVolume);
}

//点の描画
//x,y:描画する位置(0〜4)
//lightVol: 光の強度(0〜1)
void drawPoint(int x, int y, float lightVol){
  if(x<0 || 4<x || y<0 || 4<y){
    sprintf(BUF, "Input value is out of range %d %d", x, y);
    Serial.println(BUF);
    if(x<0) x=0;
    if(x>4) x=4;
    if(y<0) y=0;
    if(y>4) y=4;
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

//円の描画
//x, y:中心
//radius:半径
//fillFg:円の内側を塗りつぶす場合(true), 塗りつぶさない場合(false)
// example : (中心座標(x, y) = (2, 2), 半径r = 2, 塗りつぶし = on)
// int x=2;
// int y=2;
// float radius=2;
// bool fillFg=true;
void drawCircle(int x, int y, float radius, bool fillFg){
  drawCircle(x, y, radius,fillFg, gLightVolume);
}

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

//線の描画
//sPosX:開始点X
//sPosY:開始点Y
//ePosX:終了点X
//ePosY:終了点Y
void drawLine(int sPosX, int sPosY, int ePosX, int ePosY){
  drawLine(sPosX, sPosY, ePosX, ePosY, gLightVolume);
}

//線の描画
//sPosX:開始点X
//sPosY:開始点Y
//ePosX:終了点X
//ePosY:終了点Y
//lightVol:光の強度
void drawLine(int sPosX, int sPosY, int ePosX, int ePosY, float lightVol){
  //スタートよりもエンドの方が値が大きいこと
  if(sPosX< ePosX  || sPosY< ePosY){
    sprintf(BUF, "Input value is wrong %d %d %d %d", sPosX, sPosY, ePosX, ePosY);
    Serial.println(BUF);
  }

  //まずは、直線だけを描画
  if(sPosX == ePosX){
     for(int i=sPosY; i<=ePosY; i++){
      drawPoint(sPosX, i, lightVol);      
     }
  }else if(sPosY == ePosY){
     for(int i=sPosX; i<=ePosX; i++){
      drawPoint(i, sPosY, lightVol);      
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
    // dmx_master.setChannelValue(i+1, (height[0]==1) ?  MAX_LIGHT_VOLUME : 0);
    dmx_master.setChannelValue(i+1, (height[i]==1) ?  MAX_LIGHT_VOLUME : 0);

  }
}
