#include "Agency.h"

Agency::Agency(void)
{
}


Agency::~Agency(void)
{
}

int Agency::count(void)
{
	fstream fin;
	int count=0;
	string a_rec;
	fin.open("agency_master.csv",ios::in);

	while (getline(fin, a_rec, '\n'))
		count++;

	fin.close();
	
	return(count);
}

vector<agency> Agency::list(void)
{
	agency age1;
	vage.clear();
	fstream fin;
	string a_rec;
	fin.open("agency_master.csv",ios::in);

	while (getline(fin, a_rec, '\n'))
	{
		stringstream s(a_rec);
		getline(s,age1.agency_id,',');
		getline(s,age1.agency_name,',');
		getline(s,age1.agency_url,'\n');
		vage.push_back(age1);
	}

	fin.close();
	
	return(vage);
}

bool Agency::exists(string age)
{
	fstream fin;
	bool present = false;
	string a_rec, age_id;
	fin.open("agency_master.csv",ios::in);

	while (getline(fin, a_rec, '\n'))
	{
		stringstream s(a_rec);
		getline(s,age_id,',');
		if(age == age_id)
		{
			present = true;
			fin.close();
			return(present);
			break;
		}
	}

	fin.close();
	
	return(present);
}

agency Agency::get(string in_agency)
{
	fstream fin;
	age.agency_id = "";
	age.agency_name = "";
	age.agency_url = "";
	string temp_age;
	string a_rec;
	fin.open("agency_master.csv",ios::in);

	while (getline(fin, a_rec, '\n'))
	{
		stringstream s(a_rec);
		getline(s,temp_age,',');
		if(in_agency == temp_age)
		{
			age.agency_id = temp_age;
			getline(s,age.agency_name,',');
			getline(s,age.agency_url,'\n');
			fin.close();
			return(age);
			break;
		}
	}

	fin.close();
	
	return(age);

}
