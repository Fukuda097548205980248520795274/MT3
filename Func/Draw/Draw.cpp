#include "Draw.h"

/// <summary>
/// 球を描画する
/// </summary>
/// <param name="sphere">球</param>
/// <param name="viewProjectionMatrix">ビュー * 透視投影　行列</param>
/// <param name="viewportMatrix">ビューポート行列</param>
/// <param name="color">色</param>
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	// 分割数
	const int kSubdivisions = 18;

	// 経度分割1つ分の角度
	const float kLonEvery = (360.0f / static_cast<float>(kSubdivisions)) / 180.0f * float(M_PI);

	// 緯度分割1つ分の角度
	const float kLatEvery = (360.0f / static_cast<float>(kSubdivisions)) / 180.0f * float(M_PI);


	// 緯度の方向に分割 -π/2 ~ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivisions; ++latIndex)
	{
		// 現在の緯度
		float lat = -float(M_PI) / 2.0f + kLatEvery * latIndex;

		// 経度の方向に分割 0 ~ 2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivisions; ++lonIndex)
		{
			// 現在の経度
			float lon = lonIndex * kLonEvery;


			// 3頂点のワールド座標
			Vector3 worldVertices[3];

			worldVertices[0] =
			{
				sphere.center.x + sphere.radius * (std::cos(lat) * std::cos(lon)),
				sphere.center.y + sphere.radius * std::sin(lat),
				sphere.center.z + sphere.radius * (std::cos(lat) * std::sin(lon))
			};

			worldVertices[1] =
			{
				sphere.center.x + sphere.radius * (std::cos(lat + float(M_PI) / static_cast<float>(kSubdivisions)) * std::cos(lon)),
				sphere.center.y + sphere.radius * std::sin(lat + float(M_PI) / static_cast<float>(kSubdivisions)),
				sphere.center.z + sphere.radius * (std::cos(lat + float(M_PI) / static_cast<float>(kSubdivisions)) * std::sin(lon))
			};

			worldVertices[2] =
			{
				sphere.center.x + sphere.radius * (std::cos(lat) * std::cos(lon + 2.0f * float(M_PI) / static_cast<float>(kSubdivisions))),
				sphere.center.y + sphere.radius * std::sin(lat),
				sphere.center.z + sphere.radius * (std::cos(lat) * std::sin(lon + 2.0f * float(M_PI) / static_cast<float>(kSubdivisions)))
			};


			// 3頂点のスクリーン座標
			Vector3 screenVertices[3] = { 0.0f };

			for (uint32_t i = 0; i < 3; i++)
			{
				Vector3 ndcVertex = Transform(worldVertices[i], viewProjectionMatrix);

				screenVertices[i] = Transform(ndcVertex, viewportMatrix);
			}

			Novice::DrawLine
			(
				static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y),
				static_cast<int>(screenVertices[1].x), static_cast<int>(screenVertices[1].y),
				color
			);

			Novice::DrawLine
			(
				static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y),
				static_cast<int>(screenVertices[2].x), static_cast<int>(screenVertices[2].y),
				color
			);
		}
	}
}

