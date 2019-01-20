#include<iostream>
#include "PSBRS.h"
#include<time.h>
#include<ctype.h>

vector<Segment> search_bus(string start, string destination)
{
	vector<StopTimes> vst_times, vdest_times;
	Segment segment;
	vector<Segment> vsegment;
	CStopTimes CSt;
	CStops c_stop;
	
	vst_times = CSt.getTrips(start);
	vdest_times = CSt.getTrips(destination);
	vsegment.clear();
	
	int count=0;
	for(int i=0; i< vst_times.size(); i++)
	{
		for(int j=0; j<vdest_times.size(); j++)
		{
			// *******************************************************************
			// * Add to segment array only if the trip id in both array is equal *
			// * and the stop sequence number in destination array is greater    *
			// * than the start array.                                           *
			// *******************************************************************
			if((vst_times[i].trip_id == vdest_times[j].trip_id) && (vst_times[i].stop_seq < vdest_times[j].stop_seq))
			{
				segment.start_id = vst_times[i].stop_id;
				segment.dest_id = vdest_times[j].stop_id;
				segment.departure = vst_times[i].departure_time;
				segment.arrival = vdest_times[j].arrival_time;
				segment.trip = vdest_times[j].trip_id;
				// Calculate the distance
				segment.distance = vdest_times[j].distance - vst_times[i].distance;
				vsegment.push_back(segment);
			}
		}
	}
	return (vsegment);
}

int isInvalidDate( int dd, int mm, int yy )
{
	if( yy < 0 )
		return 1;
	if( mm < 0 || mm > 12)
		return 1;
	if( mm == 2)
	{	
		if ( yy % 4 == 0 )
		{
				if( dd > 29 || dd < 0) 
					return 1;
		}
		else
		{
				if( dd > 28 || dd < 0) 
					return 1;
		}
	}
	else if( mm == 1 || mm == 3 || mm  == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12 )
	{
		if( dd > 31 || dd < 0) 
			return 1;
	}
	else
	{
		if( dd > 30 || dd < 0) 
			return 1;
	}
	return 0;
}


int check_date(string in_date)
{
	tm tm1;
	char ch_date[80];
	char out_time[11];
	strcpy(ch_date, in_date.c_str());
	if(isdigit(ch_date[0]) && isdigit(ch_date[1]) && (ch_date[2] == '/') && isdigit(ch_date[3]) && isdigit(ch_date[4]) && (ch_date[5] == '/') && isdigit(ch_date[6]) && isdigit(ch_date[7]) && isdigit(ch_date[8]) && isdigit(ch_date[9]))
	{	
		sscanf(in_date.c_str(),"%2d/%2d/%4d",&tm1.tm_mday,&tm1.tm_mon,&tm1.tm_year);
		
		if(!isInvalidDate(tm1.tm_mday,tm1.tm_mon,tm1.tm_year))
			return(1);
		else
			return(0);
	}
	else
		return(0);
}

