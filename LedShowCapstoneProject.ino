c#include <Adafruit_NeoPixel.h>

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
  attachInterrupt(digitalPinToInterrupt(ButPin0), ForwardButton, RISING); //Sets pin 2 as the forward pin intterupt, RISING means the interrupt triggers whenever the pin goes from LOW to HIGH
  attachInterrupt(digitalPinToInterrupt(ButPin1), BackwardButton, RISING); //Sets pin 3 as the backwards pin intterupt, RISING means the interrupt triggers whenever the pin goes from LOW to HIGH

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
  if (millis() - LastInterrupt0 > 150)
  {
    //changes the led show that is being run to the next one in line
    CurrentLedShow = CurrentLedShow + 1;

    LastInterrupt0 = millis();
  }
}

void BackwardButton()
{
  //sets a no interrupt window however many milliseconds long
  if (millis() - LastInterrupt1 > 150)
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
  switch (i)
  {
    case 0: Chase(strip.Color(0, 200, 180), 8, 30, 0); // Ethan's Colour
            break;
    case 1: Chase(strip.Color(255, 30, 20), 15, 20, 1); // Ben's Colour
            break;
    case 2: Chase(strip.Color(200, 130, 0), 30, 40, 2); // Random Colour
            break;
    case 3: Chase(strip.Color(183, 54, 7), 60, 10, 3); // Damien's Colour
            break;
    case 4: Bounce(strip.Color(255, 20, 147), 5, 30, 4); //Jensen's Colour
            break;
    case 5: DoubleBounce(strip.Color(72, 6, 213), strip.Color(76, 152, 3), 6, 30, 5); // Molly and Kira's Colour
            break;
    case 6: DoubleHalfBounce(strip.Color(76, 220, 171), strip.Color(244, 184, 0), 10, 38, 6); // Jack and Molly's Favourite Colour
            break;
    case 7: Dashes(strip.Color(180, 14, 100), 10, 5, 200, 7); //{Placeholder Colour
            break;
    case 8: DashErase(strip.Color(40, 190, 60), 10, 5, 175, 8); //Placeholder Colour
            break;
    case 9: DashErase(strip.Color(45, 60, 200), 10, 10, 20, 9); //Placeholder Colour
             break;
    case 10: Wipe(strip.Color(0, 200, 0), 10); //Placeholder Colour
             break;
    case 11: ChangingWipe(5, 11);
             break;

  }
}

//turns off all led's
void LedOff()
{
  for (int i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, 0);
  }
  strip.show();
}

//Simple chase
static void Chase(uint32_t colour1, int Pixels, int Delayed, int CurrentCase)
{
  //runs the chase until it gets to the end of the strip
  for (int i = 0; i < strip.numPixels() + Pixels; i++)
  {
    if (CurrentCase != CurrentLedShow)
    {
      LedOff();
      break;
    }

    strip.setPixelColor(i  , colour1); // Draw new pixel
    strip.setPixelColor(i - Pixels, 0); // Erase pixel a few steps back
    strip.show();
    delay(Delayed);
  }
}

//one chase backing back and forth
void Bounce(uint32_t colour1, int Pixels, int Delayed, int CurrentCase)
{
  
  //makes the chase run to the end of the strip
  for (int i = 0 + Pixels; i < strip.numPixels(); i++)
  {

    if (CurrentCase != CurrentLedShow)
    {
      LedOff();
      break;
    }

    strip.setPixelColor(i, colour1); //Draws a new pixel
    strip.setPixelColor(i - Pixels, 0); //Erases pixel however many steps back
    strip.show();
    delay(Delayed); //how big the delay is before the next pixels get written and erased
  }
  
  //makes the chase run from the end of the strip back to the front of it
  for (int i = strip.numPixels() - Pixels; i >= 0; i--)
  {

    if (CurrentCase != CurrentLedShow)
    {
      LedOff();
      break;
    }

    strip.setPixelColor(i, colour1); //Draw new pixel
    strip.setPixelColor(i + Pixels, 0); //Erases pixels however many steps back
    strip.show();

    delay(Delayed); //how big the delay is before the next pixels get written and erased
  }
}

