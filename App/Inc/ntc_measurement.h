/* File description: This file contains definitions of functions used for NTC measurement. We require NTC measurement for temperature sensing parameters.
*Functions used:
 *Reference document:
*/

#include "main.h"

/* NTC parameters
 * #define R0 10000.0// Resistance at reference temperature (25°C)
#define T0 25.0
#define B 3950.0     // Beta coefficient
 * Generates a lookup tale based on R = R0 * exp(1/T - 1/T0)
 */

#ifdef _NTC_CALIB_
	float calculateTemperature(float resistance);
	float calculateTrafoTemperature(float trafo_temp);
#else
	extern float calculateTemperature(float resistance);
	extern float calculateTrafoTemperature(float trafo_temp);
#endif
