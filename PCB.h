//File: PCB.h
//Author: Milos Acimovic
#ifndef _PCB_H_
#define _PCB_H_

#include "thread.h"
#include "schedule.h"
#include "queue.h"
#include <dos.h>

#define lock lockFlag = 0;
#define unlock lockFlag = 1;\
		if(whileLockedFlagThreadTimeSliceReachedZero){\
			whileLockedFlagThreadTimeSliceReachedZero = 0;\
			dispatch();\
		}


class System;
class List;

enum ThreadState {NEW, READY, RUNNING, BLOCKED, TERMINATING};


class PCB{
public:
	static void wrapper();
	PCB(StackSize stacksize, Time timeslice, Thread* thread);
	~PCB();
	void prepareStack(); //Called in start

/*===============================================================*/
	
	static volatile PCB* running; //Pointer to running thread

/*===============================================================*/

	friend class System;
	
	friend class Thread;
	
	friend class KernelSem;
	
	friend class KernelEv;
	
	friend class List;
	
	friend class Idle;
	
	friend void interrupt timer(...);
private:
	//Thread ID
	ID id;
	
	//Context info
	unsigned int sp;
	unsigned int ss;
	unsigned int bp;
	unsigned int* stack;
	StackSize sizeOfStack;
	
	
	//Accounting info
	static ID positionalId;
	volatile ThreadState state;
	Time timeSlice;
	Time remainingTimeOnCPU;
	//Queue of blockedThreadsWaitingForThisOneToComplete
	Queue* queueOfThreadsWaitingForThisThread;
	
	//Pointer to thread
	Thread* myThread;
	
	
	//Anything else to add maybe
	
};

#endif