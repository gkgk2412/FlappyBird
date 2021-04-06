#pragma once

#include <d3d9.h>
#include <d3dx9.h>


#define  MAX_SPRITE 12

class CMySprite
{
protected:
	LPDIRECT3DTEXTURE9 m_pDonutTexture[MAX_SPRITE];
	LPD3DXSPRITE       m_pDonutSprite[MAX_SPRITE];

private:
	


public:	   
	CMySprite();
	virtual ~CMySprite();

	virtual void Create(LPDIRECT3DDEVICE9 pDevice, char *filename, int width, int height);
	virtual void Create_floor(LPDIRECT3DDEVICE9 pDevice, char *filename);
	virtual void Create_Back(LPDIRECT3DDEVICE9 pDevice, char *filename);
	virtual void Create_Pipe(LPDIRECT3DDEVICE9 pDevice, char *filename);
	virtual void OnDraw() {}
	virtual void OnUpdate(float time) {}
};

