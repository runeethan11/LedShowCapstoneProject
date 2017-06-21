#include <Adafruit_NeoPixel.h>

//Pins 2 and 3 can generate interrupts and correpspond to interrupt vectors 0 and 1 respectively
#define ButPin0 2 //Pin forward button is hooked up to
#define ButPin1 3 //Pin backward button is hooked up to.
#define LedPin 0 //Pin Leds are hooked up to
#define NumLeds 60 //Number of Leds in strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NumLeds, LedPin, NEO_GRB + NEO_KHZ800);

unsigned long LastInterrupt0;
unsigned long LastInterrupt1;
int CurrentLedShow = 0; //The variable that holds the current led pattern type

void setup()
{
  pinMode(ButPin0, INPUT_PULLUP);
  pinMode(ButPin1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ButPin0), ForwardButton, RISING); //Sets pin 2 as the forward pin intterupt
  attachInterrupt(digitalPinToInterrupt(ButPin1), BackwardButton, RISING); //Sets pin 3 as the backwards pin intterupt
  
  strip.begin(); //intializes led's
  strip.setBrightness(10); //set's the led brightness
  strip.show(); //supposedly intializes all leds to an off state
}

void loop()
{
  LedShows(CurrentLedShow);
}

//Check for if the button is pressed
void ForwardButton()
{
  //sets a no interrupt window however many milliseconds long
  if (millis() - LastInterrupt0 > 100)
  {
    //changes the led show that is being run to the next one in line
    CurrentLedShow = CurrentLedShow + 1;
    
    LastInterrupt0 = millis();
  }
}

void BackwardButton()
{
  //sets a no interrupt window however many milliseconds long
  if (millis() - LastInterrupt1 > 100)
  {
    //changes the led show that is being run to the previous one
    CurrentLedShow = CurrentLedShow - 1;
    
    LastInterrupt1 = millis();
  }
}

//runs the Led show that is currently selected
void LedShows(int i)
{
  //each case is an led show that will be run
  //it runs the case that corresponds to the variable the function is giving
  switch(i)
  {
    case 0: Chase(strip.Color(0, 200, 180), 8, 30, 0); // Ethan's Colour
            break;
    case 1: Chase(strip.Color(255, 30, 20),15, 20, 1); // Ben's Colour
            break;
    case 2: Chase(strip.Color(200, 130, 0), 30, 40, 2); // Colour
            break;
    case 3: Chase(strip.Color(183, 54, 7),60, 10, 3); // Damien's Colour
            break;
    case 4: Bounce(strip.Color(255, 20, 147), 5, 30, 4); //Jensen's Colour
            break;
    case 5: DoubleBounce(strip.Color(72, 6, 213), strip.Color(76, 152, 3), 6, 30, 5); // Molly and Kira's Colour
            break;
    case 6: DoubleHalfBounce(strip.Color(76, 220, 171), strip.Color(200, 0, 0), 6, 30, 6); // Jack and Someones Colour
            break;
    
  }
}

//turns off all led's
void LedOff(int Pixels)
{
  for(int i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i, 0);
  }
  strip.show();
}

//Simple chase
static void Chase(uint32_t colour1, int Pixels, int Delayed, int CurrentCase)
{
  
  
  for(int i=0; i<strip.numPixels()+Pixels; i++)
  {
    if (CurrentCase != CurrentLedShow)
    {
      LedOff(Pixels);
      break;
    }
    strip.setPixelColor(i  , colour1); // Draw new pixel
    strip.setPixelColor(i-Pixels, 0); // Erase pixel a few steps back
    strip.show();
    delay(Delayed);
  }
}

//one chase backing back and forth
void Bounce(uint32_t colour1, int Pixels, int Delayed, int CurrentCase)
{

  for(int i=0+Pixels; i<strip.numPixels(); i++)
  {
    
    if (CurrentCase != CurrentLedShow)
    {
      LedOff(Pixels);
      break;
    }
    
    strip.setPixelColor(i, colour1); //Draws a new pixel
    strip.setPixelColor(i-Pixels, 0); //Erases pixel however many steps back
    strip.show();
    delay(Delayed); //how big the delay is before the next pixels get written and erased
  }
  
  for (int i = strip.numPixels()-Pixels; i>=0; i--)
  {
    
   if (CurrentCase != CurrentLedShow)
   {
     LedOff(Pixels);
     break;
   }
  
   strip.setPixelColor(i, colour1); //Draw new pixel
   strip.setPixelColor(i+Pixels, 0); //Erases pixels however many steps back
   strip.show();
  
   delay(Delayed); //how big the delay is before the next pixels get written and erased  
  }
}

//two chases backing back and forth
void DoubleBounce(uint32_t colour1, uint32_t colour2, int Pixels, int Delayed, int CurrentCase)
{
  
  for(int i=0 + Pixels; i < strip.numPixels()+1; i++)
  {
    
    if (CurrentCase != CurrentLedShow)
    {
      LedOff(Pixels);
      break;
    }
    
    //first chase
    strip.setPixelColor(i, colour1); //Draw new pixel
    strip.setPixelColor(i-Pixels, 0); //Erases pixel however many steps back
    
    //second chase
    strip.setPixelColor(strip.numPixels() - i, colour2); //Draw new pixel on chase thats heading opposite way
    strip.setPixelColor(strip.numPixels() - i + Pixels, 0); //erase pixel few steps back
    
    strip.show();
    delay(Delayed);
  }
  
  for (int i=0 + Pixels; i < strip.numPixels()+1; i++)
  {
    if (CurrentCase != CurrentLedShow)
    {
      LedOff(Pixels);
      break;
    }
    
    
    
    //first chase bouncing back
    strip.setPixelColor(strip.numPixels() - i, colour1); //draws the first colour bouncing back
    strip.setPixelColor(strip.numPixels() - i + Pixels, 0); //erases the pixel however many steps back
    
    //second chase bouncing back
    strip.setPixelColor(i, colour2); //Draws the second colour bouncing back
    strip.setPixelColor(i-Pixels, 0); //Erases the pixel however many steps back
    
    strip.show();
    delay(Delayed);
  }
}

void DoubleHalfBounce(uint32_t colour1, uint32_t colour2, int Pixels, int Delayed, int CurrentCase)
{
  for(int i=0 + Pixels; i < strip.numPixels()+1; i++)
  {
    
    //The first chase across
    if (CurrentCase != CurrentLedShow)
    {
      LedOff(Pixels);
      break;
    }
    
    //first chase
    strip.setPixelColor(i, colour1); //Draw new pixel
    strip.setPixelColor(i-Pixels, 0); //Erases pixel however many steps back
    
    //second chase
    strip.setPixelColor(strip.numPixels() - i, colour2); //Draw new pixel on chase thats heading opposite way
    strip.setPixelColor(strip.numPixels() - i + Pixels, 0); //erase pixel few steps back
    
    strip.show();
    delay(Delayed);   
  }
  
  //The chases bounce back and stop at the middle
  for(int i = 0; i < strip.numPixels / 2 + 1; i++)
  {
    if (CurrentCase != CurrentLedShow)
    {
      LedOff(Pixels)
      break;
    }
  }
  
  //The chases bounce back from the middle to the ends again
  for()
  {
  }
  
  //The chases go from the sides to the other side
  for()
  {
  }
  
  //The chases go to the middle again
  for()
  {
  }
  
  //The chases bounce back to the first side
  for()
  {
  }
}

