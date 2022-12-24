#include <Gamebuino-Meta.h>

int timer;
int beepFrame;
bool ignoreRelease;
bool timerLaunched;

const int TIMER_INC = 60;
const int FRAME_PER_SEC = 24;

void raz() {
  raz(true);
}

void raz(bool razTimer) {
  if (razTimer) {
    timer = 0;
  }
  timerLaunched = false;
  beepFrame = 5;
  gb.lights.clear();
  gb.display.clear();
}

void setup() {
  gb.begin();
  raz();
}

void loop() {
  while(!gb.update());

  if (gb.buttons.released(BUTTON_A)) {
    if (ignoreRelease) {
      ignoreRelease = false;
    } else {
      raz(false);
      timer = (TIMER_INC+timer) % (4*TIMER_INC);
      timerLaunched = true;
    }
  }

  if (gb.buttons.held(BUTTON_A, 24)) {
    ignoreRelease = true;
    raz();
  }

  if (timer > 0 && gb.frameCount % FRAME_PER_SEC == 0) {
    gb.lights.clear();
    if (timer >= 3*TIMER_INC) {
      gb.lights.drawPixel(0, 0, RED);
      gb.lights.drawPixel(1, 0, RED);
    } 
    if (timer >= 2*TIMER_INC) {
      gb.lights.drawPixel(0, 1, RED);
      gb.lights.drawPixel(1, 1, RED);
    } 
    if (timer >= TIMER_INC) {
      gb.lights.drawPixel(0, 2, RED);
      gb.lights.drawPixel(1, 2, RED);
    } 

    gb.lights.drawPixel(0, 3, RED);
    gb.lights.drawPixel(1, 3, RED);
    
    gb.display.clear();
    gb.display.print(timer);

    timer--;
  }
  if (timerLaunched && timer == 0 && gb.frameCount % (FRAME_PER_SEC/2) == 0) {
    if (beepFrame > 0) {
      if (beepFrame % 2) {
        gb.lights.setColor(BLUE);
        gb.lights.drawRect(0, 0, 2, 4);
      }
      else {
        gb.lights.clear();
      }
      gb.sound.tone(440*pow(2.0/3.0, 5-beepFrame), 100);
      beepFrame--;
    }
    else {
      raz();
    }
  }
}
