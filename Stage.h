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
	//�R���X�g���N�^
	//�����Fparent 
	Stage(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};