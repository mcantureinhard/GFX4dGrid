#include "GFX4dGrid.h"

GFX4d gfx = GFX4d();
GFX4dGrid *grid;
int led;

void okPress(int val){
  Serial.print("OK: ");
  if(val == 2){
    Serial.println("pressed");
  } else {
    Serial.println("released");
  }
}

void cancelPress(int val){
  Serial.print("Cancel: ");
  if(val == 2){
    Serial.println("pressed");
  } else {
    Serial.println("released");
  }
}


void updateLed(int val){
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

  grid = new GFX4dGrid(&gfx, 320, 240, 12,16,3,1);
  grid->addButton(BLUE, DARKBLUE, WHITE, 6,14,6,2, " OK", &okPress, 1);
  grid->addButton(RED, DARKRED, WHITE, 0,14,6,2, "Cancel", &cancelPress, 1);
  led = grid->AddLedGroup(4,0,BLACK, WHITE, 3);
  grid->addSlider(GREEN, RED, WHITE, 1,4,10,2, &updateLed, 0);  
}

void loop() {
 grid->loop();
 delay(10);
 yield();
}