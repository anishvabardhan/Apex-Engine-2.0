#pragma once

#include "Engine/Maths/AABB2.h"
#include "Engine/Maths/Vec2.h"

// Game:BRICKBREAKER Hard Coded Values------------------------------------------------------------------------------

constexpr char* BB_BALL_TEXTURE = "../../Data/Textures/Ball.png";
constexpr char* BB_PADDLE_TEXTURE = "../../Data/Textures/Brick1.png";
constexpr float BB_BALL_RADIUS = 10.0f;
constexpr int NUM_OF_BRICKS = 32;
constexpr int NUM_OF_COLS = NUM_OF_BRICKS / 4;
constexpr int NUM_OF_ROWS = NUM_OF_BRICKS / 8;
constexpr float BB_PADDLE_DEVIATION_RANGE = 30.0f;
constexpr Vec2 BB_BALL_VELOCITY = Vec2(-2000.0f, 5000.0f);
const AABB2 BRICK_MAP_SPACE = AABB2(Vec2(4.0f, 512.0f), Vec2(896.0f, 720.0f));
constexpr Vec2 BRICK_DIMS = Vec2(128.0f, 52.0f);

//------------------------------------------------------------------------------------------------------------------