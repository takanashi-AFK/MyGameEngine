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
		hModel_[i] = -1;
	}

	for (int z = 0; z < ZSIZE; z++)
	{
		for (int x = 0; x < XSIZE; x++)
		{
			SetBlockType(x,z, BLOCK_WATER);
			SetBlockHeight(x, z, x % 4+z%4);
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
}

void Stage::Update()
{
	
	if (Input::IsKeyDown(DIK_P))
	{
		SetBlockHeight(7, 7, ++a);
	}
	
}

void Stage::Draw()
{

	Transform BlockTrans;//TransformŒ^‚Ì•Ï”‚ğì‚é
	//TransformŒ^‚ÍAˆÊ’uŒü‚«‘å‚«‚³‚È‚Ç‚ğˆµ‚¤Œ^
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			for (int y = 0; y < table_[x][z].height+1; y++)
			{
			BlockTrans.position_ = { (float)x,(float)y,(float)z};
			Model::SetTransform(hModel_[table_[x][z].block], BlockTrans);
			Model::Draw(hModel_[table_[x][z].block]);
			}

		}
	}

}

void Stage::Release()
{
}


void Stage::SetBlockType(int _x, int _z, BLOCKTYPE _type)
{
	if (_type <= 5);
	table_[_x][_z].block = _type;
}

void Stage::SetBlockHeight(int _x, int _z, int _height)
{
	table_[_x][_z].height = _height;
}
