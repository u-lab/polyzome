
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

//drawPointのテスト関数
void test_drawPoint(){
    Serial.println("test_drawPoint");
    clearAll();
    delay(200);
    
    setLightHeight(0, true);
    float vol =0;
    for(int i=0; i<5; i++){
        drawPoint(i,i,vol);
        vol+=0.1;
        delay(200);
    }
}

//drawPointsのテスト関数
void test_drawPoints(){
    Serial.println("test_drawPoints");
    clearAll();
    delay(200);
    
    setLightHeight(0, true);
    float vol[5][5] = { {0,0,0,0,0},  {0,0,0,0,0},  {0,0,0,0,0},  {0,0,0,0,0},  {0,0,0,0,0}};

    for(int i=0; i<5; i++){
        vol[i][i]+=0.1;       
        drawPoints(vol);
        delay(200);
    }
}

//drawCircleのテスト関数
void test_drawCircle(){
    Serial.println("test_drawCircle");
    clearAll();
    delay(200);

    setLightHeight(0, true);

    //radius=0はOK
    //drawCircle(2, 2, 0, true, 1.0);
    //delay(200);

    //radius=2で中を埋めるのはOK
    //drawCircle(2, 2, 2, true, 1.0);
    //delay(200);

    //radius=2で中を埋めないものもOK
    drawCircle(2, 2, 2, false, 1.0);
    delay(200);
}

//drawBoxのテスト関数
void test_drawBox(){
    Serial.println("test_drawBox");
    clearAll();
    delay(200);

    setLightHeight(0, true);

    //radius=2で中を埋めるものはOK
    //drawBox(2, 2, 1, true, 1.0);
    //delay(200);

    //radius=2で中を埋めないものOK
    drawBox(2, 2, 1, false, 1.0);
    delay(200);

}



