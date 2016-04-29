//File: usermainthread.cpp
//Author: Milos Acimovic


#include "umt.h"

int userMain (int argc, char* argv[]);

UMWrapper::UMWrapper(int argumentcount, char* argumentvalue[]): Thread(defaultStackSize, 1), argc(argumentcount), argv(argumentvalue){}

UMWrapper::~UMWrapper(){
	waitToComplete();	
}

void UMWrapper::run(){
	returnResult = userMain(argc, argv);
}
