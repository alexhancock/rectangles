#include "shaders.hpp"
#include "util.hpp"

GLuint Shaders::compile (const char *vert, const char *frag) {
    GLuint shader_vp = glCreateShader(GL_VERTEX_SHADER);
    GLuint shader_fp = glCreateShader(GL_FRAGMENT_SHADER);

    string vText = Util::getStringFromPath(vert);
    string fText = Util::getStringFromPath(frag);

    const char* vsText = vText.c_str();
    const char* fsText = fText.c_str();

    if (vsText == NULL || fsText == NULL) {
        std::cerr << "Either vertex shader or fragment shader file not found." << std::endl;
        return 0;
    }

    GLint vertLength[1];
    GLint fragLength[1];

    vertLength[0] = strlen(vsText);
    fragLength[0] = strlen(fsText);

    glShaderSource(shader_vp, 1, &vsText, 0);
    glShaderSource(shader_fp, 1, &fsText, 0);

    glCompileShader(shader_vp);
    glCompileShader(shader_fp);

    int infologLength = 0;
    int charsWritten  = 0;

    glGetShaderiv(shader_vp, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 0)
    {
        GLchar* infoLog = (GLchar *)malloc(infologLength);
        if (infoLog == NULL)
        {
            printf( "ERROR: Could not allocate InfoLog buffer");
            exit(1);
        }
        glGetShaderInfoLog(shader_vp, infologLength, &charsWritten, infoLog);
        printf( "Shader InfoLog:\n%s", infoLog );
        free(infoLog);
    }

    int vinfologLength = 0;
    int vcharsWritten  = 0;

    glGetShaderiv(shader_fp, GL_INFO_LOG_LENGTH, &vinfologLength);

    if (infologLength > 0)
    {
        GLchar* infoLog = (GLchar *)malloc(vinfologLength);
        if (infoLog == NULL)
        {
            printf( "ERROR: Could not allocate InfoLog buffer");
            exit(1);
        }
        glGetShaderInfoLog(shader_fp, vinfologLength, &vcharsWritten, infoLog);
        printf( "Shader InfoLog:\n%s", infoLog );
        free(infoLog);
    }

    GLuint shader_id = glCreateProgram();
    glAttachShader(shader_id, shader_vp);
    glAttachShader(shader_id, shader_fp);

    glLinkProgram(shader_id);

    return shader_id;
}


