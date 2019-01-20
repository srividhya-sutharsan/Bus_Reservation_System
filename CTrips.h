#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

struct Trip {
	string route_id;
	string trip_id;
	string trip_headsign;
	int direction;
	int total_seats;
};

class CTrips
{
public:
	Trip trip;

	CTrips(void);
	~CTrips(void);
};

