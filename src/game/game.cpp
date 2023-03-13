/// @file
/// @brief ゲームロジック
///

#include "game.hpp"

#include <ncurses.h>

namespace ncreversi {

void Game::switchTurn() {
    currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
}

void Game::gameloop() {
    // タイトルスクリーン: 枠と最低限の情報を描画し、spaceキーを待機
    screen.clearScreen();
    screen.drawFrame();
    screen.drawInfoFrame();
    screen.drawBoardBackground();
    screen.drawBoardGrid();
    screen.drawTitle();
    screen.refreshScreen();
    while (getch() != ' ') {
    }

    // ゲーム準備: リバーシ盤面を初期化して画面を再描画し、各プレイヤーの初期設定を行う
    reversi.initField();
    screen.drawBoardBackground();
    screen.drawBoardGrid();
    screen.drawSituation(reversi);
    screen.drawStones(reversi);
    screen.refreshScreen();

    player1.id = 1;
    player2.id = 2;

    // TODO: 石はルーレット的に決められるようにしたい
    player1.currentStoneKind = flipstone::Cell::Black;
    player2.currentStoneKind = flipstone::Cell::White;

    // メインループ: リバーシが終了するまで続ける
    bool isPreviousPlayerSkipped = false;
    bool isGameOver = false;
    while (!isGameOver) {
        const uint8_t playerID = currentPlayer->id;

        // ターンカーソルを描画
        screen.eraseTurnCursors();
        screen.drawTurnCursor(playerID);
        screen.refreshScreen();

        // 現在のプレイヤーが石を置ける場所がない場合
        if (!reversi.hasPlacablePoint(currentPlayer->currentStoneKind)) {
            // スキップしていなければターンスイッチ そうでなければゲーム終了
            if (!isPreviousPlayerSkipped) {
                beep();
                isPreviousPlayerSkipped = true;
                switchTurn();
            } else {
                isGameOver = true;
            }
            continue;
        }

        // ヘルパを表示
        screen.drawHelper(reversi, playerID);
        screen.refreshScreen();

        // 現在のプレイヤーに対し、石をどこに置くか要求 置ける場所が指定されるまで続ける
        flipstone::Point candidate = flipstone::Point(0, 0);
        bool canPlace = false;
        while (!canPlace) {
            candidate = currentPlayer->requirePointToPutStone(reversi);
            canPlace = reversi.createFlippablePointsList(candidate, currentPlayer->currentStoneKind, nullptr) > 0;
            if (!canPlace) {
                beep();
            }
        }
        reversi.putStone(candidate, currentPlayer->currentStoneKind);

        // ヘルパを隠し、石と数を再描画
        screen.eraseHelper(reversi);
        screen.drawStones(reversi);
        screen.drawSituation(reversi);
        screen.refreshScreen();

        // ターンを切り替えて次へ
        switchTurn();
    }

    // リザルト画面を表示し、終了
    beep();
    screen.eraseHelper(reversi);
    screen.drawSituation(reversi);
    screen.drawResult(reversi);
    screen.refreshScreen();
    while (getch() != ' ') {
    }
}

}  // namespace ncreversi
