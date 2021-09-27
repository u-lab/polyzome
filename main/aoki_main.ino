 /* 作成者 :青木
  ** 関数名 :heights
  ** 引数 : int *height：大きさ5の配列を使用して高さを指定する
  ** 関数の機能 :高さを複数点指定する
  */
//ex. 全部クリア：height=[0,0,0,0,0]
//    全部点灯：height=[1,1,1,1,1]
//　　１段目だけ点灯：height=[1,0,0,0]
void heights(int *height) {
  for (int i = 0; i < 5; i++) {
    dmx_master.setChannelValue(i + 1, (height[0] == 1) ?  MAX_LIGHT_VOLUME : 0);
  }
}

  /* 作成者 :青木
  ** 関数名 :planeAll
  ** 引数 : bool fg: ONの場合(true), OFFの場合(false)
  ** 関数の機能 :平面を全て指定する
  */
void planeAll(bool fg) {
  for (int i = 6; i <= 30; i++) {
    dmx_master.setChannelValue(i, fg ? MAX_LIGHT_VOLUME : 0);
  }
}

  /* 作成者 :青木
  ** 関数名 :all
  ** 引数 : bool fg: ONの場合(true), OFFの場合(false)
  ** 関数の機能 :全て指定する
  */
void all(bool fg) {
  for (int i = 1; i <= 30; i++) {
    dmx_master.setChannelValue(i, fg ? MAX_LIGHT_VOLUME : 0);
  }
}
/*---------------------------------------------------------------------------------------------*/
  /* 作成者 :青木
  ** 関数名 :diffusionFirst
  ** 引数 : int time        :円が広がるスピード(基準:1200)
  ** 引数 : float light     :光の強さ(基準:0.1)
  ** 関数の機能 :*中心から外へ円柱(疎)が拡大する
  */

void diffusionFirst(int time,float light){
  setLightVolume(1); 
  all(false);
  int takasa[]={1,1,1,1,1};
  heights(takasa);
  drawCircle(2,2,0,true,light);
  delay(time);
  planeAll(false);
  drawCircle(2,2,1,false,light);
  delay(time);
  planeAll(false);
  drawCircle(2,2,2,false,light);
  delay(time);
  planeAll(false);
  drawCircle(2,2,3,false,light);
  delay(time);
  planeAll(false);
  drawCircle(2,2,4,false,light);
  delay(time);
  all(false);
}

  /* 作成者 :青木
  ** 関数名 :diffusionSecond
  ** 引数 : int time        :四角が広がるスピード(基準:1200)
  ** 引数 : float light     :光の強さ(基準:0.1)
  ** 関数の機能 :*中心から外へ四角柱(疎)が拡大する
  　　　　　　　　*
  */
void diffusionSecond(int time,float light){
  setLightVolume(1); 
  all(false);
  int takasa[]={1,1,1,1,1};
  heights(takasa);
  drawBox(2,2,0,true,light);
  delay(time);
  planeAll(false);
  drawBox(2,2,1,false,light);
  delay(time);
  planeAll(false);
  drawBox(2,2,2,false,light);
  delay(time);
  planeAll(false);
  drawBox(2,2,3,false,light);
  delay(time);
  all(false);
}
