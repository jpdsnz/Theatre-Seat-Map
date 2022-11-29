/* John Jones 1001639122 */
#include "ListLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void InsertNode(LNODE **LinkedListHead, char Ticket[])
{
	LNODE *TempPtr, *PrevPtr, *NewNode;
	PrevPtr = NULL;
	TempPtr = *LinkedListHead;


    //&& (strncmp(TempPtr->Ticket, Ticket, 3) < 0 )
	while (TempPtr != NULL && (strncmp(TempPtr->Ticket, Ticket, 3) < 0 )) //TempPtr != NULL && TempPtr->node_number < NodeNumberToInsert
	{
		PrevPtr = TempPtr;
		TempPtr = TempPtr->next_ptr;
	}

	NewNode = malloc(sizeof(LNODE));
	strcpy(NewNode->Ticket, Ticket);
	//printf("\nTicket in the node is : %s\n", NewNode->Ticket);
	NewNode->next_ptr = TempPtr;

	if (PrevPtr == NULL)
	{
		*LinkedListHead = NewNode;
	}
	else
	{
		PrevPtr->next_ptr = NewNode;
	}
}

void ReturnAndFreeLinkedListNode(LNODE **LLH, char emptyTicket[])
{
    LNODE *TempPtr;

    //printf("\naddress of TempPtr is %p\n", TempPtr);
    //printf("\naddress of next pointer is %p\n", TempPtr->next_ptr);

    if(*LLH != NULL)
    {
        TempPtr = (*LLH)->next_ptr;
        strcpy(emptyTicket,(*LLH)->Ticket);
        free(*LLH);
        *LLH=TempPtr;

    }

    //return;
}





