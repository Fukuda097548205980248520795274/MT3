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

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="segment">線分</param>
/// <param name="plane">平面</param>
/// <returns>true or false</returns>
bool IsCollision(const Segment& segment, const Plane& plane)
{
	// 法線 dot 終点との差分
	float NdotD = Dot(plane.normal, segment.diff);

	// 平面と線が平行だと当たらない
	if (NdotD == 0)
	{
		return false;
	}

	return true;
}

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="line">直線</param>
/// <param name="plane">平面</param>
/// <returns>true or false</returns>
bool IsCollision(const Line& line, const Plane& plane)
{
	// 法線 dot 終点との差分
	float NdotD = Dot(plane.normal, line.diff);

	// 平面と線が平行だと当たらない
	if (NdotD == 0)
	{
		return false;
	}

	// 法線 dot 始点
	float NdotO = Dot(plane.normal, line.origin);

	// 媒介変数
	float t = (plane.distance - NdotO) / NdotD;

	if (t >= 0 && t <= 1)
	{
		return true;
	}

	return false;
}

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="ray">半直線</param>
/// <param name="plane">平面</param>
/// <returns>ture or false</returns>
bool IsCollision(const Ray& ray, const Plane& plane)
{
	// 法線 dot 終点との差分
	float NdotD = Dot(plane.normal, ray.diff);

	// 平面と線が平行だと当たらない
	if (NdotD == 0)
	{
		return false;
	}

	// 法線 dot 始点
	float NdotO = Dot(plane.normal, ray.origin);

	// 媒介変数
	float t = (plane.distance - NdotO) / NdotD;

	if (t >= 0)
	{
		return true;
	}

	return false;
}