#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

struct Stop {
	string	stop_id;
	string	stop_name;
	int		major_stop;
};

class CStops
{
public:
	CStops(void);
	~CStops(void);
	bool exist(string, string*);
};

