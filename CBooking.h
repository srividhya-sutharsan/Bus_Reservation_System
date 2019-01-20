#pragma once
#include<string>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

struct passenger
{
	string name;
	char sex;
	int age;
	int seat;
	string trip;
	string from;
	string date;
	long int pnr;
	int seq;
};

struct Booking {
	long int bpnr;
	int		bseq_no;
	char	bDate[10];
	char	btrip[10];
	char	bfrom[5];
	char	bname[21];
	char	bsex;
	int		bage;
	int		bseat;
};

class CBooking
{
public:
	CBooking(void);
	~CBooking(void);
	int book(vector<passenger> v);
	int CBooking::get_booking(long int, vector<passenger>*);
};

