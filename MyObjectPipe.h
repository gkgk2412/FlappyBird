#pragma once

#include "MySprite.h"
#include <stdio.h>

#define		MAX_ANI		6
#define MAX_ANI_FRAME	12
#define MAX_PIPE		6

class CMyPipeSprite : public CMySprite
{
protected:
	unsigned char m_maxAni; // 총 애니메이션 개수
	unsigned short m_nFrame;
	float m_interval;

	int m_infoFrame[MAX_ANI];
	unsigned char m_aniType;

	float m_fDuration[MAX_ANI][MAX_ANI_FRAME];

public:

	RECT m_rcCollision[6];

	RECT m_rcFrame[MAX_ANI][MAX_ANI_FRAME];
	int left, top, width, height;
	float bottomCol, leftCol, rightCol;

	CMyPipeSprite();
	virtual ~CMyPipeSprite();
	float positionX[MAX_PIPE] = { 200.0f, 480.0f, 670.0f, 320.0f, 510.0f, 800.0f };

	void Move(DWORD deltaTime, float speed)
	{
		for(int i = 0 ; i < MAX_PIPE; ++i)
			positionX[i] -= (speed * deltaTime / 1000);
	}

	void Create(LPDIRECT3DDEVICE9 pDevice, char* filename);
	void OnDraw(float m_Y, int selection);
	void OnUpdate(float time, float m_Y, int selection);
};

