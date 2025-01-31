#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SquareRenderer
{
private:
    unsigned int VAO;
    Shader shader;

public:
    SquareRenderer(Shader shader);

    void draw(float r, float g, float b);
    void draw(const glm::vec3& color, const glm::vec3& translate, const glm::vec2& scale);
};