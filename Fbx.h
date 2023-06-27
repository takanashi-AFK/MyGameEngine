#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include"Direct3D.h"
#include"Camera.h"

class Texture;

#pragma comment(lib, "LibFbxSDK-Md.lib")
#pragma comment(lib, "LibXml2-Md.lib")
#pragma comment(lib, "zlib-Md.lib")



class Fbx
{
	//�}�e���A��
	struct MATERIAL
	{
		Texture* pTexture;
	};

	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
	};

	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	};
	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S���� ��������vertex*3�ɂȂ�ł��傤
	int materialCount_;	//�}�e���A���̌�


	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer** pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	MATERIAL* pMaterialList_;




public:

	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();
	void	InitVertex(fbxsdk::FbxMesh* mesh);
	void	InitIndex(fbxsdk::FbxMesh* mesh);
	void	InitMaterial(fbxsdk::FbxNode* pNode);
	void	IntConstantBuffer();

	void	SetBufferToPipeline();
	void	PassDataToCB(Transform transform);

	HRESULT LoadTexture();


};