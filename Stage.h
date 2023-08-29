#pragma once
#include "Engine/GameObject.h"
#include<string>

const int BLOCK_KINDS{ 5 };
const int XSIZE{ 15 };
const int ZSIZE{ 15 };
class Stage : public GameObject
{
private:
	int hModel_[BLOCK_KINDS];
	int table_[XSIZE][ZSIZE];
	enum BLOCKTYPE
	{
		BLOCK_DEFAULT=0,
		BLOCK_BRICK, 
		BLOCK_GRASS,
		BLOCK_SAND,
		BLOCK_WATER
	};
public:
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
};