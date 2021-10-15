#include<stdlib.h>
#include "cell.h"

struct Cell* newCell(Point point)
{
	struct Cell* cell = (struct Cell*) malloc(sizeof(struct Cell));

	cell->value = point;
	cell->next = NULL;

	return cell;
}

struct CellTree* newCellTree(int hashValue, Point point)
{
	struct CellTree* cellTree = (struct CellTree*) malloc(sizeof(struct CellTree));

	cellTree -> entry = newCell(point);
	cellTree -> value = hashValue;

	cellTree -> left =  NULL;
	cellTree -> right = NULL;

	return cellTree;
}

void insertIntoCell(struct Cell** entry, Point point)
{	
	struct Cell* cell = (struct Cell*) malloc(sizeof(struct Cell));

	cell -> value = point;
	cell -> next = *entry;

	*entry = cell;
}

void insertIntoCellTree(struct CellTree** entry, int hashValue, Point point)
{
	if (*entry == NULL)
	{
		*entry = newCellTree(hashValue, point);
	}
	else
	{
		if (hashValue <  (*entry)->value)
		{
			insertIntoCellTree(&(*entry)->left, hashValue, point);
		}
		else if(hashValue > (*entry)->value)
		{
			insertIntoCellTree(&(*entry)->right, hashValue, point);
		}
		else
		{
			insertIntoCell(&((*entry)->entry), point);
		}
	}
}

struct Cell** findHash(struct CellTree* entry, int hashValue)
{
	if (entry == NULL)
	{
		return NULL;
	}
	else
	{
		if (entry -> value == hashValue)
		{
			return &(entry->entry);
		}
		else
		{
			if (hashValue > entry->value)
			{
				return findHash(entry->right, hashValue);
			}
			else
			{
				return findHash(entry->left, hashValue);
			}
		}
	}
}

void printCell(struct Cell* entry, int depth)
{
	printf("(#%d) P(%f, %f, %d, %d)\n", depth, entry->value.x, entry->value.y, entry->value.absx, entry->value.absy);
	if (entry->next != NULL)
	{
		printCell(entry->next, depth+1);
	}
}
void printCellTree(struct CellTree* entry, int depth)
{
	printf("(#%d) %d\n", depth, entry->value);
	if (entry->left != NULL)
	{
		printCellTree(entry->left, depth+1);
	}
	if (entry->right != NULL)
	{
		printCellTree(entry->right, depth+1);
	}
}

void freeCell(struct Cell** entry)
{
	if ((*entry)->next != NULL)
	{
		freeCell(&((*entry)->next));
	}
	free(*entry);
}

void freeCellTree(struct CellTree** entry)
{
	if ((*entry)->left != NULL)
	{
		freeCellTree(&((*entry)->left));
	}
	if ((*entry)->right != NULL)
	{
		freeCellTree(&((*entry)->right));
	}
	freeCell(&((*entry)->entry));
	free(*entry);
}
