# SimpleEncoder

ポーリング方式によるロータリーエンコーダライブラリ（Arduino/ESP32対応）

A polling-based rotary encoder library for Arduino/ESP32 using Gray code state machine.

## 特徴 / Features

- ✅ Gray code 状態遷移テーブルによる高精度デコード
- ✅ チャタリング（接点バウンス）対策
- ✅ 不正遷移の自動無視
- ✅ 割り込み不要のポーリング方式
- ✅ ESP32/Arduino対応

## インストール / Installation

### Arduino IDE

1. このリポジトリをダウンロード
2. Arduino IDE の `スケッチ` → `ライブラリをインクルード` → `.ZIP形式のライブラリをインストール`
3. ダウンロードしたZIPファイルを選択

### PlatformIO

```ini
lib_deps = 
    https://github.com/Igurometsuki/SimpleEncoder.git
```

## 使い方 / Usage

### 基本的な使用例

```cpp
#include "RotaryEncoder.h"

#define PIN_A 32
#define PIN_B 33

RotaryEncoder encoder(PIN_A, PIN_B);

void setup() {
  Serial.begin(115200);
  encoder.begin();
}

void loop() {
  encoder.poll();  // 必ずloop内で呼び出す
  
  int value = encoder.getValue();
  Serial.println(value);
}
```

### 配線 / Wiring

```
ロータリーエンコーダ    ESP32/Arduino
─────────────────────────────────
CLK (A相)        →    PIN_A (例: GPIO 32)
DT  (B相)        →    PIN_B (例: GPIO 33)
GND              →    GND
VCC              →    3.3V or 5V
```

## API リファレンス / API Reference

### コンストラクタ

```cpp
RotaryEncoder(uint8_t pinA, uint8_t pinB, 
              uint16_t sampleIntervalUs = 800, 
              uint8_t detentCount = 4)
```

**パラメータ:**
- `pinA` - A相のピン番号
- `pinB` - B相のピン番号
- `sampleIntervalUs` - サンプリング間隔（マイクロ秒、デフォルト: 800）
- `detentCount` - 1クリックあたりの遷移数（デフォルト: 4）

### メソッド

#### `void begin()`
エンコーダを初期化します（`setup()`内で呼び出し）

#### `void poll()`
エンコーダの状態を更新します（`loop()`内で必ず呼び出し）

#### `int getValue()`
現在のエンコーダ値を取得

#### `void reset()`
値を0にリセット

#### `void setValue(int value)`
値を任意の数値に設定

## サンプル / Examples

### BasicOLED
OLED（SSD1306）にエンコーダの値を表示

```bash
examples/BasicOLED/BasicOLED.ino
```

## パラメータ調整 / Parameter Tuning

### サンプリング間隔（sampleIntervalUs）

チャタリングが発生する場合は値を**大きく**、反応が遅い場合は**小さく**調整

```cpp
RotaryEncoder encoder(PIN_A, PIN_B, 1000);  // 1000μs = 1ms
```

### デテントカウント（detentCount）

エンコーダの仕様に応じて調整（通常は4）

```cpp
RotaryEncoder encoder(PIN_A, PIN_B, 800, 2);  // 1クリック = 2遷移
```

## 仕組み / How It Works

このライブラリは**Gray code状態遷移テーブル**を使用しています:

```
状態 = (A << 1) | B

有効な遷移:
  00 → 01 (+1 CW)
  01 → 11 (+1 CW)
  11 → 10 (+1 CW)
  10 → 00 (+1 CW)
  
  00 → 10 (-1 CCW)
  10 → 11 (-1 CCW)
  11 → 01 (-1 CCW)
  01 → 00 (-1 CCW)
```

不正な遷移（ノイズやバウンス）は自動的に無視されます。

## ライセンス / License

MIT License - 自由に使用・改変・再配布可能

## 作者 / Author

Igurometsuki

## 貢献 / Contributing

プルリクエスト歓迎！バグ報告や機能追加の提案はIssuesへお願いします。
