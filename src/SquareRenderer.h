#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SquareRenderer
{
private:
    unsigned int VAO;
    Shader shader;

    void initVAO();

public:
    SquareRenderer();
    SquareRenderer(Shader shader);

    void setShader(Shader newShader);
    void draw(const glm::vec3& color, const glm::vec2& translate, const glm::vec2& scale);
};