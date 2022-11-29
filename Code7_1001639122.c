/* John Jones 1001639122 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include "BSTLib.h"
#include "ListLib.h"
#include "QueueLib.h"
#include "StackLib.h"

///LINK LIST PROTOTYPES/////
void get_command_line_parameter(char *argv[], char ParamName[], char ParamValue[]);
void displayList (LNODE **LinkedListHead);
void readQueue(FILE *MyFile, QNODE **qHead, QNODE **qTail);
void readZip(FILE *MyFile, BNODE **Root);
///SEATMAP PROTOTYPES
void fillSeatMap (char myArray[][20], char string[], int row, int col);
int convertLetterToInt(char letter);
void seatMapSold(char myArray[][20], int a, int b);
int readSeatMap(char myArray[][20], BNODE *tree_node);
void printSeatMap (char myArray[][20], int row, int col);
int getRow(char dimensions[]);
int getCol(char dimensions[]);
int QueueCounter(QNODE *QueueHead);
int seatMapCheck(char myArray[][20], int a, int b);
void writeSeatMap (char myArray[][20], BNODE *tree_node, int row, int col);
int countEmptySeats (char myArray[][20], int row, int col);

///MAIN//////
int main(int argc, char *argv[])
{
	///File Code//////
	char zipfileName[100] = {}; //filename
	char queuefileName[100] = {}; //queue filename
	char receiptString[100] = {}; //receipt string
	char arg_value[100] = {};
	FILE *zipFile;
	FILE *qFile;
	//FILE *seatFile;

	///Code 7 Variables////
	char seatMapArray[26][20] = {};
	int receiptNum = 0; //value scanned in from receipt string
	int menuChoice=0; //choice used for menu
	char userZipChoice[6];
	//int counter=0;
	int row =0;
    int col =0;


	///Get CommandLine////
	get_command_line_parameter(argv, "ZIPFILE=", arg_value);
	strcpy(zipfileName, arg_value);

	get_command_line_parameter(argv, "RECEIPTNUMBER=", arg_value);
	strcpy(receiptString, arg_value);
	sscanf(receiptString, "%d", &receiptNum); //Search this string for int value

	get_command_line_parameter(argv, "QUEUE=", arg_value);
	strcpy(queuefileName, arg_value);


	zipFile= fopen(zipfileName, "r");
    if (zipFile== NULL)
	{
		printf(" %s did not properly open...exiting\n", zipfileName);
		exit(0);
	}

	qFile= fopen(queuefileName, "r");
    if (qFile== NULL)
	{
		printf(" %s did not properly open...exiting\n", queuefileName);
		exit(0);
	}

	LNODE *LinkedListHead = NULL;
	SNODE *StackTop = NULL;
	QNODE *QueueHead = NULL, *QueueTail = NULL;
	BNODE *Root = NULL;

    readQueue(qFile, &QueueHead, &QueueTail);
    readZip(zipFile, &Root);



    do
    {
        ///Print Menu Code////
        printf("1.\tSell tickets to next customer\n2.\tSee who's in line\n3.\tSee the seat map for a given theater\n4.\tPrint today's receipts\n\n");
        printf("Enter choice: ");
        scanf(" %d", &menuChoice);
        while(menuChoice<1 || menuChoice>4) //change first menuchoice to 1 and remove the 0 if statement later
        {
            printf("\ninvalid choice\n\n");
            printf("Enter Choice ");
            scanf(" %d", &menuChoice);
        }

        /*
        if(menuChoice==0) //only used for testing, so can quit program
        {
            break;
        }
        */

        if(menuChoice==1)
        {
            printf("\n");
            printf("Hello %s\n\n", QueueHead->Name);
            printf("Pick a theater by entering the zipcode\n\n");
            InOrder(Root);//BST print out zip and movie theater
            printf("\n");
            printf("Enter zip ");
            scanf(" %s", userZipChoice);
            BNODE *currentNode = SearchForBNODE(Root, userZipChoice);
            while(currentNode==NULL)
            {
                printf("\nInvalid zipcode");
                printf("\nEnter zip ");
                scanf(" %s", userZipChoice);
                currentNode = SearchForBNODE(Root, userZipChoice);
            }
            if(currentNode !=NULL)
            {
                //printf("\n\nSelected Zip Code is : %s\n", currentNode->ZipCode); //USED FOR CHECKING THE CURRENT NODE WAS REALLY SELECTED FROM BST
                ///Check seatmap dimensions
                while(readSeatMap(seatMapArray, currentNode)==1)
                {
                    printf("Enter zip ");
                    scanf(" %s", userZipChoice);
                    currentNode = SearchForBNODE(Root, userZipChoice);
                    while(currentNode==NULL)
                    {
                        printf("\nInvalid zipcode");
                        printf("\nEnter zip ");
                        scanf(" %s", userZipChoice);
                        currentNode = SearchForBNODE(Root, userZipChoice);
                    }
                }

                int ticketsToBuy;
                int rowPt, colPt; //hold the row and col pt to fill in
                char letter; //hold row letter variable
                char ticket[3]={}; //ticket string to copy into LNODE
                printf("\nHow many movie tickets do you want to buy? ");
                scanf("%d", &ticketsToBuy);


                row = getRow(currentNode->Dimensions); //get row value from node
                col = getCol(currentNode->Dimensions); //get col value from
                while(ticketsToBuy<=0 || ticketsToBuy>countEmptySeats(seatMapArray, row, col))
                {
                    printf("\nNot enough seats for your request or selection is out of bounds!\n");
                    printf("\nPlease choose a valid number of tickets!\n");
                    printf("\nHow many movie tickets do you want to buy? ");
                    scanf("%d", &ticketsToBuy);
                }
                //printf("\nRow value is : %d\n", row);
                //printf("\nCol value is : %d\n", row);
                while(ticketsToBuy>0)//loop until tickets are sold
                {
                    printf("\nPick a seat (Row Seat) ");
                    scanf(" %c%d", &letter, &colPt);
                    letter = toupper(letter);
                    rowPt = convertLetterToInt(letter);//converting letter to int
                    ///Check that Row/Col Point is in Bounds
                    while((rowPt<0 || rowPt>(row-1)) || (colPt<0 || colPt>col) || (seatMapCheck(seatMapArray, rowPt, colPt-1) == 1))
                    {
                        if((rowPt<0 || rowPt>(row-1)) || (colPt<0 || colPt>col))
                        {
                            row = getRow(currentNode->Dimensions); //get row value from node
                            col = getCol(currentNode->Dimensions); //get col value from node
                            printf("\nSelection out of bounds!\n");
                            printf("\nPick a seat (Row Seat) ");
                            scanf(" %c%d", &letter, &colPt);
                            letter = toupper(letter);
                            rowPt = convertLetterToInt(letter);//converting letter to int
                        }
                        ///SEATMAP CHECK////
                        if(seatMapCheck(seatMapArray, rowPt, colPt-1) == 1)
                        {
                            printf("\nSeat has been sold, Pick another seat\n");
                            printf("\nPick a seat (Row Seat) ");
                            scanf(" %c%d", &letter, &colPt);
                            letter = toupper(letter);
                            rowPt = convertLetterToInt(letter);//converting letter to int
                        }
                    }
                    ///Create String FROM LETTER AND INT To Place in Linked List
                    sprintf(ticket, "%c%d", letter, colPt); //Splice letter and Colpt into ticket.

                    /*
                    char num2char[2] = {}; //array to hold column number user selects
                    sprintf(num2char, "%d", colPt); //convert second number to char to place in char array
                    ticket[0]=letter; //place letter
                    ticket[1]=num2char[0]; //place first digit
                    ticket[2]=num2char[1]; //place second digit
                    */

                    seatMapSold(seatMapArray, rowPt,colPt-1); //Marked Sold Seat with X
                    printSeatMap(seatMapArray, row, col); //print seatmap again
                    //printf("\nticket string is %s\n", ticket);
                    InsertNode(&LinkedListHead, ticket); //Place Into linked list
                    ticketsToBuy--; //decrement ticketsToBuy
                }

            }
            ///WRITE FILE CODE
            int row = getRow(currentNode->Dimensions); //get row value from node
            int col = getCol(currentNode->Dimensions); //get col value from node
            writeSeatMap (seatMapArray, currentNode, row, col);
            push(&StackTop, &(*LinkedListHead), receiptNum, currentNode->MovieTheaterName); //Add to Stack
            receiptNum++;
            LinkedListHead = NULL;
            printf("\nThank you %s - enjoy your movie!\n\n", QueueHead->Name);
            deQueue(&QueueHead); //do this last!
            //counter = QueueCounter(*&QueueHead);
        }

        else if(menuChoice==2)
        {
            printf("\n\nCustomer Queue\n\n");
            printf("\n");
            DisplayQueue(*&QueueHead); //print out the queue
            printf("\n");
            //deQueue(&QueueHead);
            //counter = QueueCounter(*&QueueHead);
            //printf("\ncounter is %d\n", counter);
        }

        else if(menuChoice==3)
        {
            printf("Pick a theater by entering the zipcode\n\n");
            InOrder(Root);//BST print out zip and movie theater
            printf("\n");
            printf("Enter zip ");
            scanf(" %s", userZipChoice);
            BNODE *currentNode = SearchForBNODE(Root, userZipChoice);
            while(currentNode==NULL)
            {
                printf("\nInvalid zipcode");
                printf("\nEnter zip ");
                scanf(" %s", userZipChoice);
                currentNode = SearchForBNODE(Root, userZipChoice);
            }
            if(currentNode !=NULL)
            {
                //printf("\n\nSelected Zip Code is : %s\n", currentNode->ZipCode); //USED FOR CHECKING THE CURRENT NODE WAS REALLY SELECTED FROM BST
                ///Check seatmap dimensions
                while(readSeatMap(seatMapArray, currentNode)==1)
                {
                    printf("Enter zip ");
                    scanf(" %s", userZipChoice);
                    currentNode = SearchForBNODE(Root, userZipChoice);
                    while(currentNode==NULL)
                    {
                        printf("\nInvalid zipcode");
                        printf("\nEnter zip ");
                        scanf(" %s", userZipChoice);
                        currentNode = SearchForBNODE(Root, userZipChoice);
                    }
                }
            }

            //counter = QueueCounter(*&QueueHead); //need counter at the end
        }


        else if(menuChoice==4)
        {
            char emptyTicket[3] = {};
            if(StackTop == NULL)
            {
                printf("\nThere are no receipts!\n\n");
                //counter = QueueCounter(*&QueueHead); //need counter at the end
            }

            else
            {
                printf("Today's receipts\n\n");
                while(StackTop != NULL)
                {
                    printf("Receipt #%d\n", StackTop->ReceiptNumber);
                    printf("%16s", " ");
                    printf("%-s\n", StackTop->MovieTheaterName);
                    printf("%16s", " ");

                    while((StackTop->TicketList) != NULL)
                    {
                        ReturnAndFreeLinkedListNode(&(StackTop->TicketList), emptyTicket); //need to create in ListLib.c
                        printf("%-4s ", emptyTicket);
                    }
                    printf("\n\n");
                    pop(&StackTop);
                }
            }

        }
    }
    while(QueueHead != NULL); //KEEPS RUNNING UNTIL THE QUEUE IS EMPTY.


    ///QUEUE EMPTY PRINTING RECEIPTS////
    char emptyTicket[3] = {};
    printf("Good job - you sold tickets to all of the customers in line.\n\n");
    printf("Today's receipts\n\n");
                while(StackTop != NULL)
                {
                    printf("Receipt #%d\n", StackTop->ReceiptNumber);
                    printf("%16s", " ");
                    printf("%-s\n", StackTop->MovieTheaterName);
                    printf("%16s", " ");

                    while((StackTop->TicketList) != NULL)
                    {
                        ReturnAndFreeLinkedListNode(&(StackTop->TicketList), emptyTicket); //need to create in ListLib.c
                        printf("%-4s ", emptyTicket);
                    }
                    printf("\n\n");
                    pop(&StackTop);
                }
	return 0;
}

