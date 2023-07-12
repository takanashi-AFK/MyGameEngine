#include "TestObj.h"
#include"Engine/Fbx.h"
#include"Engine/Input.h"
//�R���X�g���N�^
TestObj::TestObj(GameObject* parent)
	: GameObject(parent, "TestObj"), pFbx1(nullptr)
{
}

//������
void TestObj::Initialize()
{
	pFbx1 = new Fbx;

	pFbx1->Load("Assets/odden.fbx");
	transform_.scale_.x = 0.2f;
	transform_.scale_.y = 0.2f;
	transform_.scale_.z = 0.2f;

}

//�X�V
void TestObj::Update()
{
	if (Input::IsKey(DIK_K))
	{
		KillMe();
	}
}

//�`��
void TestObj::Draw()
{
	pFbx1->Draw(transform_);
}

//�J��
void TestObj::Release()
{

}