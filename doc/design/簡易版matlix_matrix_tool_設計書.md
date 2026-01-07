# 設計書：行列計算ツール（簡易版）

## 1. データ構造
- **構造体定義**: 
  - `typedef struct { size_t rows; size_t cols; float *data; } Matrix;` 
        - `rows`: 行の大きさ
        - `cols`: 列の大きさ
        - `*data`: 行列に格納されたデータを指すポインタ
        
- **メモリ配置**: 
  - 構造体定義: NumPyのような計算を再現するため、1次元配列を論理的に2次元配列として定義
  - `i = row`, `j = col`
  - インデックス計算式: `index = i * (*data).cols + j`

## 2. モジュール構成
- `main.c`: 実行フロー
- `matrix.c`: 行列の作成・純粋な計算ロジック
- `matrix.h`:`matrix.c`のヘッダーファイル

## 3. 関数詳細仕様

### 3.1 [create_matrix]
- **プロトタイプ**: `Matrix *create_matrix(size_t rows, size_t cols);`
- **引数**:
  - `rows`: 行のサイズ
  - `cols`: 列のサイズ

- **戻り値**:
  - 成功時：`return m`で作成した構造体へのポインタを返す。
  - 失敗時：プログラムを強制終了(`exit 1`)

- **処理内容（アルゴリズム）**:
  1. 構造体`Matrix`を定義
    * もし`int rows <= 0 || int cols <= 0`だった場合は `exit 1`を実行
  2. 変数`Matrix *m`を定義しmallocで`*m`と同じサイズの領域を確保
    * もしも`m` がNULLだった場合`fprintf`で`stderr`にメッセージを表示し`exit 1` を行う 
  3. 変数`Matrix *m`の指す先の領域を`(*m).data = malloc(sizeof(float)* rows * cols)`で確保
    * もしも`(*m).data` がNULLだった場合`fprintf`で`stderr`にメッセージを表示し`*m` のfreeを実行後に`exit 1`を実行する
    * `(*m).data` がNULLではない場合、ループ処理を用いて`(*m).data[i] = 0.0;` で初期化する
  4. 構造体に引数で渡された値を格納
  5. `Matrix`型のポインタ `m`を使い構造体へのポインタを返す
  
  - **メモリ管理**:
  - 関数内で `malloc` を行い配列を確保。
  - 戻り値のメモリ解放責任は呼び出し側に帰属(free_matrixを使用し開放)

### 3.2 [print_matrix]
- **プロトタイプ**: `int print_matrix(Matrix *data);`
- **引数**:
  - `Matrix *data`: 構造体へのポインタ

- **戻り値**:
  - 成功時：`return 0`
  - 失敗時：プログラムを強制終了(`exit 1`)

- **処理内容（アルゴリズム）**:
  1. 引数`data`がNULLではないか確認
    * NULLの場合 `exit 1` を実行
  2. 2重ループを用いて各インデックスを`%f`で出力
    * 1層目のループでインデックス`i`を取り出す
    * 2層目のループでインデックス`j`を取り出し`(*data).data[i * (*data).cols + j]`を`printf` で標準出力に表示

- **メモリ管理**:
  - 配列の操作を行わないため不要。

### 3.3 [add_matrix]
- **プロトタイプ**: `Matrix *add_matrix(Matrix *data_x, Matrix *data_y);`
- **引数**:
  - `Matrix *data_x`: 計算に使用する配列
  - `Matrix *data_y`: 計算に使用する配列

- **戻り値**:
  - 成功時：`return y;`
  - 失敗時：プログラムを強制終了(`exit 1`)

- **処理内容（アルゴリズム）**:
  1. 引数`data_x`と引数`data_y`がNULLでないか確認
    * NULLの場合 `exit 1` を実行
  2. 引数`data_x`と引数`data_y`の形状が一致しているか確認
    * 一致していない場合は`exit 1` を実行
  3. `create_matrix`を使い計算結果を格納するための配列`y`を作成
  4. 2重ループを使い、配列`data_x`と配列`data_y`で対応するインデックス同士を加算
    * 1層目のループでインデックス`i`を取り出す
    * 2層目のループでインデックス`j`を取り出し`(*data_x).data[i * (*data_x).cols + j]`と`(*data_y).data[i * (*data_y).cols + j]` を加算する
      * 行列計算完了後結果を配列`y`に格納する
    * ループを使い配列`(*y).data[i * (*y).cols + j]`に加算結果を順に格納する
  5. 戻り値として配列`y`を返す

- **メモリ管理**:
  - 関数内で `malloc` を行い配列を確保。
  - 戻り値のメモリ解放責任は呼び出し側に帰属(free_matrixを使用し開放)

### 3.4 [free_matrix]
- **プロトタイプ**: `void free_matrix(Matrix *data);`
- **引数**:
  - `Matrix *data`: 開放対象のデータ構造

- **戻り値**:
  - 成功時：voidのためなし
  - 失敗時：`fprintf()`を使い`stderr`にメッセージを表示し`return`を返す

- **処理内容（アルゴリズム）**:
  1. if文で引数`data`がNULLではないことを確認
  2. if文で`(*data).data`がNULLではない場合に `(*data).data`を開放
  3. 構造体`data`を開放

- **メモリ管理**:
  - 開放専用の関数であるため不要

## 4. 共通エラー処理規定
- `fprintf` を使用し`stderr`へエラーの出力を行い `exit 1` を実行。

## 5. 制限事項
- 現時点で扱える値はfloatのみとする。