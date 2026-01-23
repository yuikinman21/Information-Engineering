import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

class Chava{
  /* ライブラリ関数群の実装:
   *   Chavacはここで定義したpublic staticメソッドを自動的に認識し，
   *   ソースコードから呼出可能にする．詳細はChavacの内部クラス
   *   Libraryを参照のこと．
   *
   *   ライブラリ関数として定義されているのは，現在のところ，
   *   println()とinput()である．
   *
   *   ライブラリ関数の返戻値型はvoidまたはint，引数の型はintのみ
   *   が許される．
   */
  private static BufferedReader in;

  public static void println(int i){
    System.out.println(String.valueOf(i));
  }

  public static int input(){
    while(true){
      try{
	return (Integer.parseInt(in.readLine()));
      }
      catch(NumberFormatException e){
	continue;
      }
      catch(IOException e){
	continue;
      }
    }
  }

  // mainメソッド: Chavacが出力したクラスファイル内のmain関数を呼ぶ．
  public static void main(String[] args){
    try{
      Class[] params = new Class[0];
      in = new BufferedReader(new InputStreamReader(System.in));
      ((Class.forName(args[0])).getMethod("main", params)).invoke(null, params);
    }
    catch(Throwable e){
      System.out.println(e);
    }
  }
}
