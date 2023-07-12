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
	
	GameObject* pCo2 = Instantiate<TestObj>(this);
	pCo2->SetPosition(XMFLOAT3(2,1,0));
	GameObject * pkasu = Instantiate<TestObj>(this);
	pkasu->SetPosition(XMFLOAT3(-2, 1, 0));
}

//�X�V
void Player::Update()
{
	if (Input::IsKey(DIK_L))
	{
		KillMe();
	}

	transform_.rotate_.y++;
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