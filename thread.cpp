//File: thread.cpp
//Author: Milos Acimovic

#include "thread.h"
#include "PCB.h"
#include "system.h"




extern void interrupt timer(...);
extern volatile int explicitDispatch;
extern volatile int lockFlag;
extern volatile int whileLockedFlagThreadTimeSliceReachedZero;


Thread::Thread(StackSize stackSize, Time timeSlice){
	lock
	myPCB = new PCB(stackSize, timeSlice, this);
	System::systemPCBManager->put(myPCB);
	unlock
}

void Thread::start(){
	//Anything else ?
	lock
	myPCB->prepareStack();
	myPCB->state = READY;
	System::thereAreReadyThreads++;
	Scheduler::put(myPCB);
	unlock
}

ID Thread::getId(){
	return myPCB->id; //permitted since we declared Thread as friend to PCB
}

ID Thread::getRunningId(){
	return PCB::running->id; //permitted since we declared Thread as friend to PCB
}

Thread::~Thread(){
	//asm cli; //NO! lockFlag = 0;
	waitToComplete();
	PCB* temp = myPCB; //myPCB
	System::systemPCBManager->remove(System::systemPCBManager->get(getId()));
	delete(temp);
	//asm sti;
}

void Thread::waitToComplete(){
	if(myPCB->state != TERMINATING && myPCB != (PCB*)PCB::running && myPCB->state != NEW){
		PCB::running->state = BLOCKED;
		myPCB->queueOfThreadsWaitingForThisThread->put((PCB*)PCB::running);
		asm cli;
		System::thereAreBlockedThreads++;
		dispatch();
	}
}

Thread* Thread::getThreadById(ID id){
	if(System::systemPCBManager->get(id) != NULL){
		return System::systemPCBManager->get(id)->myPCB->myThread;
	}else{
		return NULL;
	}
}

void dispatch(){
	asm cli;
	explicitDispatch = 1;
	timer();
	asm sti;
}
