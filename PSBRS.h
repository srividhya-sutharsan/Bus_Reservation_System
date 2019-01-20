#include<fstream>
#include<vector>
#include<conio.h>
#include "Agency.h"
#include "CRoute.h"
#include "CTrips.h"
#include "CStopTimes.h"
#include "CBooking.h"
#include<Windows.h>
#include<string>

using namespace std;

struct Segment 
{
	string	start_id;
	string	start_name;
	string	dest_id;
	string	dest_name;
	string	start_date;
	string	departure;
	string	dest_date;
	string	arrival;
	string	route;
	string	trip;
	int		available_seats;
	int		distance;
};

	


void gotoxy(int x, int y) { 
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}
