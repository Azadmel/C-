//Finding the volume of water a 3D chessboard can hold.

#include "stdafx.h"
#include <iostream>
using namespace std;

/*Given: 
	Pointer to the first element of a 2D contiguous matrix of dimension M X N i.e M rows and N columns.
	In memory, a 2D array is an array of arrays which means that I will have 1 giant block of addresses.
*/

/*Edge propogation step: The max-edge value of an inner element is minimum of the available virtual heights from adjacent cells.
Note: The virtual height of a cell marked as an edge = original height. All others are  initialized to -1.
*/

void InitArrays(int *first, int rows,int columns,bool **edgeMatrix,int**maxVirtualHeights){

	int *p = first;
	int *innerFirst = NULL;

	//considering only inner elements all of which will have 4 neighbours
	for (int i = 0;i<rows;i++){
		for(int j = 0;j<columns;j++){	
			if(i>0 && i<rows-1 && j>0 && j<columns-1){				
				//cout << *p << "-->" << *(p-1) <<"," << (*(p - columns)) <<"," <<*(p + 1) <<","<< *(p + columns) << endl;
				edgeMatrix[i][j] = false;
				maxVirtualHeights[i][j] = -1;
				if(i==1 && j==1){
					innerFirst = p; //obtain pointer to first element of inner matrix.
				}
			}
			else{
				edgeMatrix[i][j] = true;
				maxVirtualHeights[i][j] = *p;
			}		
			//cout<< i<<","<<j << " edgeinit = " << edgeMatrix[i][j] <<endl;
			*p++;
		}
	}
}

/* Takes pointer to an inner cell, i & j are it's array indices. Returns minimum value from the Edge neighbours. 
If any of the available virtual heights of adjacent cells are less than current cell's original height,v height = o height. 
Else mark current cell's v height as a minimum of available v heights */

int GetMinFromEdgeCells(int *first,int i,int j,int**maxVirtualHeights){

	int minval = maxVirtualHeights[i-1][j]; //initialised to left cell since that is where we start the neighbor comparison from.
	
	//Step1:check which neighbours' virtual heights is available(!= -1).

	if(maxVirtualHeights[i-1][j]!=-1){
		//If available virtual height is less than current cell's original height,current v height = o height
		if(maxVirtualHeights[i-1][j] < *first){
			return *first;
		}
	}
	if(maxVirtualHeights[i][j-1]!=-1){
		if(maxVirtualHeights[i][j-1] < *first){
			return *first;
		}
		else if(maxVirtualHeights[i][j-1]<minval){
			minval = maxVirtualHeights[i][j-1];
		}
	}
	if(maxVirtualHeights[i+1][j]!=-1){
		if(maxVirtualHeights[i+1][j] < *first){
			return *first;
		}
		else if(maxVirtualHeights[i+1][j]<minval){
			minval = maxVirtualHeights[i+1][j];
		}
	}
	if(maxVirtualHeights[i][j+1]!=-1){
		if(maxVirtualHeights[i][j+1] < *first){
			return *first;
		}
		else if(maxVirtualHeights[i][j+1]<minval){
			minval = maxVirtualHeights[i][j+1];
		}
	}
	return minval;
}

/* Given pointer to current cell, Check if water will spill to next adjacent cells(rightwards and downwards).
 Returns pointer to bool array where 0th index denotes spill in right adjacent cell and 1st denotes left. */
bool* CheckWaterSpill(int *first,int columns,int i,int j,bool **edgeMatrix,int virtualHeight){

	int *current = first;
	bool *spillNeighbours = new bool[2]; //Store i,j indices per cell for 2 cells
	for(int a = 0;a<2;a++){
		spillNeighbours[a] = false; 
	}
	//next cell is not on the edge
	if(!(bool)edgeMatrix[i][j+1]){
		//Virtual height of current cell>original height of next cell
		if(virtualHeight>*(current+1)){
			spillNeighbours[0] = true;	//rightwards spill
		}
	}

	if(!(bool)edgeMatrix[i+1][j]){
		//Virtual height of current cell>original height of next cell
		if(virtualHeight>*(current+columns)){
			spillNeighbours[1] = true;	//downwards spill
		}
	}
	return spillNeighbours;
}

void FindMaxEdgebasedFlow(int *q,int rows,int columns,bool **edgeMatrix,int**maxVirtualHeights){

	int *first = q;
	for(int i = 0;i<rows;i++){
		for(int j = 0;j<columns;j++){
			//Calculate virtual heights for all inner cells here.
			if((bool)edgeMatrix[i][j]==false){
				bool *spill = NULL;
				maxVirtualHeights[i][j] = GetMinFromEdgeCells(first,i,j,maxVirtualHeights);
				int calcVirtualHeight= maxVirtualHeights[i][j];
				/*If the original height of non Edge adjacent cells is > v height of cell,pass.
				 Else v height = min{v height(previously assigned),FindMaxEdgebasedFlow(Adjacent cell 1),FindMaxEdgebasedFlow(Adjacent cell 2)} */
				spill = CheckWaterSpill(first,columns,i,j,edgeMatrix,maxVirtualHeights[i][j]);
				
				if((bool)spill[0]){
					//This means rightward spill is true. Right cell is (i,j+1).
					int recMin = GetMinFromEdgeCells(first+1,i,j+1,maxVirtualHeights);
					calcVirtualHeight = min(maxVirtualHeights[i][j],recMin);
				}
				if((bool)spill[1]){
					//This means downward spill is true. Down cell is (i+1,j).
					int recMin = GetMinFromEdgeCells(first+columns,i+1,j,maxVirtualHeights);
					calcVirtualHeight = min(calcVirtualHeight,recMin);
				}
				//Final height will be the greater one out of original height vs calculated maximum possible virtual aka water height.
				maxVirtualHeights[i][j] = max(*first,calcVirtualHeight);

				//cout<<" calculated edge = "<< maxVirtualHeights[i][j] <<endl;
			}
			*first++;
		}
	}
}


int CalcContainedWater(int *p_data, int rows,int columns){
	int totalUnits = 0;
	if(rows>2 && columns>2){
	
		bool **edgeMatrix = new bool*[rows];	//this matrix will mark the edges of the chessboard.
		for(int a = 0;a<rows;a++){
			edgeMatrix[a] = new bool[columns];
		}
		int **maxVirtualHeights = new int*[rows];
		for(int a = 0;a<rows;a++){
			maxVirtualHeights[a] = new int[columns];
		}

		InitArrays(p_data,rows,columns,edgeMatrix,maxVirtualHeights);
		FindMaxEdgebasedFlow(p_data,rows,columns,edgeMatrix,maxVirtualHeights);
	
		for (int i = 0;i<rows;i++){
			for(int j = 0;j<columns;j++){	
				totalUnits += (maxVirtualHeights[i][j]- *p_data); //Subtract original heights from calculated max virtual heights to get Units contained by each cell.
				//cout<<" v height - original = "<< maxVirtualHeights[i][j] <<" - "<<*p_data <<endl;
				*p_data++;
			}
		}
		cout<< "Total Units of Water Contained = " << totalUnits <<endl;
		return totalUnits;
	}
	else{
		cout<< "The chessboard needs to be atleast 3*3 to hold any water." <<endl;
		return totalUnits;
	}
}
