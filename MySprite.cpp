#include "MySprite.h"



CMySprite::CMySprite()
{
	for(int i = 0; i < MAX_SPRITE; ++i)
	{
		m_pDonutTexture[i] = NULL;
		m_pDonutSprite[i] = NULL;
	}
}


CMySprite::~CMySprite()
{

	for (int i = 0; i < MAX_SPRITE; ++i)
	{
		if (m_pDonutSprite[i] != NULL)
			m_pDonutSprite[i]->Release();

		if (m_pDonutTexture[i] != NULL)
			m_pDonutTexture[i]->Release();
	}
}

//배경
void CMySprite::Create_Back(LPDIRECT3DDEVICE9 pDevice, char* filename)
{
	D3DXIMAGE_INFO d3dxImageInfo;

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		640, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		480, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[0]);

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		640, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		480, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[10]);

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		640, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		480, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[11]);

	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	D3DXCreateSprite(pDevice, &m_pDonutSprite[0]);
	D3DXCreateSprite(pDevice, &m_pDonutSprite[10]);
	D3DXCreateSprite(pDevice, &m_pDonutSprite[11]);
}

//캐릭터
void CMySprite::Create(LPDIRECT3DDEVICE9 pDevice, char *filename, int width, int height)
{
	D3DXIMAGE_INFO d3dxImageInfo;

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		width, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		height, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(0.0f,0.0f, 0.0f, 0.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[1]);


	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	D3DXCreateSprite(pDevice, &m_pDonutSprite[1]);
}

//바닥
void CMySprite::Create_floor(LPDIRECT3DDEVICE9 pDevice, char *filename)
{
	D3DXIMAGE_INFO d3dxImageInfo;

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		336, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		112, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[2]);

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		336, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		112, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[3]);

	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	D3DXCreateSprite(pDevice, &m_pDonutSprite[2]);
	D3DXCreateSprite(pDevice, &m_pDonutSprite[3]);
}

//파이프
void CMySprite::Create_Pipe(LPDIRECT3DDEVICE9 pDevice, char* filename)
{
	D3DXIMAGE_INFO d3dxImageInfo;

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		80, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		100, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[4]);

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		80, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		100, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[5]);

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		80, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		100, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[6]);

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		80, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		100, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[7]);

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		80, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		100, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[8]);

	D3DXCreateTextureFromFileEx(pDevice,
		filename,
		80, // I had to set width manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		100, // I had to set height manually. D3DPOOL_DEFAULT works for textures but causes problems for D3DXSPRITE.
		1,   // Don't create mip-maps when you plan on using D3DXSPRITE. It throws off the pixel math for sprite animation.
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f),
		&d3dxImageInfo,
		NULL,
		&m_pDonutTexture[9]);

	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	D3DXCreateSprite(pDevice, &m_pDonutSprite[4]);
	D3DXCreateSprite(pDevice, &m_pDonutSprite[5]);
	D3DXCreateSprite(pDevice, &m_pDonutSprite[6]);
	D3DXCreateSprite(pDevice, &m_pDonutSprite[7]);
	D3DXCreateSprite(pDevice, &m_pDonutSprite[8]);
	D3DXCreateSprite(pDevice, &m_pDonutSprite[9]);
}



