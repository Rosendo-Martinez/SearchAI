#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class LineRenderer
{
private:
    unsigned int VAO;
    Shader shader;

    void initVAO();

public:
    LineRenderer();
    LineRenderer(Shader shader);

    void setShader(Shader newShader);
    void draw(const glm::vec3& color, const glm::vec2& start, const glm::vec2& end);
};