#include <iostream>
#include <fstream>
#include <string>
#include "vector.cpp"
#include "triangle.cpp"
#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl3.h>
#else
    #include <GL/gl3.h>
#endif

#include <GLFW/glfw3.h>

char* read_file(const char* file_name){
    std::ifstream shader;
    shader.open(file_name);
    

    std::string output = "";
    if(shader.is_open()){
        char cchar = '\r';
        do{
            if(cchar != '\r')
                output += cchar;
            cchar = shader.get();
        }while(shader);
    }else{
        std::cout << "File \""<< file_name << "\" not found." << std::endl;
        return (char*) "";
    }

    shader.close();
    char* rtrn = new char[output.length()+1];
    std::strcpy(rtrn, output.c_str());
    return rtrn;
}


int main(){
    GLFWwindow *wind;

    if(!glfwInit())
        return -1;
    
      // Define version and compatibility settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //ver
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); 
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for MAC ONLY
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 

    wind = glfwCreateWindow(640, 480, "a.out", NULL, NULL);


    if(!wind){
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(wind);

    
    float verticies[] =  {
         0.5f,  0.5f, 0.0f, // top right
         0.5f, -0.5f, 0.0f, // bottom right
        -0.5f,  0.5f, 0.0f, // top left
        
        -0.7f, -0.5f, 0.0f, // bottom left
        -0.7f,  0.5f, 0.0f, // top left
         0.3f, -0.5f, 0.0f, // bottom right
    };
    unsigned int indicies[] = {
        0, 1, 2,
        3, 4, 5
    };


    const char* vsource = read_file("shaders/vertex.GLSL");
    const char* fsource = read_file("shaders/fragment.GLSL");

    unsigned int ebo;    
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int v_id;
    glGenBuffers(1, &v_id);

    glBindBuffer(GL_ARRAY_BUFFER, v_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    // vertex shader
    unsigned int vshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshader, 1, &vsource, NULL);
    glCompileShader(vshader);

    // fragment shader
    unsigned int fshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshader, 1, &fsource, NULL);
    glCompileShader(fshader);
    
    unsigned int shaderPro = glCreateProgram();
    glAttachShader(shaderPro, vshader);
    glAttachShader(shaderPro, fshader);
    glLinkProgram(shaderPro);

    int success; 

    glGetProgramiv(shaderPro, GL_LINK_STATUS, &success);
    if(!success) {
        char infoLog[1024];
        glGetProgramInfoLog(shaderPro, 1024, NULL, infoLog);
        std::cout << "Shader comp "<< infoLog;
    }

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    while(!glfwWindowShouldClose(wind)){



        glUseProgram(shaderPro);


        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 6);




                
        glfwSwapBuffers(wind);
        

        glfwPollEvents();
    }
    glDeleteShader(vshader);
    glDeleteShader(fshader);

    return 0;
}