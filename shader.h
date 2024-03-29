#ifndef SHADER_H
#define SHADER_H

// include glad to get all the required OpenGL headers
#include <glad/glad.h>
#include "glm/glm.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
public:
  // the program ID
  unsigned int ID;

  // constructor reads and builds the shader
  Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
  // use/activate the shader
  void use();
  // utility uniform functions
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  unsigned int getID() const;
  void setMatrix(const std::string &name, int n, bool isTransposed,
                 float* value) const;
//  void setMat4(const std::string &name, const glm::mat4 &mat) const;
};
#endif
