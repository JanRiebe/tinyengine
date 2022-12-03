#define INCLUDED_FROM_GLTOOLS
#include "gltools.h"
#include <GL/glu.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

void glCheckError(const char* file, int line, const char* func)
{
	GLenum error;
	const GLubyte* errStr;
	if ((error = glGetError()) != GL_NO_ERROR)
	{
		errStr = gluErrorString(error);
		cout << "OpenGL ERROR in file " << file << ", line " << line << ": "
				<< errStr << " (in function " << func << ")" << endl;
		exit(1);
	}
}

#define GLX_CONTEXT_MAJOR_VERSION_ARB       0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB       0x2092
typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig,
		GLXContext, Bool, const int*);

Display *display;
GLXContext ctx;
Window win;
Colormap cmap;

// Helper to check for extension string presence.  Adapted from:
//   http://www.opengl.org/resources/features/OGLextensions/
static bool isExtensionSupported(const char *extList, const char *extension)
{
	const char *start;
	const char *where, *terminator;

	/* Extension names should not have spaces. */
	where = strchr(extension, ' ');
	if (where || *extension == '\0')
		return false;

	/* It takes a bit of care to be fool-proof about parsing the
	 OpenGL extensions string. Don't be fooled by sub-strings,
	 etc. */
	for (start = extList;;)
	{
		where = strstr(start, extension);

		if (!where)
			break;

		terminator = where + strlen(extension);

		if (where == start || *(where - 1) == ' ')
			if (*terminator == ' ' || *terminator == '\0')
				return true;

		start = terminator;
	}

	return false;
}

static bool ctxErrorOccurred = false;
static int ctxErrorHandler(Display *dpy, XErrorEvent *ev)
{
	ctxErrorOccurred = true;
	return 0;
}

