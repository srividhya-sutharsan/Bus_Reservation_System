#include "CStops.h"


CStops::CStops(void)
{
}


CStops::~CStops(void)
{
}

bool CStops::exist(string in_stop, string* stop_name)
{
	fstream fin;
	bool present = false;
	string a_rec, stop_id;
	*stop_name = "";
	fin.open("stops_master.csv",ios::in);

	while (getline(fin, a_rec, '\n'))
	{
		stringstream s(a_rec);
		getline(s,stop_id,',');
		if(in_stop== stop_id)
		{
			present = true;
			getline(s, *stop_name,',');
			fin.close();
			return(present);
			break;
		}
	}

	fin.close();
	
	return(present);

}