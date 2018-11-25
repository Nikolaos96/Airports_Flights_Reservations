//File: airport.cc
#include <iostream>
#include <cstring>
#include "airport.h"


using namespace std;


	void flight::add_passenger(application& p,int seat){
		if(start == NULL){
			start = new Node(p, start);
			end = start;
			start2 = start;
		}else{
			Node* a = NULL;
			end = new Node(p,a,end);
			end->prev->next = end;
		}
		if(seat) A--;
                else B--;
		size++;
	}

        void flight::cancel_reservations(int id){// diagrafh ton aitisevn me auto to id

		Node* n = start;
		while(n != NULL){
			if(n->data->get_id() == id){
        	                if(n == start ){
                                	if(n->next == NULL){
						if(n->data->is_luxury_class() ) A++;
						else B++;
						delete n->data;
                                                delete n;
						start = NULL;
						end = NULL;
						size--;
                                                break;
                                        }
                                        start = n->next;
                                        start->prev = NULL;
					if(n->data->is_luxury_class() ) A++;
                                        else B++;
				}else if(n == end){
                 	                end = n->prev;
                                        end->next = NULL;
					if(n->data->is_luxury_class() ) A++;
                                        else B++;
               	                }else {
                                        n->next->prev = n->prev;
                                        n->prev->next = n->next;
					if(n->data->is_luxury_class() ) A++;
                                        else B++;
                                }
				delete n->data;
                                delete n;
				n = start;
                                size--;
	                }else n = n->next;
        	}

	}

	void flight::delete_apl(int a){// diagrafh ton aitisewn apo mia ptisi
		Node* n = start;
		while(n != NULL){
			if(a) cout << n->data->get_name() << " is on the fly" << endl;
			delete n->data;
			delete n;
			n = n->next;
		}
	}

        int flight::departs_at()const{ return departure_time; }
        int flight::arrives_at()const{ return departure_time + time_flight; }
        string flight::get_destination()const{ return destination; }

        void flight::available(int &a,int &b){ a = A; b = B; }
	int flight::get_size()const{ return size; }