//two chases backing back and forth
void DoubleBounce(uint32_t colour1, uint32_t colour2, int Pixels, int Delayed, int CurrentCase)
{
  
  //makes both chases run across the strip
  for (int i = 0 + Pixels; i < strip.numPixels() + 1; i++)
  {

    if (CurrentCase != CurrentLedShow)
    {
      LedOff();
      break;
    }

    //first chase
    strip.setPixelColor(i, colour1); //Draw new pixel
    strip.setPixelColor(i - Pixels, 0); //Erases pixel however many steps back

    //second chase
    strip.setPixelColor(strip.numPixels() - i, colour2); //Draw new pixel on chase thats heading opposite way
    strip.setPixelColor(strip.numPixels() - i + Pixels, 0); //erase pixel few steps back

    strip.show();
    delay(Delayed);
  }

  //makes both the chases run back to their starting sides
  for (int i = 0 + Pixels; i < strip.numPixels() + 1; i++)
  {
    if (CurrentCase != CurrentLedShow)
    {
      LedOff();
      break;
    }

    //first chase bouncing back
    strip.setPixelColor(strip.numPixels() - i, colour1); //draws the first colour bouncing back
    strip.setPixelColor(strip.numPixels() - i + Pixels, 0); //erases the pixel however many steps back

    //second chase bouncing back
    strip.setPixelColor(i, colour2); //Draws the second colour bouncing back
    strip.setPixelColor(i - Pixels, 0); //Erases the pixel however many steps back

    strip.show();
    delay(Delayed);
  }
}

//Two chases that bounce back and forth but bounce off eachother every second time
void DoubleHalfBounce(uint32_t colour1, uint32_t colour2, int Pixels, int Delayed, int CurrentCase)
{
  //Makes both chases run across the strip
  for (int i = 0 + Pixels; i < strip.numPixels() + 1; i++)
  {

    //The chases start and go to the opposite sides across
    if (CurrentCase != CurrentLedShow)
    {
      LedOff();
      break;
    }

    //first chase
    strip.setPixelColor(i, colour1); //Draw new pixel
    strip.setPixelColor(i - Pixels, 0); //Erases pixel however many steps back

    //second chase
    strip.setPixelColor(strip.numPixels() - i, colour2); //Draw new pixel on chase thats heading opposite way
    strip.setPixelColor(strip.numPixels() - i + Pixels, 0); //erase pixel few steps back

    strip.show();
    delay(Delayed);
  }

  //The chases bounce back from opposite sides and stop at the middle\
  for (int i = 0 + Pixels; i < strip.numPixels() / 2 + 1; i++)
  {
    if (CurrentCase != CurrentLedShow)
    {
      LedOff();
      break;
    }

    //first chase bouncing back to middle
    strip.setPixelColor(strip.numPixels() - i, colour1); //Draw new pixel
    strip.setPixelColor(strip.numPixels() - i + Pixels, 0); //erase pixel few steps back

    //second chase bouncing back to middle
    strip.setPixelColor(i, colour2); //Draw new pixel
    strip.setPixelColor(i - Pixels, 0); //Erase pixel few steps back

    strip.show();
    delay(Delayed);
  }

  //The chases bounce back from the middle to the opposite ends again
  for (int i = 0 + Pixels; i < strip.numPixels() / 2 + 1; i++)
  {
    if (CurrentCase != CurrentLedShow)
    {
      LedOff();
      break;
    }

    //first chase bouncing from middle back to opposite side
    strip.setPixelColor(strip.numPixels() / 2 + i, colour1); //Draw new pixel
    strip.setPixelColor(strip.numPixels() / 2 + i - Pixels , 0);//Erase pixel few steps back

    //Second chase bouncing from middle back to opposite side
    strip.setPixelColor(strip.numPixels() / 2 - i, colour2); //Draw new pixel
    strip.setPixelColor(strip.numPixels() / 2 - i + Pixels, 0); //erase pixel few steps back

    strip.show();
    delay(Delayed);
  }

  //The chases go from the sides to the other side
  for (int i = 0 + Pixels; i < strip.numPixels() + 1; i++)
  {
    if (CurrentCase != CurrentLedShow)
    {
      LedOff();
      break;
    }

    //first chase going back to first side
    strip.setPixelColor(strip.numPixels() - i, colour1); //Draw new pixel
    strip.setPixelColor(strip.numPixels() - i + Pixels, 0); //erase pixel few steps back

    //second chase going back to its first side
    strip.setPixelColor(i, colour2); //Draw new pixel
    strip.setPixelColor(i - Pixels, 0); //Erases pixel however many steps back

    strip.show();
    delay(Delayed);
  }

  //The chases go to the middle again
  for (int i = 0 + Pixels; i < strip.numPixels() / 2 + 1; i++)
  {
    if (CurrentCase != CurrentLedShow)
    {
      LedOff();
      break;
    }

    //first chase bouncing from first side to middle
    strip.setPixelColor(i, colour1); //Draw new pixel
    strip.setPixelColor(i - Pixels, 0); //Erases pixel however many steps back

    //second chase bouncing from opposite side to middle
    strip.setPixelColor(strip.numPixels() - i, colour2); //Draw new pixel
    strip.setPixelColor(strip.numPixels() - i + Pixels, 0); //erase pixel few steps back

    strip.show();
    delay(Delayed);
  }

  //The chases bounce back to the first side
  for (int i = 0 + Pixels; i < strip.numPixels() / 2 + 1; i++)
  {
    if (CurrentCase != CurrentLedShow)
    {
      LedOff();
      break;
    }

    //first chase bouncing back from middle to first side
    strip.setPixelColor(strip.numPixels() / 2 - i, colour1); //Draw new pixel
    strip.setPixelColor(strip.numPixels() / 2 - i + Pixels, 0); //erase pixel few steps back

    //second chase bouncing back from middle to opposite side
    strip.setPixelColor(strip.numPixels() / 2 + i, colour2); //Draw new pixel
    strip.setPixelColor(strip.numPixels() / 2 + i - Pixels , 0);//Erase pixel few steps back

    strip.show();
    delay(Delayed);
  }
}

