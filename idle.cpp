//File: idle.cpp
//Author: Milos Acimovic

#include "idle.h"
#include "system.h"
#include "PCB.h"
#include <iostream.h>

extern volatile int lockFlag;
extern volatile int whileLockedFlagThreadTimeSliceReachedZero;

void Idle::run(){
	while(1);
}

void Idle::start(){
	
	System::systemPCBManager->get(getId())->myPCB->state = NEW;
	System::systemPCBManager->get(getId())->myPCB->prepareStack();
	
}