#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
    public:
    unsigned int ID;
    const std::string lightPostion= ".position";
    const std::string lightDirection= ".direction";
    const std::string lightAmbient= ".ambient";
    const std::string lightDiffuse= ".diffuse";
    const std::string lightSpecular= ".specular";
    const std::string lightCanstant= ".constant";
    const std::string lightLinear= ".linear";
    const std::string lightQuadratic= ".quadratic";
    const std::string lightCutOff = ".cutOff";
    const std::string lightOuterCutOff = ".outerCutOff";

    const std::string ModelAttribute = "model";
    const std::string ViewAttribute = "view";
    const std::string ProjectionAttribute = "projection";
  

    Shader(const char* vertexPath, const char* fragmentPath);

    void use();
    void setBool(const std::string &name, bool value ) const;
    void setInt(const std::string &name, int value ) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void setVec3(const std::string& name, glm::vec3 &value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec4(const std::string& name, glm::vec4 &value) const;
    void setVec4(const std::string& name, float x, float y, float z, float w) const;

    void setPointLightAttribute(const std::string name,glm::vec3& position, float constant, float linear, float quadratic, glm::vec3& ambient, glm::vec3& diffuse, glm::vec3& specular);
    void setDirLightAttribute(const std::string name, glm::vec3& direction, glm::vec3& ambient, glm::vec3& diffuse, glm::vec3& specular);
  /*  struct SpotLight {
        vec3 direction;
        vec3 position;
        float cutOff;
        float outerCutOff;
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
        float constant;
        float linear;
        float quadratic;
    };*/
    void setSpotLightAttribute( const std::string name, glm::vec3& direction, glm::vec3& position,
                                float cutOff, float outerCutOff, float constant, float linear, float quadratic,
                                glm::vec3& ambient, glm::vec3& diffuse, glm::vec3& specular);

    void setMVPAttribute(glm::mat4& model, glm::mat4& view, glm::mat4& projection);

    



};

#endif