#include "stdafx.h"
#include "memory.h"

Memory* Memory::m_instanceMemory = nullptr;
Log* Memory::m_logr = nullptr;

Memory* Memory::getInstance(Log* logr)
{
	m_logr = logr;
	if(!m_instanceMemory)
		m_logr->Info("Creating memory instance... ");
	return (!m_instanceMemory) ? 
		m_instanceMemory = new Memory : 
		m_instanceMemory;
}
void Memory::destroyInstance() {
	m_logr->Info("Destroying memory instance... ");
	delete m_instanceMemory;
	m_instanceMemory = nullptr;
}
Memory::~Memory()
{
	x.clear();
	y.clear();

	for (unsigned int i = 0; i < m_size.x; i++)
	{
		u[i].clear();
		u_n[i].clear();
		u_nm[i].clear();
		q[i].clear();
	}
}
bool Memory::Allocate(sf::Vector2u size)
{
	m_logr->Info("Allocating vectors... ");
	m_size.x = size.x + 1;
	m_size.y = size.y + 1;

	u = vector<vector<double>>(m_size.x);
	u_n = vector<vector<double>>(m_size.x);
	u_nm = vector<vector<double>>(m_size.x);

	q = vector<vector<double>>(m_size.x);

	x = vector<double>(m_size.x);		// x steps array
	y = vector<double>(m_size.y);	    // y steps array

	for (unsigned int i = 0; i < m_size.x; i++)
	{
		u[i] = vector<double>(m_size.y);
		u_n[i] = vector<double>(m_size.y);
		u_nm[i] = vector<double>(m_size.y);
		q[i] = vector<double>(m_size.y);
	}

	return true;
}