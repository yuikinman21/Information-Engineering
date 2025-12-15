// //AJG23055 牧野唯希

import java.net.URL;
import java.net.HttpURLConnection;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.util.TreeSet;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
  public static void main(String[] args) {
      try {
      // ターゲットURL
      URL url = new URL(" https://www.omu.ac.jp/");
      // 接続オブジェクト
      HttpURLConnection http = (HttpURLConnection) url.openConnection();
      // リクエストメソッドをGETに設定
      http.setRequestMethod("GET");
      // 接続の確立
      http.connect();
      // 文字コード UTF-8 でリーダーを作成
      InputStreamReader isr = new InputStreamReader(http.getInputStream(), "UTF-8");
      // 行単位で読み込む為の準備
      BufferedReader br = new BufferedReader(isr);
        
      String line;
      StringBuilder htmlContent = new StringBuilder();
      
      // BufferedReader は、readLine が null を返すと読み込み終了
        while ((line = br.readLine()) != null) {
          htmlContent.append(line);
        }

        Pattern pattern = Pattern.compile("href=[\"'](https?://[^\"']+)[\"']");
        Matcher matcher = pattern.matcher(htmlContent.toString());


        TreeSet<String> links = new TreeSet<>();
        while (matcher.find()) {
            links.add(matcher.group(1));
        }

        System.out.println("Links in https://www.omu.ac.jp/");
        int count = 1;
        for (String link : links) {
            System.out.println(count + ": " + link);
            count++;
        }

      // 各々受け持ちクラスを閉じる
            br.close();
            isr.close();
            http.disconnect();

        } catch (Exception e) {
        }
    }
}
