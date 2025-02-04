#include "Grid.h"

Grid::Grid(unsigned int numberOfRows, unsigned int numberOfColumns)
    : rows(numberOfRows), columns(numberOfColumns)
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
    // free memory
    for (unsigned int i = 0; i < this->rows; i++)
    {
        delete[] this->grid[i];
    }
    delete[] this->grid;
}

/**
 * Gets the value at row i and column j;
 */
unsigned int Grid::get(unsigned int i, unsigned int j) const
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

unsigned int Grid::getNumberOfRows() const
{
    return this->rows;
}

unsigned int Grid::getNumberOfColumns() const
{
    return this->columns;
}