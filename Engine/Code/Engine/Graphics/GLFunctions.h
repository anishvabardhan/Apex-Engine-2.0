#pragma once
#include "External/GL/glcorearb.h"
#include "External/GL/wglext.h"
#include "External/GL/glext.h"
extern void* g_GLLibrary;

//-----------------------------------------------------------------------------------------------
// Template for binding GL functions 
// 
template <typename TYPE>
bool wglGetTypedProcAddress(TYPE* out, char const* name)
{
	// Grab the function from the currently bound render contect
	// most opengl 2.0+ features will be found here
	*out = (TYPE)wglGetProcAddress(name);

	if ((*out) == nullptr) {
		// if it is not part of wgl (the device), then attempt to get it from the GLL library
		// (most OpenGL functions come from here)
		*out = (TYPE)GetProcAddress((HMODULE)g_GLLibrary, name);
	}

	return (*out != nullptr);
}

//-----------------------------------------------------------------------------------------------
// Binding MACRO
#define GL_BIND_FUNCTION(f)     wglGetTypedProcAddress( &f, #f )
#define GL_CHECK_ERROR()		GLCheckError(__FILE__, __LINE__)

//-----------------------------------------------------------------------------------------------
// Functions
void BindGLFunctions();
void BindNewGLFunctions();

//-----------------------------------------------------------------------------------------------
// General GL functions
extern PFNGLCLEARPROC glClear;
extern PFNGLCLEARCOLORPROC glClearColor;
extern PFNGLORTHOFOESPROC glOrtho;
extern PFNGLENABLEPROC glEnable;
extern PFNGLDISABLEPROC glDisable;
extern PFNGLGETERRORPROC glGetError;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
extern PFNGLREADBUFFERPROC glReadBuffer;
extern PFNGLREADPIXELSPROC glReadPixels;
extern PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC glNamedFramebufferReadBuffer;
extern PFNGLVIEWPORTPROC glViewport;
extern PFNGLBLENDEQUATIONPROC glBlendEquation;

//-----------------------------------------------------------------------------------------------
// Draw functions
extern PFNGLLINEWIDTHPROC glLineWidth;
extern PFNGLDRAWARRAYSPROC glDrawArrays;
extern PFNGLBLENDFUNCPROC glBlendFunc;
extern PFNGLDEPTHFUNCPROC glDepthFunc;
extern PFNGLDEPTHMASKPROC glDepthMask;
extern PFNGLCLEARDEPTHFPROC glClearDepthf;
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLDRAWELEMENTSPROC glDrawElements;
extern PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
extern PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
extern PFNGLDRAWBUFFERSPROC glDrawBuffers;
extern PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
extern PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture;
extern PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer;
extern PFNGLPOLYGONMODEPROC glPolygonMode;

//-----------------------------------------------------------------------------------------------
// Texture functions
extern PFNGLPIXELSTOREIPROC glPixelStorei;
extern PFNGLGENTEXTURESPROC glGenTextures;
extern PFNGLBINDTEXTUREPROC glBindTexture;
extern PFNGLTEXPARAMETERIPROC glTexParameteri;
extern PFNGLTEXIMAGE2DPROC glTexImage2D;
extern PFNGLGENSAMPLERSPROC glGenSamplers;
extern PFNGLSAMPLERPARAMETERIPROC glSamplerParameteri;
extern PFNGLDELETESAMPLERSPROC glDeleteSamplers;
extern PFNGLBINDSAMPLERPROC glBindSampler;
extern PFNGLBINDSAMPLERSPROC glBindSamplers;
extern PFNGLACTIVETEXTUREPROC glActiveTexture;
extern PFNGLGETTEXIMAGEPROC glGetTexImage;
extern PFNGLTEXSTORAGE2DPROC glTexStorage2D;
extern PFNGLTEXSUBIMAGE2DPROC glTexSubImage2D;
extern PFNGLDELETETEXTURESPROC glDeleteTextures;
extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap;

//-----------------------------------------------------------------------------------------------
// Shader functions
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLDETACHSHADERPROC glDetachShader;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex;
extern PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBinding;
extern PFNGLBINDBUFFERBASEPROC glBindBufferBase;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
extern PFNGLUNIFORM1FPROC glUniform1f;
extern PFNGLUNIFORM1FVPROC glUniform1fv;
extern PFNGLUNIFORM1IVPROC glUniform1iv;
extern PFNGLUNIFORM4FVPROC glUniform4fv;
extern PFNGLUNIFORM3FVPROC glUniform3fv;
extern PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate;
extern PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate;
extern PFNGLFRONTFACEPROC glFrontFace;
extern PFNGLCULLFACEPROC glCullFace;
extern PFNGLVALIDATEPROGRAMPROC glValidateProgram;
extern PFNGLUNIFORM1IPROC glUniform1i;
extern PFNGLUNIFORM4FPROC glUniform4f;

//-----------------------------------------------------------------------------------------------
// WGL Functions
extern PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB;
extern PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
extern PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

//-----------------------------------------------------------------------------------------------
// Standalone functions
bool GLCheckError(const char* fileName, int line);
bool GLFailed();
bool GLSucceeded();