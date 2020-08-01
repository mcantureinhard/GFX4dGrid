#include "GFX4dGrid.h"
#include "PWButton.h"
#include "PWSlider.h"
#include "LedGroup.h"
#include "ToggleButton.h"


GFX4dGrid::GFX4dGrid(GFX4d *gfx, int height, int width, int gridx, int gridy, int nInputs, int nOutputs){
    this->gfx = gfx;
    this->h = height;
    this->w = width;
    this->gridx = gridx;
    this->gridy = gridy;
    this->nInputs = nInputs;
    this->nOutputs = nOutputs;
    this->gx = w/gridx;
    this->gy = h/gridy;
    this->paddingx = (w%gridx)/2;
    this->paddingy = (h%gridy)/2;
    this->lastTouch = 0;
    grid = new int*[gridy];
    for(int i = 0; i < gridy; ++i) {
        grid[i] = new int[gridx]();
    }
    this->input_count = 0;
    this->output_count = 0;
    if(nInputs){
        inputs = new PrimitiveInput*[nInputs];
    }
    if(nOutputs){
        outputs = new PrimitiveOutput*[nOutputs];
    }
}

GFX4dGrid::~GFX4dGrid(){
    for(int i = 0; i < gridy; ++i) {
        delete [] grid[i];
    }
    delete [] grid;
    if(input_count){
        for(int i = 0; i < input_count; i++){
            delete inputs[i];
        }
        delete [] inputs;
    }
    if(output_count){
        for(int i = 0; i < output_count; i++){
            delete outputs[i];
        }
        delete [] outputs;
    }
}

// I don't think adding collision detection code makes sense, it can be fix manually

int GFX4dGrid::addSlider(uint16_t colorb, uint16_t colorbp, uint16_t tcolor, uint16_t x, uint16_t y, uint16_t w, uint16_t h, void (*callback)(int,int,int), uint8_t initial_pos, int id){
    if(input_count >= nInputs){
        return -1;
    }
    uint16_t x_ = x * gx + paddingx;
    uint16_t y_ = y * gy + paddingy;
    uint16_t w_ = w * gx;
    uint16_t h_ = h * gy;
    PWSlider *slider = new PWSlider(colorb, colorbp, tcolor, x_, y_,w_,h_,this->gfx, callback, initial_pos, id);
    inputs[input_count] = slider;
    for(int i = x; i < x + w; i++){
        for(int j = y; j < y + h; j++){
            grid[j][i] = input_count+1;
        }
    }
    this->input_count++;
    return (this->input_count-1);
}
int GFX4dGrid::addButton(uint16_t colorb, uint16_t colorbp, uint16_t tcolor, uint16_t x, uint16_t y, uint16_t w, uint16_t h, String text, void (*callback)(int,int,int), int textsize, int id){
    if(input_count >= nInputs){
        return -1;
    }
    uint16_t x_ = x * gx + paddingx;
    uint16_t y_ = y * gy + paddingy;
    uint16_t w_ = w * gx;
    uint16_t h_ = h * gy;
    PWButton *button = new PWButton(colorb,colorbp, tcolor, x_,y_,w_,h_,text,this->gfx, callback, textsize, id);
    inputs[input_count] = button;
    for(int i = x; i < x + w; i++){
        for(int j = y; j < y + h; j++){
            grid[j][i] = input_count+1;
        }
    }
    this->input_count++;
    return (this->input_count-1);
}

int GFX4dGrid::addToggleButton(uint16_t *colorb, int colors, uint16_t colorbp, uint16_t tcolor, uint16_t x, uint16_t y, uint16_t w, uint16_t h, String *textOptions, int options, void (*callback)(int, int,int), int textsize, int id, int selected){
    if(input_count >= nInputs){
        return -1;
    }
    uint16_t x_ = x * gx + paddingx;
    uint16_t y_ = y * gy + paddingy;
    uint16_t w_ = w * gx;
    uint16_t h_ = h * gy;
    ToggleButton *button = new ToggleButton(colorb, colors, colorbp, tcolor, x_,y_,w_,h_,textOptions,options,this->gfx, callback, textsize, id, selected);
    inputs[input_count] = button;
    for(int i = x; i < x + w; i++){
        for(int j = y; j < y + h; j++){
            grid[j][i] = input_count+1;
        }
    }
    this->input_count++;
    return (this->input_count-1);
}

int GFX4dGrid::addNumericInput(uint16_t colorb, uint16_t colorbp, uint16_t tcolor, uint16_t x, uint16_t y, uint16_t w, uint16_t h, void (*callback)(int, int, int), int textsize, int id, uint8_t flags){
    if(input_count >= nInputs){
        return -1;
    }
    uint16_t x_ = x * gx + paddingx;
    uint16_t y_ = y * gy + paddingy;
    uint16_t w_ = w * gx;
    uint16_t h_ = h * gy;
    NumericInput *numInput = new NumericInput(colorb, colorbp, tcolor, x_,y_,w_,h_,this->gfx, callback, textsize, id, flags);
    inputs[input_count] = numInput;
    for(int i = x; i < x + w; i++){
        for(int j = y; j < y + h; j++){
            grid[j][i] = input_count+1;
        }
    }
    this->input_count++;
    return (this->input_count-1);
}

int GFX4dGrid::addLedGroup(uint16_t x, uint16_t y, uint16_t colorb, uint16_t tcolor, int count, int32_t initialValue){
    uint16_t x_ = x * gx + paddingx;
    uint16_t y_ = y * gy + paddingy;
    LedGroup *led = new LedGroup(x_, y_, colorb, tcolor, count, this->gfx, initialValue);
    outputs[output_count] = led;
    output_count++;
    return output_count-1;
}

void GFX4dGrid::updateOutput(int32_t val, int nOutput){
    if(nOutput >= output_count){
        return;
    }
    outputs[nOutput]->update(val);
}

int32_t GFX4dGrid::getOutputValue(int nOutput){
    if(nOutput >= output_count){
        return -1;
    }
    return outputs[nOutput]->getValue();
}

void GFX4dGrid::resetInput(int nInput){
    if(nInput >= input_count){
        return;
    }
    inputs[nInput]->reset();
}

void GFX4dGrid::setInputEnabled(int nInput, bool enabled){
    if(nInput >= input_count){
        return;
    }
    inputs[nInput]->setEnabled(enabled);
}

void GFX4dGrid::loop(){
    if (gfx->touch_Update()) {
        uint16_t tx = this->gfx->touch_GetX();
        uint16_t ty = this->gfx->touch_GetY();
        if(tx > this->w || ty > this->h){
            if(lastTouch != 0){
                inputs[lastTouch-1]->released();
            }
            return;
        }
        uint16_t tx_ = tx/this->gx;
        uint16_t ty_ = ty/this->gy;
        if(tx_ >= gridx){
            tx_ = gridx -1;
        }
        if(ty_ >= gridy){
            ty_ = gridy -1;
        }
        int touch = grid[ty_][tx_];
        if(lastTouch != 0 && lastTouch != touch){
            inputs[lastTouch-1]->released();
        }
        if(touch > 0){
            inputs[touch-1]->touched(tx,ty);
        }
        lastTouch = touch;
    }
}
