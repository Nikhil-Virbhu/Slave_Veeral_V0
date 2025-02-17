#define _NTC_CALIB_
#include "ntc_measurement.h"
#include <arm_math.h>

/*
NTC lookup table data: These values are calculated using the formula:

R = R0 * exp(B * (1/T - 1/T0))

where:
R = resistance at temperature T 
R0 = resistance at temperature T0 
B = material constant  
T = temperature in Kelvin 
T0 = reference temperature in Kelvin  

The values are calculated for the following parameters:
R0 = XX kOhm
B = YYYY K
T0 = 298.15K (25C)

This lookup table can be generated using the following excel file: 

*/
const float temperature_values[151] = {25.00,25.50,26.00,26.50,27.00,27.50,28.00,28.50,29.00,29.50,30.00,
		30.50,31.00,31.50,32.00,32.50,33.00,33.50,34.00,34.50,35.00,35.50,36.00,36.50,37.00,37.50,
		38.00,38.50,39.00,39.50,40.00,40.50,41.00,41.50,42.00,42.50,43.00,43.50,44.00,44.50,45.00,45.50,
		46.00,46.50,47.00,47.50,48.00,48.50,49.00,49.50,50.00,50.50,51.00,51.50,52.00,52.50,53.00,53.50,
        54.00,54.50,55.00,55.50,56.00,56.50,57.00,57.50,58.00,58.50,59.00,59.50,60.00,60.50,61.00,61.50,
        62.00,62.50,63.00,63.50,64.00,64.50,65.00,65.50,66.00,66.50,67.00,67.50,68.00,68.50,69.00,69.50,
        70.00,70.50,71.00,71.50,72.00,72.50,73.00,73.50,74.00,74.50,75.00,75.50,76.00,76.50,77.00,77.50,
        78.00,78.50,79.00,79.50,80.00,80.50,81.00,81.50,82.00,82.50,83.00,83.50,84.00,84.50,85.00,85.50,
        86.00,86.50,87.00,87.50,88.00,88.50,89.00,89.50,90.00,90.50,91.00,91.50,92.00,92.50,93.00,93.50,
        94.00,94.50,95.00,95.50,96.00,96.50,97.00,97.50,98.00,98.50,99.00,99.50,100.00};

const float resistance_values[151] ={10000.00,9780.68,9566.88,9358.44,9155.22,8957.06,8763.83,8575.39,8391.61,
	8212.35,8037.49,7866.91,7700.50,7538.13,7379.71,7225.11,7074.24,6927.00,6783.29,6643.02,6506.08,6372.40,6241.88,
	6114.45,5990.02,5868.50,5749.83,5633.93,5520.73,5410.15,5302.13,5196.60,5093.49,4992.75,4894.31,4798.12,4704.11,
	4612.23,4522.43,4434.65,4348.84,4264.95,4182.94,4102.76,4024.35,3947.68,3872.70,3799.37,3727.66,3657.51,3588.89,
	3521.77,3456.10,3391.86,3329.00,3267.49,3207.30,3148.40,3090.76,3034.35,2979.13,2925.08,2872.17,2820.37,2769.66,
	2720.01,2671.40,2623.79,2577.18,2531.53,2486.82,2443.04,2400.15,2358.14,2316.98,2276.67,2237.17,2198.47,2160.55,
	2123.40,2086.99,2051.31,2016.35,1982.08,1948.49,1915.56,1883.29,1851.65,1820.63,1790.23,1760.41,1731.18,1702.51,
	1674.40,1646.84,1619.80,1593.29,1567.29,1541.78,1516.76,1492.21,1468.13,1444.51,1421.33,1398.59,1376.28,1354.38,
	1332.90,1311.81,1291.12,1270.81,1250.87,1231.30,1212.10,1193.24,1174.73,1156.56,1138.72,1121.20,1104.00,1087.12,
	1070.53,1054.24,1038.25,1022.54,1007.11,991.96,977.08,962.45,948.09,933.98,920.12,906.50,893.12,879.97,867.05,854.36,
	841.89,829.63,817.58,805.74,794.10,782.66,771.41,760.36,749.49,738.81,728.31,717.99,707.84,697.86};

const float trafo_meas_values[101]= {-2.311,  -1.320,  -0.329, 0.662,	1.653, 	2.644,	3.635,	4.626,	5.617,	6.608,	7.599,	8.590,
		9.581,	10.572,	11.563,	12.554,	13.544,	14.535,	15.526,	16.517,	17.508,	18.499,	19.490,	20.481,	21.472,
		22.463,	23.454,	24.445,	25.436,	26.427,	27.418,	28.409,	29.400,	30.391,	31.382,	32.373,	33.364,	34.355,
		35.346,	36.337,	37.328,	38.319,	39.310,	40.301,	41.292,	42.283,	43.274,	44.265,	45.256,	46.247,	47.238,
		48.229,	49.220,	50.211,	51.202,	52.193,	53.184,	54.175,	55.166,	56.157,	57.148,	58.139,	59.130,	60.121,
		61.112,	62.103,	63.094,	64.085,	65.076,	66.067,	67.058,	68.049,	69.040,	70.031,	71.022,	72.013,	73.004,
		73.995,	74.986,	75.977,	76.968,	77.959,	78.950,	79.941,	80.932,	81.923,	82.914,	83.904,	84.895,	85.886,
		86.877,	87.868,	88.859,	89.850,	90.841,	91.832,	92.823,	93.814,	94.805,	95.796,	96.787
 };

const float trafo_temp_values[101] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,
74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100};

/*
 * Calculates temperature from resistance based on a lookup table values
    * @param resistance: NTC resistance in Ohms
    * @return temperature in Celsius
 */
float calculateTemperature(float resistance)
{
    // Check if the resistance is outside the table range
    if (resistance >= resistance_values[0])
        return 25.0; // Return default temperature

    int i = 0;
    while ((float)resistance_values[i] > (float)resistance){
        i++;
    }

    float rlow = resistance_values[i - 1];
    float rhigh = resistance_values[i];
    float tempLower = temperature_values[i - 1];
    float tempUpper = temperature_values[i];

    // Interpolating the temperature value
    float tmpcel = tempLower + (resistance - rlow) * (tempUpper - tempLower) / (rhigh - rlow);

    return tmpcel;
}


float convert_to_kelvin(float tempCelsius)
{
	return  (tempCelsius + 273.15);
}

float calculateTrafoTemperature(float trafo_temp)
{
	if (trafo_temp <= trafo_meas_values[0])
		return 0;

	int j=0;
	while((float)trafo_temp >=trafo_meas_values[j] )
	{
		j++;
	}
		float trafo_actual_temp =  trafo_temp_values[j];
		return trafo_actual_temp;
}


