#include "mesh.h"
#include "shader.h"

Mesh::Mesh(){
    VBO = -1;
    EBO = -1;
    VAO = -1;
}

void Mesh::create_mesh()
{
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    unsigned int verticesSize = 3*sizeof(float)*vertices.size();
    unsigned int texCoordsSize = 2*sizeof(float)*texCoords.size();
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize + texCoordsSize, 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, verticesSize, &vertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, verticesSize, texCoordsSize, &texCoords[0]);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)(verticesSize));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Mesh::draw(Shader &shader, Color color, glm::mat4 view, glm::mat4 projection)
{
    shader.set_texture(0);
    shader.set_color(color);
    shader.set_matrices(model, view, projection);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.get_texture());

    shader.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}