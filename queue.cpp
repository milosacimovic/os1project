//File: queue.cpp
//Author: Milos Acimovic
#include "queue.h"

void Queue::put(PCB* i){
	tail = ( head == NULL ? head : tail->next ) = new Element(i);
	num++;
}

Queue::Queue() : head(NULL), tail(NULL), num(0){}

PCB* Queue::get(){
	if(head != NULL){
		PCB* temp = head->myPCB;
		head = head->next;
		num--;
		return temp;
	}else{
		return NULL;
	}
}

int Queue::size(){
	return num;
}