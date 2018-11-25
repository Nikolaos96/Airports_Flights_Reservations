//File: airport.h
#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;

class application{
	private:
		int     id;
                string  name;
                string  last_name;
                string  destination;    //prorismos
                int     time_arrived__airport;  //xrono gia na ftasi sto aerodr$
                int     time_to_arrived;  //xrono gia ton proorismo
                string  seat;           // thesi A h B

	public:
	application(int i,string n,string l,string d,int t1,int t2,string s):id(i),name(n),last_name(l),
	destination(d),time_arrived__airport(t1),time_to_arrived(t2),seat(s){ }

	application(application &a):id(a.id),name(a.name),last_name(a.last_name),destination(a.destination), time_arrived__airport(a.time_arrived__airport),
	time_to_arrived(a.time_to_arrived), seat(a.seat) {}

	application(application* &a):id(a->id),name(a->name),last_name(a->last_name),destination(a->destination), time_arrived__airport(a->time_arrived__airport),
        time_to_arrived(a->time_to_arrived), seat(a->seat) {}

	~application(){ }

                int matches(string s1,int t1,int t2,int a,int b){
			string str("A");
			if((s1.compare(destination) == 0) && (time_arrived__airport < t1) && (time_to_arrived == t2) ){
				if(seat.compare(str) == 0){
					if(a > 0) return 1;
				}else{
					if(b > 0) return 2;
				}
			}
			return 0;
		}
                int is_luxury_class(){ string str("A"); return (seat.compare(str) == 0); }// thesi A h B
                int get_id()const { return id; }
                string get_name()const { string str;char c = ' '; for(int i=0 ; i < name.size() ; i++)str.push_back(name[i]);str+= c;
                for(int i = 0; i < last_name.size() ; i++) str.push_back(last_name[i]); return str; } //epistrofi onomatos
                int arrived_by()const{ return time_to_arrived; } //xrono gia ton proorismo
		string get_destination()const{ return destination; }
};

class flight {
	private:
		struct Node{
			application *data;
			Node* next;
			Node* prev;
			Node(application &p, Node* n=NULL, Node* k = NULL):next(n), prev(k) {
			data = new application(p);
			cout <<"New passenger with id " << p.get_id() << endl; }
		};
		string destination;
		int departure_time;
		int time_flight;
		int A;
		int B;
		Node* start;
		Node* start2;
		Node* end;
		int size;
	public:
		flight(string s,int d,int t,int a,int b):
		destination(s), departure_time(d), time_flight(t), A(a), B(b), start(NULL), size(0),end(NULL) {
		cout << "New flight creation for " << destination <<endl; }

		~flight(){
			 Node* t1 = start;
                        while(t1 != NULL){
                                Node* t2 = t1;
                                t1 = t1->next;
				delete t2->data;
                                delete t2;
                        }
		}

                void add_passenger(application& p,int seat);

                void cancel_reservations(int id);
		void delete_apl(int);

                int departs_at()const;
                int arrives_at()const;

                string get_destination()const;
                void available(int &a,int &b);

                Node* get_booking(){
                        Node* n = start2;
                        start2 = start2->next;
                        return n;
                }
		int get_size()const;

};

class airport{
	struct Node {
		flight* data;
		Node* next;
		Node* prev;
		Node(string s1,int t1,int t2,int a,int b,Node* n=NULL, Node* k = NULL):next(n), prev(k){
			data = new flight(s1,t1,t2,a,b);
		}
	};
	struct Node2 {
		application* data;
		Node2* next;
		Node2* prev;
		Node2(application &p, Node2* n=NULL, Node2* k = NULL):next(n), prev(k){
			data = new application(p); }
	};

	Node* start;
	Node* end;
	Node2* start2;
	Node2* end2;

	int size;
	int size2;
	int ttime;
	int terminal;
	int failed_applications;

	public:
		airport(int ti,int term) : start(NULL), size(0), end(NULL),start2(NULL), size2(0), end2(NULL),failed_applications(0){
		cout << "Airport creation, list flight creation, list application creation " << endl; terminal = term; ttime = ti;}
		~airport(){
			Node* t1 = start;
			while(t1 != NULL){
				Node* t2 = t1;
				t1 = t1->next;
				delete t2->data;
				delete t2;
			}
			cout << "flights list destruction" << endl;
			Node2* t3 = start2;
			while(t3 != NULL){
				Node2* t4 = t3;
				t3 = t3->next;
				delete t4->data;
				delete t4;
			}
			cout << "aplication list destruction" << endl;
			cout << "Airport destruction" << endl;
		}


		void pushFront_Apl(application& p);
		void pushBack_Apl(application& p);


		int get_time()const;
                void add_application(int id,string s1,string s2,string s3,int b,int c,string s4);


                void cancel_applications(int id);
                int add_flight(string s1,int t1,int t2,int a,int b);


                void cancel_flight(int index);
                int failed_application()const;


                void show_timetable();
                void show_people_waiting()const;

                void flow_time(int tim);
};

