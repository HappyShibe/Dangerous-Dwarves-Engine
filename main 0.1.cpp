//Dangerous Dwarves Engine Coded By Malcolm Donaldson 2016-2017
//NOTE THAT CODE THAT IS NOT FULLY UNDERSTOOD DOES NOT BELING HERE, IT BELONGS IN A SEPERATE "SANDBOX" CODE.
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

/*
-------------REMEMBER!---------------
-When you are having trouble determining where to fit a section of code, remember that code is executed sequentially
-Variable need to have descriptive yet short names
-When there is a syntax error check to make sure there is a semicolon!
-Recall that a buffer is a way to send information to memory (most often on the GPU)
-
-

-------------Code Notes----------------
-the window is called "mainWindow"
-
-
-
*/


void key_callback(GLFWwindow*mainWindow, int key, int scanCode, int action, int mode);

    //window height and width variables
     const int width = 940;
     const int height = 560;

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



    //Main loop
    //This while loop checks at each iteration if "glfwWindowShouldClose has been given a return value that instructs the window to close
    while(!glfwWindowShouldClose(mainWindow))
    {
        //checks if things like keyboard and mouse input have been detected
        glfwPollEvents();
        //Rendering code goes here


        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(mainWindow);


        //A triangle is defined
        GLfloat vertices[]=
        {
            0.0f, 0.3f, 0.0f,
            0.3f, -0.3f, 0.0f,
            -0.3f, -0.3f, 0.0f
        };
         //Set up the vertex shader
    //Make an ID for VBO
    GLuint VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);



        //set up key feedback
        //note the functions of GLFW such as GLFW_KEY_ESCAPE and GLFW_PRESS seem to output integers, when you create your own int and it equals the GLFW output then the if loop is run



    }

   //clean up GLEW and give a return value
   glfwTerminate();
    return 0;
}
//Close the window if the escape key is pressed
 void key_callback(GLFWwindow*mainWindow, int key, int scanCode, int action, int mode)
    {
            if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                glfwSetWindowShouldClose(mainWindow, GL_TRUE);
        }

