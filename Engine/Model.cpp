#include "Model.h"
#include"Direct3D.h"
namespace Model
{
	std::vector<ModelData*>modelList;
}

int Model::Load(std::string _filename)
{
	ModelData* pData = new ModelData;
	pData->filename_ = _filename;
	pData->fbx_ = nullptr;
	for (auto e : modelList) {
		if (e->filename_ == _filename)
			pData->fbx_ = e->fbx_;
		break;
	}

	if (pData->fbx_ == nullptr){
	pData->fbx_ = new Fbx;
	pData->fbx_->Load(_filename);
	}
	modelList.push_back(pData);
	return modelList.size() - 1;
}

void Model::SetTransform(int _hModel, Transform _transform)
{
	modelList[_hModel]->transform_ = _transform;
}

void Model::Draw(int _hModel)
{	
	modelList[_hModel]->fbx_->Draw(modelList[_hModel]->transform_);
}

void Model::RayCast(int _hModel, RayCastData& rayData)
{
	//0モデルのトランスフォームをcal
	modelList[_hModel]->transform_.Calclation();
	XMMATRIX wInv = XMMatrixInverse(nullptr, modelList[_hModel]->transform_.GetWorldMatrix());
	//1ワールド行列の逆
	
	//2レイの通過点を求めるモデル空間でのレイの方向ベクトルをもとめる
	XMVECTOR vpass{ rayData.start.x + rayData.dir.x,
					rayData.start.y + rayData.dir.y ,
					rayData.start.z + rayData.dir.z ,
					rayData.start.w + rayData.dir.w };
	//3raydata.startをモデル空間に変換(1をかける)
	XMVECTOR vstart = XMLoadFloat4(&rayData.start);
	vstart = XMVector3TransformCoord(vstart, wInv); //tarnsformcoordはw要素を無視してくれるらしい
	XMStoreFloat4(&rayData.start, vstart);
	//4視点から方向ベクトルをちょい伸ばした先 通過点に１をかける
	vpass = XMVector3TransformCoord(vstart, wInv);
	//5raydataを3から4に向かうベクトルにする(引き算)
	vpass = vpass - vstart;

	XMStoreFloat4(&rayData.dir, vpass);
	//指定したモデル番号のFBXにレイ
	modelList[_hModel]->fbx_->RayCast(rayData);
}

void Model::Release()
{
	bool isReferrd=false;//参照されてる？
	for (int i = 0;i<modelList.size();i++)
	{
		for (int j = i + 1; j < modelList.size(); j++)
		{
			if (modelList[i]->fbx_ == modelList[j]->fbx_) {
				isReferrd = true;
				break;
			}
		}
		if (isReferrd == false) {
			SAFE_DELETE(modelList[i]->fbx_);
		}
		SAFE_DELETE(modelList[i]);
	}
}