void writeSeatMap (char myArray[][20], BNODE *tree_node, int row, int col)
{
	int i=0;
	int j=0;

	char seatMapFile[100] = {};
    strcpy(seatMapFile, tree_node->FileName);
	FILE *sFile;
    sFile= fopen(seatMapFile, "w");
    if (sFile== NULL)
	{
		printf(" %s did not properly open...exiting\n", seatMapFile);
		exit(0);
	}

	for(i=0; i<row; i++)
	{

		for(j=0; j<col; j++)
		{
			fprintf(sFile, "%c", myArray[i][j]); //Print value of seatmap
		}

	}
	fprintf(sFile, "\n");
	if (ferror(sFile))
	{
        perror("\n\nDid not write properly write... exiting ");
	}
	fclose(sFile);
	return;
}

///Print Seatmap Array
void printSeatMap (char myArray[][20], int row, int col)
{
	int i=0;
	int j=0;
	char letter='A';
    for(i=0; i<col; i++)
    {
        printf("\tSeat %d", i+1); //Seat Number
    }
	for(i=0; i<row; i++)
	{
        printf("\nRow %c", letter); //Row Letter
        letter++;
		for(j=0; j<col; j++)
		{
			printf("\t%c", myArray[i][j]); //Print value of seatmap
		}
		printf("\n");
	}
	printf("\n\n");
	return;
}

