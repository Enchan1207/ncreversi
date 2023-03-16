/// @file
/// @brief 画面描画
///

#ifndef SIMPLE_REVERSI_SCREEN_H
#define SIMPLE_REVERSI_SCREEN_H

#include <ncurses.h>

#include <cstdint>
#include <flipstone/reversi.hpp>

#define CUSTOM_COLOR(n) static_cast<uint8_t>(n)
#define CUSTOM_COLOR_PAIR(n) COLOR_PAIR(CUSTOM_COLOR(n))

namespace ncreversi {

/// @brief ゲーム画面
class Screen final {
   private:
    Screen();
    ~Screen();

    /// @brief 表示原点x
    uint8_t originX = 0;

    /// @brief 表示原点y
    uint8_t originY = 0;

    /// @brief 戦況原点x
    uint8_t situationOriginX = 0;

    /// @brief 戦況原点y
    uint8_t situationOriginY = 0;

    /// @brief カラーパレットを初期化
    void initColorPallet();

    /// @brief リバーシの盤面座標をスクリーン座標に変換
    /// @param point リバーシ盤面座標
    /// @param x 変換後座標x
    /// @param y 変換後座標y
    void convertPointToCoordinate(const flipstone::Point& point, uint8_t& x, uint8_t& y);

   public:
    /// @brief 内部で扱う色
    enum class CustomColor : uint8_t {

        /// @brief 外枠・背景
        OuterFrame = 0x20,

        /// @brief 内枠
        InnerFrame = 0x21,

        /// @brief フィールドグリッド
        FieldGrid = 0x22,

        /// @brief 黒い石が置かれているセル
        BlackStone = 0x23,

        /// @brief 白い石が置かれているセル
        WhiteStone = 0x24,

        /// @brief カーソル1
        FieldCursor1 = 0x25,

        /// @brief カーソル2
        FieldCursor2 = 0x26,

        /// @brief ゲーム情報文字列
        InfoStrings = 0x27,

        /// @brief ゲーム情報側でのカーソル1
        InfoCursor1 = 0x28,

        /// @brief ゲーム情報側でのカーソル2
        InfoCursor2 = 0x29,

        /// @brief ヘルパー数字1
        HelperNum1 = 0x2A,

        /// @brief ヘルパー数字2
        HelperNum2 = 0x2B,

        /// @brief タイトル文字列
        TitleStrings = 0x2C
    };

    /// @brief 共有インスタンスの取得
    /// @return Screen& 共有インスタンス
    static Screen& shared() {
        static Screen screen;
        return screen;
    }

    Screen(const Screen&) = delete;
    Screen& operator=(const Screen&) = delete;

    /// @brief 画面をクリアする
    void clearScreen();

    /// @brief 画面をリフレッシュする
    void refreshScreen();

    /// @brief スクリーン表示原点の設定
    /// @param x 表示原点x
    /// @param y 表示原点y
    void setOrigin(uint8_t x, uint8_t y);

    // -- スタティックな情報 (ゲーム中に大きく変化しない部分)

    /// @brief ゲーム画面外枠の描画
    void drawFrame();

    /// @brief 盤面の描画
    void drawBoardBackground();

    /// @brief 盤面グリッドの描画
    void drawBoardGrid();

    /// @brief ゲーム情報フレームの描画
    void drawInfoFrame();

    /// @brief タイトル画面の描画
    /// @note この関数は盤面を破壊します。復元にはdrawBoardBackground, drawBoardGridを呼び出してください。
    void drawTitle();

    /// @brief リザルト画面の描画
    /// @note この関数は盤面を破壊します。復元にはdrawBoardBackground, drawBoardGridを呼び出してください。
    void drawResult(flipstone::Reversi& reversi);

    // -- ダイナミックな情報 (ゲーム中に大きく変化しうる部分)

    /// @brief プレイヤーごとの石の個数表示を更新
    void drawSituation(flipstone::Reversi& reversi);

    /// @brief ターンカーソルの描画
    /// @param id プレイヤーID
    /// @note この関数は単純に現在のターンに対応する位置にカーソルを描画します。
    ///       (Screenはカーソルの位置や状態を関知しません。)
    void drawTurnCursor(const uint8_t id);

    /// @brief ターンカーソルの削除
    void eraseTurnCursors();

    /// @brief 石の描画
    /// @param reversi 参照するリバーシ盤面
    void drawStones(flipstone::Reversi& reversi);

    /// @brief 位置選択カーソルの描画
    /// @param point 盤面位置
    /// @param id プレイヤーID
    /// @note この関数は単純に盤面位置に対応する位置にカーソルを描画します。
    ///       (Screenはカーソルの位置や状態を関知しません。)
    void drawFieldCursor(const flipstone::Point& point, const uint8_t id);

    /// @brief 位置選択カーソルの削除
    /// @param point 盤面位置
    void eraseFieldCursor(const flipstone::Point& point);

    /// @brief ヘルパ(ひっくり返せる石の数)の描画
    /// @param reversi 参照するリバーシ盤面
    /// @param id プレイヤーID
    void drawHelper(flipstone::Reversi& reversi, const uint8_t id);

    /// @brief ヘルパの削除
    /// @param reversi 参照するリバーシ盤面
    void eraseHelper(flipstone::Reversi& reversi);
};

}  // namespace ncreversi

#endif /* SIMPLE_REVERSI_SCREEN_H */
