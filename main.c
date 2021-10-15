
#include "main.h"
#include <time.h>

const int NUM_POINTS = 50000;
const double RADIUS  = 0.05;
int CELL_SIZE;

void printPoint(Point p)
{
	printf("P(%f, %f, %d, %d)\n", p.x, p.y, p.absx, p.absy);
}

int main()
{
	CELL_SIZE = floor(1.0/RADIUS);
	srand(time(NULL)); // Set random seed
	
	struct CellTree* cellTree = NULL;
	struct CellTree* treeCache = NULL;
	int count;
	clock_t start, end;
	Point points[NUM_POINTS];


	Point mask[] = {(Point){0,0,-1,-1}, (Point){0,0,-1,0}, (Point){0,0,-1,1},
			   (Point){0,0,0,-1} , (Point){0,0,0,0} , (Point){0,0,0,1} ,
			   (Point){0,0,1,-1} , (Point){0,0,1,0} , (Point){0,0,1,1}};
	
	for (int i =0; i<NUM_POINTS; i++)
	{
		double x =(double)rand()/(double)RAND_MAX;
		double y =(double)rand()/(double)RAND_MAX;
		points[i] = (Point){x,y,0,0};	

		toAbsPoint(&points[i], CELL_SIZE);
		
		
		int thisHash = toHashed(points[i], CELL_SIZE);
		insertIntoCellTree(&cellTree, thisHash, points[i]);
		
		if (findHash(treeCache, thisHash) == NULL)
		{
			for (int j=0; j<9; j++)
			{
				int tx = points[i].absx+mask[j].absx;
				int ty = points[i].absy+mask[j].absy;

				if ((tx>=0 && tx<CELL_SIZE && ty>=0 && ty<CELL_SIZE))
				{
					insertIntoCellTree(&treeCache, thisHash, (Point){0,0,tx,ty});
				}
			}
		}
	}
	
	start = clock();
	count = 0;	
	for (int i =0; i<NUM_POINTS; i++)
	{
		Point thisPoint = points[i];
		int thisHash = toHashed(thisPoint, CELL_SIZE);
		struct Cell** neighbourHashes = findHash(treeCache, thisHash);
		if (neighbourHashes != NULL)
		{
			struct Cell* neighbour = (*neighbourHashes);
			while (neighbour != NULL)
			{
				int thatHash = toHashed(neighbour->value, CELL_SIZE);
				struct Cell** neighbourCells = findHash(cellTree, thatHash);
				if (neighbourCells != NULL)
				{
					struct Cell* neighbourCell = (*neighbourCells);
					while (neighbourCell != NULL)
					{
						if (dist(thisPoint, neighbourCell->value) <= RADIUS)
						{
							count += 1;
						}
						neighbourCell = neighbourCell -> next;
					}	
				}
				neighbour = neighbour->next;
			}
		}
	}	
	end = clock() - start;
	printf("Time taken: %f s\n", (double)end/CLOCKS_PER_SEC);

	printf("%d\n", count);
	
	start = clock();
	count = 0;
	for (int i = 0; i <NUM_POINTS; i++)
	{
		for (int j =0; j < NUM_POINTS; j++)
		{
			if (dist(points[i], points[j])<=RADIUS)
			{
				count+=1;
			}
		}
	}
	
	end = clock() - start;
	printf("Time taken: %f s\n", (double)end/CLOCKS_PER_SEC);
	printf("%d\n", count);
	
	freeCellTree(&cellTree);
	freeCellTree(&treeCache);
	
	return 0;
}
