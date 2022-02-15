#pragma once

class Vec2;
class AABB2;

float Clamp(float value, float min, float max);
float CosDegrees(float degrees);
float SinDegrees(float degrees);
float Atan2Degrees(float y, float x);
float RangeMap(float inputValue, float inputBegin, float inputEnd, float outputBegin, float outputEnd);
bool Disc_AABB2Collision(Vec2& center, float radius, AABB2& box);