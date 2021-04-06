#pragma once

#include "MySprite.h"
#include <stdio.h>

#define		MAX_ANI		6
#define MAX_ANI_FRAME	12

class CMyBackSprite : public CMySprite
{
protected:
	RECT m_rcFrame[MAX_ANI][MAX_ANI_FRAME];
	unsigned char m_maxAni; // 총 애니메이션 개수
	unsigned short m_nFrame;
	float m_interval;

	int m_infoFrame[MAX_ANI];
	unsigned char m_aniType;

	float m_fDuration[MAX_ANI][MAX_ANI_FRAME];

public:
	CMyBackSprite();
	virtual ~CMyBackSprite();

	void Create(LPDIRECT3DDEVICE9 pDevice, char* filename);
	void OnDraw(int selection);
	void OnUpdate(float time, int selection);
};

