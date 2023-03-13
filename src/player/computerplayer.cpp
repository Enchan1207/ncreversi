/// @file
/// @brief 適切な場所に石を自動で配置するCP
///

#include <ctime>

#include "player.hpp"

using namespace flipstone;

namespace ncreversi {

Point ComputerPlayer::requirePointToPutStone(Reversi& reversi) {
    // 最も多くの石をひっくり返せる点を探す
    uint8_t maxFlippableCount = 0;
    flipstone::Point maxFlippablePoint(-1, -1);
    for (uint8_t y = 0; y < 8; y++) {
        for (uint8_t x = 0; x < 8; x++) {
            // 盤面の状態を取得し、より多くの石をひっくり返せる点を更新していく
            const flipstone::Point point(x, y);
            uint8_t flippableCount = reversi.createFlippablePointsList(point, currentStoneKind, nullptr);
            if (flippableCount > maxFlippableCount) {
                maxFlippableCount = flippableCount;
                maxFlippablePoint = point;

                // 人間アピール
                struct timespec delay = {0, 50000000};  // 50ms
                screen.drawFieldCursor(point, id);
                screen.refreshScreen();
                nanosleep(&delay, nullptr);
                screen.eraseFieldCursor(point);
                screen.refreshScreen();
                nanosleep(&delay, nullptr);
            }
        }
    }

    return maxFlippablePoint;
}

}  // namespace ncreversi
