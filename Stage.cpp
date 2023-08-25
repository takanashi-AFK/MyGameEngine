#include "Stage.h"
#include"Engine/SceneManager.h"
#include"Engine/Input.h"
#include"Engine/Model.h"
#include"Engine/Camera.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage")
{
}

void Stage::Initialize()
{
	hModel_ = Model::Load("Assets/BoxDefault.fbx");
}

void Stage::Update()
{
	
	
}

void Stage::Draw()
{

	Transform BlockTrans;//TransformŒ^‚Ì•Ï”‚ğì‚é
	//TransformŒ^‚ÍAˆÊ’uŒü‚«‘å‚«‚³‚È‚Ç‚ğˆµ‚¤Œ^

	for (int Width_ = 0; Width_ < 15; Width_++)
	{
		for (int Depth_ = 0; Depth_ < 15; Depth_++)
		{
			BlockTrans.position_.x = Width_;
			BlockTrans.position_.z = Depth_;

			Model::SetTransform(hModel_, BlockTrans);
			Model::Draw(hModel_);

		}
	}
}

void Stage::Release()
{
}
