#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

AsyncDelay delay_1s;

int savePin[10][2] = {
  {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}
};

void setup() {
  CircuitPlayground.begin();
  CircuitPlayground.playTone(1000, 200); // Play a tone to indicate the start of the program
}

void loop() {

  int sound = CircuitPlayground.mic.soundPressureLevel(10);

  if (delay_1s.isExpired()) {
    // Rotate LEDs in a circle and allow user to select the combination
    for (int i = 0; i < 10; i++) {
      int currentSave = savePin[i][0];
      int green = map(i, 0, 9, 50, 255);
      CircuitPlayground.setPixelColor(currentSave, 0, green, 0);   
      delay(100);

      if (CircuitPlayground.rightButton()) {
        // saves the users input LED color
        CircuitPlayground.playTone(500, 200);             
        delay(500);
        break;
      }
      if (CircuitPlayground.leftButton()) {
        //rests the clock
        CircuitPlayground.clearPixels();
        CircuitPlayground.playTone(800, 200);
      }
      int red = map(sound, 0, 50, 50, 255);
      int brightness = map(currentSave, 0, 10, 50, 255);
      CircuitPlayground.setPixelColor(currentSave, red, 0, brightness);
    }
    delay_1s.repeat();
  }
}
