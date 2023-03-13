/// @file
/// @brief ゲーム中に動く部分の描画
///

#include "screen.hpp"

namespace ncreversi {

void Screen::drawSituation(flipstone::Reversi& reversi) {
    attron(CUSTOM_COLOR_PAIR(CustomColor::InfoStrings));

    uint8_t baseX = situationOriginX;
    uint8_t baseY = situationOriginY;

    // 盤面から計数
    uint8_t stoneCount1 = reversi.totalizeCell(flipstone::Cell::Black);
    uint8_t stoneCount2 = reversi.totalizeCell(flipstone::Cell::White);
    uint8_t stoneSymbolCount1 = stoneCount1 / 4;
    uint8_t stoneSymbolCount2 = stoneCount2 / 4;

    // 石の数とその目安
    attron(A_BOLD);
    mvprintw(baseY + 2, baseX + 5, "                ");
    for (uint8_t i = 0; i < stoneSymbolCount1; i++) {
        mvprintw(baseY + 2, baseX + 5 + i, "*");
    }
    mvprintw(baseY + 2, baseX + 24, "  ");
    mvprintw(baseY + 2, baseX + 24, "%d", stoneCount1);

    mvprintw(baseY + 7, baseX + 5, "                ");
    for (uint8_t i = 0; i < stoneSymbolCount2; i++) {
        mvprintw(baseY + 7, baseX + 5 + i, "o");
    }
    mvprintw(baseY + 7, baseX + 24, "  ");
    mvprintw(baseY + 7, baseX + 24, "%d", stoneCount2);

    attrset(0);
}

void Screen::drawTurnCursor(const uint8_t id) {
    uint8_t baseX = situationOriginX;
    uint8_t baseY = situationOriginY;

    // 描画
    attron(A_BOLD);
    if (id == 1) {
        attron(A_BOLD | CUSTOM_COLOR_PAIR(CustomColor::InfoCursor1));
    }
    if (id == 2) {
        baseY += 5;
        attron(A_BOLD | CUSTOM_COLOR_PAIR(CustomColor::InfoCursor2));
    }
    mvprintw(baseY, baseX, ">");

    attrset(0);
}

void Screen::eraseTurnCursors() {
    uint8_t baseX = situationOriginX;
    uint8_t baseY = situationOriginY;

    attron(CUSTOM_COLOR_PAIR(CustomColor::OuterFrame));
    mvprintw(baseY, baseX, " ");
    mvprintw(baseY + 5, baseX, " ");
    attrset(0);
}

void Screen::drawStones(flipstone::Reversi& reversi) {
    attron(A_BOLD);

    for (uint8_t y = 0; y < 8; y++) {
        for (uint8_t x = 0; x < 8; x++) {
            const flipstone::Point point(x, y);
            // 盤面状態を取得
            flipstone::Cell cell = reversi.referCell(point);

            // リバーシの座標をスクリーン座標に変換
            uint8_t coordX = 0;
            uint8_t coordY = 0;
            convertPointToCoordinate(point, coordX, coordY);

            // 書き込み
            if (cell == flipstone::Cell::White) {
                attron(CUSTOM_COLOR_PAIR(CustomColor::WhiteStone));
                mvprintw(coordY, coordX, "o");
                continue;
            }
            if (cell == flipstone::Cell::Black) {
                attron(CUSTOM_COLOR_PAIR(CustomColor::BlackStone));
                mvprintw(coordY, coordX, "*");
                continue;
            }

            attron(CUSTOM_COLOR_PAIR(CustomColor::FieldGrid));
            mvprintw(coordY, coordX, " ");
        }
    }

    attrset(0);
}

void Screen::drawFieldCursor(const flipstone::Point& point, const uint8_t id) {
    // リバーシの座標をスクリーン座標に変換
    uint8_t coordX = 0;
    uint8_t coordY = 0;
    convertPointToCoordinate(point, coordX, coordY);

    // 描画
    attron(A_BOLD);
    if (id == 1) {
        attron(A_BOLD | CUSTOM_COLOR_PAIR(CustomColor::FieldCursor1));
    }
    if (id == 2) {
        attron(A_BOLD | CUSTOM_COLOR_PAIR(CustomColor::FieldCursor2));
    }

    mvprintw(coordY, coordX - 1, "[");
    mvprintw(coordY, coordX + 1, "]");
    attrset(0);
}

void Screen::eraseFieldCursor(const flipstone::Point& point) {
    // リバーシの座標をスクリーン座標に変換
    uint8_t coordX = 0;
    uint8_t coordY = 0;
    convertPointToCoordinate(point, coordX, coordY);

    // 描画
    attron(A_BOLD | CUSTOM_COLOR_PAIR(CustomColor::FieldGrid));
    mvprintw(coordY, coordX - 1, " ");
    mvprintw(coordY, coordX + 1, " ");
    attrset(0);
}

void Screen::drawHelper(flipstone::Reversi& reversi, const uint8_t id) {
    // ヘルパの色を変える
    if (id == 1) {
        attron(CUSTOM_COLOR_PAIR(CustomColor::HelperNum1));
    }
    if (id == 2) {
        attron(CUSTOM_COLOR_PAIR(CustomColor::HelperNum2));
    }

    // 描画
    flipstone::Cell stone = (id == 1) ? flipstone::Cell::Black : flipstone::Cell::White;
    for (uint8_t y = 0; y < 8; y++) {
        for (uint8_t x = 0; x < 8; x++) {
            const flipstone::Point point(x, y);
            // 盤面状態を取得
            flipstone::Cell cell = reversi.referCell(point);

            // リバーシの座標をスクリーン座標に変換
            uint8_t coordX = 0;
            uint8_t coordY = 0;
            convertPointToCoordinate(point, coordX, coordY);

            // 空のセルのみ計算・表示
            if (cell != flipstone::Cell::Empty) {
                continue;
            }

            uint8_t count = reversi.createFlippablePointsList(point, stone, nullptr);
            if (count == 0) {
                continue;
            }

            if (count < 10) {
                mvprintw(coordY, coordX, "%d", count);
            } else {
                mvprintw(coordY, coordX, "#");
            }
        }
    }

    attrset(0);
}

void Screen::eraseHelper(flipstone::Reversi& reversi) {
    attron(CUSTOM_COLOR_PAIR(CustomColor::FieldGrid));
    for (uint8_t y = 0; y < 8; y++) {
        for (uint8_t x = 0; x < 8; x++) {
            const flipstone::Point point(x, y);
            // 盤面状態を取得
            flipstone::Cell cell = reversi.referCell(point);

            // リバーシの座標をスクリーン座標に変換
            uint8_t coordX = 0;
            uint8_t coordY = 0;
            convertPointToCoordinate(point, coordX, coordY);

            // 空のセルのみ塗りつぶす
            if (cell == flipstone::Cell::Empty) {
                mvprintw(coordY, coordX, " ");
            }
        }
    }

    attrset(0);
}

}  // namespace ncreversi
