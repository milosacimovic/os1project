//File: queue.h
//Author: Milos Acimovic
//For test purposes this queue will be tested as a seperate module with elements that are integers

#include <iostream.h>
class PCB;



class Queue{
public:
	struct Element{
		PCB* myPCB;
		Element* next;
		Element(PCB* pcb) : myPCB(pcb), next(NULL){}
	};
	
	Queue();
	
	int size();
	void put(PCB* i);
	PCB* get();
private:
	int num;
	Element* head;
	Element* tail;
};