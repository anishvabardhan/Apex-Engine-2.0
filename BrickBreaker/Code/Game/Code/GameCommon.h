#pragma once

#include "Engine/Maths/AABB2.h"
#include "Engine/Maths/Vec2.h"

// Game:BRICKBREAKER Hard Coded Values------------------------------------------------------------------------------

constexpr char* BB_BALL_TEXTURE = "../../Data/Textures/Ball.png";
constexpr char* BB_PADDLE_TEXTURE = "../../Data/Textures/Brick1.png";
constexpr float BB_BALL_RADIUS = 10.0f;
constexpr int BB_NUM_OF_BRICKS = 32;
constexpr int BB_NUM_OF_COLS = BB_NUM_OF_BRICKS / 4;
constexpr int BB_NUM_OF_ROWS = BB_NUM_OF_BRICKS / 8;
constexpr float BB_PADDLE_DEVIATION_RANGE = 30.0f;
constexpr Vec2 BB_BALL_VELOCITY = Vec2(-40.0f, 70.0f);
const AABB2 BB_BRICK_MAP_SPACE = AABB2(Vec2(0.0f, 512.0f), Vec2(896.0f, 720.0f));
constexpr Vec2 BB_BRICK_DIMS = Vec2(128.0f, 52.0f);
constexpr Vec2 BB_PADDLE_POSITION = Vec2(462.0f, 20.0f);
constexpr Vec2 BB_PADDLE_DIMS = Vec2(200.0f, 25.0f);
constexpr Vec2 BB_BALL_POSITION = Vec2(552.0f, 55.0f);
constexpr float BB_BALL_MIN_VELOCITY = -70.0f;
constexpr float BB_BALL_MAX_VELOCITY = 100.0f;

//------------------------------------------------------------------------------------------------------------------