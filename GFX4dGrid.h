#ifndef _GFX4dGrid_H
#define _GFX4dGrid_H

#include "GFX4d.h"
#include "PrimitiveInput.h"
#include "PrimitiveOutput.h"
#include "PWButton.h"
#include "PWSlider.h"
#include "LedDigit.h"
#include "NumericInput.h"


class GFX4dGrid {
    private:
    GFX4d *gfx;
    uint8_t gridx;
    uint8_t gridy;
    uint16_t h;
    uint16_t w;
    uint8_t gx;
    uint8_t gy;
    uint8_t paddingx;
    uint8_t paddingy;
    uint8_t input_count;
    uint8_t output_count;
    uint8_t nInputs;
    uint8_t nOutputs;
    int lastTouch;
    PrimitiveOutput **outputs;
    PrimitiveInput **inputs;
    int **grid;
    public:
    // I decided to use number inputs/outputs to avoid resizing
    GFX4dGrid(GFX4d *gfx, int height, int width, int gridx, int gridy, int nInputs, int nOutputs);
    ~GFX4dGrid();
    int addSlider(uint16_t colorb, uint16_t colorbp, uint16_t tcolor, uint16_t x, uint16_t y, uint16_t w, uint16_t h, void (*callback)(int,int, int), uint8_t initial_pos, int id);
    int addButton(uint16_t colorb, uint16_t colorbp, uint16_t tcolor, uint16_t x, uint16_t y, uint16_t w, uint16_t h, String text, void (*callback)(int, int, int), int textsize, int id);
    int addToggleButton(uint16_t *colorb, int colors, uint16_t colorbp, uint16_t tcolor, uint16_t x, uint16_t y, uint16_t w, uint16_t h, String *textOptions, int options, void (*callback)(int, int, int), int textsize, int id);
    int addNumericInput(uint16_t colorb, uint16_t colorbp, uint16_t tcolor, uint16_t x, uint16_t y, uint16_t w, uint16_t h, void (*callback)(int, int, int), int textsize, int id, uint8_t flags);
    int addLedGroup(uint16_t x, uint16_t y, uint16_t colorb, uint16_t tcolor, int count);
    void updateOutput(int32_t val, int nOutput);
    int32_t getOutputValue(int nOutput);
    void resetInput(int nInput);
    void setInputEnabled(int, bool);
    void loop();
};

#endif