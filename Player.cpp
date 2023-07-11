#include "Player.h"
#include"Engine/Fbx.h"
#include"Engine/Input.h"
#include"TestObj.h"
//�R���X�g���N�^
Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), pFbx(nullptr)
{
}

//������
void Player::Initialize()
{
	pFbx = new Fbx;

	pFbx->Load("Assets/odden.fbx");
	Instantiate<TestObj>(this);
}

//�X�V
void Player::Update()
{
	if (Input::IsKeyUp(DIK_L))
	{
		KillMe();
	}
}

//�`��
void Player::Draw()
{
	pFbx->Draw(transform_);
}

//�J��
void Player::Release()
{
	pFbx->Release();
	SAFE_DELETE(pFbx);
}