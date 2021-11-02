#include "Renderer.h"
#include "MeshBuilder.h"
#include "Mesh.h"
#include "Engine/Graphics/GLFunctions.h"

static Renderer* m_Renderer = nullptr;

//---------------------------------------------------------------------------------------------------------
// Defining the Constructors/Destructors

Renderer::Renderer()
{
	glViewport(0, 0, 1024, 1024);
}

//------------------------------------------------------------------------------------------------------

Renderer::~Renderer()
{
}

//---------------------------------------------------------------------------------------------------------
// Initializing the Renderer

void Renderer::InitRender()
{

	//--------------------------------------------------------------------------------------------------
	//Setup OpenGL3 Viewport
	
	glViewport(0, 0, 1024, 1024);

	//--------------------------------------------------------------------------------------------------
	//Clear Buffers to Preset Values

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
	//--------------------------------------------------------------------------------------------------
	//Specify Clear Values for the Color Buffers

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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

void Renderer::Drawtext(const Vec2& position, const Vec4& color, const std::string& asciiText, float quadHeight, Font* font, Shader shader)
{
	font->GetSpriteSheet().GetSpriteSheetTexture().Bind(TEXTURESLOT::SLOT0);

	float quadWidth = quadHeight;

	AABB2 quadPos;
	AABB2 uvPos;

	quadPos.m_Mins.m_Y = position.m_Y;
	quadPos.m_Maxs.m_Y = position.m_Y + quadHeight;

	for (size_t i = 0; i < asciiText.size(); i++)
	{
		MeshBuilder* mb = new MeshBuilder();

		quadPos.m_Mins.m_X = (i * quadWidth) + position.m_X;
		quadPos.m_Maxs.m_X = ((i + 1) * quadWidth) + position.m_X;

		uvPos = font->GetGlyphUV(asciiText[i]);

		mb->Push(VertexMaster(Vec3(quadPos.m_Mins.m_X, quadPos.m_Mins.m_Y, 0.0f), Vec4(color.m_X, color.m_Y, color.m_Z, color.m_W), Vec2(uvPos.m_Mins.m_X, uvPos.m_Maxs.m_Y)));
		mb->Push(VertexMaster(Vec3(quadPos.m_Maxs.m_X, quadPos.m_Mins.m_Y, 0.0f), Vec4(color.m_X, color.m_Y, color.m_Z, color.m_W), Vec2(uvPos.m_Maxs.m_X, uvPos.m_Maxs.m_Y)));
		mb->Push(VertexMaster(Vec3(quadPos.m_Maxs.m_X, quadPos.m_Maxs.m_Y, 0.0f), Vec4(color.m_X, color.m_Y, color.m_Z, color.m_W), Vec2(uvPos.m_Maxs.m_X, uvPos.m_Mins.m_Y)));
		mb->Push(VertexMaster(Vec3(quadPos.m_Mins.m_X, quadPos.m_Maxs.m_Y, 0.0f), Vec4(color.m_X, color.m_Y, color.m_Z, color.m_W), Vec2(uvPos.m_Mins.m_X, uvPos.m_Mins.m_Y)));
		
		Mesh* mesh = mb->CreateMesh<VertexMaster::PCU>();

		Mat4 model = Mat4::translation(Vec3(0.0f, 0.0f, 0.0f));
		shader.SetUniform1i("u_Texture", 0);
		shader.SetUniformMat4f("u_Model", model);

		mesh->Begin(GL_TRIANGLES);
		DrawMesh(mesh);
		mesh->End();

		delete mesh;
		delete mb;
	}
}

//------------------------------------------------------------------------------------------------------
// Drawing a Quad on the screen with a Texture parameter

void Renderer::DrawQuad(const Vec2& position, const Vec2& dimensions, const Texture& texture, const AABB2& texCoords, const Vec4& color, Shader shader)
{
	texture.Bind(TEXTURESLOT::SLOT2);

	MeshBuilder* mb = new MeshBuilder();

	mb->Push(VertexMaster(Vec3(position.m_X                 , position.m_Y                 , 0.0f), Vec4(color.m_X, color.m_Y, color.m_Z, color.m_W), Vec2(texCoords.m_Mins.m_X, texCoords.m_Maxs.m_Y)));
	mb->Push(VertexMaster(Vec3(position.m_X + dimensions.m_X, position.m_Y                 , 0.0f), Vec4(color.m_X, color.m_Y, color.m_Z, color.m_W), Vec2(texCoords.m_Maxs.m_X, texCoords.m_Maxs.m_Y)));
	mb->Push(VertexMaster(Vec3(position.m_X + dimensions.m_X, position.m_Y + dimensions.m_Y, 0.0f), Vec4(color.m_X, color.m_Y, color.m_Z, color.m_W), Vec2(texCoords.m_Maxs.m_X, texCoords.m_Mins.m_Y)));
	mb->Push(VertexMaster(Vec3(position.m_X                 , position.m_Y + dimensions.m_Y, 0.0f), Vec4(color.m_X, color.m_Y, color.m_Z, color.m_W), Vec2(texCoords.m_Mins.m_X, texCoords.m_Mins.m_Y)));
	
	Mesh* mesh = mb->CreateMesh<VertexMaster::PCU>();

	Mat4 model = Mat4::translation(Vec3(0.0f, 0.0f, 0.0f));
	shader.SetUniform1i("u_Texture", 2);
	shader.SetUniformMat4f("u_Model", model);

	mesh->Begin(GL_TRIANGLES);
	DrawMesh(mesh);
	mesh->End();

	delete mesh;
	delete mb;
}

//------------------------------------------------------------------------------------------------------
// Drawing a Quad on the screen a Texture File path parameter

void Renderer::DrawQuad(const Vec2& position, Vec2 meshDim, Vec4 color, const std::string& path, Shader shader)
{
	MeshBuilder* mb = new MeshBuilder();
	Texture* texture = GetOrCreateTexture(path);

	mb->Push(VertexMaster(Vec3(position.m_X              , position.m_Y              , 0.0f), Vec4(color.m_X, color.m_Y, color.m_Z, color.m_W), Vec2(0.0f, 0.0f)));
	mb->Push(VertexMaster(Vec3(position.m_X + meshDim.m_X, position.m_Y              , 0.0f), Vec4(color.m_X, color.m_Y, color.m_Z, color.m_W), Vec2(1.0f, 0.0f)));
	mb->Push(VertexMaster(Vec3(position.m_X + meshDim.m_X, position.m_Y + meshDim.m_Y, 0.0f), Vec4(color.m_X, color.m_Y, color.m_Z, color.m_W), Vec2(1.0f, 1.0f)));
	mb->Push(VertexMaster(Vec3(position.m_X              , position.m_Y + meshDim.m_Y, 0.0f), Vec4(color.m_X, color.m_Y, color.m_Z, color.m_W), Vec2(0.0f, 1.0f)));
	
	Mesh* mesh = mb->CreateMesh<VertexMaster::PCU>();

	Mat4 model = Mat4::translation(Vec3(0.0f, 0.0f, 0.0f));

	texture->Bind(TEXTURESLOT::SLOT1);

	shader.SetUniform1i("u_Texture", 1);
	shader.SetUniformMat4f("u_Model", model);

	mesh->Begin(GL_TRIANGLES);
	DrawMesh(mesh);
	mesh->End();

	delete mesh;
	delete mb;
}


//------------------------------------------------------------------------------------------------------
// Drawing a FramBuffer

void Renderer::DrawFrameBuffer(const Vec2& position, Vec2 meshDim)
{
	MeshBuilder* mb = new MeshBuilder();

	mb->Push(VertexMaster(Vec3(position.m_X              , position.m_Y              , 0.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 0.0f)));
	mb->Push(VertexMaster(Vec3(position.m_X + meshDim.m_X, position.m_Y              , 0.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)));
	mb->Push(VertexMaster(Vec3(position.m_X + meshDim.m_X, position.m_Y + meshDim.m_Y, 0.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)));
	mb->Push(VertexMaster(Vec3(position.m_X              , position.m_Y + meshDim.m_Y, 0.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)));
	
	Mesh* mesh = mb->CreateMesh<VertexMaster::PCU>();

	mesh->Begin(GL_TRIANGLES);
	DrawMesh(mesh);
	mesh->End();

	delete mesh;
	delete mb;
}

//------------------------------------------------------------------------------------------------------
/*All the Drawing functions go through a Common 
DrawMesh() function to help minimize the point of error*/

void Renderer::DrawMesh(Mesh* mesh)
{
	glDrawElements(mesh->m_DrawType, 6, GL_UNSIGNED_INT, nullptr);
}

//------------------------------------------------------------------------------------------------------
// Copying current frambuffer to next framebuffer

void Renderer::CopyFrameBuffer(FrameBuffer* current, FrameBuffer* next)
{
	glBindTexture(GL_TEXTURE_2D, current->GetColorAttachmentID());
	glBindTexture(GL_TEXTURE_2D, next->GetColorAttachmentID());

	glBindFramebuffer(GL_READ_FRAMEBUFFER, current->GetFrameBufferID());

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, next->GetFrameBufferID());

	glBlitFramebuffer(0, 0, 1024, 1024, 0, 0, 1024, 1024, GL_COLOR_BUFFER_BIT, GL_NEAREST);

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