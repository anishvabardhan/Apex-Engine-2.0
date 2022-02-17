#include "Renderer.h"

#include "MeshBuilder.h"
#include "Vertex.h"
#include "Mesh.h"
#pragma comment(lib, "opengl32")
#include "Buffers/FrameBuffer.h"
#include "Font.h"
#include "Shader.h"
#include "ShaderDefinition.h"
#include "Engine/Core/Color.h"
#include "Engine/Core/EngineCommon.h"
#include "External/stb_image.h"

static Renderer* m_Renderer = nullptr;

void* g_GLLibrary = nullptr;
void* m_OurWindowHandleToDeviceContext = nullptr;
void* m_OurWindowHandleToRenderContext = nullptr;

extern Shader* g_Shader;

//---------------------------------------------------------------------------------------------------------
// Defining the Constructors/Destructors

Renderer::Renderer()
{
}

//------------------------------------------------------------------------------------------------------

Renderer::~Renderer()
{
}

//---------------------------------------------------------------------------------------------------------
// Initializing the Renderer

void Renderer::StartUp()
{
	g_GLLibrary = ::LoadLibraryA("opengl32.dll");
	m_OurWindowHandleToDeviceContext = GetDC(reinterpret_cast<HWND>(Window::GetInstance()->GetHandle()));

	HGLRC tempContext = reinterpret_cast<HGLRC>(CreateOldRenderContext(m_OurWindowHandleToDeviceContext));

	MakeContextCurrent(m_OurWindowHandleToDeviceContext, tempContext);
	BindNewGLFunctions();

	HGLRC realContext = reinterpret_cast<HGLRC>(CreateRealRenderContext(m_OurWindowHandleToDeviceContext, 4, 2));

	MakeContextCurrent(m_OurWindowHandleToDeviceContext, realContext);
	wglDeleteContext(tempContext);

	BindGLFunctions();

	m_OurWindowHandleToRenderContext = realContext;

	m_DefaultTexture = CreateTextureFromColor(Color::WHITE);
}

void Renderer::InitRender()
{

	//--------------------------------------------------------------------------------------------------
	//Setup OpenGL3 Viewport
	
	//glViewport(0, 0, 1024, 1024);

	//--------------------------------------------------------------------------------------------------
	//Clear Buffers to Preset Values

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
	//--------------------------------------------------------------------------------------------------
	//Specify Clear Values for the Color Buffers

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
}

void Renderer::ShutDown()
{
	wglMakeCurrent(reinterpret_cast<HDC>(m_OurWindowHandleToDeviceContext), NULL);
	wglDeleteContext(reinterpret_cast<HGLRC>(m_OurWindowHandleToRenderContext));
	if (!ReleaseDC(reinterpret_cast<HWND>(Window::GetInstance()->GetHandle()), reinterpret_cast<HDC>(m_OurWindowHandleToDeviceContext)))
		MessageBox(reinterpret_cast<HWND>(Window::GetInstance()->GetHandle()), L"Cannot Release !!", L"ERROR!!", MB_OK);

	m_OurWindowHandleToDeviceContext = nullptr;
	m_OurWindowHandleToRenderContext = nullptr;

	FreeLibrary((HMODULE)g_GLLibrary);
}

void Renderer::SwappingBuffers()
{
	SwapBuffers(reinterpret_cast<HDC>(m_OurWindowHandleToDeviceContext));
}

bool Renderer::MakeContextCurrent(void* hdc, void* hglrc)
{
	return wglMakeCurrent(reinterpret_cast<HDC>(hdc), reinterpret_cast<HGLRC>(hglrc));
}

void* Renderer::CreateOldRenderContext(void* hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int pixel_format = ::ChoosePixelFormat(reinterpret_cast<HDC>(hdc), &pfd);
	if (pixel_format == NULL)
		return NULL;

	if (!::SetPixelFormat(reinterpret_cast<HDC>(hdc), pixel_format, &pfd))
		return NULL;

	void* context = reinterpret_cast<void*>(::wglCreateContext(reinterpret_cast<HDC>(hdc)));
	if (context == NULL)
		return NULL;

	return context;
}

