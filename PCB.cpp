//File: PCB.cpp
//Author: Milos Acimovic

#include "PCB.h"
#include "system.h"

ID PCB::positionalId = 0;
volatile PCB* PCB::running = NULL;
extern volatile int lockFlag;
extern volatile int whileLockedFlagThreadTimeSliceReachedZero;


PCB::PCB(StackSize stacksize, Time timeslice, Thread* thread){
	
	stack = new unsigned [sizeOfStack = stacksize];
	timeSlice = timeslice;
	remainingTimeOnCPU = timeslice;
	myThread = thread;
	queueOfThreadsWaitingForThisThread = new Queue();
	id = positionalId++;
	state = NEW;
	
}

PCB::~PCB(){

	if(queueOfThreadsWaitingForThisThread != NULL)delete queueOfThreadsWaitingForThisThread;
	if(stack != NULL) delete[] stack;
	
}

void PCB::prepareStack(){
	
	stack[sizeOfStack - 1] = 0x200; //PSW with interrupts enabled
	stack[sizeOfStack - 2] = FP_SEG(&PCB::wrapper); //CS of the start of wrapper function
	stack[sizeOfStack - 3] = FP_OFF(&PCB::wrapper); //IP of the start of wrapper function
	//Registers ax, bx, cx, dx, es, ds, si, di, bp
	ss = FP_SEG(stack + sizeOfStack - 12);
	sp = FP_OFF(stack + sizeOfStack - 12);
	bp = sp;
	
}

void PCB::wrapper(){
	
	running->myThread->run();
	asm cli;
		
	while(running->queueOfThreadsWaitingForThisThread->size() > 0){
		PCB* temp = running->queueOfThreadsWaitingForThisThread->get();
		temp->state = READY;
		System::thereAreBlockedThreads--;
		System::thereAreReadyThreads++;
		Scheduler::put(temp);
	}
	running->state = TERMINATING;
	dispatch();
		
}


