#ifndef CELL_H
#define CELL_H

#include<math.h>
#include<stdio.h>

typedef struct
{
	double x;
	double y;
	int absx;
	int absy;
} Point;

struct Cell
{
	Point  	    value;
	struct Cell* next;
};


struct CellTree
{
	int value;
	struct CellTree*  left;
	struct CellTree* right;
	struct Cell* 	 entry;
};

struct Cell* newCell(Point);
struct CellTree* newCellTree(int, Point);
void insertIntoCell(struct Cell**, Point);
void insertIntoCellTree(struct CellTree**, int, Point);
void printCellTree(struct CellTree*, int);
void printCell(struct Cell*, int);
struct Cell** findHash(struct CellTree*, int);
void freeCellTree(struct CellTree**);
void freeCell(struct Cell**);

#endif
