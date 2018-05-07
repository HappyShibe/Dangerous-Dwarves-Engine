//Dangerous Dwarves Engine Coded By Malcolm Donaldson 2016-2017
//include the necessary libraries
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <Shader.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//---------FOR ADDITONAL INFORMATION ON THE FUNCTIONS OF A LINE OR THE PARAMETERS, REFER TO THE ENGINE MANUAL---------
//callbacks for GLFW keyboard and mouse inputs
void key_callback(GLFWwindow*mainWindow, int key, int scanCode, int action, int mode);
void mouseCallback(GLFWwindow*mainWindow, double xpos, double ypos);

 //Declaration of variables
     //Screen dimensions
     const int width = 966;
     const int height = 700;
     bool keys[1024];
     void movement();
     GLfloat deltaTime = 0.0f;
     GLfloat lastFrame = 0.0f;
     GLfloat lastX = (width/2);
     GLfloat lastY = (height/2);
     GLfloat pitch = 0.0f;
     GLfloat yaw = -90.0f;
     bool firstMouse = true;

        //Define camera values
        glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 15.5f);
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 cameraDirection = glm::normalize(cameraPosition - cameraTarget);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

  //Define the Vertex shader
  const GLchar* vertexShaderSource = "#version 330 core\n"
  "layout(location = 0) in vec3 position;\n"
  "layout(location = 1) in vec3 color;\n"
  "out vec3 aColor;\n"
  "uniform mat4 model;\n"
  "uniform mat4 view;\n"
  "uniform mat4 projection;\n"
  "void main()\n"
  "{\n"
  "gl_Position = projection*view*model*vec4(position, 1.0f);\n"
  "aColor = color;\n"
  "}\0";

  //Define the Fragment shader
  const GLchar* fragmentShaderSource = "#version 330 core\n"
  "in vec3 aColor;\n"
  "out vec4 color;\n"
  "void main()\n"
  "{\n"
  "color = vec4(aColor, 1.0f);\n"
  "}\n\0";

     //Define a the points
        GLfloat vertices[]=
        {
          /*0*/ -0.3f, -0.3f, 0.0f,     1.0f, 0.5f, 0.0f,
          /*1*/  0.3f, 0.3f, 0.0f,      0.0f, 0.5f, 1.0f,
          /*2*/  0.3f, -0.3f, 0.0f,     0.5f, 1.0f, 0.1f,
          /*3*/  -0.3f, 0.3f, 0.0f,     0.9f, 0.1f, 0.4f,
          /*4*/  0.3f, 0.3f, -0.6f,     1.0f, 0.5f, 0.0f,
          /*5*/  0.3f, -0.3f, -0.6f,    0.0f, 0.5f, 1.0f,
          /*6*/  -0.3f, 0.3f, -0.6f,    0.5f, 1.0f, 0.1f,
          /*7*/  -0.3f, -0.3f, -0.6f,   0.9f, 0.1f, 0.4f
        };

        GLuint indices[] =
        {
            0,1,2,
            0,1,3,
            7,6,5,
            6,4,5,
            1,3,6,
            1,4,6,
            1,2,4,
            2,4,5,
            2,5,7,
            0,2,7,
            0,7,3,
            3,7,6
        };

        glm::vec3 cubePositions[] =
        {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(3.0f, 4.0f, -6.0f),
            glm::vec3(7.0f, 5.0f, 0.0f)
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

   //Fullscreen
   // GLFWwindow*mainWindow = glfwCreateWindow(640, 480,"Dangerous Dwarves Engine", glfwGetPrimaryMonitor(), nullptr);
    GLFWwindow*mainWindow = glfwCreateWindow(width, height, "Dangerous Dwarves Engine", nullptr, nullptr);
    glfwMakeContextCurrent(mainWindow);

    GLFWwindow*windowtwo = glfwCreateWindow(300, 700, "test", nullptr, nullptr);

    glfwSetWindowPos(mainWindow, 0, 25);
    glfwSetWindowPos(windowtwo, 980, 25);

    //GLFW callbacks
    glfwSetKeyCallback(mainWindow, key_callback);
    glfwSetCursorPosCallback(mainWindow, mouseCallback);
    //Set the cursor type
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //Output an error if the window was unable to be created
    if(mainWindow == NULL)
    {
        std::cout << "Window Invalid" << std::endl;
        glfwTerminate();
        return -1;}

    //Set up GLEW
    glewExperimental = GL_TRUE;

    //Output an error if GLEW could not start
    if(glewInit()!=GLEW_OK)
    {
        std::cout <<"GLEW did not start correctly" << std::endl;
        return -1;}

    //Define the size of the window
    int width;
    int height;
    glfwGetFramebufferSize(mainWindow, &width, &height);
    glViewport(0,0, width, height);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Create the vertex shader
    GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //Check for vertex shader compilation errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout <<"Vertex Shader Could not be compiled" << infoLog << std::cout;
    }

    //Create the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //Check for fragment shader errors
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

    //Check for shader program errors
    glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);
       if(!success)
    {
        glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout <<"Shader program Could not be compiled" << infoLog << std::cout;
    }

    //Clean up shaders when you are done with them
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Create a Vertex Buffer Object (VBO), Vertex Array Object (VAO) and an Element Buffer Object (EBO) to manage memory
    GLuint VBO;
    glGenBuffers(1, &VBO);
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    GLuint EBO;
    glGenBuffers(1, &EBO);

    //Creates a buffer and binds the vertex  data so it can be sent to the GPU
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Vertex Attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);


    //Main loop
    //This while loop checks at each iteration if "glfwWindowShouldClose has been given a return value that instructs the window to close
    while(!glfwWindowShouldClose(mainWindow))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //Checks if things like keyboard and mouse input have been detected
        glfwPollEvents();
        movement();

        //Enables depth test, to check which objects are behind others
        glEnable(GL_DEPTH_TEST);

        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        //Use the shaders
        glUseProgram(shaderProgram);

        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
        view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
        projection = glm::perspective(50.0f, (float)width/(float)height, 0.1f, 100.0f);
        model = glm::rotate(model, (GLfloat)glfwGetTime()*1.2f, glm::vec3(0.7f, 7.20f, -4.0f));

        GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(mainWindow);
    }

   //clean up GLEW and give a return value
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);
   glfwTerminate();
    return 0;
}

 //Mouse movement
 void mouseCallback(GLFWwindow*mainWindow, double xpos, double ypos)
 {
     if(firstMouse)
     {
         lastY = ypos;
         lastX = xpos;
         firstMouse = false;
     }

     GLfloat xoffset = xpos - lastX;
     GLfloat yoffset = lastY - ypos;
     lastX = xpos;
     lastY = ypos;
     GLfloat sensitivity = 0.065f;
     xoffset *= sensitivity;
     yoffset *= sensitivity;

     yaw += xoffset;
     pitch += yoffset;

    if(pitch > 89.0f)
       pitch = 89.0f;
    if(pitch < -89.0f)
       pitch = -89.0f;


     glm::vec3 front;
     front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
     front.y = sin(glm::radians(pitch));
     front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
     cameraFront = glm::normalize(front);

     std::cout <<"x: "<< xpos << " y: " << ypos << std::endl;
 }

   //Key presses
   void key_callback(GLFWwindow*mainWindow, int key, int scanCode, int action, int mode)
    {
            if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                glfwSetWindowShouldClose(mainWindow, GL_TRUE);

                if(action == GLFW_PRESS)
     keys[key] = true;
     else if(action == GLFW_RELEASE)
        keys[key] = false;

        }
   //Movement
   void movement()
    {
       GLfloat cameraSpeed = 5.0f * deltaTime;
                if(keys[GLFW_KEY_W])
                  cameraPosition += cameraSpeed * cameraFront;
                if(keys[GLFW_KEY_UP])
                  cameraPosition += cameraSpeed * cameraFront;
                if(keys[GLFW_KEY_D])
                  cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
                if(keys[GLFW_KEY_RIGHT])
                  cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
                if(keys[GLFW_KEY_S])
                  cameraPosition -= cameraSpeed * cameraFront;
                if(keys[GLFW_KEY_DOWN])
                  cameraPosition -= cameraSpeed * cameraFront;
                if(keys[GLFW_KEY_A])
                  cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
                if(keys[GLFW_KEY_LEFT])
                  cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

        }




