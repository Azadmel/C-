#ifndef ChessVolume 
#define ChessVolume

#include <algorithm>

/* This function fills in the the edgeMatrix based on the given 2D array to mark which cells are on the edge and which aren't. It also sets
the default max virtual height values of cells in another 2D array
 It takes pointer to the 0th element of original 2D array, number of rows and columns as the 2D edge and virtual heights array. 
*/
void InitArrays(int *first, int rows,int columns,bool **edgeMatrix,int**maxVirtualHeights);

/* This function takes pointer to an inner cell, i & j are it's array indices. Returns minimum value from the Edge neighbours.
*/
int GetMinFromEdgeCells(int *first,int i,int j,int**maxVirtualHeights);

/* Given pointer to current cell, Checks if water will spill to next adjacent cells(rightwards and downwards).
 Returns pointer to a bool array where 0th index denotes spill in right adjacent cell and 1st denotes left. 
 */
bool* CheckWaterSpill(int *first,int columns,int i,int j,bool **edgeMatrix,int virtualHeight);

/* This function takes pointer to the 0th element of chessboard and it calculates the maximum virtual heights of all inner cells.
*/
void FindMaxEdgebasedFlow(int *q,int rows,int columns,bool **edgeMatrix,int**maxVirtualHeights);

/*
	The function asked for in the question. Takes in pointer to 0th element of 2D array, number of rows and columns. Returns the total volume
	of water that can be contained in the chessboard.
*/
int CalcContainedWater(int *p_data, int rows,int columns);

#endif