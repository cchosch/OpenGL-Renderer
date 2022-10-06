#include <iostream>
#include <fstream>
#include <string>
#include "vector.cpp"
#include "triangle.cpp"
#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

#include <GLFW/glfw3.h>

char* read_file(const char* file_name){
    std::ifstream shader;
    shader.open(file_name);
    

    std::string output = "";
    if(shader.is_open()){
        char cchar = '\0';
        do{
            if(cchar != '\0')
                output += cchar;
            cchar = shader.get();
        }while(shader);
        
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
    
    
    wind = glfwCreateWindow(640, 480, "a.out", NULL, NULL);


    if(!wind){
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(wind);

    
    Triangle *t = new Triangle((float[]) {
        -0.5f, -0.5f, 
         0.5f, -0.5f, 
         0.0f,  0.5f 
    });


    const char* vertSource = read_file("vertex.GLSL");
    while(!glfwWindowShouldClose(wind)){
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);

        unsigned int v_id;

        glGenBuffers(1, &v_id);

        glBindBuffer(GL_ARRAY_BUFFER, v_id);

        glBufferData(GL_ARRAY_BUFFER, sizeof(t->verticies), t->verticies, GL_STATIC_DRAW);

        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
                

        glEnd();
        glfwSwapBuffers(wind);
        

        glfwPollEvents();
    }

    return 0;
}