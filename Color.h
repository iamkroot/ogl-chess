#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

/**
 * @brief Representation of color for easy use with glColor4fv
 */
typedef struct {
    float rgba[4];
} Color;

#define fromHex(r, g, b) {(float) r / 256, (float) g / 256, (float) b / 256, 1}

namespace Colors {
    const Color WHITE = {1, 1, 1, 1};
    const Color BLACK = {0, 0, 0, 0};
    const Color RED = {1, 0, 0, 1};
    const Color GREEN = {0, 1, 0, 1};
    const Color BLUE = {0, 0, 1, 1};
    const Color SKY_BLUE = {0.529, 0.808, 0.922, 1};
    const Color SILVER = {0.6, 0.6, 0.6, 1};
    const Color LIGHT_GREY = {0.4, 0.4, 0.4, 1};
    const Color DARK_GREY = {0.125, 0.125, 0.125, 1};
    const Color BROWN = {0.75390625, 0.6015625, 0.41796875, 1};
    const Color COFFEE = fromHex(0x4B, 0x37, 0x1C);
    const Color CHOCOLATE = fromHex(0x23, 0x17, 0x09);
    const Color TAWNY = fromHex(0x80, 0x47, 0x1C);
}

#undef fromHex

/**
 * @brief Color palette for the scene
 */
typedef struct {
    Color bg;
    Color board_light;
    Color board_dark;
    Color board_side;
    Color piece_light;
    Color piece_dark;
} Palette;

extern Palette palette;
#endif //COLOR_H
