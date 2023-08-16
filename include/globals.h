#pragma once


double g_dt;			// delta time step
double g_dx;			// 1 pixel / WIDTH
double g_dy;			// 1 pixel / HEIGHT

double g_C;				//Courant number
double g_C2;			//Courant number^2

int g_Nx;				// Width of simulation area
int g_Ny;				// Height of simulation area

double g_xMid;			// midpoint in normalized coords
double g_yMid;			// midpoint in normalized coords
