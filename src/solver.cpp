#include "stdafx.h"
#include "solver.h"

double Solver::m_tim = 0;

double delta = 0;
int iplus, iminus, jplus, jminus;

double elasticity = 0;
double damping = 0;

Solver::Solver()
{

}

void Solver::simStep(Memory* mem, Graphics* graph,StateModifier* sm, double scale)
{

	vector<vector<double>>& u = mem->u;
	vector<vector<double>>& u_n = mem->u_n;
	vector<vector<double>>& u_nm = mem->u_nm;
	vector<vector<double>>& q = mem->q;

	vector<double>& x = mem->x;
	vector<double>& y = mem->y;

	for (int i = 1; i < m_Nx; i++)
	{
		iplus = (i + 1);
		iminus = (i - 1);

		for (int j = 1; j < m_Ny; j++)
		{
			jplus = (j + 1);
			jminus = (j - 1);

			if (q[iplus][j] + q[iminus][j] + q[i][jplus] + q[i][jminus] + q[i][j] > 0.0)
				//if (q[i][j] >  0.0)
			{

				delta = //u_n[iplus][j] + u_n[iminus][j] + u_n[i][jplus] + u_n[i][jminus] - 4.0 * u_n[i][j];
					(0.5 * (q[i][j] + q[iplus][j]) * (u_n[iplus][j] - u_n[i][j])
						+ 0.5 * (q[i][j] + q[iminus][j]) * (u_n[iminus][j] - u_n[i][j])
						+ 0.5 * (q[i][j] + q[i][jplus]) * (u_n[i][jplus] - u_n[i][j])
						+ 0.5 * (q[i][j] + q[i][jminus]) * (u_n[i][jminus] - u_n[i][j]));

				u[i][j] = -u_nm[i][j] + 2 * u_n[i][j] + mC2 * delta + sm->DriveForce(x[i], y[j], m_tim)
					- u_n[i][j] * elasticity				 //"elasticity" term enforcing oscillations
					- (u_n[i][j] - u_nm[i][j]) * damping;			 //damping
			}
			graph->m_image_wnd.setPixel(i, j, color_scheme(mem->u[i][j], scale));
		}
	}
}

void Solver::update(Memory* mem)
{
	m_tim += m_dt;
	
	//copy arrays before next step
	mem->u_nm = mem->u_n;
	mem->u_n = mem->u;

}

bool Solver::init(int width, int height, double dt, double cv, Memory* mem)
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
		mem->x[xi] = xi * m_dx;			// mesh points in space

	m_dy = 1.0 / height;				// 1 pixel

	mC = c * m_dt / m_dy;				// courant number
	m_dy = m_dt * c / mC;

	m_Ny = int(round(L / m_dy));

	for (int yi = 0; yi <= m_Ny; yi++)	// create space mesh
		mem->y[yi] = mem->x[yi + (m_Nx - m_Ny) / 2];		// aspect correction for uniform scale on both axis

	mC2 = mC * mC;						// help variable in the scheme

	m_dx = mem->x[1] - mem->x[0];
	m_dy = mem->y[1] - mem->y[0];

	m_xMid = m_Nx * m_dx / 2;
	m_yMid = m_Nx * m_dx / 2;

	mem->m_logr->m_stream << "Simulation size: " << m_Nx << " x " << m_Ny;
	mem->m_logr->Info(mem->m_logr->m_stream.str().c_str());
	mem->m_logr->m_stream << "Simulation parameters: dx=" << m_dx << " dy=" << m_dy << " dt=" << m_dt << " C=" << mC;
	mem->m_logr->Info(mem->m_logr->m_stream.str().c_str());

	if (mC >= 1)
		mem->m_logr->Warn("Courant constatnt C > 1 may cause simulation instability!");
	
	elasticity = 0.0005 * m_dt;
	damping = 0.01 * m_dt;

	return true;
}

void Solver::initialConditions(Memory* mem, StateModifier* sm)
{
	mem->m_logr->Info("Setting initial conditions:");

	vector<vector<double>>& u = mem->u;
	vector<vector<double>>& u_n = mem->u_n;
	vector<vector<double>>& u_nm = mem->u_nm;
	vector<vector<double>>& q = mem->q;

	vector<double>& x = mem->x;
	vector<double>& y = mem->y;

	// set medium coeffitient q(x)
	for (int i = 0; i <= m_Nx; i++)
	{
		for (int j = 0; j <= m_Ny; j++)
		{
			q[i][j] = sm->MediumCoeff(x[i], y[j]);
		}
	}

	// set initial condition u(x,y, 0) = I(x)
	for (int i = 0; i <= m_Nx; i++)
	{
		for (int j = 0; j <= m_Ny; j++)
		{
			u[i][j] = sm->InitialState(x[i], y[j]);
			u_n[i][j] = sm->InitialState(x[i], y[j]);
			u_nm[i][j] = sm->InitialState(x[i], y[j]);
		}
	}
}