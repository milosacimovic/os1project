//File: list.cpp
//Author: Milos Acimovic

#include "list.h"

List::List(): first(NULL), last(NULL){}

void List::put(PCB* pcb){
	ElementD* temp = new ElementD(pcb);
	if(first == NULL){
		first = temp;
		last = temp;
	}else{
		last->next = temp;
		temp->prev = last;
		last = temp;
	}
}


PCB* List::get(){
	ElementD* temp;
	if(first != NULL){

		temp = first;
		first = first->next;
		return temp->myPCB;
	}
	return 0;
}


void List::remove(ElementD* current){
	
	if(current != NULL){
		if(current == first){
			first = first->next;
		}else if(current == last){
			last = current->prev;
			current->prev = NULL;
			last->next = NULL;
		}else{
			current->prev->next = current->next;
			current->next->prev = current->prev;
		}
		delete current;
	}
}



ElementD* List::get(ID threadId){
	ElementD* current = first;
	
	while(current != 0 && current->myPCB->id != threadId){
		current = current->next;
	}
	
	if(current != 0){
		return current;
	}else{
		return 0;
	}
}