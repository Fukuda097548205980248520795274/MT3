#include <Novice.h>
#include "Struct.h"
#include "Const.h"
#include "./Func/Vector/Vector.h"
#include "./Func/Matrix/Matrix.h"

const char kWindowTitle[] = "LE2A_11_フクダソウワ_MT3";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};


	/*---------------
	    変数を作る
	---------------*/

	/*   クロス積   */

	// ベクトル
	Vector3 v1 = { 1.2f , -3.9f , 2.5f };
	Vector3 v2 = { 2.8f , 0.4f , -1.3f };

	// クロス積
	Vector3 cross = Cross(v1, v2);
	

	/*   図形   */

	// 回転
	Vector3 rotate = { 0.0f , 0.0f , 0.0f };

	// 移動
	Vector3 translate = { 0.0f , 0.0f , 0.0f };



	// カメラの位置
	Vector3 cameraPosition = { 0.0f , 0.0f , -10.0f };


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		/*-------------
		    移動操作
		-------------*/

		// Wキーで、奥に移動する
		if (keys[DIK_W])
		{
			translate.z += 0.1f;
		}

		// Sキーで、手前に移動する
		if(keys[DIK_S])
		{
			translate.z -= 0.1f;
		}

		// Aキーで、左に移動する
		if (keys[DIK_A])
		{
			translate.x -= 0.1f;
		}

		// Dキーで、右に移動する
		if (keys[DIK_D])
		{
			translate.x += 0.1f;
		}


		/*   回転   */

		// Y軸回転させる
		rotate.y += 0.02f;

		// 1周したら、Y軸回転を初期化する
		if (rotate.y >= 2.0f * float(M_PI))
		{
			rotate.y = 0.0f;
		}


		/*-------------
		    座標変換
		-------------*/

		// ワールド行列
		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f , 1.0f , 1.0f }, rotate, translate);

		// ビュー行列
		Matrix4x4 viewMatrix = Inverse(MakeAffineMatrix({ 1.0f , 1.0f , 1.0f }, { 0.0f , 0.0f , 0.0f }, cameraPosition));

		// 透視投影行列
		Matrix4x4 projectionMatrix = MakePrespectiveFovMatrix(0.45f, static_cast<float>(kWindowWidth) / static_cast<float>(kWindowHeight), 0.1f, 100.0f);


		// ワールド * ビュー * 透視投影　行列
		Matrix4x4 worldViewProjectionMatrix = Multiply(Multiply(worldMatrix, viewMatrix), projectionMatrix);

		// ビューポート変換行列
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0.0f, 0.0f, static_cast<float>(kWindowWidth), static_cast<float>(kWindowHeight), 0.0f, 1.0f);


		// スクリーン座標の頂点
		Vector3 screenVertices[3] = { 0.0f };

		for (uint32_t i = 0; i < 3; i++)
		{
			Vector3 ndcVertex = Transform(kLocalVertices[i], worldViewProjectionMatrix);
			screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// 三角形
		Novice::DrawTriangle
		(
			static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y),
			static_cast<int>(screenVertices[1].x), static_cast<int>(screenVertices[1].y),
			static_cast<int>(screenVertices[2].x), static_cast<int>(screenVertices[2].y),
			0xFF0000FF, kFillModeSolid
		);

		// クロス積の値
		VectorScreenPrintf(0, 0, cross, " : cross");
		
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
