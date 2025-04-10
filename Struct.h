#pragma once

// 2次元ベクトル
typedef struct Vector2
{
	float x;
	float y;
}Vector2;

// 3次元ベクトル
typedef struct Vector3
{
	float x;
	float y;
	float z;
}Vector3;

// 4x4行列
typedef struct Matrix4x4
{
	float m[4][4];
}Matrix4x4;

// 球
typedef struct Sphere
{
	// 中心点
	Vector3 center;

	// 半径
	float radius;
}Sphere;

// 線分
typedef struct Segment
{
	// 始点
	Vector3 origin;

	// 終点への差分ベクトル
	Vector3 diff;
}Segment;

// 直線
typedef struct Line
{
	// 始点
	Vector3 origin;

	// 終点への差分ベクトル
	Vector3 diff;
}Line;

// 半直線
typedef struct Ray
{
	// 始点
	Vector3 origin;

	// 終点への差分ベクトル
	Vector3 diff;
}Ray;

// 平面
typedef struct Plane
{
	// 法線
	Vector3 normal;

	// 距離
	float distance;
}Plane;

// 三角形
typedef struct Triangle
{
	// 頂点
	Vector3 vertices[3];
}Triangle;

// AABB
typedef struct AABB
{
	// 最小点
	Vector3 min;

	// 最大点
	Vector3 max;
}AABB;