#include "TestObj.h"
#include"Engine/Fbx.h"
#include"Engine/Input.h"
//コンストラクタ
TestObj::TestObj(GameObject* parent)
	: GameObject(parent, "TestObj"), pFbx1(nullptr)
{
}

//初期化
void TestObj::Initialize()
{
	pFbx1 = new Fbx;

	pFbx1->Load("Assets/odden.fbx");
	transform_.scale_.x = 0.2f;
	transform_.scale_.y = 0.2f;
	transform_.scale_.z = 0.2f;

}

//更新
void TestObj::Update()
{
	if (Input::IsKey(DIK_K))
	{
		KillMe();
	}
}

//描画
void TestObj::Draw()
{
	pFbx1->Draw(transform_);
}

//開放
void TestObj::Release()
{

}