#pragma once
#include <vector>
#include "log.h"

using namespace std;

class Memory
{
public:
	static Memory* m_instanceMemory;
	static Log* m_logr;
	~Memory();
	Memory(Memory const&) = delete;
	void operator=(Memory const&) = delete;
	static Memory* getInstance(Log* logr);
	void destroyInstance();
private:
	Memory() {};

public:
	sf::Vector2u m_size;
	// declare wave arrays
	vector<vector<double>> u;
	vector<vector<double>> u_n;
	vector<vector<double>> u_nm;
	// declare wave medium coefficient array
	vector<vector<double>> q;

	vector<double> x;		// x steps array
	vector<double> y;	    // y steps array
public:
	bool Allocate(sf::Vector2u size);

};

