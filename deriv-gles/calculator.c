#include <math.h>
#define MYPI 3.14159265

float frameCount___ = 0.1;

float getMyX () {

  frameCount___ += .005;
  float amplitude = 2;
  float period = 1;

  float x = amplitude * sin(MYPI * frameCount___ / period);
  if (frameCount___ > 100000)
  {
    frameCount___ = 0;
  }
  return x;
}

static float frameCount___2 = 0.1;

float getMyY()
{

  frameCount___2 += .05;
  float amplitude = 2;
  float period = 1;

  float x = amplitude * sin(MYPI * frameCount___ / period);

  if (frameCount___2 > 100000)
    {
      frameCount___2 = 0;
  }
  return x;
}

static float frameCount___3 = 0.01;

float getMyZubac()
{

  frameCount___3 += 0.01;
  float amplitude = 2;
  float period = 1;

  float x = amplitude * sin(MYPI * frameCount___ / period);
  if (frameCount___3 > 100000)
  {
    frameCount___3 = 0;
  }
  return x;
}