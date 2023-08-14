#pragma once
class Solver
{
public:
	double m_dt;					// delta time step
	double m_dx;					// 1 pixel / WIDTH
	double m_dy;					// 1 pixel / HEIGHT

	int m_Nx;						// Width for arrays
	int m_Ny;						// Height for arrays

	double m_xMid;				// midpoint in normalized coords
	double m_yMid;				// midpoint in normalized coords

public:
		Solver();
};