void* Renderer::CreateRealRenderContext(void* hdc, int major, int minor)
{
	const int format_attribs[] = {
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_COLOR_BITS_ARB, 32,
			WGL_DEPTH_BITS_ARB, 24,
			WGL_STENCIL_BITS_ARB, 8,
			NULL, NULL
	};

	size_t const MAX_PIXEL_FORMATS = 128;
	int formats[MAX_PIXEL_FORMATS];
	int pixel_format = 0;
	UINT format_count = 0;

	BOOL succeeded = wglChoosePixelFormatARB(reinterpret_cast<HDC>(hdc),
		format_attribs,
		nullptr,
		MAX_PIXEL_FORMATS,
		formats,
		&format_count);

	if (!succeeded) 
	{
		return nullptr;
	}

	for (unsigned int i = 0; i < format_count; ++i) 
	{
		pixel_format = formats[i];
		succeeded = SetPixelFormat(reinterpret_cast<HDC>(hdc), pixel_format, NULL);
		if (succeeded) 
		{
			break;
		}
		else 
		{
			//DWORD error = GetLastError();
		}
	}

	if (!succeeded) {
		return nullptr;
	}

	int context_flags = 0;
#if defined(_DEBUG)
	context_flags |= WGL_CONTEXT_DEBUG_BIT_ARB;
#endif

	const int attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, major,
		WGL_CONTEXT_MINOR_VERSION_ARB, minor,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		WGL_CONTEXT_FLAGS_ARB, context_flags,
		0, 0
	};

	void* context = wglCreateContextAttribsARB(reinterpret_cast<HDC>(hdc), NULL, attribs);
	if (context == NULL) {
		return nullptr;
	}

	return context;
}

void Renderer::BindFont(const Font* font, int textureSlot)
{
	font->GetSpriteSheet().GetSpriteSheetTexture().Bind(m_TextureSlot[textureSlot]);

	g_Shader->SetUniform1i("u_Texture", textureSlot);
}

void Renderer::BindTexture(const Texture* texture, int textureSlot)
{
	if(!texture)
		texture = m_DefaultTexture;

	texture->Bind(m_TextureSlot[textureSlot]);

	g_Shader->SetUniform1i("u_Texture", textureSlot);
}

void Renderer::SetCameraUniform(const Mat4& camera)
{
	g_Shader->SetUniformMat4f("u_Proj", camera);
}

void Renderer::SetModelTranslation(const Mat4& transform)
{
	g_Shader->SetUniformMat4f("u_Model", transform);
}

//---------------------------------------------------------------------------------------------------------

void Renderer::CreateInstance()
{
	m_Renderer = new Renderer();
}

//------------------------------------------------------------------------------------------------------

Renderer* Renderer::GetInstance()
{
	return m_Renderer;
}

//------------------------------------------------------------------------------------------------------

void Renderer::DestroyInstance()
{
	delete m_Renderer;
	m_Renderer = nullptr;
}

//------------------------------------------------------------------------------------------------------
// Enabling Blend functionality

void Renderer::EnableBlend(enum APEX_BLEND_FACTOR src, enum APEX_BLEND_FACTOR dest, enum APEX_BLEND_OP mode)
{
	glLineWidth(2.0f);
	glEnable(GL_BLEND);

	glBlendFunc(src, dest);

	glBlendEquation(mode);
}

//------------------------------------------------------------------------------------------------------
// Disabling Blend functionality

void Renderer::DisableBlend()
{
	glDisable(GL_BLEND);
}

//------------------------------------------------------------------------------------------------------
// Drawing Text on the screen

