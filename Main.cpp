//インクルード
#include <Windows.h>
#include "Direct3D.h"
#include"Quad.h"
#include"Camera.h"
#include"Sprite.h"
#include"Dice.h"
#include"Transform.h"
//定数宣言
const char* WIN_CLASS_NAME = "SampleGame";  //ウィンドウクラス名
const int WINDOW_WIDTH = 800;  //ウィンドウの幅
const int WINDOW_HEIGHT = 600; //ウィンドウの高さ

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウクラス（設計図）を作成
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);             //この構造体のサイズ
	wc.hInstance = hInstance;                   //インスタンスハンドル
	wc.lpszClassName = WIN_CLASS_NAME;          //ウィンドウクラス名
	wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
	wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //アイコン
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //小さいアイコン
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル
	wc.lpszMenuName = NULL;                     //メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）
	RegisterClassEx(&wc); //クラスを登録

	//ウィンドウサイズの計算
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;     //ウィンドウ幅
	int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ

	//ウィンドウを作成
	HWND hWnd = CreateWindow(
		"SampleGame",         //ウィンドウクラス名
		"サンプルゲーム",     //タイトルバーに表示する内容
		WS_OVERLAPPEDWINDOW, //スタイル（普通のウィンドウ）
		CW_USEDEFAULT,       //表示位置左（おまかせ）
		CW_USEDEFAULT,       //表示位置上（おまかせ）
		winW,                 //ウィンドウ幅
		winH,                 //ウィンドウ高さ
		NULL,                //親ウインドウ（なし）
		NULL,                //メニュー（なし）
		hInstance,           //インスタンス
		NULL                 //パラメータ（なし）
	);

	//ウィンドウを表示
	ShowWindow(hWnd, nCmdShow);

	HRESULT hr;
	//Direct3D初期化

	hr = Direct3D::Initialize(winW, winH, hWnd);	
	if (FAILED(hr))return hr;
	Camera::Initialize();
	Camera::SetTarget(XMFLOAT3{ 0,2,-5});
	Dice* d = new Dice;
	hr = d->Initialize();

	Sprite* s = new Sprite;
	hr = s->Initialize();

	if (FAILED(hr))return hr;

	//メッセージループ（何か起きるのを待つ）
	int i=0;
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//メッセージあり
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//メッセージなし
		else
		{
			Camera::Update();
			//ゲームの処理
			Direct3D::BeginDraw();

			//描画処理
			XMMATRIX mat = XMMatrixRotationY(XMConvertToRadians(45));
			//Y軸で45°回転
			XMMATRIX MoveMat = { 1,0,0,0,
							 	 0,1,0,0,
								 0,0,1,0,
								 4,0,0,1 };
			//XMMATRIX ZoomMat = XMMatrixScaling(1, 3, 1);

			XMMATRIX ZoomMat = { 1,0,0,0,
								 0,3,0,0,
								 0,0,1,0,
								 0,0,0,1 };
		//	XMMATRIX OKOKwakatta = XMMatrixTranslation(4, 0, 0) * XMMatrixScaling(1, 3, 1);
			XMMATRIX MoveZoomMat = { 1,0,0,0,
									 0,3,0,0,
									 0,0,1,0,
									 4,0,0,1 };

			XMMATRIX ZrotXmovMat = XMMatrixTranslation(3, 0, 0) *  XMMatrixScaling(1, 3, 1) * XMMatrixRotationZ(XMConvertToRadians(-45));

			// Quadの描画処理
			static float angle = 0;
			angle += 0.05;

			// 各面の回転行列を作成
			XMMATRIX rotateMatX = XMMatrixRotationX(XMConvertToRadians(angle));
			XMMATRIX rotateMatY = XMMatrixRotationY(XMConvertToRadians(angle));
			XMMATRIX rotateMatZ = XMMatrixRotationZ(XMConvertToRadians(angle));

			// 各面を回転させる
			XMMATRIX matFront = rotateMatX * rotateMatY;
			XMMATRIX matBack = rotateMatX * rotateMatY;
			XMMATRIX matTop = rotateMatX * rotateMatZ;
			XMMATRIX matBottom = rotateMatX * rotateMatZ;
			XMMATRIX matLeft = rotateMatY * rotateMatZ;
			XMMATRIX matRight = rotateMatY * rotateMatZ;




			// 各面の回転行列を組み合わせる
			XMMATRIX gebo = matFront * matBack * matTop * matBottom * matLeft * matRight;
			XMMATRIX guruguru = XMMatrixRotationY(XMConvertToRadians(i/12));

			Transform dicetransform;
			dicetransform.position_.y = 3.0f;
			dicetransform.rotate_.y = angle;
			d->Draw(dicetransform);

			Transform spriteTransform;
			spriteTransform.scale_.x = 512.0f / 800.0f;
			spriteTransform.scale_.y = 256.0f / 600.0f;
			s->Draw(spriteTransform);
			i++;
			Direct3D::EndDraw();
		}
	}

	Direct3D::Release();
	SAFE_RELEASE(s);
	SAFE_RELEASE(d);
	return 0;
}

//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);  //プログラム終了
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}