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

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="triangle">三角形</param>
/// <param name="segment">線分</param>
/// <returns>true or false</returns>
bool IsCollision(const Triangle& triangle, const Segment& segment)
{
	// 三角形の法線
	Vector3 normal = Normalize(Cross(Subtract(triangle.vertices[1], triangle.vertices[0]), Subtract(triangle.vertices[2], triangle.vertices[1])));

	// 法線 dot 終点との差分
	float NdotD = Dot(normal, segment.diff);

	// 平面と線が平行だと当たらない
	if (NdotD == 0)
	{
		return false;
	}

	// 法線 dot 始点
	float NdotO = Dot(normal, segment.origin);

	// 三角形の中心点
	Vector3 center =
	{
		(triangle.vertices[0].x + triangle.vertices[1].x + triangle.vertices[2].x) / 3.0f,
		(triangle.vertices[0].y + triangle.vertices[1].y + triangle.vertices[2].y) / 3.0f,
		(triangle.vertices[0].z + triangle.vertices[1].z + triangle.vertices[2].z) / 3.0f
	};

	// 距離
	float distance = Dot(center, normal);

	// 媒介変数
	float t = (distance - NdotO) / NdotD;


	Vector3 v01 = Subtract(triangle.vertices[1], triangle.vertices[0]);
	Vector3 v12 = Subtract(triangle.vertices[2], triangle.vertices[1]);
	Vector3 v20 = Subtract(triangle.vertices[0], triangle.vertices[2]);

	Vector3 v1p = Subtract(Add(segment.origin, Multiply(t, segment.diff)), triangle.vertices[1]);
	Vector3 v2p = Subtract(Add(segment.origin, Multiply(t, segment.diff)), triangle.vertices[2]);
	Vector3 v0p = Subtract(Add(segment.origin, Multiply(t, segment.diff)), triangle.vertices[0]);

	Vector3 cross01 = Cross(v01, v1p);
	Vector3 cross12 = Cross(v12, v2p);
	Vector3 cross20 = Cross(v20, v0p);

	if (Dot(cross01, normal) >= 0.0f &&
		Dot(cross12, normal) >= 0.0f &&
		Dot(cross20, normal) >= 0.0f)
	{
		return true;
	}

	return false;
}


/// <summary>
/// 当たり判定
/// </summary>
/// <param name="triangle">三角形</param>
/// <param name="line">直線</param>
/// <returns>true or false</returns>
bool IsCollision(const Triangle& triangle, const Line& line)
{
	// 三角形の法線
	Vector3 normal = Normalize(Cross(Subtract(triangle.vertices[1], triangle.vertices[0]), Subtract(triangle.vertices[2], triangle.vertices[1])));

	// 法線 dot 終点との差分
	float NdotD = Dot(normal, line.diff);

	// 平面と線が平行だと当たらない
	if (NdotD == 0)
	{
		return false;
	}

	// 法線 dot 始点
	float NdotO = Dot(normal, line.origin);

	// 三角形の中心点
	Vector3 center =
	{
		(triangle.vertices[0].x + triangle.vertices[1].x + triangle.vertices[2].x) / 3.0f,
		(triangle.vertices[0].y + triangle.vertices[1].y + triangle.vertices[2].y) / 3.0f,
		(triangle.vertices[0].z + triangle.vertices[1].z + triangle.vertices[2].z) / 3.0f
	};

	// 距離
	float distance = Dot(center, normal);

	// 媒介変数
	float t = (distance - NdotO) / NdotD;

	if (t >= 0.0f && t <= 1.0f)
	{
		Vector3 v01 = Subtract(triangle.vertices[1], triangle.vertices[0]);
		Vector3 v12 = Subtract(triangle.vertices[2], triangle.vertices[1]);
		Vector3 v20 = Subtract(triangle.vertices[0], triangle.vertices[2]);

		Vector3 v1p = Subtract(Add(line.origin, Multiply(t, line.diff)), triangle.vertices[1]);
		Vector3 v2p = Subtract(Add(line.origin, Multiply(t, line.diff)), triangle.vertices[2]);
		Vector3 v0p = Subtract(Add(line.origin, Multiply(t, line.diff)), triangle.vertices[0]);

		Vector3 cross01 = Cross(v01, v1p);
		Vector3 cross12 = Cross(v12, v2p);
		Vector3 cross20 = Cross(v20, v0p);

		if (Dot(cross01, normal) >= 0.0f &&
			Dot(cross12, normal) >= 0.0f &&
			Dot(cross20, normal) >= 0.0f)
		{
			return true;
		}
	}


	return false;
}

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="triangle">三角形</param>
/// <param name="ray">半直線</param>
/// <returns>true or false</returns>
bool IsCollision(const Triangle& triangle, const Ray& ray)
{
	// 三角形の法線
	Vector3 normal = Normalize(Cross(Subtract(triangle.vertices[1], triangle.vertices[0]), Subtract(triangle.vertices[2], triangle.vertices[1])));

	// 法線 dot 終点との差分
	float NdotD = Dot(normal, ray.diff);

	// 平面と線が平行だと当たらない
	if (NdotD == 0)
	{
		return false;
	}

	// 法線 dot 始点
	float NdotO = Dot(normal, ray.origin);

	// 三角形の中心点
	Vector3 center =
	{
		(triangle.vertices[0].x + triangle.vertices[1].x + triangle.vertices[2].x) / 3.0f,
		(triangle.vertices[0].y + triangle.vertices[1].y + triangle.vertices[2].y) / 3.0f,
		(triangle.vertices[0].z + triangle.vertices[1].z + triangle.vertices[2].z) / 3.0f
	};

	// 距離
	float distance = Dot(center, normal);

	// 媒介変数
	float t = (distance - NdotO) / NdotD;

	if (t >= 0.0f)
	{
		Vector3 v01 = Subtract(triangle.vertices[1], triangle.vertices[0]);
		Vector3 v12 = Subtract(triangle.vertices[2], triangle.vertices[1]);
		Vector3 v20 = Subtract(triangle.vertices[0], triangle.vertices[2]);

		Vector3 v1p = Subtract(Add(ray.origin, Multiply(t, ray.diff)), triangle.vertices[1]);
		Vector3 v2p = Subtract(Add(ray.origin, Multiply(t, ray.diff)), triangle.vertices[2]);
		Vector3 v0p = Subtract(Add(ray.origin, Multiply(t, ray.diff)), triangle.vertices[0]);

		Vector3 cross01 = Cross(v01, v1p);
		Vector3 cross12 = Cross(v12, v2p);
		Vector3 cross20 = Cross(v20, v0p);

		if (Dot(cross01, normal) >= 0.0f &&
			Dot(cross12, normal) >= 0.0f &&
			Dot(cross20, normal) >= 0.0f)
		{
			return true;
		}
	}


	return false;
}


