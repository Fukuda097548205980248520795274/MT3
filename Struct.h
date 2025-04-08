#pragma once

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