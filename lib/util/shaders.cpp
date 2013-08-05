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

    GLuint shader_id = glCreateProgram();
    glAttachShader(shader_id, shader_vp);
    glAttachShader(shader_id, shader_fp);

    glLinkProgram(shader_id);

    return shader_id;
}
