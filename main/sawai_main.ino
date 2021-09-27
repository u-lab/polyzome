void sawai_proc(){

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
  ** 関数名 : all_trye
  ** 引数 : なし
  ** 関数の機能 : フェードin なかったので作ったフェードアウトと組み合わせて使うと良き
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
    delay(50);
  }

}

  /*
  ** 関数名 : fade_light
  ** 引数 : なし
  ** 関数の機能 : フェードout なかったので作った.フェードinと組み合わせて使うと良き
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
    delay(50);
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
                                
void growkamo_fireworks(){
int launch_spots[]={22,8,15,29,24,13,6,25,14,16,18};  
  for(int i=0;i<=10;i++){
    for(int k=0;k<=4;k++){
      setLightHeight(k, true); 
      dmx_master.setChannelValue(launch_spots[i], 90+k*7);
      delay(30+k*3);
      setLightHeight(k, false);
    }
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
  grow_lightbox(0);

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
delay(100);
 drawPoints(plane);

delay(200);

clearAll();
}                                


/*
** 関数名 : uu
** 引数 : bool clearPlane :clearplaneを途中に入れます
          bool clearAll   :clearallを入れます
** 関数の機能 : 発生の表現一個目、たららんっと光が横に流れていく
** 作者: 澤井
** 日付: 2021/9/24
*/ 

int uu(bool clearPlane,bool clear_All ){

  setLightVolume(0.04);
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

  
}

void hanahubuki(){
uu(true,true); 
for(float j=0.04;j<=1;j+=0.01){
  setLightHeight(1,true);
   setLightHeight(2,true);
  setLightHeight(3,true);
  setLightHeight(4,true);
  setLightHeight(0,true);
 float lights4[][5]={
          {0,0,0,0,0},
          {0,j,0,j,0},
          {0,0,j,0,0},
          {0,j,0,j,0},
          {0,0,0,0,0}
};


  drawPoints(lights4);
    delay(70);
  }
clearAll();    

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

  setLightVolume(0.04);

  for(float i=0.03;i<=1;i+=0.01){
    handler_sawai_part3(2,2,2,70,false,i);
  }
  delay(100);

 clearAll();

  handler_sawai_part3(3,4,4,800,true,0.04);

  handler_sawai_part3(2,4,4,500,true,0.02);
  handler_sawai_part3(1,3,3,500,true,0.05);
  //handler_sawai_part3(1,4,4,300,true);
  //TEST 繰り返し構文で setLightVolume上げてぴかぴかさせる？(予定:現状後回し)別の段でしてあげるときれいかも

  handler_sawai_part3(1,2,3,200,true,0.8);
  handler_sawai_part3(3,3,2,350,true,0.04);
  handler_sawai_part3(0,1,4,100,true,0.05);

  handler_sawai_part3(2,3,4,300,true,1);
  handler_sawai_part3(2,4,3,200,true,0.5);
  handler_sawai_part3(0,3,0,500,true,1);
  handler_sawai_part3(0,4,3,300,true,0.6);
  handler_sawai_part3(1,0,2,400,true,0.4);


  handler_sawai_part3(2,0,2,300,true,0.09);
  handler_sawai_part3(4,1,4,200,true,1);
  handler_sawai_part3(3,1,1,400,true,0.5);
  handler_sawai_part3(3,0,0,500,true,0.6);
  handler_sawai_part3(1,2,0,420,true,0.1);
  handler_sawai_part3(3,4,1,350,true,1);
  handler_sawai_part3(1,2,3,300,true,0.2);
  handler_sawai_part3(3,4,2,400,true,1);

  delay(500);
  //trueにして全部を高速点灯させることにする  本来は高さ指定の制限のために同じ高さにしていたがこっちの方が奇麗に見えるくねえ？？ってことで変更

  handler_sawai_part3(0,3,0,300,true,1);
  handler_sawai_part3(2,4,1,300,true,1);
  handler_sawai_part3(0,3,2,400,true,1);
  handler_sawai_part3(0,4,3,300,true,0.8);
  handler_sawai_part3(1,0,4,300,true,0.08);
  handler_sawai_part3(2,0,0,400,true,0.4);
  handler_sawai_part3(4,1,3,350,true,0.1);
  handler_sawai_part3(3,1,2,400,true,0.7);
  handler_sawai_part3(3,0,4,500,true,0.7);
  handler_sawai_part3(1,2,1,300,true,0.2);
  handler_sawai_part3(3,4,3,400,true,0.1);
  handler_sawai_part3(1,2,4,300,true,0.4);
  handler_sawai_part3(3,4,4,300,true,0.1);

  delay(500);


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

  for(int i=0;i<3;i++){
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

  for(int i=3;i<5;i++){
    setLightHeight(i,true);
    delay(200);
    drawPoints(lights3);
    
  }



  handler_sawai_part3(0,3,2,300,true,1);
  handler_sawai_part3(2,4,4,400,true,1);
  handler_sawai_part3(0,3,4,400,true,1);
  handler_sawai_part3(0,4,1,200,true,0.8);
  handler_sawai_part3(1,0,2,300,true,0.08);
  handler_sawai_part3(2,0,2,400,false,0.4);
  handler_sawai_part3(4,1,3,500,false,0.1);
  handler_sawai_part3(3,1,2,400,false,0.7);
  handler_sawai_part3(3,0,2,500,false,0.7);
  handler_sawai_part3(1,2,4,200,true,0.2);
  handler_sawai_part3(3,4,1,400,true,0.1);
  handler_sawai_part3(1,2,1,200,true,0.4);
  handler_sawai_part3(3,4,0,300,true,0.1);
  handler_sawai_part3(2,0,2,100,true,0.09);
  handler_sawai_part3(4,1,4,200,true,1);
  handler_sawai_part3(3,1,1,100,true,0.5);
  handler_sawai_part3(3,0,0,500,true,0.6);
  handler_sawai_part3(1,2,0,100,true,0.1);
  handler_sawai_part3(3,4,1,350,true,1);
  handler_sawai_part3(1,2,3,200,true,0.2);
  handler_sawai_part3(3,4,2,300,true,1);

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
   {
     dmx_master.setChannelValue(i, MAX_LIGHT_VOLUME);
     dmx_master.setChannelValue(3, MAX_LIGHT_VOLUME);
   }
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
