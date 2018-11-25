#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <cstdlib>
#include "airport.h"

using namespace std;


int main(int argc, char* argv[]){
int space, terminal, i;

	if(argv[1] == NULL){
		cout << "Error no argument in command line " << endl;
		return -1;
	}else space = atoi(argv[1]);

	cout << "Give me number of terminal" << endl;
        cin >> terminal;

	time_t curr_t;
        airport a(time(&curr_t)%24,terminal);


        ifstream file_f;
        file_f.open("flights.txt");
        if(!file_f){
                cout << "Error with file flights" << endl;
                return -1;
        }
        string str1;
        int time1, time2, A, B;
        while(file_f >> str1){ // diavazw ptiseis
                file_f >> time1;
                file_f >> time2;
                file_f >> A;
                file_f >> B;
                int p = a.add_flight(str1,time1,time2,A,B);
                if(p < 0) cout << "All terminal are full " << endl; // den iparxei diathsimos stathmos gia eisagwgi ptisis
                else cout << "New flight to the terminal " << p << endl;
        }
        file_f.close();

	ifstream file_a;
        file_a.open("aplications.txt");
        if(!file_a){
                cout <<"Error with file aplications" << endl;
                return -1;
        }

        string name,last_name, destination, seat;
        int id, time_ar_dest, time_ar_air;

	while(file_a >> name){ // diavazw aitiseis
		file_a >> last_name;
		file_a >> destination;
		file_a >> seat;
                file_a >> id;
                file_a >> time_ar_dest;
                file_a >> time_ar_air;
                a.add_application(id,name,last_name,destination,time_ar_dest,time_ar_air,seat);
        }
        file_a.close();
	cout << endl;
	cout << "Current time is " << a.get_time() << endl; //ektipono ton texon xrono
        cout << endl;
        a.show_timetable();     // ektipono tis ptisis
        cout << endl;
	a.show_people_waiting();// ektipono tis aitiseis sti lista anamonis
        a.cancel_flight(0); 	// h pthsh ston stathmo 0 diagrafetai
        cout << endl;
        a.show_timetable();	// ektipono tis ptiseis
        cout << endl;
        a.show_people_waiting();// ektipono tis aitiseis sti lista anamonis
        cout << endl;
        a.cancel_applications(111222);// akirwsi aitishw me id 111222
        cout << endl;
        a.show_people_waiting(); //ektipono tis aitiseis sti lista anamonis
        cout << endl;
	cout <<"Failed applications are " << a.failed_application() << endl; // akiromenes aitiseis
	cout << endl;

        a.flow_time(space); //----------------------

	ifstream file_ff;
        file_ff.open("fflights.txt");
        if(!file_ff){
                cout << "Error with file with flights" << endl;
                return -1;
        }

	while(file_ff >> str1){	// diavazw kai alles ptiseis
                file_ff >> time1;
                file_ff >> time2;
                file_ff >> A;
                file_ff >> B;
                int p = a.add_flight(str1,time1,time2,A,B);
                if(p < 0) cout << "All terminal are full " << endl;
                else cout << "New flight to the terminal " << p << endl;
        }
        file_ff.close();

        cout << endl;
        a.show_timetable(); // ektipono tis ptisis
        cout << endl;
        a.show_people_waiting(); // ektipono tis aitiseis sti lista anamonis


	return 0;
}