///Fill Seatmap Array
void fillSeatMap (char myArray[][20], char string[], int row, int col)
{
	int i=0;
	int j=0;
	int count=0;
	for(i=0; i<row; i++)
	{
		for(j=0; j<col; j++)
		{
            myArray[i][j]= string[count];
            count++;
		}
	}
	return;
}

int countEmptySeats (char myArray[][20], int row, int col)
{
	int i=0;
	int j=0;
	int counter=0;
	for(i=0; i<row; i++)
	{
		for(j=0; j<col; j++)
		{
            if (myArray[i][j]=='O')
                counter++;
		}
	}
	return counter;
}
///Mark a sold seat in the array
void seatMapSold(char myArray[][20], int a, int b)
{
    myArray[a][b]='X';
	return;
}


int seatMapCheck(char myArray[][20], int a, int b)
{
    if (myArray[a][b]=='X')
        return 1;

    return 0;
}

///Get Row and Col From a String
int getRow(char dimensions[])
{
    int row;
    int col;
    sscanf(dimensions, " %dx%d", &row, &col);
    return row;
}

int getCol(char dimensions[])
{
    int row;
    int col;
    sscanf(dimensions, " %dx%d", &row, &col);
    return col;
}

void get_command_line_parameter(char *argv[], char ParamName[], char ParamValue[])
{
	int i= 0;
	while (argv[++i] != NULL)
	{
		if (!strncmp(argv[i], ParamName, strlen(ParamName)))
		{
			strcpy(ParamValue, strchr(argv[i], '=') + 1);
		}
	}
return;
}

