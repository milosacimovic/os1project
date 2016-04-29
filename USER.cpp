//File: user.cpp
//Author: Milos Acimovic

//===========================================================================//
//   Project: Operating Systems 1 project
//   File:    user.cpp
//   Date:    May 2015
//===========================================================================//
#include <iostream.h>
#include <stdlib.h>
#include "thread.h"
#include "intLock.h"


//---------------------------------------------------------------------------//
//  Ovo se menja u testu
//---------------------------------------------------------------------------//

Time time_slice = 2;   // 0 ili defaultTimeSlice

int N = 3;            // 1 <= N <= 19

//---------------------------------------------------------------------------//


class A : public Thread {
public:
	A(Time time_slice): Thread(defaultStackSize, time_slice) {}
	A():Thread(defaultStackSize, 40){}
	virtual ~A() {waitToComplete(); }
protected:
	virtual void run();

};



//---------------------------------------------------------------------------//
class B : public Thread {
public:
	B () : Thread(defaultStackSize, 20) {}
	virtual ~B() {waitToComplete(); }

protected:
	virtual void run();
};




//---------------------------------------------------------------------------//
// Korisnicki program mora obavezno da definise ovu f-ju
//---------------------------------------------------------------------------//
void tick(){}

//---------------------------------------------------------------------------//



	
void A::run(){
	
	for(int i = 0; i < 30; i++){
	
		intLock
		cout << "u A::run() counter number:" << i<< " id no. = "<<getId() << '\n';
		intUnlock
		
		for (int k = 0; k<10000; ++k)
			for (int j = 0; j <30000; ++j);
	}
	intLock
	cout << "A marked terminating\n";
	intUnlock
}

//---------------------------------------------------------------------------//


void B::run(){
		
	for(int i = 0; i < 30; i++){
	
		intLock
		cout << "u B::run() counter number:" << i << " id no. = "<<getId() <<'\n';
		intUnlock
		
		for (int k = 0; k<10000; ++k)
			for (int j = 0; j <30000; ++j);
	}
	
	intLock
	cout<<"B marked terminating\n";
	intUnlock
}





int userMain (int argc, char* argv[]){
	
	intLock
	if(argc <2){
		cout<<"Invalid input!"<<endl;
		intUnlock
		return -1;
	}
	N = atoi(argv[1]);
	N = N>19 ? 19 : N;
	time_slice = atoi(argv[2]);
	
	A **athreads = new A*[N];
	B* threadb = new B();
	int i;
	
	
	for (i=0; i<N; i++){
		athreads[i] = new A(time_slice);
		athreads[i]->start();
	}
	threadb->start();
	intUnlock
	
	for(i = 0; i < 30;i++){
		intLock
		cout << "userMain with id: "  << Thread::getThreadById(2)->getId() << "counter = " << i<< '\n';
		intUnlock
		
		for(int j = 0; j < 3000; j++)
			for(int z = 0; z < 3000; z++);
	}
		
	for (i=0; i<N; i++){
		delete athreads[i];
	}  
	delete [] athreads;
	delete threadb;
	
	
	intLock
	cout<<"userMain finished! and its id is: " <<Thread::getRunningId()<<'\n';
	intUnlock
	return 0;
}
//---------------------------------------------------------------------------//
