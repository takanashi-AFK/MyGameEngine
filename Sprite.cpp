#include "Sprite.h"
#include"Camera.h"


Sprite::Sprite() :
	pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr), pTexture_(nullptr),index_(nullptr),vertices_(nullptr)
{
}

Sprite::~Sprite()
{
	Release();
}

HRESULT Sprite::Initialize()
{
	InitVertexData();
	CreateVertexBuffer();
	InitIndexData();
	CreateIndexBuffer();
	CreateConstantBuffer();
	LoadTexture();
	return S_OK;
}

void Sprite::Draw(XMMATRIX& worldMatrix)
{
	PassDataToCB(worldMatrix);
	SetBufferToPipeline();
}

void Sprite::InitVertexData()
{
     vertices_ = new std::vector<VERTEX>
	{
		// 頂点情報
	{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) },
	{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },
	{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) },
	{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },
	};
}
void Sprite::InitIndexData()
{
	index_ = new std::vector<int>
	{
	//インデックス情報
	0,1,2,
	0,2,3
	};
}

HRESULT Sprite::CreateVertexBuffer()
{
	HRESULT hr;
	// 頂点データ用バッファの設定
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * vertices_->size();
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = &vertices_[0];
	hr = Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "頂点バッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}
}

HRESULT Sprite::CreateIndexBuffer()
{
	HRESULT hr;
	// インデックスバッファを生成する
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * index_->size();
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = &index_[0];
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	hr = Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "インデックスバッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}
}

HRESULT Sprite::CreateConstantBuffer()
{
	HRESULT hr;

	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "コンスタントバッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}
}

HRESULT Sprite::LoadTexture()
{
	pTexture_ = new Texture;
	pTexture_->Load("Assets/Dice.png");

	return S_OK;
}

void Sprite::PassDataToCB(DirectX::XMMATRIX& worldMatrix)
{
	D3D11_MAPPED_SUBRESOURCE pdata;
	CONSTANT_BUFFER cb;
	cb.matW = worldMatrix;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る

	//テクスチャとサンプラーをシェーダーへ
	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);
	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);
	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//再開
}

void Sprite::SetBufferToPipeline()
{
	//頂点バッファ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

	Direct3D::pContext_->DrawIndexed(index_->size(), 0, 0);
}


void Sprite::Release()
{
	pTexture_->Release();
	SAFE_RELEASE(pTexture_);
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}

