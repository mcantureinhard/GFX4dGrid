#include "GFX4dGrid.h"

GFX4d gfx = GFX4d();
GFX4dGrid *grid;
int led;
int slider;

String options[] = {"ON", "OFF"};
uint16_t colors[] = {SEAGREEN,MEDIUMVIOLETRED};

void okPress(int val, int id){
  Serial.print("OK: ");
  if(val == 2){
    Serial.println("pressed");
  } else {
    Serial.println("released");
  }
}

void clearPress(int val, int id){
  Serial.print("Cancel: ");
  if(val == RELEASED){
    grid->updateOutput(0, led);
    grid->resetInput(slider);
  }
}

void cb(int v, int d){
  if(v == RELEASED){
    int32_t val = grid->getOutputValue(led);
    val *= 10;
    val += d;
    val %= 1000;
    updateLed(val, d);
  }
}


void updateLed(int val, int id){
  grid->updateOutput((uint16_t)val, led);
}

void setup() {
  Serial.begin(115200);
  gfx.begin();
  gfx.Cls();
  gfx.ScrollEnable(true);
  gfx.BacklightOn(true);
  gfx.Orientation(PORTRAIT);
  gfx.SmoothScrollSpeed(5);
  gfx.TextColor(WHITE); gfx.Font(2);  gfx.TextSize(1);
  gfx.touch_Set(TOUCH_ENABLE);
  String ok = "NOP";

  grid = new GFX4dGrid(&gfx, 320, 240, 12,16,5,1);
  grid->addButton(BLUE, DARKBLUE, WHITE, 6,14,6,2, ok, &okPress, 2, 1);
  grid->addButton(RED, DARKRED, WHITE, 0,14,6,2, "clear", &clearPress, 2, 2);
  led = grid->addLedGroup(0,0,BLACK, WHITE, 3);
  slider = grid->addSlider(GREEN, RED, WHITE, 1,4,10,2, &updateLed, 0, 1);
  grid->addToggleButton(colors, 2, GRAY, WHITE, 6, 0, 4, 4, options, 2, &okPress, 2, 3);
  grid->addNumericInput(BLACK, WHITE, WHITE, 0,6,12,8, &cb, 2, 4, 0);
}

void loop() {
 grid->loop();
 delay(10);
 yield();
}