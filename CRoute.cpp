#include "CRoute.h"


CRoute::CRoute(void)
{
}


CRoute::~CRoute(void)
{
}

int CRoute::count(void) {
	fstream fin;
	int count=0;
	string a_rec;
	fin.open("routes_master.csv",ios::in);

	while (getline(fin, a_rec, '\n'))
		count++;

	fin.close();
	
	return(count);
}


vector<Route> CRoute::list(void)
{
	Route route1;
	vroute.clear();
	fstream fin;
	string a_rec;
	fin.open("routes_master.csv",ios::in);

	while (getline(fin, a_rec, '\n'))
	{
		stringstream s(a_rec);
		getline(s,route1.route_id,',');
		getline(s,route1.agency_id, ',');
		getline(s,route1.route_name,',');
		getline(s,route1.route_desc,'\n');
		vroute.push_back(route1);
	}

	fin.close();
	
	return(vroute);
}

bool CRoute::get(string in_route, Route *out_route)
{
	fstream fin;
	out_route->route_id = "";
	out_route->agency_id = "";
	out_route->route_name = "";
	out_route->route_desc = "";

	string temp_route;
	string a_rec;
	fin.open("routes_master.csv",ios::in);

	while (getline(fin, a_rec, '\n'))
	{
		stringstream s(a_rec);
		getline(s,temp_route,',');
		if(in_route == temp_route)
		{
			out_route->route_id = temp_route;
			getline(s,out_route->agency_id,',');
			getline(s,out_route->route_name,',');
			getline(s,out_route->route_desc,'\n');
			fin.close();
			return(true);
			break;
		}
	}

	fin.close();
	
	return(false);
}
