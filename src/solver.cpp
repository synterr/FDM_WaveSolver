#include "stdafx.h"
#include "solver.h"

Solver::Solver()
{
	m_dt = 0.01;
	m_dx = 0.01;
	m_dy = 0.01;
	
	m_Nx = 0;	
	m_Ny = 0;	
	
	m_xMid = 0.5;
	m_yMid = 0.5;
}

bool Solver::Init(int width, int height, double dt, double cv, Memory* mem)
{
	mem->m_logr->Info("Initializing simulation:");

	double c = cv;//0.06				// precision factor

	m_dt = dt;	//0.02					// delta time step
	int L = 1;							// lenght normalized to 1

	m_dx = 1.0 / width;					// 1 pixel

	mC = c * m_dt / m_dx;				// courant number
	m_dx = m_dt * c / mC;
	m_Nx = int(round(L / m_dx));

	for (int xi = 0; xi <= m_Nx; xi++)	// create space mesh
		mem->x[xi] = xi * m_dx;				// mesh points in space

	m_dy = 1.0 / height;					// 1 pixel

	mC = c * m_dt / m_dy;					// courant number
	m_dy = m_dt * c / mC;

	m_Ny = int(round(L / m_dy));

	for (int yi = 0; yi <= m_Ny; yi++)	// create space mesh
		mem->y[yi] = mem->x[yi + (m_Nx - m_Ny) / 2];		// aspect correction for uniform scale on both axis

	mC2 = mC * mC;					// help variable in the scheme

	m_dx = mem->x[1] - mem->x[0];
	m_dy = mem->y[1] - mem->y[0];

	m_yMid = 0.5;
	m_xMid = 0.5;

	mem->m_logr->m_stream << "Simulation size: " << m_Nx << " x " << m_Ny;
	mem->m_logr->Info(mem->m_logr->m_stream.str().c_str());
	mem->m_logr->m_stream << "Simulation parameters: dx=" << m_dx << " dy=" << m_dy << " dt=" << m_dt << " C=" << mC;
	mem->m_logr->Info(mem->m_logr->m_stream.str().c_str());

	if (mC >= 1)
		mem->m_logr->Warn("Courant constatnt C > 1 may cause simulation instability!");

	return true;
}