//A line of dashes however long
//DashLength is how long each dash is
//PixelGap is how many pixels from the first pixel of one dash to the first pixel of the next dash
void Dashes(uint32_t colour1, int PixelGap, int DashLength, int Delayed, int CurrentCase)
{
  //runs the function till the dashes meet the specified length
  for (int DashSize = 0; DashSize < DashLength; DashSize++)
  {
    if (CurrentCase != CurrentLedShow)
    {
      LedOff();
      break;
    }
    
    //Draws each pixel one by one in each dash
    for (int i = 0; i < strip.numPixels(); i = i + PixelGap)
    {
      if (CurrentCase != CurrentLedShow)
      {
        LedOff();
        break;
      }
      
      strip.setPixelColor(i + DashSize, colour1);
      strip.show();
      delay(Delayed);
    }
  }
}

//Just like Dashes but the Dashes get erased afterwords and then it repeats
//DashLength is how long each dash is
//PixelGap is how many pixels from the first pixel of one dash to the first pixel of the next dash
void DashErase(uint32_t colour1, int PixelGap, int DashLength, int Delayed, int CurrentCase)
{
  //Draws the dashes all the way across the strip
  for (int DashSize = 0; DashSize < DashLength; DashSize++) //runs the function till the dashes meet the specified length
  {
    if (CurrentCase != CurrentLedShow)
    {
      LedOff();
      break;
    }
    
    //Draws each pixel one by one in each dash
    for (int i = 0; i < strip.numPixels(); i = i + PixelGap)
    {
      if (CurrentCase != CurrentLedShow)
      {
        LedOff();
        break;
      }
      
      strip.setPixelColor(i + DashSize, colour1);    //turn every third pixel on
      strip.show();
      delay(Delayed);
    }
  }
  
  //Erases the dashes just like they were drawn
  for (int DashSize = 0; DashSize < DashLength; DashSize++)
  {
    if (CurrentCase != CurrentLedShow)
    {
      LedOff();
      break;
    }
    
    //Erases each pixel one by one in each dash
    for (int i = 0; i < strip.numPixels(); i = i + PixelGap)
    {
      if (CurrentCase != CurrentLedShow)
      {
        LedOff();
        break;
      }
      
      strip.setPixelColor(i + DashSize, 0);
      strip.show();
      delay(Delayed);
    }
  }
}

//A normal simple wipe
void Wipe(uint32_t colour1, int CurrentCase)
{
  for(int i = 0; i < strip.numPixels(); i++)
  {
    if(CurrentCase != CurrentLedShow)
    {
      LedOff();
      break;
    }
    strip.setPixelColor(i, colour1);
    strip.show();
  }
}

//a wipe that changes colour
void ChangingWipe(int Delayed, int CurrentCase)
{
  for(int ColourValue = 0; ColourValue < 255; ColourValue++)
  {
    if(CurrentCase != CurrentLedShow)
    {
      LedOff();
      break;
    }
    
    for(int i = 0; i< strip.numPixels(); i++)
    {
      if(CurrentCase != CurrentLedShow)
      {
        LedOff();
        break;
      }
      strip.setPixelColor(i, Wheel(ColourValue));
    }
    strip.show();
    delay(Delayed);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}




