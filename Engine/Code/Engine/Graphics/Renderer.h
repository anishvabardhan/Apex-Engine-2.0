#pragma once

#include "Texture.h"
#include "Engine/Core/Color.h"
#include "Engine/Window/Window.h"
#include "Engine/Core/CoreIncludes.h"
#include "Engine/Graphics/GLFunctions.h"

class Shader;
class ShaderDefinition;
class Texture;
class Font;
class FrameBuffer;
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
	APEX_ONE_MINUS_CONSTANT_ALPHA  =      GL_ONE_MINUS_CONSTANT_ALPHA
};

static std::map<String, APEX_BLEND_FACTOR> ParseBlendFac{
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

static std::map<String, APEX_BLEND_OP> ParseBlendOp{
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
	std::map<String, Texture*> m_LoadedTextures;
	std::map<ShaderDefinition*, Shader*> m_LoadedShaders;
	std::map<XMLElement*, ShaderDefinition*> m_LoadedShaderDefinitions;
	std::map<String, Font*> m_LoadedFonts;
	Texture* m_DefaultTexture = nullptr;
	Shader* m_DefaultShader = nullptr;
	ShaderDefinition* m_DefaultShaderDef = nullptr;
public:
	Renderer();
    ~Renderer();

	void StartUp();
	void ShutDown();

	void SwappingBuffers();

	bool MakeContextCurrent(void* hdc, void* hglrc);
	void* CreateOldRenderContext(void* hdc);
	void* CreateRealRenderContext(void* hdc, int major, int minor);

	void BindDefaultShader();
	void BindFont(const Font* font, int textureSlot);
	void BindTexture(const Texture* texture = nullptr, int textureSlot = 0);

	void UnBindDefaultShader();

	// MVP UNIFORMS UPDATION METHODS
	void SetCameraUniform(const Mat4& camera);
	void SetModelTranslation(const Mat4& transform = Mat4::Identity());

	void CopyFrameBuffer(FrameBuffer* current, FrameBuffer* next);
	void Clear() const;
	void ClearColor(const Vec4& color = Color::CLEAR_COLOR) const;

	Font* GetOrCreateFont(const String& path);
	Texture* GetOrCreateTexture(const String& path);
	Shader* GetOrCreateShader(ShaderDefinition* shaderDef);
	Shader* GetDefaultShader() const;
	ShaderDefinition* GetOrCreateShaderDef(XMLElement* element);

	static void EnableBlend(enum APEX_BLEND_FACTOR src, enum APEX_BLEND_FACTOR dest, enum APEX_BLEND_OP mode = APEX_BLEND_OP::APEX_FUNC_ADD);
	static void DisableBlend();

	// DRAW CALL METHODS
	void Drawtext(const Vec2& position, const Vec4& color, const String& asciiText, float quadHeight, Font* font);
	void DrawAABB2(const AABB2& aabb2, const Vec4& color);
	void DrawHollowAABB2(const AABB2& aabb2, const float& thickness, const Vec4& color);
	void DrawLine(Vec2& start, Vec2& end, const float& thickness, const Vec4& color);
	void DrawArrow(Vec2& start, Vec2& end, const float& thickness, const Vec4& color);
	void DrawDisc(const Vec2& center, const float& radius, const Vec4& color);

	void DrawRing(const Vec2& center, const float& radius, const Vec4& color);
	void DrawMesh(Mesh* mesh);
private:
	void CreateTexture(const String& texturePath);
	Texture* CreateTextureFromColor(const Vec4& color);
};