int scr_search(Segment* segment)
{
	string start, destination, in_str;
	char ch_str[80];
	vector<Segment> vsegment;
	CStops c_stop;
	Stop stop;
	system("CLS");
	gotoxy(5,2); cout << "From Stop :";
	gotoxy(40,2); cout << "To Stop :";
	gotoxy(20,2); cin >> start;
	while(!c_stop.exist(start, &stop.stop_name))
	{		
		gotoxy(20,2); cout << "                    ";
		gotoxy(20,3); cout << "Stop Not Found";
		gotoxy(20,2); cin >> start;
	}
	gotoxy(20,3); cout << "              ";
	gotoxy(20,3); cout << stop.stop_name;

	gotoxy(55,2); cin >> destination;
	while(!c_stop.exist(destination, &stop.stop_name))
	{		
		gotoxy(55,2); cout << "                    ";
		gotoxy(55,3); cout << "Stop Not Found";
		gotoxy(55,2); cin >> destination;
	}
	gotoxy(55,3); cout << "              ";
	gotoxy(55,3); cout << stop.stop_name;

	vsegment = search_bus(start, destination);

	gotoxy(2,5); cout << "SL#";
	gotoxy(5,5); cout << "START";
	gotoxy(15,5); cout <<  "DEST.";
	gotoxy(25,5); cout << "DEPARTURE";
	gotoxy(40,5); cout << "ARRIVAL";
	gotoxy(55,5); cout << "TRIP";
	gotoxy(65,5); cout << "DISTANCE";

	if(vsegment.size() > 0)
	{
		short i, opt;
		for(i=0; i<vsegment.size(); i++)
		{
			gotoxy(2,i+6); cout << i+1;
			gotoxy(5,i+6); cout <<  vsegment[i].start_id;
			gotoxy(15,i+6); cout << vsegment[i].dest_id;
			gotoxy(25,i+6); cout <<  vsegment[i].departure;
			gotoxy(40,i+6); cout <<  vsegment[i].arrival;
			gotoxy(55,i+6); cout << vsegment[i].trip;
			gotoxy(65,i+6); cout << vsegment[i].distance;
		}	
		
		gotoxy(10,i+8); cout << "To reserve select an option (0 to exit) :";
		gotoxy(55,i+8); cin >> in_str;
	
		strcpy(ch_str,in_str.c_str());
		while( (in_str.size() > 2) || !isdigit((int)ch_str[0]) || (stoi(in_str.c_str())<1) || (stoi(in_str.c_str())>vsegment.size()) )
		{
			gotoxy(25,21); cout << "Invalid Option... Re-enter...";
			gotoxy(55,i+8); for(int i=0;i<in_str.length();i++) cout<< " ";
			gotoxy(55,i+8); cin >> in_str;
			strcpy(ch_str,in_str.c_str());
		}
		opt = stoi(in_str.c_str());
		if(opt > 0)
		{
			*segment = vsegment[opt-1];
			return(1);
		}
		else
		{
			return(0);
		}
	}
	else
	{
		gotoxy(2,6); cout << "No direct trips found. Press Enter...";
		return(0);
	}
	return(0);
}



