/**
* Differnt lighting situations.
*/
#include <cmath>
enum Lighting {NIGHT, DIM_LIGHT, MEDIUM_LIGHT, BRIGHT_LIGHT};

class Exposure {
 public:
  /**
  * See https://www.omnicalculator.com/other/exposure#how-to-calculate-the-exposure-value for equation.
  * @return exposure value for photograph.
  */
  double exposureValue(double aperture, double shutter, int ISO);

  /**
  * A photo is considered correctly exposed if the EV value falls within the
  * corresponding range:
  *     NIGHT: EV < -1;
  *     DIM_LIGHT: -1 <= EV < 6;
  *     MEDIUM_LIGHT: 6 <= EV < 12;
  *     BRIGHT_LIGHT: EV >= 12;
  * If the EV is below the range, then the photograph will be overexposed
  * (i.e. the photograph is too bright) and if the EV is above the range,
  * then the photograph will be underexposed (i.e. the photograph is too dark).
  * @return 0 if correct exposure, > 0 if photograph will be overexposed,
  * < 0 if photograph will be underexposed.
  */
  int exposure(Lighting light, double EV);
};
