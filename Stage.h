#pragma once
#include "Engine/GameObject.h"
#include<string>
#include"windows.h"
const int BLOCK_KINDS{ 5 };
const int XSIZE{ 15 };
const int ZSIZE{ 15 };
class Stage : public GameObject
{
private:
	int hModel_[BLOCK_KINDS];
	int a = 1;
	enum BLOCKTYPE
	{
		BLOCK_DEFAULT = 0, 
		BLOCK_BRICK, 
		BLOCK_GRASS,
		BLOCK_SAND,
		BLOCK_WATER
	};

	struct {
		BLOCKTYPE block = BLOCK_DEFAULT;
		int height = 1;
	}table_[XSIZE][ZSIZE];


	int mode_;//0:上げる :1下げる 2:種類変える
	int select_;//種類

public:
	BOOL DialogProc2(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
	BOOL MenuProc2(HWND hMenu, UINT msg, WPARAM wp, LPARAM lp);
	//コンストラクタ
	//引数：parent 
	Stage(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetBlockType(int _x,int _z ,BLOCKTYPE _type);

	void SetBlockHeight(int _x, int _z, int _height);

	void SaveBlockData();

	
};