/// <summary>
/// グリッドを描画する
/// </summary>
/// <param name="viewProjectionMatrix">ビュー * 透視投影　行列</param>
/// <param name="viewportMatrix">ビューポート変換行列</param>
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix)
{
	// グリッドの半分の幅
	const float kGridHalfWidth = 2.0f;

	// 分割数
	const int kSubdivisions = 16;

	// 長さ
	const float kGridEvery = (kGridHalfWidth * 2.0f) / static_cast<float>(kSubdivisions);


	// 奥から手前への線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivisions; ++xIndex)
	{
		// ワールド座標
		Vector3 worldVertices[2];

		worldVertices[0] =
		{
			-kGridHalfWidth + kGridEvery * static_cast<float>(xIndex),
			0.0f,
			-kGridHalfWidth,
		};

		worldVertices[1] =
		{
			-kGridHalfWidth + kGridEvery * static_cast<float>(xIndex),
			0.0f,
			kGridHalfWidth,
		};


		// スクリーン座標
		Vector3 screenVertices[2] = { 0.0f };

		for (uint32_t i = 0; i < 2; i++)
		{
			// ワールド行列
			Matrix4x4 worldMatrix = MakeAffineMatrix({ 0.0f , 0.0f ,0.0f }, { 0.0f , 0.0f , 0.0f }, worldVertices[i]);

			// ワールド * ビュープロジェクション　行列
			Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, viewProjectionMatrix);

			Vector3 ndcVertex = Transform({ 1.0f , 1.0f , 1.0f }, worldViewProjectionMatrix);

			screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		}

		// 中心点は黒線
		if (xIndex == kSubdivisions / 2)
		{
			Novice::DrawLine
			(
				static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y),
				static_cast<int>(screenVertices[1].x), static_cast<int>(screenVertices[1].y),
				0x000000FF
			);
		}
		else
		{
			// その他はグレー

			Novice::DrawLine
			(
				static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y),
				static_cast<int>(screenVertices[1].x), static_cast<int>(screenVertices[1].y),
				0x999999FF
			);
		}
	}


	// 左から右への線を順々に引いていく
	for (uint32_t zIndex = 0; zIndex <= kSubdivisions; ++zIndex)
	{
		// ワールド座標
		Vector3 worldVertices[2];

		worldVertices[0] =
		{
			-kGridHalfWidth,
			0.0f,
			-kGridHalfWidth + kGridEvery * static_cast<float>(zIndex),
		};

		worldVertices[1] =
		{
			kGridHalfWidth,
			0.0f,
			-kGridHalfWidth + kGridEvery * static_cast<float>(zIndex),
		};


		// スクリーン座標
		Vector3 screenVertices[2] = { 0.0f };

		for (uint32_t i = 0; i < 2; i++)
		{
			// ワールド行列
			Matrix4x4 worldMatrix = MakeAffineMatrix({ 0.0f , 0.0f ,0.0f }, { 0.0f , 0.0f , 0.0f }, worldVertices[i]);

			// ワールド * ビュープロジェクション　行列
			Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, viewProjectionMatrix);

			Vector3 ndcVertex = Transform({ 1.0f , 1.0f , 1.0f }, worldViewProjectionMatrix);

			screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		}

		// 中心は黒線
		if (zIndex == kSubdivisions / 2)
		{
			Novice::DrawLine
			(
				static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y),
				static_cast<int>(screenVertices[1].x), static_cast<int>(screenVertices[1].y),
				0x000000FF
			);
		} 
		else
		{
			// その他はグレー

			Novice::DrawLine
			(
				static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y),
				static_cast<int>(screenVertices[1].x), static_cast<int>(screenVertices[1].y),
				0x999999FF
			);
		}
	}
}

/// <summary>
/// 平面を描画する
/// </summary>
/// <param name="plane">平面</param>
/// <param name="viewProjectionMatrix">ビュー * 透視投影　行列</param>
/// <param name="viewportMatrix">ビューポート変換行列</param>
/// <param name="color">色</param>
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	// 平面の中心点
	Vector3 center = Multiply(plane.distance, plane.normal);

	// 垂直ベクトル
	Vector3 perpendiculers[4];

	// 1. 法線と垂直なベクトル
	perpendiculers[0] = Normalize(Perpendiculer(plane.normal));

	// 2. 1の逆ベクトル
	perpendiculers[1] = { -perpendiculers[0].x ,-perpendiculers[0].y , -perpendiculers[0].z };

	// 3. 1と法線のクロス積
	perpendiculers[2] = Cross(plane.normal, perpendiculers[0]);

	// 4. 3の逆ベクトル
	perpendiculers[3] = { -perpendiculers[2].x , -perpendiculers[2].y , -perpendiculers[2].z };


	// 点
	Vector3 points[4];

	for (uint32_t index = 0; index < 4; index++)
	{
		Vector3 extend = Multiply(2.0f, perpendiculers[index]);
		Vector3 point = Add(center, extend);
		points[index] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);
	}

	Novice::DrawLine
	(
		static_cast<int>(points[0].x), static_cast<int>(points[0].y),
		static_cast<int>(points[3].x), static_cast<int>(points[3].y),
		color
	);

	Novice::DrawLine
	(
		static_cast<int>(points[3].x), static_cast<int>(points[3].y),
		static_cast<int>(points[1].x), static_cast<int>(points[1].y),
		color
	);

	Novice::DrawLine
	(
		static_cast<int>(points[1].x), static_cast<int>(points[1].y),
		static_cast<int>(points[2].x), static_cast<int>(points[2].y),
		color
	);

	Novice::DrawLine
	(
		static_cast<int>(points[2].x), static_cast<int>(points[2].y),
		static_cast<int>(points[0].x), static_cast<int>(points[0].y),
		color
	);
}

