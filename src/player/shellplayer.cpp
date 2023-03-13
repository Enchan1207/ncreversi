/// @file
/// @brief シェルを持つ実際のプレイヤー
///

#include "player.hpp"

using namespace flipstone;

namespace ncreversi {

Point ShellPlayer::requirePointToPutStone(Reversi& reversi) {
    flipstone::Point cursorPos = lastCursorPos;
    flipstone::Point previousPos = cursorPos;

    bool isConfirmed = false;
    while (!isConfirmed) {
        screen.eraseFieldCursor(previousPos);
        screen.drawFieldCursor(cursorPos, id);
        screen.refreshScreen();

        // キー待機
        previousPos = cursorPos;
        switch (getch()) {
            case KEY_UP:
                if (cursorPos.y > 0) {
                    cursorPos.advance(flipstone::Direction(0, -1));
                }
                break;

            case KEY_DOWN:
                if (cursorPos.y < 7) {
                    cursorPos.advance(flipstone::Direction(0, 1));
                }
                break;

            case KEY_LEFT:
                if (cursorPos.x > 0) {
                    cursorPos.advance(flipstone::Direction(-1, 0));
                }
                break;

            case KEY_RIGHT:
                if (cursorPos.x < 7) {
                    cursorPos.advance(flipstone::Direction(1, 0));
                }
                break;

            case ' ':
                isConfirmed = true;
                break;

            default:
                break;
        }
    }

    // 確定
    screen.eraseFieldCursor(cursorPos);
    screen.refreshScreen();
    lastCursorPos = cursorPos;
    return cursorPos;
}

}  // namespace ncreversi
