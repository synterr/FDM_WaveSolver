#pragma once

extern double g_dt;			// delta time step
extern double g_dx;			// 1 pixel / WIDTH
extern double g_dy;			// 1 pixel / HEIGHT

extern double g_C;				//Courant number
extern double g_C2;			//Courant number^2

extern int g_Nx;				// Width of simulation area
extern int g_Ny;				// Height of simulation area

extern double g_xMid;			// midpoint in normalized coords
extern double g_yMid;			// midpoint in normalized coords

namespace StateMod
{
	double MediumCoeff(double& xi, double& yi);
	double InitialState(double& xi, double& yi);
	double DriveForce(double& xi, double& yi, double& t);
}

