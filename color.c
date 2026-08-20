#include <math.h>
#include "color.h"

RGB hueToRgb(double hue){
  double H = hue * 360;
  uint8_t X = (1 - fabs( fmod((H / 60), 2) - 1)) * 255;
  if(hue == 0.99)			 return (RGB){.R =   0, .G =   0, .B =   0};
  if(   0 <= H && H <  60) return (RGB){.R = 255, .G =   X, .B =   0};
  if(  60 <= H && H < 120) return (RGB){.R =   X, .G = 255, .B =   0};
  if( 120 <= H && H < 180) return (RGB){.R =   0, .G = 255, .B =   X};
  if( 180 <= H && H < 240) return (RGB){.R =   0, .G =   X, .B = 255};
  if( 240 <= H && H < 300) return (RGB){.R =   X, .G =   0, .B = 255};
  if( 300 <= H && H < 360) return (RGB){.R = 255, .G =   0, .B =   X};
  return (RGB){.R = 0, .G = 0, .B = 0};
}

