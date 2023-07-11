#include "TestObj.h"
#include"Engine/Fbx.h"
//コンストラクタ
TestObj::TestObj(GameObject* parent)
	: GameObject(parent, "TestObj"), pFbx1(nullptr)
{
}

//初期化
void TestObj::Initialize()
{
	pFbx1 = new Fbx;

	pFbx1->Load("Assets/F_Wall.fbx");
	this->transform_.position_.x = 2;
}

//更新
void TestObj::Update()
{
}

//描画
void TestObj::Draw()
{
	pFbx1->Draw(transform_);
}

//開放
void TestObj::Release()
{
	pFbx1->Release();
	SAFE_DELETE(pFbx1);
}