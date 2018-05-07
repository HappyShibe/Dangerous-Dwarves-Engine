#ifndef SHADER_H
#define SHADER_H


class Shader
{
    public:



//Define the Vertex shader
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";

//Define the Fragment shader
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(0.3f, 0.3f, 0.3f, 1.0f);\n"
"}\n\0";
    protected:

    private:
};

#endif // SHADER_H
