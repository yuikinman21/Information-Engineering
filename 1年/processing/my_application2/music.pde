Minim minim; //Minim型変数であるminimの宣言
AudioPlayer player; //サウンドデータ格納用の変更
AudioPlayer Jump;
AudioPlayer Get;

void stop() {
player.close(); //サウンドデータを終了
minim.stop();
super.stop(); /*superは、 サブクラスのスーパークラスを参照するために使用される
キーワード*/
}
void music() {
    minim = new Minim(this); //初期化,thisは現在のオブジェクトを参照する。
    player = minim.loadFile("BeeGM.mp3"); 
    Jump = minim. loadFile("jump2.mp3");
    Get = minim. loadFile("get.mp3");
    
    player.loop(); //再生
    player.rewind();
}
