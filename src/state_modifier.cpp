#include "stdafx.h"
#include "state_modifier.h"

namespace StateMod
{
	constexpr auto TWO_PI = 3.14159265358979f * 2;

	//ellipse parameters
	static double a = 0.4;	//x-axis
	static double b = 0.2;		//y-axis
	//focal source position in ellipse
	static double x0 = ((0.5 - (sqrt(a * a - b * b))));

	//circle parameters
	static double c = 0.08;	//x-axis
	static double d = 0.08;	//y-axis

	static double timer = 0;
	static double wave_count = 0;

	static double ret = 0;


	double MediumCoeff(double& xi, double& yi)
	{
		double ret;

		/* Flat medium */
		ret = 1;

		//Main Ellipse
		if ((xi - g_xMid) * (xi - g_xMid) / (a * a) + (yi - g_yMid) * (yi - g_yMid) / (b * b) < 1)
			ret = 1;
		else
			ret = 0;

		//Center Circle
		if ((xi - g_xMid) * (xi - g_xMid) / (c * c) + (yi - g_yMid) * (yi - g_yMid) / (d * d) < 1)
			ret = 0.6;

		return ret;
	}

	double InitialState(double& xi, double& yi)
	{
		double ret;

		/* Flat zero */
		ret = 0;


		return ret;
	}


	double DriveForce(double& xi, double& yi, double& t)
	{
		// In theory, single point drive functions should follow derivatives of functions shapes to recreate

		/* Flat zero */
		ret = 0;
		/* Timed One period sin middle point Driver */

		if (yi == g_yMid && xi == (int)floor(x0 * g_Nx) * g_dx)
		{
			//double x1 = ((0.5 + (sqrt(a * a - b * b)))) * Nx;

			if ((int)(t * 100) % 1370 == 0)
			{
				timer = t;
				wave_count++;
			}

			if (wave_count < 5 && (t - timer) < TWO_PI / 30 && (t - timer) >= 0)
			{
				ret = 120 * cos((t - timer) * 15) * g_dt;
			}

		}

		return ret;
	}
}