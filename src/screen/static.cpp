/// @file
/// @brief スタティックなパーツの描画
///

#include "screen.hpp"

namespace ncreversi {

void Screen::drawFrame() {
    // 外枠
    attron(CUSTOM_COLOR_PAIR(CustomColor::OuterFrame));
    for (size_t y = 0; y < 21; y++) {
        mvprintw(originY + y, originX, "                                                                      ");
    }

    // 内枠
    attron(CUSTOM_COLOR_PAIR(CustomColor::InnerFrame));
    for (size_t y = 1; y < 20; y++) {
        mvprintw(originY + y, originX + 2, "                                     ");
    }

    attrset(0);
}

void Screen::drawBoardBackground() {
    attron(CUSTOM_COLOR_PAIR(CustomColor::FieldGrid));
    for (size_t y = 2; y < 19; y++) {
        mvprintw(originY + y, originX + 4, "                                 ");
    }
    attrset(0);
}

void Screen::drawBoardGrid() {
    attron(CUSTOM_COLOR_PAIR(CustomColor::FieldGrid));

    for (size_t y = 2; y < 19; y++) {
        if (y % 2 == 0) {
            mvprintw(originY + y, originX + 4, "*---+---+---+---+---+---+---+---*");
        } else {
            mvprintw(originY + y, originX + 4, "|   |   |   |   |   |   |   |   |");
        }
    }
    attrset(0);
}

void Screen::drawInfoFrame() {
    attron(CUSTOM_COLOR_PAIR(CustomColor::InfoStrings));

    uint8_t baseX = situationOriginX;
    uint8_t baseY = situationOriginY;

    // プレイヤー名
    attron(A_BOLD);
    mvprintw(baseY, baseX + 2, "Player");
    mvprintw(baseY + 5, baseX + 2, "Computer");
    attroff(A_BOLD);

    // 石の色と数の枠
    mvprintw(baseY + 1, baseX + 4, "stone: black (*)");
    mvprintw(baseY + 2, baseX + 4, "[                ]");
    mvprintw(baseY + 2, baseX + 23, "(  )");
    mvprintw(baseY + 6, baseX + 4, "stone: white (o)");
    mvprintw(baseY + 7, baseX + 4, "[                ]");
    mvprintw(baseY + 7, baseX + 23, "(  )");

    attrset(0);
}

void Screen::drawTitle() {
    attron(A_BOLD | CUSTOM_COLOR_PAIR(CustomColor::TitleStrings));

    uint8_t mainTitleBaseY = originY + 6;
    uint8_t subTitleBaseY = originY + 14;

    mvprintw(mainTitleBaseY - 1, originX + 5, "                               ");
    mvprintw(mainTitleBaseY, originX + 5, "  S I M P L E   R E V E R S I  ");
    mvprintw(mainTitleBaseY + 1, originX + 5, "                      v0.1.0   ");
    mvprintw(subTitleBaseY - 1, originX + 5, "                               ");
    mvprintw(subTitleBaseY, originX + 5, "    Type space key to start    ");
    mvprintw(subTitleBaseY + 1, originX + 5, "                               ");
}

void Screen::drawResult(flipstone::Reversi& reversi) {
    attron(A_BOLD | CUSTOM_COLOR_PAIR(CustomColor::TitleStrings));

    uint8_t baseY = originY + 5;

    mvprintw(baseY + 0, originX + 5, "                               ");
    mvprintw(baseY + 1, originX + 5, "       G a m e   s e t !       ");
    mvprintw(baseY + 2, originX + 5, "                               ");
    mvprintw(baseY + 3, originX + 5, "                               ");
    mvprintw(baseY + 4, originX + 5, "                               ");
    mvprintw(baseY + 5, originX + 5, "                               ");
    mvprintw(baseY + 6, originX + 5, "                               ");
    mvprintw(baseY + 7, originX + 5, "                               ");
    mvprintw(baseY + 8, originX + 5, "                               ");
    mvprintw(baseY + 9, originX + 5, "     Type space key to end     ");
    mvprintw(baseY + 10, originX + 5, "                               ");

    // 計数・表示
    uint8_t stoneCount1 = reversi.totalizeCell(flipstone::Cell::Black);
    uint8_t stoneCount2 = reversi.totalizeCell(flipstone::Cell::White);
    mvprintw(baseY + 3, originX + 11, "Player ......... %2d", stoneCount1);
    mvprintw(baseY + 4, originX + 11, "Computer ....... %2d", stoneCount2);

    if (stoneCount1 > stoneCount2) {
        mvprintw(baseY + 6, originX + 15, "Player win!");
    } else if (stoneCount1 < stoneCount2) {
        mvprintw(baseY + 6, originX + 14, "Computer win!");
    } else {
        mvprintw(baseY + 6, originX + 18, "Draw!");
    }
}

}  // namespace ncreversi
