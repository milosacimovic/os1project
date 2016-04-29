//File: List.h 
//Author: Milos Acimovic

#ifndef _list_h_
#define _list_h_

#include "thread.h"
#include <iostream.h>
#include "PCB.h"
//Following data structure is a doubly linked list

struct ElementD{

	PCB* myPCB;
	ElementD* next;
	ElementD* prev;
	ElementD(PCB* pcb):myPCB(pcb), next(NULL), prev(NULL){}
};

class List{
public:
	List();
	
	
	void put(PCB* pcb);
	PCB* get();
	ElementD* get(ID id);
	void remove(ElementD*);
	
private:
	ElementD* first; 
	ElementD* last;
};

#endif