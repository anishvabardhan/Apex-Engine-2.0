#pragma once

#include "Engine/Maths/Vec2.h"
#include "Engine/Maths/AABB2.h"

static const float APEX_WINDOW_DIMS[] = {0.0f, 1024.0f, 0.0f, 1024.0f};
static const char* APEX_SHADER_XML = "E:/Dev/Apex-Engine-2.0/BrickBreaker/Data/Materials/shader.xml";
static const char* APEX_SCREENSHADER_XML = "E:/Dev/Apex-Engine-2.0/BrickBreaker/Data/Materials/screenShader.xml";
static const char* APEX_DEFAULT_TEXTURE = "E:/Dev/Apex-Engine-2.0/BrickBreaker/Data/Textures/Default.png";
static const char* APEX_FONT_BITMAP = "E:/Dev/Apex-Engine-2.0/BrickBreaker/Data/Textures/NewFont.png";

static const char* BB_BALL_TEXTURE = "E:/Dev/Apex-Engine-2.0/BrickBreaker/Data/Textures/Ball.png";
static const char* BB_PADDLE_TEXTURE = "E:/Dev/Apex-Engine-2.0/BrickBreaker/Data/Textures/Brick1.png";
static const int NUM_OF_BRICKS = 32;
static const int NUM_OF_COLS = NUM_OF_BRICKS / 4;
static const int NUM_OF_ROWS = NUM_OF_BRICKS / 8;
static const float BB_PADDLE_ACCELARATION = 1500.0f;
static const Vec2 BB_BALL_VELOCITY = Vec2(-500.0f, 2000.0f);
static const AABB2 BRICK_MAP_SPACE = AABB2(Vec2(4.0f, 512.0f), Vec2(896.0f, 720.0f));
static const Vec2 BRICK_DIMS = Vec2(128.0f, 52.0f);