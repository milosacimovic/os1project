//File: main.cpp
//Author: Milos Acimovic

#include "system.h"

#include "umt.h"
#include <iostream.h>

int main (int argc, char* argv[]) {
	cout << "main started\n";
	System::initializeThreadManagement();
	cout << "timer initialized and mainPCB created with id no. = " <<Thread::getRunningId()<<"\n";
	UMWrapper* wrapperMain = new UMWrapper(argc, argv);
	cout << "created UserMain\n";
	wrapperMain->start();
	cout << "in Main about to execute waitToComplete\n";
	wrapperMain->waitToComplete();
	
	int result = wrapperMain->returnResult;
	delete wrapperMain;
	cout << "in Main restoring system state with result of userMain = "<<result<<"\n";
	System::restoreSystemState();
	cout << "Happy end";
	return result;
}
