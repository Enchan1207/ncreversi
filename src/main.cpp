/// @file
/// @brief entrypoint
///

#include <ncurses.h>

#include "game.hpp"

using namespace ncreversi;

int main(int argc, char const *argv[]) {
    // プレイヤー初期化
    ShellPlayer shellPlayer;
    ComputerPlayer computerPlayer;

    // ゲーム初期化
    Game game(shellPlayer, computerPlayer);

    // ゲームループ
    game.gameloop();
    return 0;
}
