#include "Player.h"
#include"Engine/Fbx.h"
#include"Engine/Input.h"
#include"TestObj.h"
#include"Engine/Model.h"
//�R���X�g���N�^
Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), pFbx(nullptr)
{
}

//������
void Player::Initialize()
{

	pFbx = new Fbx;

	hModel_ = Model::Load("Assets/odden.fbx");
	
	/*GameObject* pCo2 = Instantiate<TestObj>(this);
	pCo2->SetPosition(XMFLOAT3(2,1,0));
	GameObject * pkasu = Instantiate<TestObj>(this);
	pkasu->SetPosition(XMFLOAT3(-2, 1, 0));*/
}

//�X�V
void Player::Update()
{
	/*if (Input::IsKey(DIK_L))
	{
		KillMe();
	}*/

	transform_.rotate_.y++;

	if (Input::IsKey(DIK_A))
	{
		transform_.position_.x -= 0.1f;
	}
	if (Input::IsKey(DIK_D))
	{
		transform_.position_.x += 0.1f;
	}
	if (Input::IsKeyDown(DIK_SPACE))
	{
		GameObject* pBullet =Instantiate<TestObj>(pParent_);
		pBullet->SetPosition(transform_.position_);
	}

}

//�`��
void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Player::Release()
{
	//pFbx->Release();
	//SAFE_DELETE(pFbx);
}