#include "Institution.h"
#include "LinkedList.h"
#include "Stack.h"
#include <stdio.h>
#include "CException.h"
#include "ErrorCode.h"

int Institution_reverse(LinkedList *inputList, LinkedList *outputList)
{	
	int i = 0 , count = 0 ;
	Institution *ptr2Inst , *PopStack;
	Stack *stack = Stack_create();
	
	/*removeHead and Push into stack*/
	do
	{
		ptr2Inst = (Institution *)List_removeHead(inputList);
		Stack_push(stack , ptr2Inst);
	}while(ptr2Inst != NULL);
	
	do
	{
		PopStack = Stack_pop(stack);
		List_addTail(outputList , PopStack);
		if(PopStack !=NULL)
			count++;
	}while(PopStack != NULL);
	
	return count; //minus one because the NULL 
}

/*Compare if institution are same type
 *Input:
 *			elem1 is a pointer to the first institution
 *			type is a pointer to institution type
*/
int isUniversityCollege (void *elem1 , void *type)
{
	Institution *Inst_type = (Institution *)elem1;
	Institution *expected_type = (Institution *)type;
	
	if(Inst_type == expected_type)
		return 1;
	
	else return 0;
}

/*Select if institution are same type
 *Input:
 *			inputList is a list of institions that we insert
 *			outputList is a list of institions that we selected
 *			criterion is a pointer to the criterion for selection
 *Output:
 *			number of institution selected
*/
int Institution_select(	LinkedList *inputList, 
						LinkedList *outputList ,
						void *criterion,
						int (*compare)(void *, void *))
{
	int result = 0 , selected = 0;
	Institution *inst;
	
	do
	{
		inst = (Institution *)List_removeHead(inputList);//insert first institution
		
		if(inst != NULL)
			result = isUniversityCollege((Institution*)inst->type , (Institution*)criterion);//compare type

		if(result == 1 && inst != NULL) //if type is same and inst not NULL
		{
			List_addTail(outputList , inst);
			selected++;
		}
			
	}while(inst != NULL);
	
	return selected++; //return selected institution type
}

int wasEstablishedBefore(void *elem , void *year)
{
	Institution* instYear = (Institution*)elem;
	int *specified_year = (int*)year;
		
	if(instYear->yearEstablished > 2014)
		Throw(ERR_INVALID_YEAR);
		
	if(instYear->yearEstablished < *specified_year)
		return 1;
		
	else return 0;
}