/// @file
/// @brief ゲームループ管理
///

#ifndef SIMPLE_REVERSI_GAME_H
#define SIMPLE_REVERSI_GAME_H

#include <cstdint>
#include <flipstone/reversi.hpp>

#include "player.hpp"
#include "screen.hpp"

namespace ncreversi {

/// @brief ゲームループ管理
class Game final {
   private:
    /// @brief 画面への参照
    Screen& screen = Screen::shared();

    /// @brief 盤面
    flipstone::Reversi reversi;

    /// @brief プレイヤー1
    Player& player1;

    /// @brief プレイヤー2
    Player& player2;

    /// @brief 現在のプレイヤー
    Player* currentPlayer = &player1;

    /// @brief ターンを交代する
    void switchTurn();

   public:
    /// @brief 2人のプレイヤーを割り当ててゲームを初期化する
    /// @param player1 プレイヤー1
    /// @param player2 プレイヤー2
    Game(Player& player1, Player& player2) : player1(player1), player2(player2){};

    /// @brief ゲームを進行する
    void gameloop();
};

}  // namespace ncreversi

#endif /* SIMPLE_REVERSI_GAME_H */