void initGL()
{
	display = XOpenDisplay(0);

	if (!display)
	{
		cout << "Failed to open X display\n" << endl;
		exit(1);
	}

	// Get a matching FB config
	static int visual_attribs[] =
	{ GLX_X_RENDERABLE, True, GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
			GLX_RENDER_TYPE, GLX_RGBA_BIT, GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
			GLX_RED_SIZE, 8, GLX_GREEN_SIZE, 8, GLX_BLUE_SIZE, 8,
			GLX_ALPHA_SIZE, 8, GLX_DEPTH_SIZE, 24, GLX_STENCIL_SIZE, 8,
			GLX_DOUBLEBUFFER, True, None };

	int glx_major, glx_minor;

	// FBConfigs were added in GLX version 1.3.
	if (!glXQueryVersion(display, &glx_major, &glx_minor)
			|| ((glx_major == 1) && (glx_minor < 3)) || (glx_major < 1))
	{
		cout << "Invalid GLX version" << endl;
		exit(1);
	}

	cout << "Getting matching framebuffer configs" << endl;
	int fbcount;
	GLXFBConfig *fbc = glXChooseFBConfig(display, DefaultScreen( display ),
			visual_attribs, &fbcount);
	if (!fbc)
	{
		cout << "Failed to retrieve a framebuffer config" << endl;
		exit(1);
	}
	cout << "Found " << fbcount << " matching FB configs." << endl;

	// Pick the FB config/visual with the most samples per pixel
	cout << "Getting XVisualInfos" << endl;
	int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;

	int i;
	for (i = 0; i < fbcount; i++)
	{
		XVisualInfo *vi = glXGetVisualFromFBConfig(display, fbc[i]);
		if (vi)
		{
			int samp_buf, samples;
			glXGetFBConfigAttrib(display, fbc[i], GLX_SAMPLE_BUFFERS,
					&samp_buf);
			glXGetFBConfigAttrib(display, fbc[i], GLX_SAMPLES, &samples);

			cout << "  Matching fbconfig " << i << ", visual ID "
					<< vi->visualid << ": SAMPLE_BUFFERS = " << samp_buf
					<< ", SAMPLES = " << samples << endl;

			if (best_fbc < 0 || (samp_buf && samples > best_num_samp))
				best_fbc = i, best_num_samp = samples;
			if (worst_fbc < 0 || !samp_buf || samples < worst_num_samp)
				worst_fbc = i, worst_num_samp = samples;
		}
		XFree(vi);
	}

	GLXFBConfig bestFbc = fbc[best_fbc];

	// Be sure to free the FBConfig list allocated by glXChooseFBConfig()
	XFree(fbc);

	// Get a visual
	XVisualInfo *vi = glXGetVisualFromFBConfig(display, bestFbc);
	cout << "Chosen visual ID = " << vi->visualid << endl;

	cout << "Creating colormap" << endl;
	XSetWindowAttributes swa;
	swa.colormap = cmap = XCreateColormap(display,
			RootWindow( display, vi->screen ) ,
			vi->visual, AllocNone );
	swa.background_pixmap = None;
	swa.border_pixel = 0;
	swa.event_mask = StructureNotifyMask | KeyPressMask | KeyReleaseMask
			| ButtonPressMask | ButtonReleaseMask | PointerMotionMask;

	cout << "Creating window" << endl;
	win = XCreateWindow(display, RootWindow( display, vi->screen ) ,
	0, 0, 512, 512, 0, vi->depth, InputOutput,
	vi->visual,
	CWBorderPixel|CWColormap|CWEventMask, &swa );
	if (!win)
	{
		cout << "Failed to create window." << endl;
		exit(1);
	}

	// Done with the visual info data
	XFree(vi);

	XStoreName(display, win, "GL 4.2 Window");

	XAutoRepeatOff(display);

	cout << "Mapping window" << endl;
	XMapWindow(display, win);

	// Get the default screen's GLX extension list
	const char *glxExts = glXQueryExtensionsString(display,
			DefaultScreen( display ) );

	// NOTE: It is not necessary to create or make current to a context before
	// calling glXGetProcAddressARB
	glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
	glXCreateContextAttribsARB =
			(glXCreateContextAttribsARBProc) glXGetProcAddressARB(
					(const GLubyte *) "glXCreateContextAttribsARB");

	ctx = 0;

	// Install an X error handler so the application won't exit if GL 4.2
	// context allocation fails.
	//
	// Note this error handler is global.  All display connections in all threads
	// of a process use the same error handler, so be sure to guard against other
	// threads issuing X commands while this code is running.
	ctxErrorOccurred = false;
	int (*oldHandler)(Display*, XErrorEvent*) =
	XSetErrorHandler(&ctxErrorHandler);

	// Check for the GLX_ARB_create_context extension string and the function.
	// If it does, try to get a GL 4.2 context!
	if (isExtensionSupported(glxExts, "GLX_ARB_create_context")
			&& glXCreateContextAttribsARB)
	{
		int context_attribs[] =
		{ GLX_CONTEXT_MAJOR_VERSION_ARB, 4, GLX_CONTEXT_MINOR_VERSION_ARB, 2,
				GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
				None };

		cout << "Creating context" << endl;
		ctx = glXCreateContextAttribsARB(display, bestFbc, 0, True,
				context_attribs);

		// Sync to ensure any errors generated are processed.
		XSync(display, False);
		if (!ctxErrorOccurred && ctx)
			cout << "Created GL 4.2 context" << endl;
	}

	// Sync to ensure any errors generated are processed.
	XSync(display, False);

	// Restore the original error handler
	XSetErrorHandler(oldHandler);

	if (ctxErrorOccurred || !ctx)
	{
		cout << "Failed to create an OpenGL context" << endl;
		exit(1);
	}

	// Verifying that context is a direct context
	if (!glXIsDirect(display, ctx))
	{
		cout << "Indirect GLX rendering context obtained" << endl;
	}
	else
	{
		cout << "Direct GLX rendering context obtained" << endl;
	}

	cout << "Making context current" << endl;
	glXMakeCurrent(display, win, ctx);
}

void exitGL()
{
	glXMakeCurrent(display, 0, 0);
	glXDestroyContext(display, ctx);

	XAutoRepeatOn(display);
	XDestroyWindow(display, win);
	XFreeColormap(display, cmap);
	XCloseDisplay(display);
}