void Renderer::Drawtext(const Vec4& color, const std::string& asciiText, float quadHeight, Font* font)
{
	float quadWidth = quadHeight;

	AABB2 quadPos;
	AABB2 uvPos;

	quadPos.m_Mins.m_Y = 0.0f;
	quadPos.m_Maxs.m_Y = quadHeight;

	for (size_t i = 0; i < asciiText.size(); i++)
	{
		MeshBuilder* mb = new MeshBuilder();

		quadPos.m_Mins.m_X = (i * quadWidth);
		quadPos.m_Maxs.m_X = ((i + 1) * quadWidth);

		uvPos = font->GetGlyphUV(asciiText[i]);

		mb->Color3f(color);
		mb->TexCoord2f(Vec2(uvPos.m_Mins.m_X, uvPos.m_Maxs.m_Y));
	    mb->Position3f(Vec3(quadPos.m_Mins.m_X, quadPos.m_Mins.m_Y, 0.0f));
	    
	    mb->TexCoord2f(Vec2(uvPos.m_Maxs.m_X, uvPos.m_Maxs.m_Y));
	    mb->Position3f(Vec3(quadPos.m_Maxs.m_X, quadPos.m_Mins.m_Y, 0.0f));
	    
	    mb->TexCoord2f(Vec2(uvPos.m_Maxs.m_X, uvPos.m_Mins.m_Y));
	    mb->Position3f(Vec3(quadPos.m_Maxs.m_X, quadPos.m_Maxs.m_Y, 0.0f));
	    
	    mb->TexCoord2f(Vec2(uvPos.m_Mins.m_X, uvPos.m_Mins.m_Y));
	    mb->Position3f(Vec3(quadPos.m_Mins.m_X, quadPos.m_Maxs.m_Y, 0.0f));

		Mesh* mesh = mb->CreateMesh<VertexPCU>();

		mesh->Begin(GL_TRIANGLES);
		DrawMesh(mesh);
		mesh->End();

		delete mesh;
		delete mb;
	}
}

void Renderer::DrawAABB2(const AABB2& aabb2, const Vec4& color)
{
	MeshBuilder* mb = new MeshBuilder();

	mb->Color3f(Vec4(color.m_X, color.m_Y, color.m_Z, color.m_W));
	mb->TexCoord2f(Vec2::ZERO_ZERO);
	mb->Position3f(Vec3(aabb2.m_Mins.m_X, aabb2.m_Mins.m_Y, 0.0f));

	mb->TexCoord2f(Vec2::ONE_ZERO);
	mb->Position3f(Vec3(aabb2.m_Maxs.m_X, aabb2.m_Mins.m_Y, 0.0f));

	mb->TexCoord2f(Vec2::ONE_ONE);
	mb->Position3f(Vec3(aabb2.m_Maxs.m_X, aabb2.m_Maxs.m_Y, 0.0f));

	mb->TexCoord2f(Vec2::ZERO_ONE);
	mb->Position3f(Vec3(aabb2.m_Mins.m_X, aabb2.m_Maxs.m_Y, 0.0f));
	
	Mesh* mesh = mb->CreateMesh<VertexPCU>();

	mesh->Begin(GL_TRIANGLES);
	DrawMesh(mesh);
	mesh->End();

	delete mesh;
	delete mb;
}

void Renderer::DrawLine(Vec2& start, Vec2& end, float thickness, const Vec4& color)
{
	MeshBuilder* mb = new MeshBuilder();

	Vec2 distance = end - start;
	Vec2 forward = distance.GetNormalised();

	forward.SetLength(thickness / 2.0f);
	Vec2 left = forward.GetRotated90Degrees();

	Vec2 endLeft = end + forward + left;
	Vec2 endRight = end + forward - left;
	Vec2 startLeft = start - forward + left;
	Vec2 startRight = start - forward - left;

	mb->Color3f(color);
	mb->TexCoord2f(Vec2::ZERO_ZERO);
	mb->Position3f(Vec3(startLeft.m_X, startLeft.m_Y, 0.0f));

	mb->TexCoord2f(Vec2::ONE_ZERO);
	mb->Position3f(Vec3(endLeft.m_X, endLeft.m_Y, 0.0f));

	mb->TexCoord2f(Vec2::ONE_ONE);
	mb->Position3f(Vec3(endRight.m_X, endRight.m_Y, 0.0f));

	mb->TexCoord2f(Vec2::ZERO_ONE);
	mb->Position3f(Vec3(startRight.m_X, startRight.m_Y, 0.0f));
	
	Mesh* mesh = mb->CreateMesh<VertexPCU>();

	mesh->Begin(GL_TRIANGLES);
	DrawMesh(mesh);
	mesh->End();

	delete mesh;
	delete mb;
}

