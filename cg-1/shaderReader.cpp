//
//  shaderReader.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/20.
//

#include "shaderReader.hpp"

char *readFromFile(const char *fileName) {
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) return NULL;
    
    fseek(fp, 0L, SEEK_END);
    size_t size = ftell(fp);
    char *buf = new char[size + 1];
    
    fseek(fp, 0L, SEEK_SET);
    fread(buf, 1, size, fp);
    fclose(fp);
    
    buf[size] = '\0';
    return buf;
}

void loadVertexShader(const char *baseUrl, const char *fileName, GLuint program) {
    char path[255];
    snprintf(path, 255, "%s/%s", baseUrl, fileName);
    GLchar *src = readFromFile(path);

    GLuint shader = glCreateShader(GL_VERTEX_SHADER);
    GLint length = (GLint) strlen(src);
    
    glShaderSource(shader, 1, &src, &length);
    delete[] src;
    
    glCompileShader(shader);
    
    char log[1000];
    int logLength;
    glGetShaderInfoLog(shader, 1000, &logLength, log);
    if (logLength) {
        log[logLength] = '\0';
        printf("vertex shader compilation error:\n%s\n", log);
    }

    glAttachShader(program, shader);
}

void loadFragmentShader(const char *baseUrl, const char *fileName, GLuint program) {
    char path[255];
    snprintf(path, 255, "%s/%s", baseUrl, fileName);
    GLchar *src = readFromFile(path);

    GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
    GLint length = (GLint) strlen(src);
    
    glShaderSource(shader, 1, &src, &length);
    delete[] src;
    
    glCompileShader(shader);
    
    char log[1000];
    int logLength;
    glGetShaderInfoLog(shader, 1000, &logLength, log);
    if (logLength) {
        log[logLength] = '\0';
        printf("fragment shader compilation error:\n%s\n", log);
    }

    glAttachShader(program, shader);
}
