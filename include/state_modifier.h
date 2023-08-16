#pragma once
#include "solver.h"

class StateModifier
{
public:
	double m_dt;			// delta time step
	double m_dx;			// 1 pixel / WIDTH
	double m_dy;			// 1 pixel / HEIGHT

	int m_Nx;				// Width of simulation area
	int m_Ny;				// Height of simulation area

	double m_xMid;			// midpoint in normalized coords
	double m_yMid;			// midpoint in normalized coords

public:
	StateModifier();
	StateModifier(double dt, double dx, double dy, int Nx, int Ny);
	double MediumCoeff(double& xi, double& yi);
	double InitialState(double& xi, double& yi);
	double DriveForce(double& xi, double& yi, double& t);
};