void Renderer::DrawArrow(Vec2& start, Vec2& end, float thickness, const Vec4& color)
{
	MeshBuilder* mb1 = new MeshBuilder();

	Vec2 distance = end - start;
	Vec2 forward = distance.GetNormalised();

	forward.SetLength(thickness / 2.0f);
	Vec2 left = forward.GetRotated90Degrees();

	Vec2 endLeft = end - forward + left;
	Vec2 endRight = end - forward - left;
	Vec2 startLeft = start - forward + left;
	Vec2 startRight = start - forward - left;

	mb1->Color3f(color);
	mb1->TexCoord2f(Vec2::ZERO_ZERO);
	mb1->Position3f(Vec3(startLeft.m_X, startLeft.m_Y, 0.0f));

	mb1->TexCoord2f(Vec2::ONE_ZERO);
	mb1->Position3f(Vec3(endLeft.m_X, endLeft.m_Y, 0.0f));

	mb1->TexCoord2f(Vec2::ONE_ONE);
	mb1->Position3f(Vec3(endRight.m_X, endRight.m_Y, 0.0f));

	mb1->TexCoord2f(Vec2::ZERO_ONE);
	mb1->Position3f(Vec3(startRight.m_X, startRight.m_Y, 0.0f));
	
	Mesh* mesh1 = mb1->CreateMesh<VertexPCU>();

	mesh1->Begin(GL_TRIANGLES);
	DrawMesh(mesh1);
	mesh1->End();

	delete mesh1;
	delete mb1;

	MeshBuilder* mb2 = new MeshBuilder();
	
	float Orientation = ( end - start ).GetAngleDegrees();
	Vec2 rightVert = Vec2::MakeFromPolarDegrees( Orientation - 25.f , 3 * thickness );
	Vec2 leftVert = Vec2::MakeFromPolarDegrees( Orientation + 25.f , 3 * thickness );

	Vec2 top = end - forward;
	Vec2 bottomLeft = end - leftVert;
	Vec2 bottomRight = end - rightVert;

	mb2->Color3f(color);
	mb2->TexCoord2f(Vec2::ZERO_ZERO);
	mb2->Position3f(Vec3(top.m_X, top.m_Y, 0.0f));

	mb2->TexCoord2f(Vec2::ONE_ZERO);
	mb2->Position3f(Vec3(bottomLeft.m_X, bottomLeft.m_Y, 0.0f));

	mb2->TexCoord2f(Vec2::HALF_ONE);
	mb2->Position3f(Vec3(bottomRight.m_X, bottomRight.m_Y, 0.0f));

	Mesh* mesh2 = mb2->CreateMesh<VertexPCU>();

	mesh2->Begin(GL_TRIANGLES);
	DrawMesh(mesh2);
	mesh2->End();

	delete mesh2;
	delete mb2;
}

void Renderer::DrawDisc(const Vec2& center, const float& radius, const Vec4& color)
{
	for(int i = 0; i < NUM_OF_DISC_VERTICES; i++)
	{
		MeshBuilder* mb = new MeshBuilder();
	    
	    mb->Color3f(color);
	    mb->TexCoord2f(Vec2(0.0f, 0.0f));
	    mb->Position3f(Vec3(center.m_X, center.m_Y, 0.0f));

		float startDeg, endDeg;
		float angle = 360.0f / NUM_OF_DISC_VERTICES;
		Vec2 start, end;

		startDeg = angle * static_cast<float>(i);
		endDeg = angle * static_cast<float>(i + 1);

		start = Vec2(center.m_X + cosf(toRadians(startDeg)) * radius, center.m_Y + sinf(toRadians(startDeg)) * radius);
		end = Vec2(center.m_X + cosf(toRadians(endDeg)) * radius, center.m_Y + sinf(toRadians(endDeg)) * radius);

	    mb->TexCoord2f(Vec2(1.0f, 0.0f));
	    mb->Position3f(Vec3(start.m_X, start.m_Y, 0.0f));
	    
	    mb->TexCoord2f(Vec2(0.5f, 1.0f));
	    mb->Position3f(Vec3(end.m_X, end.m_Y, 0.0f));
	    
	    Mesh* mesh = mb->CreateMesh<VertexPCU>();
	    mesh->m_Indices = 3;
	    
	    mesh->Begin(GL_TRIANGLES);
	    DrawMesh(mesh);
	    mesh->End();
	    
	    delete mesh;
	    delete mb;
	}
}

