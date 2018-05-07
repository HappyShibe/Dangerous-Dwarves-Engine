//Dangerous Dwarves Engine Coded By Malcolm Donaldson 2016-2017
//NOTE THAT CODE THAT IS NOT FULLY UNDERSTOOD DOES NOT BELING HERE, IT BELONGS IN A SEPERATE "SANDBOX" CODE.
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <Shader.h>
#include <stb_image.h>
/*
---------FOR ADDITONAL INFORMATION ON THE FUNCTIONS OF A LINE OR THE PARAMETERS, REFER TO THE ENGINE MANUAL---------

-------------REMEMBER!---------------
-When you are having trouble determining where to fit a section of code, remember that code is executed sequentially
-Variable need to have descriptive yet short names
-When there is a syntax error check to make sure there is a semicolon!
-Recall that a buffer is a way to send information to memory (most often on the GPU)
-
-

*/


void key_callback(GLFWwindow*mainWindow, int key, int scanCode, int action, int mode);


    //window height and width variables
     const int width = 940;
     const int height = 560;

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
"uniform vec4 aColor;"
"void main()\n"
"{\n"
"color = aColor;\n"
"}\n\0";



     //Define a triangle
        GLfloat vertices[]=
        {
          /*0*/  -0.3f, -0.3f, 0.0f,
          /*1*/  0.3f, 0.3f, 0.0f,
          /*2*/  0.3f, -0.3f, 0.0f,
          /*3*/  -0.3f, 0.3f, 0.0f

        };

        GLuint indices[] =
        {
            0,1,2,
            0,1,3


        };

int main()
{
    //Set up OpenGL stuff
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


    //Create a window using GLFW
    GLFWwindow*mainWindow = glfwCreateWindow(width, height,"Dangerous Dwarves Engine", nullptr, nullptr);
    glfwMakeContextCurrent(mainWindow);
    //Output an error if the window was unable to be created
    if(mainWindow == NULL)
    {
        std::cout << "Window Invalid" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(mainWindow, key_callback);


    //Set up GLEW
    glewExperimental = GL_TRUE;
    //Output an error if GLEW could not start
    if(glewInit()!=GLEW_OK)
    {
        std::cout <<"GLEW did not start correctly" << std::endl;
        return -1;
    }

    //define the size of the window
    int width;
    int height;
    glfwGetFramebufferSize(mainWindow, &width, &height);
    glViewport(0,0, width, height);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //SHADER STUFF

    //Tell OpenGL how to interpret the vertex information you give to it


    //Create the shaders Link the vertex shader you created (glCreateShader creates the shader and GL_VERTEX_SHADER specifies the shader type
    GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //Attach and compile the shader
    //glShaderSource has following parameters. 1: takes in the shader object to be compiled. 2:The number of strings, 3:The source code to be used 4: can be left NULL
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);


    //Check for vertex shader compilation errors infolog gives a specific error
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout <<"Vertex Shader Could not be compiled" << infoLog << std::cout;
    }

    //Now for the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

     if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout <<"Fragment Shader Could not be compiled" << infoLog << std::cout;
    }

    //Now for the shader program that is the final, usable version of the shaders that we put in the while loop.
    GLint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //Check for errors
    glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);
       if(!success)
    {
        glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout <<"Shader program Could not be compiled" << infoLog << std::cout;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);



    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //VBO and VAO

        //Set up the vertex shader
    //Make an ID for VBO. REMEMBER that a VBO manages memory and holds information like coordinate data and pixel color, which it can send to the GPU in a large batch
    GLuint VBO;
    glGenBuffers(1, &VBO);
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    GLuint EBO;
    glGenBuffers(1, &EBO);


    //creates a buffer and binds the vertex  data so it can be sent to the GPU
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);


    //Main loop
    //This while loop checks at each iteration if "glfwWindowShouldClose has been given a return value that instructs the window to close
    while(!glfwWindowShouldClose(mainWindow))
    {
        //checks if things like keyboard and mouse input have been detected
        glfwPollEvents();
        //Rendering code goes here


        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glUseProgram(shaderProgram);

        GLfloat timeValue = glfwGetTime();
        GLfloat redValue = (sin(timeValue) /2) + 0.4;
        GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "aColor");
        glUniform4f(vertexColorLocation, redValue, 0.0f, 0.0f, 1.0f);


        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(mainWindow);


    //set up key feedback
    //note the functions of GLFW such as GLFW_KEY_ESCAPE and GLFW_PRESS seem to output integers, when you create your own int and it equals the GLFW output then the if loop is run

    }

   //clean up GLEW and give a return value
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);
   glfwTerminate();
    return 0;
}
//Close the window if the escape key is pressed
 void key_callback(GLFWwindow*mainWindow, int key, int scanCode, int action, int mode)
    {
            if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                glfwSetWindowShouldClose(mainWindow, GL_TRUE);
        }


