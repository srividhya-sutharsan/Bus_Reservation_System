#include "CStopTimes.h"


CStopTimes::CStopTimes(void)
{
}


CStopTimes::~CStopTimes(void)
{
}

vector<StopTimes> CStopTimes::getTrips(string in_stop)
{
	vstoptimes.clear();
	fstream fin;
	string a_rec, temp_str;
	StopTimes st_time;
	fin.open("stop_times.csv",ios::in);
	while (getline(fin, a_rec, '\n'))
	{
		stringstream s(a_rec);
		getline(s,st_time.trip_id,',');
		getline(s,st_time.stop_id,',');
		getline(s,temp_str,',');
		st_time.stop_seq = stoi(temp_str);
		getline(s,temp_str,',');
		st_time.stop_headsign = stoi(temp_str);
		getline(s,st_time.arrival_time,',');
		getline(s,st_time.departure_time,',');
		getline(s,temp_str,'\n');
		st_time.distance = stoi(temp_str);
		if(in_stop == st_time.stop_id)
			vstoptimes.push_back(st_time);
	}
	fin.close();
	
	return(vstoptimes);
}