void readZip(FILE *MyFile, BNODE **Root)
{
	///--Begin File Read Code--//
	char buffer[100] = {}; //declaring buffer to use for input
	char theatreName[100]={};
	char zipCode[100]={};
	char fileName[100] ={};
	char dimensions[100] = {};

    int counter = 0; //declaring counter to pass
    //--Begin File Read Loop--//
    char* token;
    while (fgets(buffer, sizeof(buffer), MyFile) != NULL)
    {
        buffer[strlen(buffer)-1] = '\0'; // kill the newline fgets() stores
        //printf("\nbuffer is : %s\n", buffer); //print out buffer to TEST
        token = strtok(buffer, "|");
        while (token != NULL)
        {
            strcpy(theatreName, token);
            //printf("\nOriginal token is %s\n", token);
            token = strtok(NULL, "|");
            strcpy(zipCode, token);
			token = strtok(NULL, "|");
            strcpy(fileName, token);
			token = strtok(NULL, "|");
            strcpy(dimensions, token);
            //printf("\nString token is %s\n", token);
            token = strtok(NULL, "|");
            //Code to add node - passing in the letter and the string for the draw command
            //printf("\nChar is: %c", newLetter); //Print out variable to test for char
            //printf("\nString is: %s", cmdString); //print out variable to test for string
            AddBSTNode(*&Root, theatreName, zipCode, fileName, dimensions);
            counter++;
        }
    }
    if (ferror(MyFile))
	{
        perror("\n\nDid not read properly... exiting ");
	}
    //printf("\nFinal count of B nodes is: %d\n\n", counter); //show count of nodes
    fclose(MyFile); //close file
    ///END FILE READ CODE AND NODE GENERATION
}



