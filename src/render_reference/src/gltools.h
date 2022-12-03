#ifndef GL_TOOLS_H_
#define GL_TOOLS_H_

#define GL3_PROTOTYPES
#include "gl3.h"
#include <GL/glx.h>

#ifndef NDEBUG
#define GL_CHECK_ERROR() glCheckError(__FILE__, __LINE__, __FUNCTION__)
#else
#define GL_CHECK_ERROR()
#endif

#ifndef INCLUDED_FROM_GLTOOLS
extern Display *display;
extern GLXContext ctx;
extern Window win;
extern Colormap cmap;
#endif

void glCheckError(const char* file, int line, const char* func);

void initGL();

void exitGL();

GLuint createShaderProgram(const char* vsFilename, const char* tcFilename,
		const char* teFilename, const char* gsFilename, const char* fsFilename);

__int64_t continuousTimeNs();

#endif /* GL_TOOLS_H_ */
