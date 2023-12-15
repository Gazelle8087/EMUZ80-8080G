# EMUZ80-8080G
アクセスいただきましてありがとうございます。  

奥江聡さん作MEZ8080を小改造し8080の2相クロックをPICのNCOで生成し  
処理効率向上にトライしたファームウエアを公開します。  

## 基板改造
本ファームウエアを動作させるにはMEZ8080基板の  
パターンカット1か所とジャンパ線1か所追加の改造が必要です。  
この改造によってPHI2駆動ピンをRA5からRE1に変更します。  
![MEZ8080改造箇所](https://github.com/Gazelle8087/EMUZ80-8080G/blob/main/MEZ8080_modify.jpg)  
## 8080用コード  
8080用コードは以前作成したemuz80+mez8085用の物を流用しました。  
詳細は以下リンク先ご覧ください。  
https://drive.google.com/drive/folders/1abwFj7vFJUoVxqDc4fVLAgv0AT-kCIrY
## 変更履歴
Ver1.0 2023.12.15 初版公開

## 参照元や参考情報
本ソースはGPLライセンス規約に基づき  
電脳伝説さん、奥江さんが公開されたソースを改変して作成いたしました。  

MEZ8080の詳細は以下リポジトリご参照ください  
https://github.com/satoshiokue/MEZ8080  

emuz80+mez8080用オリジナルファームウエアは以下リポジトリさん参照ください。  
https://github.com/satoshiokue/EMUZ80-8080  

オリジナル・参考ソースへのリンクは、ソースの冒頭に  
リンクを記入していますので必要に応じご参照ください。  

本ソースとHEXはGPLライセンスを遵守のうえご自由に再配布いただいて構いません。  

2023.12.15 Gazelle https://twitter.com/Gazelle8087
