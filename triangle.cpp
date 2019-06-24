#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const char * const verteShaderSource[]{
    "#version 330 core \n"
    "layout ( location=0 ) in vec3 aPos; \n"
    "layout ( location=1 ) in vec3 aCol; \n"
    "out vec4 ourColor;\n"
    "void main() \n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourColor = vec4(aCol, 1.0);\n"
    "}\n"
};

const char * const fragmentShaderSource[]{
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec4 ourColor;\n"

    "void main()\n"
    "{\n"
    "   FragColor= ourColor;\n"
    "}\n"
};

int main(){

  //Initialize the parameters
  // ------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  //Create window 
  // ------------
  GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // create vertex shader
  //---------------------
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);

  // create and compile shaders
  //---------------------
  glShaderSource(vertexShader, 1, verteShaderSource, NULL);
  glCompileShader(vertexShader);

  int  success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success)
  {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if(!success){
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      std::cout << "ERRORR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  // create shader program
  //---------------
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();

  // attach shader and link the program
  //-----------------------------------
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if(!success){
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      std::cout << "ERRORR::SHADER::PROGRAM::LINKING::FAILED\n" << infoLog << std::endl;
  }

  // delete shaders, not needed after program is linked
  //---------------------------------------------------
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // set up vertex data (and buffer(s)) and configure vertex attributes
  //-------------------------------------------------------------------
  float vertices[] = {
    // position         // colors
    -0.5f, -0.5f, 0.0f, 0.5f, 0.0f, 0.0f, // bottom right
    0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f,  // bottom left
    0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.5f         // top
  };

  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  // Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);

  // set vertex attribute values
  //----------------------------
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (float), (void*)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (float), (void*)(3*sizeof(float)));

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  // unbind -note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
  glBindBuffer(GL_ARRAY_BUFFER,0);
  // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
  // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
  glBindVertexArray(0);

  // uncomment this call to draw in wireframe polygons.
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while(!glfwWindowShouldClose(window))
  {
    // input
    //--------
    processInput(window);

    // render
    //-------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw our first triangle
    glUseProgram(shaderProgram);

//    // update the uniform color
//    float timeValue = glfwGetTime();
//    float greenValue = sin(timeValue) / 2.0f + 0.5f;
//    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
//    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    // now render the triangle
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glBindVertexArray(0); // no need to unbind it every time

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}
