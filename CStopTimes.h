#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include"CStops.h"

using namespace std;

struct StopTimes 
{
	string	trip_id;
	string	stop_id;
	int		stop_seq;
	int		stop_headsign;
	string	arrival_time;
	string	departure_time;
	int		distance;
};

class CStopTimes
{
public:
	StopTimes stoptimes;
	vector<StopTimes> vstoptimes;
	
	Stop stop;

	vector<StopTimes> getTrips(string);

	CStopTimes(void);
	~CStopTimes(void);
};

