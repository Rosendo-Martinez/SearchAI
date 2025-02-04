#include "Grid.h"

/**
 * Does not allocate memory for grid.
 */
Grid::Grid()
{
}

/**
 * Calls createGrid() to create the grid.
 */
Grid::Grid(unsigned int numberOfRows, unsigned int numberOfColumns)
{
    this->createGrid(numberOfRows, numberOfColumns);
}

Grid::~Grid()
{
    this->free();
}

/**
 * Allocates memory for the grid.
 */
void Grid::createGrid(unsigned int rows, unsigned int columns)
{
    this->free(); // free old mem.

    // Create 2D array
    this->grid = new unsigned int*[rows];
    for (unsigned int i = 0; i < rows; i++)
    {
        this->grid[i] = new unsigned int[columns];
        // TODO: initialize with default value
    }

    this->rows = rows;
    this->columns = columns;
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

/**
 * Frees memory.
 */
void Grid::free()
{
    if (this->grid != nullptr)
    {
        // free memory
        for (unsigned int i = 0; i < this->rows; i++)
        {
            delete[] this->grid[i];
        }
        delete[] this->grid;
    }
}