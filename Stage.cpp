#include "Stage.h"
#include"Engine/SceneManager.h"
#include"Engine/Input.h"
#include"Engine/Model.h"
#include"Engine/Camera.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage")
{
	for (int i = 0; i < BLOCK_KINDS; i++)
	{
		hModel_[i] = 0;
	}

	for (int x = 0; x < XSIZE;  x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			table_[x][z] = 0;
		}
	}
	

	
}

void Stage::Initialize()
{
	std::string modelName[] =
	{
		"BoxDefault.fbx",
		"BoxBrick.fbx",
		"BoxGrass.fbx",
		"BoxSand.fbx",
		"BoxWater.fbx"
	};
	std::string fNameBase = "Assets/";
	for (int i = 0; i < BLOCK_KINDS; i++)
	{
	hModel_[i] = Model::Load(fNameBase+modelName[i]);
	assert(hModel_[i] >= 0);
	}

	for (int z = 0; z < ZSIZE; z++)
	{
		for (int x = 0; x < XSIZE; x++)
		{
			table_[x][z] = (x+z)%5;
		}
	}
}

void Stage::Update()
{
	
	
}

void Stage::Draw()
{

	Transform BlockTrans;//TransformŒ^‚Ì•Ï”‚ðì‚é
	//TransformŒ^‚ÍAˆÊ’uŒü‚«‘å‚«‚³‚È‚Ç‚ðˆµ‚¤Œ^
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			
			BlockTrans.position_.x = x;
			BlockTrans.position_.z = z;

			Model::SetTransform(table_[x][z], BlockTrans);
			Model::Draw(table_[x][z]);

		}
	}
}

void Stage::Release()
{
}
