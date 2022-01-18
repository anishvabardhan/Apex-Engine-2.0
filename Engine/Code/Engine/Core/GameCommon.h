#pragma once

#include "Engine/Maths/Vec2.h"
#include "Engine/Maths/AABB2.h"

// Engine Hard Coded Values-----------------------------------------------------------------------------------------

static const float APEX_WINDOW_DIMS[] = {0.0f, 1024.0f, 0.0f, 1024.0f};
static const char* APEX_SHADER_XML = "../../Data/Materials/shader.xml";
static const char* APEX_SCREENSHADER_XML = "../../Data/Materials/screenShader.xml";
static const char* APEX_DEFAULT_TEXTURE = "../../Data/Textures/Default.png";
static const char* APEX_FONT_BITMAP = "../../Data/Textures/NewFont.png";

//------------------------------------------------------------------------------------------------------------------
// Game:BRICKBREAKER Hard Coded Values------------------------------------------------------------------------------

static const char* BB_BALL_TEXTURE = "../../Data/Textures/Ball.png";
static const char* BB_PADDLE_TEXTURE = "../../Data/Textures/Brick1.png";
static const int NUM_OF_BRICKS = 32;
static const int NUM_OF_COLS = NUM_OF_BRICKS / 4;
static const int NUM_OF_ROWS = NUM_OF_BRICKS / 8;
static const float BB_PADDLE_ACCELARATION = 1500.0f;
static const Vec2 BB_BALL_VELOCITY = Vec2(-500.0f, 2000.0f);
static const AABB2 BRICK_MAP_SPACE = AABB2(Vec2(4.0f, 512.0f), Vec2(896.0f, 720.0f));
static const Vec2 BRICK_DIMS = Vec2(128.0f, 52.0f);

//------------------------------------------------------------------------------------------------------------------