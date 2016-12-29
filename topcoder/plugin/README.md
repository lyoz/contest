# TopCoder Plugins

moj + CodeProcessor + FileEditを使う．

ファイルは https://github.com/lovrop/topcoder-moj/releases からダウンロードする．
- https://github.com/lovrop/topcoder-moj/archive/v4.18.zip

## moj.jar のビルド
ローカルでのカスタムテストの出力形式を修正して使う．

```
$ sh build-jar.sh
```

## 設定
ContestAppletProd.jnlp 実行後のプラグインの設定．

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
