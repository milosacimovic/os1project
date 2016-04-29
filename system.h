//File: system.h
//Author: Milos Acimovic
#ifndef _system_h_
#define _system_h_

#include "list.h"
#include "idle.h"

class PCB;


typedef void interrupt (*pInterrupt)(...);
//lock and unlock primitives

class System {
public:

	static void initializeThreadManagement();
	//helper functions
	static void initializeAndRedirectTimerEntry();
	static void initializeSystemPCBManager();
	
	static void restoreSystemState();
	static void restoreTimerEntry();
	
private:
	static List* systemPCBManager;
	static Idle* idle;
	static PCB* mainPCB;
	static volatile int thereAreReadyThreads;
    static volatile int thereAreBlockedThreads;
	
	friend void interrupt timer(...);
	friend class Thread;
	friend class Idle;
	friend class PCB;
};
#endif