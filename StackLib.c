/* John Jones 1001639122 */
#include "StackLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


///Stack Functions/////
void push(SNODE **StackTop, LNODE *List, int receipt, char Theater[])
{
	SNODE *NewNode = malloc(sizeof(SNODE));
	strcpy(NewNode->MovieTheaterName, Theater);
	NewNode->ReceiptNumber = receipt;
	NewNode->TicketList = List;
	//NewNode->node_number = NodeNumber;
	NewNode->next_ptr = NULL;

	if (*StackTop == NULL)
	{
		*StackTop = NewNode;
	}
	else
	{
		NewNode->next_ptr = *StackTop;
		*StackTop = NewNode;
	}
}

void pop(SNODE **StackTop)
{
	SNODE *TempPtr = *StackTop;

	if (*StackTop == NULL)
	{
		printf("Pop not executed - stack is empty\n\n");
	}
	else
	{

		free(*StackTop);
		*StackTop = TempPtr->next_ptr;
	}
}
