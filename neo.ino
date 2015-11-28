#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define BUTTON_PIN   2    // Digital IO pin connected to the button.  This will be
                          // driven with a pull-up resistor so the switch should
                          // pull the pin to ground momentarily.  On a high -> low
                          // transition the button press logic will execute.

#define PIXEL_PIN    0    // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 60

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

bool oldState = HIGH;
int showType = 0;
int bright = 7;    //select 1 thru 10


void setup() {
      // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Get current button state.
  bool newState = digitalRead(BUTTON_PIN);

  // Check if state changed from high to low (button press).
  if (newState == LOW && oldState == HIGH) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if (newState == LOW) {
      showType++;
      if (showType > 4) // Be sure to update with same number of options in case statement below.	
        showType=0;
      startShow(showType);
    }
  }

  // Set the last button state to the old state.
  oldState = newState;
}

void startShow(int i) {
  switch(i){
    case 0: colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
            break;
    case 1: colorWipe(strip.Color(255, 0, 0), 50);  // Red
            break;
    case 2: colorWipe(strip.Color(0, 255, 0), 50);  // Green
            break;
    case 3: colorWipe(strip.Color(0, 0, 255), 50);  // Blue
            break;
    case 4: xmasRandom(); // Random color flash
    		    break;
    //case 4: theaterChase(strip.Color(127, 127, 127), 50); // White
    //        break;
    //case 5: theaterChase(strip.Color(127,   0,   0), 50); // Red
    //        break;
    //case 6: theaterChase(strip.Color(  0,   0, 127), 50); // Blue
    //        break;
    //case 7: rainbow(20);
    //        break;
    //case 8: rainbowCycle(20);
    //        break;
    //case 9: theaterChaseRainbow(50);
    //        break;
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void xmasRandom() {
 for(int i=0; i<strip.numPixels(); i++) {
    int wait = .20 ;  
    int randr = random(0,(25*bright));
    int randg = random(0,(25*bright)); 
    int randb = random(0,(25*bright));
    int randi = random(1,strip.numPixels());
    int randii = random(1,strip.numPixels());
      strip.setPixelColor(randi, randr, randg, randb);
     // strip.setPixelColor(i-1, strip.Color(r,g,(b-150)));
     // strip.setPixelColor(i-2, strip.Color(r,g,(b-200)));
     // strip.setPixelColor(i-3, strip.Color(r,g,(b-250))); // add more of these lines to make the trail longer
      strip.show();
      //delay(100);
      //strip.setPixelColor(randii, strip.Color(0,0,0)); // make sure the i-number is the amount of the trail
      //strip.show();
      delay(wait);   
	}
}