int scr_reserve(Segment* segment)
{
	string in_date="", prev_date;
	system("CLS");
	gotoxy(5,5); cout << "START";
	gotoxy(5,6); cout <<  segment->start_id;
	gotoxy(15,5); cout << "DEST.";
	gotoxy(15,6); cout << segment->dest_id;
	gotoxy(22,5); cout << "DEP_TIME";
	gotoxy(22,6); cout << segment->departure;
	gotoxy(33,5); cout << "ARR_TIME";
	gotoxy(33,6); cout << segment->arrival;
	gotoxy(42,5); cout << "ROUTE";
	gotoxy(42,6); cout << segment->route;
	gotoxy(48,5); cout << "TRIP_ID";
	gotoxy(48,6); cout << segment->trip;
	gotoxy(56,5); cout << "KMS";
	gotoxy(56,6); cout << segment->distance;
	gotoxy(60,5); cout << "DD/MM/YYYY";
	gotoxy(71,5); cout << "SEATS_AVL";
	
	//
	//get available seats
	//
get_date:
	int x=0, row=0, col=0, pass=0;
	string str_pass="";
	while(x==0) {
		gotoxy(60,6); cout <<"           ";
		gotoxy(71,6); cout <<"     ";
		for(row=0; row<10; row++)
			for(col=0; col<4;col++)
			{
				int seat_num = row*4 + col + 1;
				gotoxy(3+(3*col),10+row); cout << "   ";
			}
		gotoxy(60,6); cin >> in_date;
		x = check_date(in_date);
		if(x==0) 
		{
			gotoxy(60,7);
			cout<<"Invalid date...";
		}
		else
		{
			gotoxy(60,7);
			cout<<"               ";
			for(row=0; row<10; row++)
				for(col=0; col<4;col++)
				{
					int seat_num = row*4 + col + 1;
					gotoxy(3+(3*col),10+row); cout << seat_num;
				}
		}
	};
	gotoxy(71,6); cout << 40;
	gotoxy(20,8); cout << "Y to book; N to Change date; X to exit :";
	char in;
	gotoxy(65,8); in=getche();
	while(in!='Y'&&in!='y'&&in!='N'&&in!='n'&&in!='X'&&in!='x')
	{
		gotoxy(65,9);cout<<"Invalid Choice, reenter";
		gotoxy(65,8);cout<<" ";gotoxy(65,8);
		in=getch();
	}
		
	gotoxy(65,9);cout<<"                       ";
	gotoxy(20,8); cout << "                                               ";
	if(in == 'N' || in == 'n') goto get_date;
	if(in == 'X' || in == 'x') return(0);
	
	char ch_inp[80];
	pass = 0;
	gotoxy(25,12); cout << "Number of passengers :";
	gotoxy(50,12); cin >> str_pass;
	strcpy(ch_inp,str_pass.c_str());
	if(isdigit((int)ch_inp[0]))
		pass = stoi(str_pass.c_str());
	
	while (pass < 1 || pass > 6)
	{
		gotoxy(50,13); cout << "Value from 1 to 6 allowed";
		gotoxy(50,12); cout << "          ";
		gotoxy(50,12); cin >> str_pass;
		strcpy(ch_inp,str_pass.c_str());
		if(isdigit((int)ch_inp[0]))
			pass = stoi(str_pass.c_str());
		else
			pass = 0;
	}
	gotoxy(50,13); cout << "                         ";
	gotoxy(25,12); cout << "                                    ";
	
	gotoxy(20,10); cout << "SL#";
	gotoxy(25,10); cout << "PASSENGER NAME";
	gotoxy(50,10); cout << "SEX";
	gotoxy(56,10); cout << "AGE";
	gotoxy(62,10); cout << "SEAT#";
	gotoxy(68,10); cout << "STATUS";
	
	vector<passenger> vp1;
	passenger p1;

	time_t now = time(0);
	gotoxy(50,8); cout << "PNR Number : " << now;
	p1.pnr = now;
	p1.date = in_date;
	p1.trip = segment->trip;
	p1.from = segment->start_id;

	for(int i=0; i<pass; i++)
	{
		gotoxy(20,11+i); cout << i+1;
		gotoxy(25,11+i); cout << "______________________";
		gotoxy(50,11+i); cout << "_";
		gotoxy(56,11+i); cout << "__";
		gotoxy(62,11+i); cout << "__";
	}

	for(int i=0; i<pass; i++)
	{
		gotoxy(25,11+i); cin >> p1.name;
		char ins;
		gotoxy(50,11+i); ins=getche();
		while(ins!='M'&&ins!='m'&&ins!='F'&&ins!='f')
		{
			gotoxy(40,22);cout<<"Invalid Sex, enter M or F...";
			gotoxy(50,11+i);cout<<"_";gotoxy(50,11+i);
			ins=getche();
		}
		gotoxy(40,22);cout<<"                             "; 
		
		string st_inp;
		gotoxy(56,11+i); cin >> st_inp;
		
		strcpy(ch_inp,st_inp.c_str());
		if(isdigit(ch_inp[0]) && isdigit(ch_inp[1]))
			p1.age = stoi(st_inp.substr(0,2));
		else
			p1.age = 0;

		while (p1.age < 1 || p1.age > 99)
		{
			gotoxy(40,22); cout << "Value from 01 to 99 allowed";
			gotoxy(56,11+i); cout << "__    __          ";
			gotoxy(56,11+i); cin >> st_inp;
			strcpy(ch_inp,st_inp.c_str());
			if(isdigit(ch_inp[0]) && isdigit(ch_inp[1]))
				p1.age = stoi(st_inp.substr(0,2));
			else
				p1.age = 0;
		}
		gotoxy(40,22); cout << "                           ";
		
		gotoxy(62,11+i); cin >> st_inp;
		strcpy(ch_inp,st_inp.c_str());
		if(isdigit(ch_inp[0]) && isdigit(ch_inp[1]))
			p1.seat = stoi(st_inp.substr(0,2));
		else
			p1.seat = 0;

		while (p1.seat < 1 || p1.seat > 40)
		{
			gotoxy(40,22); cout << "Valid seats from 01 to 40...";
			gotoxy(62,11+i); cout << "__           ";
			gotoxy(62,11+i); cin >> st_inp;
			strcpy(ch_inp,st_inp.c_str());
			if(isdigit(ch_inp[0]) && isdigit(ch_inp[1]))
				p1.seat = stoi(st_inp.substr(0,2));
			else
				p1.seat = 0;
		}
		gotoxy(40,22); cout << "                            ";
		//gotoxy(62,11+i); cin >> p1.seat;
		gotoxy(68,11+i); cout << "OK";
		vp1.push_back(p1);
	}

	gotoxy(40,22); cout << "Please press Y to book, N to cancel : ";
	getche();
	system("CLS");
	CBooking cb;
	int x1 = cb.book(vp1);
	cout << x1;
	vp1.clear();
	long int temp_pnr = now;
	cout << temp_pnr;
	getch();
	vector<passenger> vp2;
	vp2.clear();
	x1 = cb.get_booking(temp_pnr,&vp2);
	cout << endl << " retreived " << x1 << "rows" << endl;
	getch();
	system("CLS");
	gotoxy(1,10);  cout << "PNR";
	gotoxy(15,10); cout << "SEQ";
	gotoxy(20,10); cout << "TRIP";
	gotoxy(30,10); cout << "DATE";
	gotoxy(41,10); cout << "FROM";
	gotoxy(51,10); cout << "NAME";
	gotoxy(72,10); cout << "AGE";
	gotoxy(76,10); cout << "SEX";
	gotoxy(81,10); cout << "SEAT";
	for(int i=0;i<vp2.size();i++)
	{
		gotoxy(1,11+i);  cout << vp2[i].pnr;
		gotoxy(15,11+i); cout << vp2[i].seq;
		gotoxy(20,11+i); cout << vp2[i].trip;
		gotoxy(30,11+i); cout << vp2[i].date;
		gotoxy(41,11+i); cout << vp2[i].from;
		gotoxy(51,11+i); cout << vp2[i].name;
		gotoxy(72,11+i); cout << vp2[i].age;
		gotoxy(76,11+i); cout << vp2[i].sex;
		gotoxy(81,11+i); cout << vp2[i].seat;
	}
	getch();
	return(0);
}

