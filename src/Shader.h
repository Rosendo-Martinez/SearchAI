#ifndef SHADER
#define SHADER

class Shader
{
public:
    Shader();
    
    void compile(const char* vsPath, const char* fsPath);
    void use();
    void setVector(const char* name, float x, float y, float z);

private:
    unsigned int ID;
};

#endif