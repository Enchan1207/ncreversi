/// @file
/// @brief プレイヤー基底クラス
///

#ifndef SIMPLE_REVERSI_PLAYER_H
#define SIMPLE_REVERSI_PLAYER_H

#include <ncurses.h>

#include <reversi.hpp>

#include "screen.hpp"

namespace ncreversi {

/// @brief プレイヤーのインタフェースクラス
class Player {
   public:
    /// @brief 画面への参照
    Screen& screen = Screen::shared();

    /// @brief 現在プレイヤーが打つべき石の種類
    flipstone::Cell currentStoneKind = flipstone::Cell::Empty;

    /// @brief プレイヤーID
    uint8_t id = 0;

    /**
     * @brief 盤面の状態をもとに、次に石を置く場所を判断する
     *
     * @param reversi 盤面
     * @return flipstone::Point 次に石を置く場
     */
    virtual flipstone::Point requirePointToPutStone(flipstone::Reversi& reversi) = 0;
};

/// @brief 入出力可能なシェルを持つ実際のプレイヤー
class ShellPlayer final : public Player {
   private:
    /// @brief 前回のカーソル位置
    flipstone::Point lastCursorPos;

   public:
    flipstone::Point requirePointToPutStone(flipstone::Reversi& reversi) override;
};

/// @brief 適切な場所に石を自動で配置するCP
class ComputerPlayer final : public Player {
   public:
    flipstone::Point requirePointToPutStone(flipstone::Reversi& reversi) override;
};

}  // namespace ncreversi

#endif /* SIMPLE_REVERSI_PLAYER_H */