GLuint createShaderProgram(const char* vsFilename, const char* tcFilename,
		const char* teFilename, const char* gsFilename, const char* fsFilename)
{
#ifndef NDEBUG
	const unsigned int MAX_BUFFER_SIZE = 1024;
	char* log = new char[MAX_BUFFER_SIZE];
	int logLength;
#endif

	GLuint sp = glCreateProgram();
	GL_CHECK_ERROR();

	GLuint vs, tc, te, gs, fs;

	// Create vertex shader
	vs = glCreateShader(GL_VERTEX_SHADER);
	GL_CHECK_ERROR();
	ifstream vsFile(vsFilename);
	string buffer((std::istreambuf_iterator<char>(vsFile)),
			std::istreambuf_iterator<char>());
#ifndef NDEBUG
	cout << buffer << endl;
#endif
	vsFile.close();
	const char* code = buffer.c_str();
	int bufferLength = buffer.length();
	glShaderSource(vs, 1, &code, &bufferLength);
	GL_CHECK_ERROR();
	glCompileShader(vs);
	GL_CHECK_ERROR();
#ifndef NDEBUG
	glGetShaderInfoLog(vs, MAX_BUFFER_SIZE - 1, &logLength, log);
	GL_CHECK_ERROR();
	cout << log << endl;
#endif
	glAttachShader(sp, vs);
	GL_CHECK_ERROR();
	glDeleteShader(vs);
	GL_CHECK_ERROR();

	// Create tessellation evaluation shader
	if (tcFilename)
	{
		tc = glCreateShader(GL_TESS_CONTROL_SHADER);
		GL_CHECK_ERROR();
		ifstream tcFile(tcFilename);
		string buffer((std::istreambuf_iterator<char>(tcFile)),
				std::istreambuf_iterator<char>());
#ifndef NDEBUG
		cout << buffer << endl;
#endif
		tcFile.close();
		const char* code = buffer.c_str();
		int bufferLength = buffer.length();
		glShaderSource(tc, 1, &code, &bufferLength);
		GL_CHECK_ERROR();
		glCompileShader(tc);
		GL_CHECK_ERROR();
#ifndef NDEBUG
		glGetShaderInfoLog(tc, MAX_BUFFER_SIZE - 1, &logLength, log);
		GL_CHECK_ERROR();
		cout << log << endl;
#endif
		glAttachShader(sp, tc);
		GL_CHECK_ERROR();
		glDeleteShader(tc);
		GL_CHECK_ERROR();
	}

	// Create tessellation control shader
	if (teFilename)
	{
		te = glCreateShader(GL_TESS_EVALUATION_SHADER);
		GL_CHECK_ERROR();
		ifstream teFile(teFilename);
		string buffer((std::istreambuf_iterator<char>(teFile)),
				std::istreambuf_iterator<char>());
#ifndef NDEBUG
		cout << buffer << endl;
#endif
		teFile.close();
		const char* code = buffer.c_str();
		int bufferLength = buffer.length();
		glShaderSource(te, 1, &code, &bufferLength);
		GL_CHECK_ERROR();
		glCompileShader(te);
		GL_CHECK_ERROR();
#ifndef NDEBUG
		glGetShaderInfoLog(te, MAX_BUFFER_SIZE - 1, &logLength, log);
		GL_CHECK_ERROR();
		cout << log << endl;
#endif
		glAttachShader(sp, te);
		GL_CHECK_ERROR();
		glDeleteShader(te);
		GL_CHECK_ERROR();
	}

	// Create tessellation control shader
	if (gsFilename)
	{
		gs = glCreateShader(GL_GEOMETRY_SHADER);
		GL_CHECK_ERROR();
		ifstream gsFile(gsFilename);
		string buffer((std::istreambuf_iterator<char>(gsFile)),
				std::istreambuf_iterator<char>());
#ifndef NDEBUG
		cout << buffer << endl;
#endif
		gsFile.close();
		const char* code = buffer.c_str();
		int bufferLength = buffer.length();
		glShaderSource(gs, 1, &code, &bufferLength);
		GL_CHECK_ERROR();
		glCompileShader(gs);
		GL_CHECK_ERROR();
#ifndef NDEBUG
		glGetShaderInfoLog(gs, MAX_BUFFER_SIZE - 1, &logLength, log);
		GL_CHECK_ERROR();
		cout << log << endl;
#endif
		glAttachShader(sp, gs);
		GL_CHECK_ERROR();
		glDeleteShader(gs);
		GL_CHECK_ERROR();
	}

	// Create fragment shader
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	GL_CHECK_ERROR();
	ifstream fsFile(fsFilename);
	buffer = string((std::istreambuf_iterator<char>(fsFile)),
			std::istreambuf_iterator<char>());
#ifndef NDEBUG
	cout << buffer << endl;
#endif
	fsFile.close();
	code = buffer.c_str();
	bufferLength = buffer.length();
	glShaderSource(fs, 1, &code, &bufferLength);
	GL_CHECK_ERROR();
	glCompileShader(fs);
	GL_CHECK_ERROR();
#ifndef NDEBUG
	glGetShaderInfoLog(fs, MAX_BUFFER_SIZE - 1, &logLength, log);
	GL_CHECK_ERROR();
	cout << log << endl;
#endif
	glAttachShader(sp, fs);
	GL_CHECK_ERROR();
	glDeleteShader(fs);
	GL_CHECK_ERROR();

	// Link program
	glLinkProgram(sp);
	GL_CHECK_ERROR();
#ifndef NDEBUG
	glGetProgramInfoLog(sp, MAX_BUFFER_SIZE, &logLength, log);
	GL_CHECK_ERROR();
	cout << log << endl;
	delete[] log;
#endif

	return sp;
}

__int64_t continuousTimeNs()
{
        timespec now;
        clock_gettime(CLOCK_REALTIME, &now);

        __int64_t result = (__int64_t ) now.tv_sec * 1000000000
                        + (__int64_t ) now.tv_nsec;

        return result;
}

