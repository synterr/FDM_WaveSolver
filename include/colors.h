#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#define COLOR_SCHEME 0   /* choice of color scheme */

#define C_LUM 0          /* color scheme modifies luminosity (with slow drift of hue) */
#define C_HUE 1          /* color scheme modifies hue */

#define SCALE 0          /* set to 1 to adjust color scheme to variance of field */
#define SLOPE 3          /* sensitivity of color on wave amplitude */
#define ATTENUATION 0.0  /* exponential attenuation coefficient of contrast with time */

#define COLORHUE 220     /* initial hue of water color for scheme C_LUM */ 
#define LUMMEAN 0.5      /* amplitude of luminosity variation for scheme C_LUM */
#define LUMAMP 0.4       /* amplitude of luminosity variation for scheme C_LUM */
#define HUEMEAN 240.0    /* mean value of hue for color scheme C_HUE */
#define HUEAMP 200.0      /* amplitude of variation of hue for color scheme C_HUE */

extern double g_hueshift;

namespace Colors
{

	static double hue, y, r, amplitude;
	static int intpart;
	static sf::Color rgb;

	static vector<sf::Color>  varhue_table(36000);
	static vector<sf::Color>  varlume_table(10000);
	static vector<double>     tanh_table(200000);

	void computeColorTables();
	static float HueToRGB(double v1, double v2, double vH);
	static sf::Color HSLToRGB(double h, double s, double l);
	sf::Color color_scheme(double& value, double& scale);
	static void freeColorTables();

}