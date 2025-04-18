#include "Shader.hpp"

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1 , &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    ID = glCreateProgram();
    glAttachShader(ID,vertex);
    glAttachShader(ID,fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);

   
    
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}


void Shader::setVec3(const std::string& name, glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}


void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x,y,z);
}

void Shader::setVec4(const std::string& name, glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}


void Shader::setPointLightAttribute(const std::string name, glm::vec3& position, float constant, float linear, float quadratic, glm::vec3& ambient, glm::vec3& diffuse, glm::vec3& specular)
{
    //����λ��
    
    setVec3(name+lightPostion, position);
    setVec3(name + lightAmbient, ambient);
    setVec3(name + lightDiffuse, diffuse);
    setVec3(name + lightSpecular, specular);
    setFloat(name + lightCanstant, constant);
    setFloat(name + lightLinear, linear);
    setFloat(name + lightQuadratic, quadratic);
}

void Shader::setDirLightAttribute(const std::string name, glm::vec3& direction, glm::vec3& ambient, glm::vec3& diffuse, glm::vec3& specular)
{
    setVec3(name + lightDirection, direction);
    setVec3(name + lightAmbient, ambient);
    setVec3(name + lightDiffuse, diffuse);
    setVec3(name + lightSpecular, specular);
}

void Shader::setSpotLightAttribute(const std::string name, glm::vec3& direction, glm::vec3& position,
    float cutOff, float outerCutOff, float constant, float linear, float quadratic,
    glm::vec3& ambient, glm::vec3& diffuse, glm::vec3& specular)
{
    setVec3(name + lightDirection, direction);
    setVec3(name + lightPostion, position);
    setVec3(name + lightAmbient, ambient);
    setVec3(name + lightDiffuse, diffuse);
    setVec3(name + lightSpecular, specular);
    setFloat(name + lightCutOff, cutOff);
    setFloat(name + lightOuterCutOff, outerCutOff);
    setFloat(name + lightCanstant, constant);
    setFloat(name + lightLinear, linear);
    setFloat(name + lightQuadratic, quadratic);
}

void Shader::setMVPAttribute( glm::mat4& model, glm::mat4& view, glm::mat4& projection)
{
    setMat4(ModelAttribute, model);
    setMat4(ViewAttribute, view);
    setMat4( ProjectionAttribute, projection);

}


