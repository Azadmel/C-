# C++
Code sample for calculating volume of a chessboard:

Base assumption:
For water to be contained in cell, it needs to be surrounded by 4 higher neighboring cells (not 8 as diagonal neighbors are excluded) to be leakproof. Thus cells on the edges will never hold any water.

My algorithm:

ii)	For every inner cell, max virtual height in theory is its original height + max possible water height. For inner cells, their virtual heights are more or less determined by the edge cells so that water doesn’t overflow.
iii)	I iterate over the inner cells, calculate their virtual heights from available edge heights. In my head this seemed like an Edge Propagation step as the movement is from inner top left cell to the inner bottom right.
iv)	For a cell where water could flow to next adjacent cells, I call a method to calculate the virtual height of the lower height cells. 
v)	After all max virtual heights are obtained, Volume of water is sum of capacities of all cells=max virtual heights matrix – original matrix.

