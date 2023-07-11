#include "Player.h"
#include"Engine/Fbx.h"
#include"Engine/Input.h"
#include"TestObj.h"
//コンストラクタ
Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), pFbx(nullptr)
{
}

//初期化
void Player::Initialize()
{
	pFbx = new Fbx;

	pFbx->Load("Assets/odden.fbx");
	Instantiate<TestObj>(this);
}

//更新
void Player::Update()
{
	if (Input::IsKeyUp(DIK_L))
	{
		KillMe();
	}
}

//描画
void Player::Draw()
{
	pFbx->Draw(transform_);
}

//開放
void Player::Release()
{
	pFbx->Release();
	SAFE_DELETE(pFbx);
}