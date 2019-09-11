#include <iostream>
#include <cstdint>
#include "DynamicArray2D.h"
#include <iomanip>
// https://youtu.be/P8Xa2BitN3I

int main()
{
	int grid_rows, grid_cols, blocked_cells;
	std::cin >> grid_rows >> grid_cols >> blocked_cells;	
	
	DynamicArray2D<int> path2d(grid_rows, grid_cols);	
	// reset the array	
	for (auto& cell : path2d)
		cell = 0;
			
	int x, y;
	for (int blocked=0; blocked< blocked_cells; ++blocked)
	{
		std::cin >> x >> y;		
		path2d[y][x] = -1;
	}

	// check the number of possible paths from top left to bottom right cell (assuming none of them are blocked).
	// you can only move down or right n each step
	path2d[grid_rows - 1][grid_cols - 1] = 1;

	auto safe_get = [&](int row, int col)
	{
		if (row >= grid_rows)
			return 0;
		if (col >= grid_cols)
			return 0;
		auto result = path2d[row][col];
		if (result > 0)
			return result;
		return 0;
	};

	for (int row = grid_rows - 1; row >= 0; --row)
	{
		for (int col = grid_cols-1; col >=0; --col)
		{
			if (path2d[row][col] == 0)			
				path2d[row][col] = safe_get(row + 1, col) + safe_get(row, col + 1);
			
		}
	}
	std::cout << path2d[0][0] << std::endl;

	// print the grid	
	for (auto row = 0; row < grid_rows; ++row)
	{
		std::cout << std::endl;
		for (auto col = 0; col < grid_cols; ++col)
		{
			auto cell = path2d[row][col];
			std::cout << std::setw(5);
			if (cell < 0)
				std::cout << "X";
			else
				std::cout << path2d[row][col];
		}
			
	}
		
	return 0;

}