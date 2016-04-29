//File: idle.h 
//Author: Milos Acimovic
//CANNOT end in scheduler
#ifndef _idle_h_
#define _idle_h_

#include "thread.h"

class Idle : public Thread{
public:
	Idle() : Thread(defaultStackSize, 0) {}
	~Idle() {waitToComplete();}
	void run();
	void start();
};

#endif