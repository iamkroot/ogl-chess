#include "GLUtils.h"

void GLAPIENTRY
glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message,
              const void* userParam) {
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " << message << std::endl;
#define casePrint(val) case val: {std::cout << #val; break;}
    std::cout << "Source: ";
    switch (source) {
        casePrint(GL_DEBUG_SOURCE_API)
        casePrint(GL_DEBUG_SOURCE_WINDOW_SYSTEM)
        casePrint(GL_DEBUG_SOURCE_SHADER_COMPILER)
        casePrint(GL_DEBUG_SOURCE_THIRD_PARTY)
        casePrint(GL_DEBUG_SOURCE_APPLICATION)
        casePrint(GL_DEBUG_SOURCE_OTHER)
    }
    std::cout << std::endl << "Type: ";
    switch (type) {
        casePrint(GL_DEBUG_TYPE_ERROR)
        casePrint(GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR)
        casePrint(GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR)
        casePrint(GL_DEBUG_TYPE_PORTABILITY)
        casePrint(GL_DEBUG_TYPE_PERFORMANCE)
        casePrint(GL_DEBUG_TYPE_MARKER)
        casePrint(GL_DEBUG_TYPE_PUSH_GROUP)
        casePrint(GL_DEBUG_TYPE_POP_GROUP)
        casePrint(GL_DEBUG_TYPE_OTHER)
    }
    std::cout << std::endl << "Severity: ";

    switch (severity) {
        casePrint(GL_DEBUG_SEVERITY_HIGH)
        casePrint(GL_DEBUG_SEVERITY_MEDIUM)
        casePrint(GL_DEBUG_SEVERITY_LOW)
        casePrint(GL_DEBUG_SEVERITY_NOTIFICATION)
    }
    std::cout << std::endl;
#undef casePrint
}

void handleKeys(unsigned char key, int x, int y) {

}