void Renderer::DrawRing(const Vec2& center, const float& radius, const Vec4& color)
{
	for(int i = 0; i < NUM_OF_DISC_VERTICES; i++)
	{
		MeshBuilder* mb = new MeshBuilder();
	    
	    mb->Color3f(color);

		float startDeg, endDeg;
		float angle = 360.0f / NUM_OF_DISC_VERTICES;
		Vec2 start, end;

		startDeg = angle * static_cast<float>(i);
		endDeg = angle * static_cast<float>(i + 1);

		start = Vec2(cosf(toRadians(startDeg)) * radius, sinf(toRadians(startDeg)) * radius);
		end = Vec2(cosf(toRadians(endDeg)) * radius, sinf(toRadians(endDeg)) * radius);

	    mb->TexCoord2f(Vec2(0.0f, 0.0f));
	    mb->Position3f(Vec3(start.m_X, start.m_Y, 0.0f));

	    mb->TexCoord2f(Vec2(1.0f, 0.0f));
	    mb->Position3f(Vec3(end.m_X, end.m_Y, 0.0f));
		
	    mb->TexCoord2f(Vec2(1.0f, 1.0f));
	    mb->Position3f(Vec3(end.m_X - (RING_THICKNESS * cosf(toRadians(endDeg))), end.m_Y - (RING_THICKNESS * sinf(toRadians(endDeg))), 0.0f));

		mb->TexCoord2f(Vec2(0.0f, 1.0f));
	    mb->Position3f(Vec3(start.m_X - (RING_THICKNESS * cosf(toRadians(startDeg))), start.m_Y - (RING_THICKNESS * sinf(toRadians(startDeg))), 0.0f));
	    
	    Mesh* mesh = mb->CreateMesh<VertexPCU>();
	    
	    mesh->Begin(GL_TRIANGLES);
	    DrawMesh(mesh);
	    mesh->End();
	    
	    delete mesh;
	    delete mb;
	}
}

//------------------------------------------------------------------------------------------------------
/*All the Drawing functions go through a Common 
DrawMesh() function to help minimize the point of error*/

void Renderer::DrawMesh(Mesh* mesh)
{
	if(mesh->m_Indices == 6)
	{
		glDrawElements(mesh->m_DrawType, mesh->m_Indices, GL_UNSIGNED_INT, nullptr);
	}
	else
	{
		glDrawArrays(mesh->m_DrawType, 0, mesh->m_Indices);
	}
}

Texture* Renderer::GetDefaultTexture() const
{
	return m_DefaultTexture;
}

void Renderer::CreateTexture(const std::string& texturePath)
{
	Texture* texture = new Texture(texturePath);

	stbi_set_flip_vertically_on_load(1);
	texture->m_LocalBuffer = stbi_load(texturePath.c_str(), &texture->m_Width, &texture->m_Height, &texture->m_Channels, 0);

	GLenum internalFormat = 0;
	GLenum dataFormat = 0;

	if (texture->m_Channels == 4)
	{
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;
	}
	else if (texture->m_Channels == 3)
	{
		internalFormat = GL_RGB8;
		dataFormat = GL_RGB;
	}

	glGenTextures(1, &texture->m_RendererID);
	glBindTexture(GL_TEXTURE_2D, texture->m_RendererID);

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, texture->m_Width, texture->m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, texture->m_LocalBuffer);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	if (texture->m_LocalBuffer)
	{
		stbi_image_free(texture->m_LocalBuffer);
	}

	m_LoadedTextures[texturePath] = texture;

	texture = nullptr;
}

