#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "examples.h"

#define degToRad(angleInDegrees) ((angleInDegrees)*M_PI / 180.0)

int main()
{  
    example_sine_tracking();
    return 0;
}