#ifndef SHADER
#define SHADER

class Shader
{
public:
    Shader();
    
    void compile(const char* vsPath, const char* fsPath);
    void use();

private:
    unsigned int ID;
};

#endif