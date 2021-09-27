
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
** 戻り値 : なし
** 関数の機能 : 死の表現1つ目、上段から下段に消えていき、上段から下段についていく。
5*5*5の光っている箱と暗い箱が交互に下に押し出され、消えていくイメージ
** 作者: seigo
** 日付: 2021/09/22
*/
void deathFirst(int time){
  //上から一段づつ消す
  for(int i=4; i>=0; i--){
    setLightHeight(i, false);
    delay(time);
  }
  //上から一段づつ点ける
  for(int i=4; i>0; i--){
    setLightHeight(i, true);
    delay(time);
  }
}

/*
** 関数名 : deathSecond
** 引数 : int time : 柱が消えるスピード(基準:100)
** 戻り値 : なし
** 関数の機能 : 死の表現2つ目、柱がランダムに消えていき、ランダムについていく
** 作者: seigo
** 日付: 2021/09/22
*/
void deathSecond(int time){
  int downNumbers[25]={25,16,11,15,28,30,20,14,23,22,26,24,9,12,21,27,7,18,13,8,10,19,17,29,6};
  for(int i=0; i<25; i++){
    dmx_master.setChannelValue(downNumbers[i], 0);
    delay(time);
  }
  //柱がランダムについていく
  int upNumbers[25]={12,16,7,20,30,27,6,22,13,17,18,11,10,9,25,15,8,26,24,19,14,21,23,28,29};
  for(int i=0; i<25; i++){
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
