#include "TestObj.h"
#include"Engine/Fbx.h"
//�R���X�g���N�^
TestObj::TestObj(GameObject* parent)
	: GameObject(parent, "TestObj"), pFbx1(nullptr)
{
}

//������
void TestObj::Initialize()
{
	pFbx1 = new Fbx;

	pFbx1->Load("Assets/F_Wall.fbx");
	this->transform_.position_.x = 2;
}

//�X�V
void TestObj::Update()
{
}

//�`��
void TestObj::Draw()
{
	pFbx1->Draw(transform_);
}

//�J��
void TestObj::Release()
{
	pFbx1->Release();
	SAFE_DELETE(pFbx1);
}