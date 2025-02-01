#include <glad/glad.h>
#include "LineRenderer.h"

LineRenderer::LineRenderer(Shader shader)
{
    const float vertices[] = 
    {
        0.0f, 0.0f,
        1.0f, 0.0f
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
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    this->VAO = VAO;
    this->shader = shader;
}

void LineRenderer::draw(const glm::vec3& color, const glm::vec2& start, const glm::vec2& end)
{
    // Create model matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(start, 0.0));
    model[0] = glm::vec4(end - start, 0.0f, 0.0f);

    // Set uniforms
    this->shader.use();
    this->shader.setVector("color", color);
    this->shader.setMat4("model", model);

    // Draw line
    glBindVertexArray(this->VAO);
    glLineWidth(2.0f);
    glDrawArrays(GL_LINES, 0, 2);

    // Unbind VAO, and program
    glBindVertexArray(0);
    glUseProgram(0);
}