#include <Novice.h>
#include "Struct.h"
#include "./Func/Vector/Vector.h"
#include "./Func/Matrix/Matrix.h"

const char kWindowTitle[] = "LE2A_11_フクダソウワ_MT3";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};


	/*---------------
	    変数を作る
	---------------*/

	// 移動
	Vector3 translate = { 4.1f , 2.6f , 0.8f };

	// 平行移動行列
	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);


	// 拡縮
	Vector3 scale = { 1.5f , 5.2f , 7.3f };

	// 拡大縮小行列
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);


	// 座標
	Vector3 point = { 2.3f , 3.8f , 1.4f };

	// 座標変換で使う行列
	Matrix4x4 transformMatrix =
	{
		1.0f , 2.0f , 3.0f , 4.0f ,
		3.0f , 1.0f , 1.0f , 2.0f ,
		1.0f , 4.0f , 2.0f , 3.0f ,
		2.0f , 2.0f , 1.0f , 3.0f
	};

	// 変換した座標
	Vector3 transformed = Transform(point, transformMatrix);


	// 行の高さ
	int rowHeight = 128;
	


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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VectorScreenPrintf(0, 0, transformed, "transformed");
		MatrixScreenPrintf(0, 32, translateMatrix, "translateMatrix");
		MatrixScreenPrintf(0, 32 + rowHeight, scaleMatrix, "scaleMatrix");
		
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
