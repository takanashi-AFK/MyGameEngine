#include "Stage.h"
#include"Engine/SceneManager.h"
#include"Engine/Input.h"
#include"Engine/Model.h"
#include"Engine/Camera.h"
#include "Engine/Direct3D.h"
#include"resource.h"
#include"Engine/Input.h"

const int MaxZ = 1;
const int MinZ = 0;
const XMFLOAT2 Offset = { 0,0 };

BOOL Stage::DialogProc2(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		
		SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING,0,(LPARAM)"Box_Default");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING,0,(LPARAM)"Box_BRICK");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING,0,(LPARAM)"Box_GRASS");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING,0,(LPARAM)"Box_SAND");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING,0,(LPARAM)"Box_WATER");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, 0, 0);

		return TRUE;
	}
	return FALSE;
}

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

	float w = (float)(Direct3D::scrWidth / 2);
	float h = (float)(Direct3D::scrHeight / 2);
	XMMATRIX vp =
	{
		w,0,0,0,
		0,-h,0,0,
		0,0,MaxZ-MinZ,0,
		Offset.x+w,Offset.y + h,MinZ,1
	};

	XMMATRIX invVP = XMMatrixInverse(nullptr,vp)
	XMMATRIX invProj = 

	XMMATRIX invView=
	XMFLOAT3 mousePosFront= 

}

void Stage::Draw()
{

	Transform BlockTrans;//Transformå^ÇÃïœêîÇçÏÇÈ
	//Transformå^ÇÕÅAà íuå¸Ç´ëÂÇ´Ç≥Ç»Ç«ÇàµÇ§å^
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

