#pragma once

#include <DirectXMath.h>
#include "Direct3D.h"
#include"Texture.h"
#include<vector>

using namespace DirectX;


class Sprite
{
//�R���X�^���g�o�b�t�@
struct CONSTANT_BUFFER
{
	XMMATRIX	matW;
};

//���_���
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
};

protected:
	
	std::vector<VERTEX> vertices_;
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	
	std::vector<int>index_;
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
	Texture* pTexture_;

public:
	Sprite();
	~Sprite();
	HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix);
	void Release();
private:

	virtual void InitVertexData();
	HRESULT CreateVertexBuffer();

	virtual void InitIndexData();
	HRESULT CreateIndexBuffer();

	HRESULT CreateConstantBuffer();

	HRESULT LoadTexture();

	void PassDataToCB(DirectX::XMMATRIX& worldMatrix);
	
	void SetBufferToPipeline();
};