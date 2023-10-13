#include "Stage.h"
#include"Engine/SceneManager.h"
#include"Engine/Input.h"
#include"Engine/Model.h"
#include"Engine/Camera.h"
#include "Engine/Direct3D.h"
#include"resource.h"
#include"Engine/Input.h"
#include<fstream>
#include<iostream>
#include <sstream>


const int MaxZ = 1;
const int MinZ = 0;
const XMFLOAT2 Offset = { 0,0 };
int ValueOfChange = 1;

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

	case WM_COMMAND:
		switch (LOWORD(wp)) {
		case IDC_RADIO_UP:
			if (HIWORD(wp) == BN_CLICKED) {
				// ラジオボタン "上げる" がクリックされたときの処理
				ValueOfChange = 1;
			}
			break;
		case IDC_RADIO_DOWN:
			if (HIWORD(wp) == BN_CLICKED) {
				// ラジオボタン "下げる" がクリックされたときの処理
				ValueOfChange = -1;
			}
			break;
		}
		break;
	}
	return FALSE;
}

BOOL Stage::MenuProc2(HWND hMenu, UINT msg, WPARAM wp, LPARAM lp)
{
	//switch (LOWORD(wp))
	//{
	//case ID_FILE_SAVE:
	//	PostQuitMessage(0);
	//	return 0;
	//}
	//		
	return FALSE;
}

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage")
{
	for (int i = 0; i < BLOCK_KINDS; i++)
	{
		hModel_[i] = -1;
	}

	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			table_[x][z].block = BLOCK_DEFAULT;
			table_[x][z].height = 1;
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
	if (!Input::IsMouseButtonDown(0))return;
	
	float w = (float)(Direct3D::scrWidth / 2);
	float h = (float)(Direct3D::scrHeight / 2);
	XMMATRIX vp =
	{
	w, 0, 0, 0,
	0,-h, 0, 0,
	0, 0, 1, 0,
	w, h, 0, 1
	};

	XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
	XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
	XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

	XMFLOAT3 mousePosFront = Input::GetMousePosition();
	mousePosFront.z = 0.0f;
	XMFLOAT3 mousePosBack = Input::GetMousePosition();
	mousePosBack.z = 1.0;

	XMVECTOR vMousePosFront = XMLoadFloat3(&mousePosFront);
	vMousePosFront = XMVector3TransformCoord(vMousePosFront, invVP * invProj * invView);


	XMVECTOR vMousePosBack = XMLoadFloat3(&mousePosBack);
	vMousePosBack = XMVector3TransformCoord(vMousePosBack, invVP * invProj * invView);

	
	for (int x = 0; x < 15; x++) {
		for (int z = 0; z < 15; z++) {
			for (int y = 0; y < table_[x][z].height + 1; y++) {
				RayCastData frontToback;
				frontToback.hit = false;
				XMStoreFloat4(&frontToback.start, vMousePosFront);
				XMStoreFloat4(&frontToback.dir, vMousePosBack - vMousePosFront);
				Transform trans;
				trans.position_.x = x;
				trans.position_.y = y;
				trans.position_.z = z;
				Model::SetTransform(hModel_[0], trans);
				Model::RayCast(hModel_[0], frontToback);

				if (frontToback.hit) {
					table_[x][z].height += ValueOfChange;
				}
			}
		}
	}	
}

void Stage::Draw()
{
	Transform BlockTrans;//Transform型の変数を作る
	//Transform型は、位置向き大きさなどを扱う型
	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			for (int y = 0; y < table_[x][z].height; y++)
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

void Stage::SaveBlockData()
{
	char fileName1[MAX_PATH] = "無題.map";
	std::string buffer;
	OPENFILENAME ofn;
	std::stringstream oss;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrFilter = TEXT("マップデータ(*.map)\0*.map\0");
	ofn.lpstrFile = fileName1;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = TEXT("map");
	ofn.lpstrDefExt;
	BOOL selFile = GetSaveFileName(&ofn);

	if (selFile == FALSE)return;
	std::ofstream outputFile(fileName1);

	

	for (int x = 0; x < XSIZE; x++)
	{
		for (int z = 0; z < ZSIZE; z++)
		{
			oss<< table_[x][z].height;
		}
	}
	
	outputFile << oss.str();
	outputFile.close();
	//fucking save mode 
	//i cant follow you,
	//good bye fucking file data,table data ,and Stage data.
}