/* John Jones 1001639122 */
#include "QueueLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


///Queue Functions/////
void enQueue(char Name[], QNODE **QueueHead, QNODE **QueueTail)
{
	QNODE *NewNode = malloc(sizeof(QNODE));
    strcpy(NewNode->Name, Name);
	NewNode->next_ptr = NULL;

	/* Queue is empty */
	if (*QueueHead == NULL)
	{
		*QueueHead = *QueueTail = NewNode;
	}
	else
	{
		(*QueueTail)->next_ptr = NewNode;
		*QueueTail = NewNode;
	}
}

void deQueue(QNODE **QueueHead)
{
	QNODE *TempPtr = (*QueueHead)->next_ptr;

	if (*QueueHead == NULL)
	{
		printf("Queue is emtpy\n\n");
	}
	else
	{
		free(*QueueHead);
		*QueueHead = TempPtr;
	}
}

void DisplayQueue(QNODE *QueueHead)
{
	QNODE *TempPtr= QueueHead;

	while (TempPtr!= NULL)
	{
		printf("%s\n", TempPtr->Name);
		TempPtr= TempPtr->next_ptr;
	}
	return;
}
