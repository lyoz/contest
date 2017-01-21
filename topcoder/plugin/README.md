# TopCoder Plugins

moj + CodeProcessor + FileEditを使う．

ファイルは https://github.com/lovrop/topcoder-moj/releases からダウンロードする．
- https://github.com/lovrop/topcoder-moj/archive/v4.18.zip

## moj.jar のビルド
ローカルでのカスタムテストの出力形式を修正して使う．

```
$ sh build-jar.sh
```

## アプレット(ContestAppletProd.jnlp)
### アプレット設定
1. ダウンロード
   - https://www.topcoder.com/contest/arena/ContestAppletProd.jnlp
2. 例外サイトへの追加
   - コントロールパネル > Java
     - [セキュリティ]タブの例外サイトリストに `http://www.topcoder.com` を追加する
3. Options
   - Disable Enter/Exit Messagesにチェック
   - Enable Timestampsにチェック
   - Setup User Preferences
     - [Chat] Emphasis System: 色をcyan(0,255,255)にする
     - フォントは適当に設定する(Meiryo UI + Inconsolata?)
### プラグイン設定
1. Options > EditorでEditor Preferenceを開く．
   - Common ClassPath: `FileEdit.jarとmoj.jarのファイルパス`
2. [Add]
   - Name: `CodeProcessor`
   - EntryPont: `codeprocessor.EntryPoint`
   - ClassPath: `CodeProcessor.jarのファイルパス`
   - [OK] EditorsにCodeProcessorが追加されるので，Defaultにチェックする．
3. CodeProcessorの行を選択して[Configure]. CodeProcessor Configurationを開く
   - Editor EntryPoint: `fileedit.EntryPoint`
     - [Configure]
       - Enter directory to read/write problems to: `ソースコードが生成されるディレクトリ`
       - Backup existing file then overwrite (uncheck if you want to keep existing file)のチェックを外す
       - Code Templateタブに切り替え，C++のテンプレートを編集して[Save]
   - CodeProcessor Script
     - [Add]
       - `moj.moj`
4. 各ダイアログで[Save]して[Close]
