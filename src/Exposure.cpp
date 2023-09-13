#include "Exposure.h"
#include <cmath>

double Exposure::exposureValue(double aperture, double shutter, int ISO) {
double EV = log2(100*(pow(aperture, 2.0))/(ISO*shutter));
return EV;
}
int Exposure::exposure(Lighting light, double EV) {
if (light == NIGHT && EV < -1)
return 0;
else if (light == DIM_LIGHT && -1 <= EV && EV < 6)
return 0;
else if (light == MEDIUM_LIGHT && 6 <= EV && EV < 12)
return 0;
else if (light == BRIGHT_LIGHT && EV >= 12)
return 0;
else
return -1;
}
