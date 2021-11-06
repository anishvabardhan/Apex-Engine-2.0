#pragma once

#include "Engine/Window/Window.h"
#include "Engine/Core/CoreIncludes.h"
#include "Buffers/FrameBuffer.h"
#include "Font.h"
#include "Texture.h"
#include "Shader.h"

struct Mesh;

enum APEX_BLEND_FACTOR {
	APEX_ZERO                      =      GL_ZERO,
	APEX_ONE                       =      GL_ONE,
	APEX_SRC_COLOR                 =      GL_SRC_COLOR,
	APEX_ONE_MINUS_SRC_COLOR       =      GL_ONE_MINUS_SRC_COLOR,
	APEX_DST_COLOR                 =      GL_DST_COLOR,
	APEX_ONE_MINUS_DST_COLOR       =      GL_ONE_MINUS_DST_COLOR,
	APEX_SRC_ALPHA                 =      GL_SRC_ALPHA,
	APEX_ONE_MINUS_SRC_ALPHA       =      GL_ONE_MINUS_SRC_ALPHA,
	APEX_DST_ALPHA                 =      GL_DST_ALPHA,
	APEX_ONE_MINUS_DST_ALPHA       =      GL_ONE_MINUS_DST_ALPHA,
	APEX_CONSTANT_COLOR            =      GL_CONSTANT_COLOR,
	APEX_ONE_MINUS_CONSTANT_COLOR  =      GL_ONE_MINUS_CONSTANT_COLOR,
	APEX_CONSTANT_ALPHA            =      GL_CONSTANT_ALPHA,
	APEX_ONE_MINUS_CONSTANT_ALPHA  =      GL_ONE_MINUS_CONSTANT_ALPHA,
};

static std::map<std::string, APEX_BLEND_FACTOR> ParseBlendFac{
	{"zero",                              APEX_ZERO                     },
	{"one",                               APEX_ONE                      },
	{"src_color",                         APEX_SRC_COLOR                },
	{"one_minus_src_color",               APEX_ONE_MINUS_SRC_COLOR      },
	{"dst_color",                         APEX_DST_COLOR                },
	{"one_minus_dst_color",               APEX_ONE_MINUS_DST_COLOR      },
	{"src_alpha",                         APEX_SRC_ALPHA                },
	{"one_minus_src_alpha",               APEX_ONE_MINUS_SRC_ALPHA      },
	{"dst_alpha",                         APEX_DST_ALPHA                },
	{"one_minus_dst_alpha",               APEX_ONE_MINUS_DST_ALPHA      },
	{"constant_color",                    APEX_CONSTANT_COLOR           },
	{"one_minus_constant_color",          APEX_ONE_MINUS_CONSTANT_COLOR },
	{"constant_alpha",                    APEX_CONSTANT_ALPHA           },
	{"one_minus_constant_alpha",          APEX_ONE_MINUS_CONSTANT_ALPHA }
};

enum APEX_BLEND_OP {
	APEX_FUNC_ADD                  =      GL_FUNC_ADD,
	APEX_FUNC_SUBTRACT             =      GL_FUNC_SUBTRACT,
	APEX_FUNC_REVERSE_SUBTRACT     =      GL_FUNC_REVERSE_SUBTRACT,
	APEX_MIN                       =      GL_MIN,
	APEX_MAX                       =      GL_MAX
};

static std::map<std::string, APEX_BLEND_OP> ParseBlendOp{
	{"add", APEX_FUNC_ADD},
	{"subtract", APEX_FUNC_SUBTRACT},
	{"reverse_subtract", APEX_FUNC_REVERSE_SUBTRACT},
	{"min", APEX_MIN},
	{"max", APEX_MAX}
};

extern void* g_GLLibrary;
extern void* m_OurWindowHandleToDeviceContext;
extern void* m_OurWindowHandleToRenderContext;

class Renderer
{
	std::map<std::string, Texture*> m_LoadedTextures;
	std::map<ShaderDefinition*, Shader*> m_LoadedShaders;
	std::map<std::string, Font*> m_LoadedFonts;
public:
	Renderer();
    ~Renderer();

	void StartUp();
	void InitRender();
	void ShutDown();

	void SwappingBuffers();

	bool MakeContextCurrent(void* hdc, void* hglrc);
	void* CreateOldRenderContext(void* hdc);
	void* CreateRealRenderContext(void* hdc, int major, int minor);

	void Drawtext(const Vec2& position, const Vec4& color, const std::string& asciiText, float quadHeight, Font* font, Shader shader);
	void DrawQuad(const Vec2& position, const Vec2& dimensions, const Texture& texture, const AABB2& texCoords, const Vec4& color, Shader shader);
	void DrawQuad(const Vec2& position, Vec2 meshDim, Vec4 color, const std::string& path, Shader shader);
	void DrawFrameBuffer(const Vec2& position, Vec2 meshDim);
	void DrawMesh(Mesh* mesh);
	void CopyFrameBuffer(FrameBuffer* current, FrameBuffer* next);
	void Clear() const;
	void ClearColor() const;

	Font* GetOrCreateFont(const std::string& path);
	Texture* GetOrCreateTexture(const std::string& path);
	Shader* GetOrCreateShader(ShaderDefinition* shaderDef);

	static void CreateInstance();
	static Renderer* GetInstance();
	static void DestroyInstance();

	static void EnableBlend(enum APEX_BLEND_FACTOR src, enum APEX_BLEND_FACTOR dest, enum APEX_BLEND_OP mode = APEX_BLEND_OP::APEX_FUNC_ADD);
	static void DisableBlend();
};