int main_menu()
{
	string in_str;
	int choice;
	char ch_str[80];
	system("CLS");
	gotoxy(24,2); cout << "PS BUS RESERVATION SYSTEM";
	gotoxy(20,10); cout << "1.   SEARCH / RESERVATION";
	gotoxy(20,12); cout << "2.   ADMINISTRATION";
	gotoxy(20,14); cout << "3.   EXIT";
	gotoxy(25,20); cout << "Enter option : ";
	gotoxy(40,20); cin >> in_str;
	strcpy(ch_str,in_str.c_str());
	while( (in_str.length() > 1) || !isdigit((int)ch_str[0]) || (stoi(in_str.c_str())<1) || (stoi(in_str.c_str())>3) )
	{
		gotoxy(25,21); cout << "Invalid Option... Re-enter...";
		gotoxy(40,20); for(int i=0;i<in_str.length();i++) cout<< " ";
		gotoxy(40,20); cin >> in_str;
		strcpy(ch_str,in_str.c_str());
	}
	return(stoi(in_str.c_str()));
}

int main() {
	Segment segment;
	while(true)
	{
		int choice = main_menu();
		int result=0;
		switch(choice)
		{
		case 1:	result = scr_search(&segment);
				if(result)
				{
					scr_reserve(&segment);
				};
			break;
		case 2: cout << "Choice is 2";
				getch();
			break;
		case 3: return(0);
			break;
		default: 
			break;
		}
	};
	return(0);
}