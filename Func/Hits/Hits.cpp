#include "Hits.h"

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="s1">球1</param>
/// <param name="s2">球2</param>
/// <returns>true or false</returns>
bool IsCollision(const Sphere& s1, const Sphere& s2)
{
	// 球同士の距離
	float distance = Length(Subtract(s2.center, s1.center));

	if (distance <= s1.radius + s2.radius)
	{
		return true;
	}

	return false;
}

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="sphere">球</param>
/// <param name="plane">平面</param>
/// <returns>true or false</returns>
bool IsCollision(const Sphere& sphere, const Plane& plane)
{
	float distance = Dot(plane.normal, sphere.center) - plane.distance;

	if (std::fabs(distance) <= sphere.radius)
	{
		return true;
	}

	return false;
}