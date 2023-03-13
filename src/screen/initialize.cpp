/// @file
/// @brief 初期化処理など
///

#include "screen.hpp"

namespace ncreversi {

Screen::Screen() {
    initscr();
    start_color();
    initColorPallet();
    noecho();
    keypad(stdscr, true);
    curs_set(0);

    // 原点調整
    setOrigin(0, 0);
    situationOriginX = originX + 41;
    situationOriginY = originY + 6;
}

Screen::~Screen() {
    endwin();
}

void Screen::initColorPallet() {
    // カスタム色番号をわざわざオープンにする必要はないので、ここでまとめて定義

    // フィールドグリッド前景色
    init_color(0x10, 800, 800, 800);

    // 盤面背景色
    init_color(0x11, 0, 600, 0);

    // ペア生成
    init_pair(CUSTOM_COLOR(CustomColor::OuterFrame), COLOR_WHITE, COLOR_WHITE);
    init_pair(CUSTOM_COLOR(CustomColor::InnerFrame), COLOR_BLACK, COLOR_BLACK);
    init_pair(CUSTOM_COLOR(CustomColor::FieldGrid), 0x10, 0x11);
    init_pair(CUSTOM_COLOR(CustomColor::BlackStone), COLOR_BLACK, 0x11);
    init_pair(CUSTOM_COLOR(CustomColor::WhiteStone), COLOR_WHITE, 0x11);
    init_pair(CUSTOM_COLOR(CustomColor::FieldCursor1), COLOR_RED, 0x11);
    init_pair(CUSTOM_COLOR(CustomColor::FieldCursor2), COLOR_BLUE, 0x11);
    init_pair(CUSTOM_COLOR(CustomColor::InfoStrings), COLOR_BLACK, COLOR_WHITE);
    init_pair(CUSTOM_COLOR(CustomColor::InfoCursor1), COLOR_RED, COLOR_WHITE);
    init_pair(CUSTOM_COLOR(CustomColor::InfoCursor2), COLOR_BLUE, COLOR_WHITE);
    init_pair(CUSTOM_COLOR(CustomColor::HelperNum1), COLOR_WHITE, COLOR_RED);
    init_pair(CUSTOM_COLOR(CustomColor::HelperNum2), COLOR_WHITE, COLOR_BLUE);
    init_pair(CUSTOM_COLOR(CustomColor::TitleStrings), COLOR_WHITE, COLOR_BLACK);
}

void Screen::clearScreen() {
    clear();
}

void Screen::refreshScreen() {
    refresh();
}

void Screen::setOrigin(uint8_t x, uint8_t y) {
    originX = x;
    originY = y;
}

void Screen::convertPointToCoordinate(const flipstone::Point& point, uint8_t& x, uint8_t& y) {
    uint8_t baseX = originX + 6;
    uint8_t baseY = originY + 3;

    x = point.x * 4 + baseX;
    y = point.y * 2 + baseY;
}

}  // namespace ncreversi
