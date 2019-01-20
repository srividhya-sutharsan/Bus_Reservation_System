#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

struct agency {
	string agency_id;
	string agency_name;
	string agency_url;
};

class Agency
{
public:
	agency age;					// Object to store agency details
	vector<agency> vage;		// Dynamic Array of agencies as Vector

	int count(void);			// Returns the number  of agencies in the system
	vector<agency> list(void);	// Returns the  list  of agencies
	agency get(string);			// Get the details of the agency
	bool exists(string);		// Finds if the agency exists
	Agency(void);				// Constructor
	~Agency(void);				// Destructor
};

