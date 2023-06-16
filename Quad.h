#pragma once

#include <DirectXMath.h>
#include "Direct3D.h"
#include"Texture.h"

using namespace DirectX;

//コンスタントバッファ
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
};

//頂点情報
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
	XMVECTOR normal;
};

class Quad
{
protected:
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	Texture* pTexture_;

public:
	Quad();
	~Quad();
	HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix);
	void Release();
	HRESULT BufferMaker(VERTEX* _v, int* _index,int _vNum,int _iNum);
	void BufferSetter(XMMATRIX& worldMatrix);
};