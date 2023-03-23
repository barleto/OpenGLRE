#include "Renderer.h"

void Renderer::draw(const VertexArray& va, const Shader& shader) const
{
    va.bind();
    shader.bind();
    glDrawElements(GL_TRIANGLES, va.getElementCount(), GL_UNSIGNED_INT, 0);
}
