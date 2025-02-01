struct GridRawData
{
    const unsigned int rows = 0;
    const unsigned int cols = 0;
    const char* rawData = nullptr;

    GridRawData(unsigned int rows, unsigned cols, const char* rawData)
        : rows(rows), cols(cols), rawData(rawData)
    {}
};

GridRawData* gridData = nullptr;

void initializeGridData()
{    
    unsigned int cols = 4;
    unsigned int rows = 4;
    const char* rawData = 
    {
        "0 1 0 1 "
        "1 0 1 0 "
        "0 1 0 1 "
        "1 0 1 0 "
    };

    gridData = new GridRawData(rows, cols, rawData);
}