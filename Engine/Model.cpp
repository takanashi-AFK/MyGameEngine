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
	//0���f���̃g�����X�t�H�[����cal
	modelList[_hModel]->transform_.Calclation();
	XMMATRIX wInv = XMMatrixInverse(nullptr, modelList[_hModel]->transform_.GetWorldMatrix());
	//1���[���h�s��̋t
	
	//2���C�̒ʉߓ_�����߂郂�f����Ԃł̃��C�̕����x�N�g�������Ƃ߂�
	XMVECTOR vpass{ rayData.start.x + rayData.dir.x,
					rayData.start.y + rayData.dir.y ,
					rayData.start.z + rayData.dir.z ,
					rayData.start.w + rayData.dir.w };
	//3raydata.start�����f����Ԃɕϊ�(1��������)
	XMVECTOR vstart = XMLoadFloat4(&rayData.start);
	vstart = XMVector3TransformCoord(vstart, wInv); //tarnsformcoord��w�v�f�𖳎����Ă����炵��
	XMStoreFloat4(&rayData.start, vstart);
	//4���_��������x�N�g�������傢�L�΂����� �ʉߓ_�ɂP��������
	vpass = XMVector3TransformCoord(vstart, wInv);
	//5raydata��3����4�Ɍ������x�N�g���ɂ���(�����Z)
	vpass = vpass - vstart;

	XMStoreFloat4(&rayData.dir, vpass);
	//�w�肵�����f���ԍ���FBX�Ƀ��C
	modelList[_hModel]->fbx_->RayCast(rayData);
}

void Model::Release()
{
	bool isReferrd=false;//�Q�Ƃ���Ă�H
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
