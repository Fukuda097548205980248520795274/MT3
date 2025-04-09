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
				sphere.radius * (std::cos(lat) * std::cos(lon)),
				sphere.radius * std::sin(lat),
				sphere.radius * (std::cos(lat) * std::sin(lon))
			};

			worldVertices[1] =
			{
				sphere.radius * (std::cos(lat + float(M_PI) / static_cast<float>(kSubdivisions)) * std::cos(lon)),
				sphere.radius * std::sin(lat + float(M_PI) / static_cast<float>(kSubdivisions)),
				sphere.radius * (std::cos(lat + float(M_PI) / static_cast<float>(kSubdivisions)) * std::sin(lon))
			};

			worldVertices[2] =
			{
				sphere.radius * (std::cos(lat) * std::cos(lon + 2.0f * float(M_PI) / static_cast<float>(kSubdivisions))),
				sphere.radius * std::sin(lat),
				sphere.radius * (std::cos(lat) * std::sin(lon + 2.0f * float(M_PI) / static_cast<float>(kSubdivisions)))
			};


			// 3頂点のスクリーン座標
			Vector3 screenVertices[3] = { 0.0f };

			for (uint32_t i = 0; i < 3; i++)
			{
				// ワールド行列
				Matrix4x4 worldMatrix = MakeAffineMatrix({ 0.0f , 0.0f ,0.0f }, { 0.0f , 0.0f , 0.0f }, worldVertices[i]);

				// ワールド * ビュープロジェクション　行列
				Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, viewProjectionMatrix);

				Vector3 ndcVertex = Transform({1.0f , 1.0f , 1.0f}, worldViewProjectionMatrix);

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