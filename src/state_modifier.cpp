#include "stdafx.h"
#include "state_modifier.h"

constexpr auto TWO_PI = 3.14159265358979f * 2;

//ellipse parameters
static double a = 0.4;	//x-axis
static double b = 0.2;		//y-axis
//focal source position in ellipse
double x0 = ((0.5 - (sqrt(a * a - b * b))));

//circle parameters
static double c = 0.08;	//x-axis
static double d = 0.08;	//y-axis

static double timer = 0;
static double wave_count = 0;

StateModifier::StateModifier()
{
	m_dt = 0;
	m_dx = 0;
	m_dy = 0;
	m_Nx = 0;
	m_Ny = 0;

	m_xMid = 0;
	m_yMid = 0;
}

StateModifier::StateModifier(double dt, double dx, double dy, int Nx, int Ny)
{
	m_dt = dt;
	m_dx = dx;
	m_dy = dy;
	m_Nx = Nx;
	m_Ny = Ny;

	m_xMid = Nx * dx / 2;
	m_yMid = Nx * dx / 2;
}

double StateModifier::MediumCoeff(double& xi, double& yi)
{
	double ret;

	/* Flat medium */
	ret = 1;

	//Main Ellipse
	if ((xi - m_xMid) * (xi - m_xMid) / (a * a) + (yi - m_yMid) * (yi - m_yMid) / (b * b) < 1)
		ret = 1;
	else
		ret = 0;

	//Center Circle
	if ((xi - m_xMid) * (xi - m_xMid) / (c * c) + (yi - m_yMid) * (yi - m_yMid) / (d * d) < 1)
		ret = 0.6;

	return ret;
}

double StateModifier::InitialState(double& xi, double& yi)
{
	double ret;

	/* Flat zero */
	ret = 0;


	return ret;
}


double StateModifier::DriveForce(double& xi, double& yi, double t)
{
	// In theory, single point drive functions should follow derivatives of functions shapes to recreate
	double ret;

	/* Flat zero */
	ret = 0;
	/* Timed One period sin middle point Driver */


	if (yi == m_yMid && xi == (int)floor(x0 * m_Nx) * m_dx)
	{
		//double x1 = ((0.5 + (sqrt(a * a - b * b)))) * Nx;

		if ((int)(t * 100) % 1370 == 0)
		{
			timer = t;
			wave_count++;
		}

		if (wave_count < 5 && (t - timer) < TWO_PI / 30 && (t - timer) >= 0)
		{
			ret = 120 * cos((t - timer) * 15);
		}

	}
	return ret;
}