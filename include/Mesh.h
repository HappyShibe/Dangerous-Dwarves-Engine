#ifndef MESH_H
#define MESH_H

class Mesh
{
public:
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> texture;

    Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
    {
        this->vertices = vertices;
        this->indices =indices;
        this->texture = texture;

        this->setupMesh();
    }

    void Draw (Shader shader);
private:
    GLuint VAO, VBO, EBO;

    void setupMesh();
    {
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VAO);
        glGenBuffers(1, &this->EBO);

        glBindVertexArray(this->VAO)
    }
};

#endif // MESH_H
