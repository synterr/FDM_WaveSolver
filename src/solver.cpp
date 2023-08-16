#include "stdafx.h"
#include "solver.h"

namespace Solver
{
	double m_tim;

	double delta;
	int iplus, iminus, jplus, jminus;

	void simStep(Memory* mem, Graphics* graph, double scale)
	{

		vector<vector<double>>& u = mem->u;
		vector<vector<double>>& u_n = mem->u_n;
		vector<vector<double>>& u_nm = mem->u_nm;
		vector<vector<double>>& q = mem->q;

		vector<double>& x = mem->x;
		vector<double>& y = mem->y;

		for (int i = 1; i < g_Nx; i++)
		{
			iplus = (i + 1);
			iminus = (i - 1);

			for (int j = 1; j < g_Ny; j++)
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

					u[i][j] = -u_nm[i][j] + 2 * u_n[i][j] + g_C2 * delta + StateMod::DriveForce(x[i], y[j], m_tim)
						- u_n[i][j] * g_elasticity				 //"elasticity" term enforcing oscillations
						- (u_n[i][j] - u_nm[i][j]) * g_damping;			 //damping
				}
				graph->m_image_wav.setPixel(i, j, Colors::color_scheme(mem->u[i][j], scale));
			}
		}
		m_tim += g_dt;

		//copy arrays before next step
		mem->u_nm = mem->u_n;
		mem->u_n = mem->u;
	}

	bool init(int width, int height, double dt, double cv, Memory* mem)
	{
		mem->m_logr->Info("Initializing simulation:");

		double c = cv;//0.06				// precision factor

		g_dt = dt;	//0.02					// delta time step
		int L = 1;							// lenght normalized to 1

		g_dx = 1.0 / width;					// 1 pixel

		g_C = c * g_dt / g_dx;				// courant number
		g_dx = g_dt * c / g_C;
		g_Nx = int(round(L / g_dx));

		for (int xi = 0; xi <= g_Nx; xi++)	// create space mesh
			mem->x[xi] = xi * g_dx;			// mesh points in space

		g_dy = 1.0 / height;				// 1 pixel

		g_C = c * g_dt / g_dy;				// courant number
		g_dy = g_dt * c / g_C;

		g_Ny = int(round(L / g_dy));

		for (int yi = 0; yi <= g_Ny; yi++)	// create space mesh
			mem->y[yi] = mem->x[yi + (g_Nx - g_Ny) / 2];		// aspect correction for uniform scale on both axis

		g_C2 = g_C * g_C;						// help variable in the scheme

		g_dx = mem->x[1] - mem->x[0];
		g_dy = mem->y[1] - mem->y[0];

		g_xMid = g_Nx * g_dx / 2;
		g_yMid = g_Nx * g_dx / 2;

		mem->m_logr->m_stream << "Simulation size: " << g_Nx << " x " << g_Ny;
		mem->m_logr->Info(mem->m_logr->m_stream.str().c_str());
		mem->m_logr->m_stream << "Simulation parameters: dx=" << g_dx << " dy=" << g_dy << " dt=" << g_dt << " C=" << g_C;
		mem->m_logr->Info(mem->m_logr->m_stream.str().c_str());

		if (g_C >= 1)
			mem->m_logr->Warn("Courant constatnt C > 1 may cause simulation instability!");

		g_elasticity = 0.0005 * g_dt;
		g_damping = 0.01 * g_dt;

		return true;
	}

	void initialConditions(Memory* mem)
	{
		mem->m_logr->Info("Setting initial conditions:");

		vector<vector<double>>& u = mem->u;
		vector<vector<double>>& u_n = mem->u_n;
		vector<vector<double>>& u_nm = mem->u_nm;
		vector<vector<double>>& q = mem->q;

		vector<double>& x = mem->x;
		vector<double>& y = mem->y;

		// set medium coeffitient q(x)
		for (int i = 0; i <= g_Nx; i++)
		{
			for (int j = 0; j <= g_Ny; j++)
			{
				q[i][j] = StateMod::MediumCoeff(x[i], y[j]);
			}
		}

		// set initial condition u(x,y, 0) = I(x)
		for (int i = 0; i <= g_Nx; i++)
		{
			for (int j = 0; j <= g_Ny; j++)
			{
				u[i][j] = StateMod::InitialState(x[i], y[j]);
				u_n[i][j] = StateMod::InitialState(x[i], y[j]);
				u_nm[i][j] = StateMod::InitialState(x[i], y[j]);
			}
		}
	}
}