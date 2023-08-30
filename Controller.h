#pragma once
#include "Engine/GameObject.h"
class Controller : public GameObject
{
private:
	XMFLOAT3 CamPos = { 0,5,-5 };
	XMFLOAT3 CamTarget = { 0,0,0 };
public:
	//コンストラクタ
	//引数：parent 
	Controller(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};