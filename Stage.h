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


	int mode_;//0:�グ�� :1������ 2:��ޕς���
	int select_;//���

public:
	BOOL DialogProc2(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);
	BOOL MenuProc2(HWND hMenu, UINT msg, WPARAM wp, LPARAM lp);
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

	void SetBlockType(int _x,int _z ,BLOCKTYPE _type);

	void SetBlockHeight(int _x, int _z, int _height);

	void SaveBlockData();

	
};