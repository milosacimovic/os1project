//File:usermainthread.h
//Author: Milos Acimovic

#ifndef _umt_h_
#define _umt_h_

#include "thread.h"

class UMWrapper: public Thread {
private:
	int argc;
	char** argv;
protected:
	void run();
public:
	UMWrapper(int argc, char* argv[]);
	~UMWrapper();
	int returnResult;
};

#endif
