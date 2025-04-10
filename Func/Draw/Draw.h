#pragma once
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include "Struct.h"
#include "./Func/Matrix/Matrix.h"
#include "./Func/Vector/Vector.h"

/// <summary>
/// 球を描画する
/// </summary>
/// <param name="sphere">球</param>
/// <param name="viewProjectionMatrix">ビュー * 透視投影　行列</param>
/// <param name="viewportMatrix">ビューポート行列</param>
/// <param name="color">色</param>
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

/// <summary>
/// グリッドを描画する
/// </summary>
/// <param name="viewProjectionMatrix">ビュー * 透視投影　行列</param>
/// <param name="viewportMatrix">ビューポート変換行列</param>
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

/// <summary>
/// 平面を描画する
/// </summary>
/// <param name="plane">平面</param>
/// <param name="viewProjectionMatrix">ビュー * 透視投影　行列</param>
/// <param name="viewportMatrix">ビューポート変換行列</param>
/// <param name="color">色</param>
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);