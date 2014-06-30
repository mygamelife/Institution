#include "Institution.h"
#include "LinkedList.h"
#include "Stack.h"
#include <stdio.h>
#include <malloc.h>

int Institution_reverse(LinkedList *inputList, LinkedList *outputList)
{	
	int i = 0 ;
	Institution *ptr2Inst , *PopStack;
	Stack *stack = Stack_create();
	
	//remove head and push into stack
	do
	{
		ptr2Inst = (Institution *)List_removeHead(inputList);
		if(ptr2Inst != NULL)
			printf("ptr2Inst %s\n" , ptr2Inst->name);
		else
			printf("ptr2Inst address %p\n" , ptr2Inst);
		Stack_push(stack,ptr2Inst);
	}while(ptr2Inst != NULL);
	
	//Pop the stack and add into tail
	do
	{
		PopStack = Stack_pop(stack);
		if(PopStack != NULL)
			printf("PopStack %s\n" , *PopStack);
		else
			printf("PopStack address %p\n" , PopStack);
		List_addTail(outputList , PopStack);
	}while(PopStack != NULL);
}

int isUniversityCollege (void *elem1 , void *type)
{
	int *target_type = (int*)elem1;
	int *expected_type = (int*)type;
	
	if(target_type == expected_type)
		return 1;
	
	else return 0;
}

int Institution_select(	LinkedList *inputList, 
						LinkedList *outputList ,
						void *criterion,
						int (*compare)(void *, void *))
{
	int* criterion_type = (int*)criterion;
	compare( , criterion);
}