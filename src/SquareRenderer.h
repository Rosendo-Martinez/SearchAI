#include "Shader.h"

class SquareRenderer
{
private:
    unsigned int VAO;
    Shader shader;

public:
    SquareRenderer(Shader shader);

    void draw(float r, float g, float b);
};