Texture* Renderer::CreateTextureFromColor(const Vec4& color)
{
	Texture* texture = new Texture();

	GLenum internalFormat = GL_RGBA8;
	GLenum dataFormat = GL_RGBA;

	texture->m_Width = 1;
	texture->m_Height = 1;
	texture->m_Channels = 4;
	texture->m_LocalBuffer = (unsigned char*)&color.m_X;

	glGenTextures(1, &texture->m_RendererID);
	glBindTexture(GL_TEXTURE_2D, texture->m_RendererID);

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, texture->m_Width, texture->m_Height, 0, dataFormat, GL_FLOAT, texture->m_LocalBuffer);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}

//------------------------------------------------------------------------------------------------------
// Copying current frambuffer to next framebuffer

void Renderer::CopyFrameBuffer(FrameBuffer* current, FrameBuffer* next)
{
	Vec2 dims = current->m_Dims;

	if(next)
	{
		dims = next->m_Dims;
	}

	glBindFramebuffer(GL_READ_FRAMEBUFFER, current->GetFrameBufferID());

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, (next ? next->GetFrameBufferID() : NULL));

	glBlitFramebuffer(0, 0, (GLint)current->m_Dims.m_X, (GLint)current->m_Dims.m_Y, 0, 0, (GLint)dims.m_X, (GLint)dims.m_Y, GL_COLOR_BUFFER_BIT, GL_NEAREST);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::ClearColor() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

//------------------------------------------------------------------------------------------------------
/*Creating a Font if it doesn't exits and storing it 
inside a map with the key value being its file path*/

Font* Renderer::GetOrCreateFont(const std::string& path)
{
	if (m_LoadedFonts.find(path) != m_LoadedFonts.end())
	{
		return m_LoadedFonts.at(path);
	}
	else
	{
		Texture* texture = new Texture(path);
		LOG_CHECK(texture != nullptr) << "Data is null";

		SpriteSheet* bitMapsheet = new SpriteSheet(*texture, 16, 16);
		LOG_CHECK(bitMapsheet != nullptr) << "Data is null";

		Font* font = new Font(*bitMapsheet);
		LOG_CHECK(font != nullptr) << "Data is null";

		m_LoadedFonts[path] = font;

		return font;
	}
}

//------------------------------------------------------------------------------------------------------
/*Creating a Texture if it doesn't exits and storing it
inside a map with the key value being its file path*/

Texture* Renderer::GetOrCreateTexture(const std::string& path)
{
	if (m_LoadedTextures.find(path) != m_LoadedTextures.end())
	{
		return m_LoadedTextures.at(path);
	}
	else
	{
		Texture* texture = new Texture(path);
		LOG_CHECK(texture != nullptr) << "Data is null";

		m_LoadedTextures[path] = texture;

		return texture;
	}
}

//------------------------------------------------------------------------------------------------------
/*Creating a Shader if it doesn't exits and storing it
inside a map with the key value being its XML Definition*/

Shader* Renderer::GetOrCreateShader(ShaderDefinition* shaderDef)
{
	if (m_LoadedShaders.find(shaderDef) != m_LoadedShaders.end())
	{
		return m_LoadedShaders.at(shaderDef);
	}
	else
	{
		Shader* shader = new Shader(shaderDef);
		LOG_CHECK(shader != nullptr) << "Data is null";

		m_LoadedShaders[shaderDef] = shader;

		return shader;
	}
}

ShaderDefinition* Renderer::GetOrCreateShaderDef(XMLElement* element)
{
	if(m_LoadedShaderDefinitions.find(element) != m_LoadedShaderDefinitions.end())
	{
		return m_LoadedShaderDefinitions.at(element);
	}
	else
	{
		ShaderDefinition* shaderDef = new ShaderDefinition(*element);
		LOG_CHECK(shaderDef != nullptr) << "Data is null";

		m_LoadedShaderDefinitions[element] = shaderDef;

		return shaderDef;
	}
}
