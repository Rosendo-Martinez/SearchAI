#include <glad/glad.h>
#include "SquareRenderer.h"

SquareRenderer::SquareRenderer(Shader shader)
{
    // square
    const float vertices[] = {
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };

    // Generate IDs
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Copy data to buffer
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    this->VAO = VAO;
    this->shader = shader;
}

void SquareRenderer::draw(const glm::vec3& color, const glm::vec2& translate, const glm::vec2& scale)
{
    // Create model matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(translate, 1.0f));
    model = glm::scale(model, glm::vec3(scale, 1.0));

    // Set uniforms
    this->shader.use();
    this->shader.setVector("color", color);
    this->shader.setMat4("model", model);

    // Draw square
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Unbind VAO, and shader
    glBindVertexArray(0);
    glUseProgram(0);
}