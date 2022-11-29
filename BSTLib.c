/* John Jones 1001639122 */
#include "BSTLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


///BST Functions/////
void AddBSTNode(BNODE **current_node, char MovieTheaterName[], char ZipCode[], char FileName[], char Dimensions[])
{
	if (*current_node == NULL)
	{
		*current_node = (BNODE *)malloc(sizeof(BNODE));
		(*current_node)->left = (*current_node)->right = NULL;
		//(*current_node)->node_data = add_data;
		strcpy((*current_node)->MovieTheaterName, MovieTheaterName);
		strcpy((*current_node)->ZipCode, ZipCode);
		strcpy((*current_node)->FileName, FileName);
		strcpy((*current_node)->Dimensions, Dimensions);
	}
	else
	{
		if (strncmp(ZipCode, (*current_node)->ZipCode, 6) < 0) //add_data < (*current_node)->node_data
			AddBSTNode(&(*current_node)->left, MovieTheaterName, ZipCode, FileName, Dimensions);

		else if (strncmp(ZipCode, (*current_node)->ZipCode, 6) > 0) //add_data > (*current_node)->node_data
			AddBSTNode(&(*current_node)->right, MovieTheaterName, ZipCode, FileName, Dimensions);

		else
			printf(" Duplicate Element !! Not Allowed !!!");
	}
}

void InOrder(BNODE *tree_node)
{
    if(tree_node!= NULL)
    {
        InOrder(tree_node->left);
        printf("%-40s%5s\n", tree_node->MovieTheaterName, tree_node->ZipCode);
        //printf("%-18s\n", tree_node->ZipCode);
        InOrder(tree_node->right);
    }
}


BNODE *SearchForBNODE(BNODE *tree_node, char ZipCode[])
{
    int value;
    if (tree_node==NULL)
    {
        return NULL;
    }
    if(tree_node != NULL)
    {
        //printf("node is: %s\n", tree_node->ZipCode);
        value = strncmp(ZipCode, tree_node->ZipCode, 6);
        if(value == 0)
        {
            //printf("found match! at %s with zipcode %s\n", tree_node->MovieTheaterName,tree_node->ZipCode );
            return tree_node;
        }

        if(value < 0)
        {
            return SearchForBNODE(tree_node->left, ZipCode);
        }

        if(value > 0)
        {
            return SearchForBNODE(tree_node->right, ZipCode);
        }

    }
    //value = strncmp(ZipCode, tree_node->ZipCode, 6);

    return tree_node;//return tree_node;
}
