#pragma once
#include <vector>

using namespace std;

class Memory
{

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
	Memory();
	~Memory();
	bool Allocate(sf::Vector2u size);
};

