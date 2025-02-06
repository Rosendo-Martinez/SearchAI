struct GridRawData
{
    const unsigned int rows = 0;
    const unsigned int cols = 0;
    const char* rawData = nullptr;

    GridRawData(unsigned int rows, unsigned cols, const char* rawData)
        : rows(rows), cols(cols), rawData(rawData)
    {}
};

// GridRawData* gridData = nullptr;

const unsigned int GRID_RAW_DATA_SIZE = 1;
GridRawData* GRID_RAW_DATA[GRID_RAW_DATA_SIZE];

void initializeGridData()
{    
    const char* RAW_DATA_1 = 
    {
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
        "0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 "
        "0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 "
        "0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 "
        "0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 "
        "0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 "
        "0 0 0 0 0 0 1 1 1 1 1 1 0 0 0 0 "
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
    };
    GRID_RAW_DATA[0] = new GridRawData(16, 16, RAW_DATA_1);

    const char* RAW_DATA_2 = 
    {
        "0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 "
        "0 1 1 1 1 0 1 1 1 1 0 1 1 1 1 0 "
        "0 1 0 0 0 0 1 0 0 1 0 0 0 0 1 0 "
        "0 1 1 1 1 0 0 0 0 0 0 1 1 0 1 0 "
        "0 1 0 0 0 0 1 0 0 1 0 1 1 0 1 1 "
        "0 0 0 0 0 1 1 0 1 1 1 0 0 0 1 0 "
        "1 1 0 1 1 1 0 0 0 0 1 1 1 0 1 0 "
        "0 1 0 1 0 0 0 1 1 0 0 0 1 0 0 0 "
        "0 0 0 1 0 0 0 1 1 0 0 0 1 0 1 0 "
        "0 1 0 1 1 1 0 0 0 0 1 1 1 0 1 1 "
        "0 1 0 0 0 1 1 1 0 1 1 0 0 0 0 0 "
        "1 1 0 1 1 0 1 0 0 1 0 0 0 0 1 0 "
        "0 1 0 1 1 0 0 0 0 0 0 1 1 1 1 0 "
        "0 1 0 0 0 0 1 0 0 1 0 0 0 0 1 0 "
        "0 1 1 1 1 0 1 1 1 1 0 1 1 1 1 0 "
        "0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 "
    };
    GRID_RAW_DATA[1] = new GridRawData(16,16, RAW_DATA_2);

}