#pragma once
#include "memory.h"
#include "state_modifier.h"

class Solver
{
public:
	double m_dt;			// delta time step
	double m_dx;			// 1 pixel / WIDTH
	double m_dy;			// 1 pixel / HEIGHT
	
	double mC;				//Courant number
	double mC2;				//Courant number^2
	
	int m_Nx;				// Width of simulation area
	int m_Ny;				// Height of simulation area

	double m_xMid;			// midpoint in normalized coords
	double m_yMid;			// midpoint in normalized coords

	static double m_tim;

public:
		Solver();
		bool init(int width, int height, double dt, double cv, Memory* mem);
		void initialConditions(Memory* mem, StateModifier* sm);
		void simStep(Memory* mem, Graphics* graph, StateModifier* sm, double scale);
		void update(Memory* mem);
};

