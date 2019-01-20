#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

struct Route {
	string route_id;
	string agency_id;
	string route_name;
	string route_desc;
};

class CRoute
{
public:
	Route route;					// Object to store Route details
	vector<Route> vroute;			// Dynamic Array of Routes as Vector

	int count(void);			// Returns the number  of Routes in the system
	vector<Route> list(void);	// Returns the  list  of Routes
	bool get(string, Route*);			// Get the details of the Route
	
	CRoute(void);
	~CRoute(void);
};

