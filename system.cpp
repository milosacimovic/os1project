//File: system.cpp
//Author: Milos Acimovic

#include "system.h"
extern void tick();


volatile int explicitDispatch = 0;
volatile int lockFlag = 1;
volatile int whileLockedFlagThreadTimeSliceReachedZero = 0;
volatile unsigned int tss;
volatile unsigned int tsp;
volatile unsigned int tbp;

		
List* System::systemPCBManager = new List();
PCB* System::mainPCB = new PCB(0, 0, NULL); // It will not be in the systemPCBManager, hence any reference to mainPCB will go through friendship of System class
Idle* System::idle = NULL;
volatile int System::thereAreReadyThreads = 0;
volatile int System::thereAreBlockedThreads = 0;

/*===========================================================*/
/*===========================================================*/
void interrupt timer(...){
	
	//Semaphore maintenance
	//perhaps thread maintenance
	
	
	if(PCB::running->timeSlice != 0 && !explicitDispatch && PCB::running->state == RUNNING){
		PCB::running->remainingTimeOnCPU--;
	}
	
	tick(); //VERY IMPORTANT!
	
	if (explicitDispatch || (PCB::running->remainingTimeOnCPU == 0 && PCB::running->timeSlice != 0) || PCB::running->state == NEW) {
		if(lockFlag){
			//==================Save PCB::running context===================//
			asm {
				mov tsp, sp
				mov tss, ss
				mov tbp, bp
			}	

			PCB::running->sp = tsp;
			PCB::running->ss = tss;
			PCB::running->bp = tbp;
			//==============================================================//
			//Figure out when the thread isn't put back in the scheduler
			if (PCB::running->state == RUNNING) {	
				PCB::running->state = READY;	
				Scheduler::put((PCB*)PCB::running);
				System::thereAreReadyThreads++;
			}
			//workout the logic of when  the idle thread needs to execute
			//the idle thread needs to be able to get the CPU
			//if there are no ready threads and there are blocked threads on semaphores 
			//or events or waiting queues waiting for child threads to complete
			//in that case avoidance of getting a thread from a scheduler
			//and marking idle as running getting from the systemPCBManager
			//and avoidance of marking idle thread as running
			if(System::thereAreReadyThreads){
				PCB::running = Scheduler::get();
				PCB::running->state = RUNNING;
				System::thereAreReadyThreads--;
			}else if (System::thereAreBlockedThreads){
				PCB::running = System::systemPCBManager->get(System::idle->getId())->myPCB;
			}else{
				PCB::running = System::mainPCB;//is this else part necessary
			}
			//===================================================//
			tsp = PCB::running->sp;
			tss = PCB::running->ss; 
			tbp = PCB::running->bp;
			
			//Accounting maintenance
			PCB::running->remainingTimeOnCPU = PCB::running->timeSlice;
			
			//Stack switch
			asm {
				mov sp, tsp   
				mov ss, tss
				mov bp, tbp
			}     
			//==================================================//
		}else whileLockedFlagThreadTimeSliceReachedZero = 1;
	} 
    	
	if(!explicitDispatch) asm int 60h;
	
	explicitDispatch = 0;
}

/*================================================================================================================*/
void System::initializeThreadManagement(){
	initializeSystemPCBManager(); //has to execute before redirection of timer routine 
	initializeAndRedirectTimerEntry();
	idle = new Idle();
	idle->start();
}


void System::initializeSystemPCBManager(){
	mainPCB->state = RUNNING;
	PCB::running = mainPCB;
}

void System::initializeAndRedirectTimerEntry(){
	pInterrupt oldTimer = getvect(8);
	setvect(8, timer);
	setvect(96, oldTimer);
	
}
/*==================================================================================================================*/
void System::restoreSystemState(){
	if(PCB::running != mainPCB) return;
	delete idle;
	delete systemPCBManager;
	delete mainPCB;
	restoreTimerEntry();
}

void System::restoreTimerEntry(){
	pInterrupt oldTimer = getvect(96);
	setvect(8, oldTimer);
}

