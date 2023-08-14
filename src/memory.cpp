#include "stdafx.h"
#include "memory.h"

Memory::Memory()
{
	
}

Memory::~Memory()
{
	x.clear();
	y.clear();

	for (unsigned int i = 0; i < m_size.x + 1; i++)
	{
		u[i].clear();
		u_n[i].clear();
		u_nm[i].clear();
		q[i].clear();
	}
}
bool Memory::Allocate(sf::Vector2u size)
{
	m_size = size;
	u = vector<vector<double>>((int)m_size.x + 1);
	u_n = vector<vector<double>>((int)m_size.x + 1);
	u_nm = vector<vector<double>>((int)m_size.x + 1);

	q = vector<vector<double>>((int)m_size.x + 1);

	x = vector<double>((int)m_size.x + 1);		// x steps array
	y = vector<double>((int)m_size.y + 1);	    // y steps array

	for (unsigned int i = 0; i < (int)m_size.x + 1; i++)
	{
		u[i] = vector<double>((int)m_size.y + 1);
		u_n[i] = vector<double>((int)m_size.y + 1);
		u_nm[i] = vector<double>((int)m_size.y + 1);;
		q[i] = vector<double>((int)m_size.y + 1);;
	}

	return true;
}