#include "CBooking.h"

CBooking::CBooking(void)
{
}


CBooking::~CBooking(void)
{
}

int CBooking::get_booking(long int in_pnr, vector<passenger>* vp)
{
	Booking b;
	passenger p;
	vp->clear();
	int i = 0;
	ifstream fin("bookings.dat", ios::binary | ios::in);
	while(!fin.eof())
	{
		fin.read((char *)&b,sizeof(Booking));
		//if(p.pnr == in_pnr)
		//{
			i++;
			p.trip=b.btrip;
			p.age = b.bage;
			p.pnr = b.bpnr;
			p.date = b.bDate;
			p.from = b.bfrom;
			p.seq = b.bseq_no;
			p.name = b.bname;
			p.sex = b.bsex;
			p.seat = b.bseat;
			vp->push_back(p);
		//}
	}
	fin.close();

	return(i);
}

int CBooking::book(vector<passenger> v)
{
	ofstream fout("bookings.dat", ios::binary | ios::app);
 
	passenger p;
	Booking b;
	
	for(int i=0;i<v.size();i++)
	{
		strcpy(b.btrip,v[i].trip.c_str());
		b.bage = v[i].age;
		b.bpnr = v[i].pnr;
		strcpy(b.bDate,v[i].date.c_str());
		strcpy(b.bfrom,v[i].from.c_str());
		b.bseq_no = v[i].seq;
		strcpy(b.bname,v[i].name.c_str());
		b.bsex = v[i].sex;
		b.bseat = v[i].seat;
		b.bseat = v[i].seat;
		fout.write((char *)&b,sizeof(Booking));
	}

	fout.close();
	return(v.size());
}