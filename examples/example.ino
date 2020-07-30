#include "GFX4dGrid.h"

GFX4d gfx = GFX4d();
GFX4dGrid *grid;
int led;

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

void cancelPress(int val, int id){
  Serial.print("Cancel: ");
  if(val == 2){
    Serial.println("pressed");
  } else {
    Serial.println("released");
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
  String ok = " Ok";
  String cancel = "Cancel";

  grid = new GFX4dGrid(&gfx, 320, 240, 12,16,4,1);
  grid->addButton(BLUE, DARKBLUE, WHITE, 6,14,6,2, ok, &okPress, 1, 1);
  grid->addButton(RED, DARKRED, WHITE, 0,14,6,2, cancel, &cancelPress, 1, 2);
  led = grid->addLedGroup(4,0,BLACK, WHITE, 3);
  grid->addSlider(GREEN, RED, WHITE, 1,4,10,2, &updateLed, 0, 1);
  grid->addToggleButton(colors, 2, GRAY, WHITE, 4, 8, 4, 2, options, 2, &okPress, 2, 3); 
}

void loop() {
 grid->loop();
 delay(10);
 yield();
}