/// <summary>
/// 線分を描画する
/// </summary>
/// <param name="segment">線分</param>
/// <param name="viewProjectionMatrix">ビュー * 透視投影　行列</param>
/// <param name="viewportMatrix">ビューポート変換行列</param>
/// <param name="color">色</param>
void DrawSegment(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	// 始点
	Vector3 start = Transform(Transform(segment.origin, viewProjectionMatrix), viewportMatrix);

	// 終点
	Vector3 end = Transform(Transform(Add(segment.origin, segment.diff), viewProjectionMatrix), viewportMatrix);

	Novice::DrawLine
	(
		static_cast<int>(start.x), static_cast<int>(start.y),
		static_cast<int>(end.x), static_cast<int>(end.y),
		color
	);
}


/// <summary>
/// 直線を描画する
/// </summary>
/// <param name="line">直線</param>
/// <param name="viewProjectionMatrix">ビュー * 透視投影　行列</param>
/// <param name="viewportMatrix">ビューポート変換行列</param>
/// <param name="color">色</param>
void DrawLine(const Line& line, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	// 始点
	Vector3 start = Transform(Transform(line.origin, viewProjectionMatrix), viewportMatrix);
	Sphere startSphere = { line.origin , 0.01f };

	// 終点
	Vector3 end = Transform(Transform(Add(line.origin, line.diff), viewProjectionMatrix), viewportMatrix);
	Sphere endSphere = { Add(line.origin , line.diff) , 0.01f};

	Novice::DrawLine
	(
		static_cast<int>(start.x), static_cast<int>(start.y),
		static_cast<int>(end.x), static_cast<int>(end.y),
		color
	);

	DrawSphere(startSphere, viewProjectionMatrix, viewportMatrix, color);
	DrawSphere(endSphere, viewProjectionMatrix, viewportMatrix, color);
}


/// <summary>
/// 半直線を描画する
/// </summary>
/// <param name="ray">半直線</param>
/// <param name="viewProjectionMatrix">ビュー * 透視投影　行列</param>
/// <param name="viewportMatrix">ビューポート変換行列</param>
/// <param name="color">色</param>
void DrawRay(const Ray& ray, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	// 始点
	Vector3 start = Transform(Transform(ray.origin, viewProjectionMatrix), viewportMatrix);
	Sphere startSphere = { ray.origin , 0.01f };

	// 終点
	Vector3 end = Transform(Transform(Add(ray.origin, ray.diff), viewProjectionMatrix), viewportMatrix);

	Novice::DrawLine
	(
		static_cast<int>(start.x), static_cast<int>(start.y),
		static_cast<int>(end.x), static_cast<int>(end.y),
		color
	);

	DrawSphere(startSphere, viewProjectionMatrix, viewportMatrix, color);
}

/// <summary>
/// 三角形を描画する
/// </summary>
/// <param name="triangle">三角形</param>
/// <param name="viewProjectionMatrix">ビュー * 透視投影　行列</param>
/// <param name="viewportMatrix">ビューポート変換行列</param>
/// <param name="color">色</param>
void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	// スクリーン座標
	Vector3 screenVertices[3];

	for (uint32_t i = 0; i < 3; i++)
	{
		screenVertices[i] = Transform(Transform(triangle.vertices[i], viewProjectionMatrix), viewportMatrix);
	}

	Novice::DrawTriangle
	(
		static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y),
		static_cast<int>(screenVertices[1].x), static_cast<int>(screenVertices[1].y),
		static_cast<int>(screenVertices[2].x), static_cast<int>(screenVertices[2].y),
		color, kFillModeWireFrame
	);
}