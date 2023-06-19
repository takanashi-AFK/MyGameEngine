#pragma once

#include <DirectXMath.h>
#include "Direct3D.h"
#include"Texture.h"
#include<vector>
#include<d3d11.h>


using namespace DirectX;


class Sprite
{
//コンスタントバッファ
struct CONSTANT_BUFFER
{
	XMMATRIX	matW;
};

//頂点情報
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
};

protected:
	
	std::vector<VERTEX> vertices_;
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	TexMetadata image_;
	
	std::vector<int>index_;
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	Texture* pTexture_;

public:
	Sprite();
	~Sprite();
	HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix);
	void Release();
private:

	virtual void InitVertexData(int winH,int winW);
	HRESULT CreateVertexBuffer();

	virtual void InitIndexData();
	HRESULT CreateIndexBuffer();

	HRESULT CreateConstantBuffer();

	HRESULT LoadTexture();

	void PassDataToCB(DirectX::XMMATRIX& worldMatrix);
	
	void SetBufferToPipeline();
};