#include "Grid.h"

Grid::Grid(unsigned int numberOfRows, unsigned int numberOfColumns)
{
    // Create 2D array
    this->grid = new unsigned int*[numberOfRows];
    for (unsigned int i = 0; i < numberOfRows; i++)
    {
        this->grid[i] = new unsigned int[numberOfColumns];
        // TODO: initialize with default value
    }
}

Grid::~Grid()
{
    // TODO
}

/**
 * Gets the value at row i and column j;
 */
unsigned int Grid::get(unsigned int i, unsigned int j)
{
    return this->grid[i][j];
}

/**
 * Sets the value at row i and column j;
 */
void Grid::set(unsigned int i, unsigned int j, unsigned int newValue)
{
    this->grid[i][j] = newValue;
}