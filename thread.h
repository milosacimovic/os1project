//File: thread.h
//Author: Milos Acimovic

#ifndef _thread_h_
#define _thread_h_

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; //time, x ms
const Time defaultTimeSlice = 2; //default = 2 * 55 ms
typedef int ID;

class PCB; //Kernel's implementation of a user's thread. This is a forward declaration

class Thread {
public:

	void start();
	void waitToComplete();
	virtual ~Thread();
	
	ID getId();
	static ID getRunningId();
	static Thread* getThreadById(ID id);
	
protected:
	friend class PCB;
	Thread(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual void run() {}
	
private:
	PCB* myPCB;
 
};

void dispatch();

#endif