int readSeatMap(char myArray[][20], BNODE *tree_node)
{
    char dims[100] = {};
    strcpy(dims, tree_node->Dimensions);
    char buffer[100] = {};
    char seatMapFile[100] = {};
    int row;
    int col;
    strcpy(seatMapFile, tree_node->FileName);
    FILE *sFile;
    sFile= fopen(seatMapFile, "r");
    if (sFile== NULL)
	{
		printf(" %s did not properly open...exiting\n", seatMapFile);
		exit(0);
	}
    sscanf(dims, " %dx%d", &row, &col);
    while (fgets(buffer, sizeof(buffer), sFile) != NULL)
    {
        buffer[strlen(buffer)-1] = '\0'; // kill the newline fgets() stores
        //printf("\nbuffer is : %s\n", buffer); //print out buffer to TEST
    }
    if (ferror(sFile))
	{
        perror("\n\nDid not read properly... exiting ");
	}
    //printf("\nFinal count of Q nodes is: %d\n\n", counter); //show count of nodes
    fclose(sFile); //close file

    //Check if Dimensions of seatmap file match the dimensions of theater
    int seatsize = strlen(buffer);
    //printf("\nSize of seat map is %d\n", strlen(buffer));
    if((row*col)!=seatsize)
    {
        printf("\nDimensions not matching, pick another theater\n");
        return 1;
    }



    fillSeatMap(myArray, buffer, row, col);
    printSeatMap(myArray, row, col);
    return 0;
}

void readQueue(FILE *MyFile, QNODE **qHead, QNODE **qTail)
{
	///--Begin File Read Code--//
	char buffer[100] = {}; //declaring buffer to use for input
    int counter = 0; //declaring counter to pass
    //--Begin File Read Loop--//
    //char* token;
    while (fgets(buffer, sizeof(buffer), MyFile) != NULL)
    {
        buffer[strlen(buffer)-1] = '\0'; // kill the newline fgets() stores
        //printf("\nbuffer is : %s\n", buffer); //print out buffer to TEST
        enQueue(buffer, *&qHead, *&qTail); //add the name from buffer to Queue
        counter++;
    }
    if (ferror(MyFile))
	{
        perror("\n\nDid not read properly... exiting ");
	}
    //printf("\nFinal count of Q nodes is: %d\n\n", counter); //show count of nodes
    fclose(MyFile); //close file
    ///END FILE READ CODE AND NODE GENERATION
    return;
}


int convertLetterToInt(char letter)
{
    int val1=0;
    val1 = toupper(letter) - 65;
    return val1;
}

int QueueCounter(QNODE *QueueHead)
{
    int counter = 0;
	QNODE *TempPtr= QueueHead;

	while (TempPtr!= NULL)
	{
		//printf("%s\n", TempPtr->Name);
		counter++;
		TempPtr= TempPtr->next_ptr;
	}
	return counter;
}