//------------------------------------------------------------------------------------------------------------------


		void airport::pushFront_Apl(application& p){// eisagwgi sthn arxi sth lista anamonis
			if(start2 == NULL){
				start2 = new Node2(p,start2);
				end2 = start2;
			}else{
				start2 = new Node2(p,start2);
				start2->next->prev = start2;
			}
			size2++;
		}
		void airport::pushBack_Apl(application& p){// eisagwgi sto telos tis listas anamonis
			if(start2 == NULL) pushFront_Apl(p);
			else{
				Node2* a = NULL;
				end2 = new Node2(p,a,end2);
				end2->prev->next = end2;
				size2++;
			}
		}

		int airport::get_time()const{ return ttime; }

                void airport::add_application(int id,string s1,string s2,string s3,int b,int c,string s4){
			application p(id,s1,s2,s3,b,c,s4);
			if(start != NULL){
				Node* n = start;
				while(n != NULL){
					int a,b, i;
					n->data->available(a,b);
					i = p.matches(n->data->get_destination(),n->data->departs_at(),n->data->arrives_at(),a,b);
					if(i != 0){// h matches epistrefei 1 kai thesi A kai 2 gia thesi B
						if(i == 1) n->data->add_passenger(p,1);
						else n->data->add_passenger(p,2);
						return;
					}
					n = n->next;
				}
			}
			pushBack_Apl(p); // eisagwgi aitiseis sti lista anamonis
			cout << "A application added to the waiting list " << endl;
		}


                void airport::cancel_applications(int id){

			Node *p = start;
                        while(p != NULL){ // diagrafei tis aitiseis me auto ti id apo oles tis ptiseis
                                p->data->cancel_reservations(id);
                                p = p->next;
                        }


			Node2* n = start2;
			while(n != NULL){ // diagrafei tis aitiseis me auto to id apo th lista anamonis
				if(n->data->get_id() == id){
					if(n == start2 ){
						if(n->next == NULL){
							delete n->data;
							delete n;
							start2 = NULL;
							end2 = NULL;
							size2--;
							break;
						}
						start2 = n->next;
						start2->prev = NULL;
					}else if(n == end2){
						end2 = n->prev;
						end2->next = NULL;
					}else {
						n->next->prev = n->prev;
						n->prev->next = n->next;
					}
					delete n->data;
					delete n;
					n = start2;
					size2--;
				}else n = n->next;
			}
		}

                int airport::add_flight(string s1,int t1,int t2,int a,int b){
			if(size < terminal){ // eisagwgi ptisis an to megethos tis listas einai mikrotero apo to plithos ton terminal
                                if(start == NULL){// eisagwgi sthn arxi tis listas apo ptiseis
                                        start = new Node(s1,t1,t2,a,b, start);
                                        end = start;
                                }else{ // eisagwgh st telos tis lists apo ptiseis
                                        Node* aa = NULL;
                                        end = new Node(s1,t1,t2,a,b,aa,end);
                                        end->prev->next = end;
                                }
                                size++;
                                Node* n2 = end;
                                Node2* n = start2;
                                while(n != NULL){// elegxos an kapoia apo tis aitiseis sti lista anamonis tairiazei me tin kainourgia ptisi
					 int a5 = n->data->matches(s1,t1,t1+t2,a,b);
                                        if(a5){
                                                application p(n->data);
                                                if(a5 == 1) n2->data->add_passenger(p,1);
                                                else n2->data->add_passenger(p,2);
                                                if(n == start2){
                                                        if(n->next == NULL){
                                                                start2 = NULL;
                                                                end2 = NULL;
                                                                delete n->data;
                                                                delete n;
                                                                size2--;
                                                                break;
                                                        }
                                                        start2 = n->next;
                                                        start2->prev = NULL;
                                                }else if(n == end2){
                                                        end2 = n->prev;
                                                        end2->next = NULL;
                                                }else{
                                                        n->prev->next = n->next;
                                                        n->next->prev = n->prev;
                                                }
						delete n->data;
						delete n;
                                                size2--;
                                                n = start2;
                                        }else
                                                n = n->next;
                                }
                                return size;
                        }else return -1;
		}

                void airport::cancel_flight(int index){

			if(index > size-1){
				cout <<"There is no station with a number " << index << endl;
				return;
			}

                        Node* t = start;
                        if(index == 0){// diagrafw tin prwth ptisi
				if(start->next != NULL ){
                                        start = start->next;
                                        start->prev = NULL;
                                }else{
                                        start = NULL;
                                        end = NULL;
                                }
				for(int i = 0 ; i < t->data->get_size() ; i++){//vazw tis aitiseis apo tin ptish pou akirwthike stin
                                        application p((t->data->get_booking())->data);// arxi tis listas anamonis
                                        pushFront_Apl(p);
                                }
                                failed_applications += t->data->get_size();
                                t->data->delete_apl(0);
                                delete t;
			}else if(index == size -1){//diagrafw tin teleytaia
				t = end;
				end = t->prev;
				end->next = NULL;
				 for(int i = 0 ; i < t->data->get_size() ; i++){//vazw tis aitiseis apo tin ptish pou akirwthike stin
                                        application p((t->data->get_booking())->data);// arxi tis listas anamonis
                                        pushFront_Apl(p);
                                }
                                failed_applications += t->data->get_size();
				t->data->delete_apl(0);
				delete t;
                        }else{// diagrafw kapoia endiamesh ptisi
                                while(--index >0) t = t->next;
                                Node* t2 = t->next;
                                t->next = t->next->next;
				t->next->prev = t2->prev;
				 for(int i = 0 ; i < t2->data->get_size() ; i++){//vazw tis aitiseis apo tin ptish pou akirwthike stin
                                        application p((t2->data->get_booking())->data);// arxi tis listas anamonis
                                        pushFront_Apl(p);
                                }
                                failed_applications += t2->data->get_size();
				t2->data->delete_apl(0);
                                delete t2;
                        }
                        size--;

		}

                int airport::failed_application()const{ return failed_applications; }

                void airport::show_timetable(){
			if(start == NULL){// elegxos an yparxoun ptiseis
				cout <<"There are no available flights " <<endl;
				return ;
			}

			int a, b; // emfanizei tis diathsimes ptiseis taksinomimenes
			for(int i = 0 ; i <24 ; i++){
				Node* nn = start;
				while(nn != NULL){
					nn->data->available(a,b);
					if((a > 0 || b > 0 ) && i == nn->data->departs_at() ){
						cout <<"The flight to " << nn->data->get_destination() <<" departs on  " << nn->data->departs_at() << endl;
						cout << "Arrives at its destination on "<< nn->data->arrives_at() << endl ;
						cout << "Still has " << a+b <<" seats" << endl;
					}
					nn = nn->next;
				}
			}
		}


                void airport::show_people_waiting()const{
			Node2* n = start2;// emfanizei ta onomata apo tis aitiseis sti lista anamonis
			if(n != NULL){
				while(n != NULL){
					cout << "Waits the waiting list " << n->data->get_name() << endl;
					n = n->next;
				}
			}else
			cout << "The waiting list is empty" << endl;
		}


                void airport::flow_time(int tim){
			int k = ttime;
			ttime += tim;
			if(ttime > 24) ttime -= 24;

			while(tim > 0){
				Node* n = start;
				while(n != NULL){// diagrafei ton ptiseon pou prepei na exoun anaxwrisei
					if(n->data->departs_at() == k){
						n->data->delete_apl(1);
						if(n == start ){
							if(start->next == NULL ){
								cout <<"The flight to " << n->data->get_destination() <<" departs" << endl;
                                        			delete n;
								start = NULL;
                                                        	end = NULL;
								break;
                                			}
							cout <<"The flight to " << n->data->get_destination() <<" departs" << endl;
							start = n->next;
							start->prev = NULL;
                                			delete n;
							n = start;
                        			}else if(n == end){
                                			end = n->prev;
                                			end->next = NULL;
							cout <<"The flight to " << n->data->get_destination() <<" departs" << endl;
                                			delete n;
							n = end;
                        			}else{
							n->prev->next = n->next;
							n->next->prev = n->prev;
							cout <<"The flight to " << n->data->get_destination() <<" departs" << endl;
                                			delete n;
							n = start;
                        			}
                        			size--;

					}else
						n = n->next;
				}

				Node2* t = start2;

				while(t != NULL){ // diagrafei tis aitiseis pou oi wra tous exei perasei ton trexonta xrono
					if(t->data->arrived_by() == k){
						if(start2 == t){
							start2 = t->next;
							if(start2 != NULL) start2->prev = NULL;
						}else if(t == end2){
							end2 = t->prev;
							end2->next = NULL;
						}else{
							t->prev->next = t->next;
							t->next->prev = t->prev;
						}
						delete t->data;
                                                delete t;
						t = start2;
					}else
						t = t->next;
				}
				k++;
				if(k == 24) k = 0;
				tim--;
			}

		}

