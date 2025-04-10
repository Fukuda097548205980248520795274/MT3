#pragma once
#include "Struct.h"
#include "./Func/Vector/Vector.h"
#include "./Func/Draw/Draw.h"

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="s1">球1</param>
/// <param name="s2">球2</param>
/// <returns>true or false</returns>
bool IsCollision(const Sphere& s1, const Sphere& s2);