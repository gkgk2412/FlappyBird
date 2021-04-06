#pragma once

#include "MySprite.h"
#include <stdio.h>

#define		MAX_ANI		6
#define MAX_ANI_FRAME	12

class CMyAnimationSprite : public CMySprite
{
protected:
	RECT m_rcFrame[MAX_ANI][MAX_ANI_FRAME];

	RECT rcCollision;

	unsigned char m_maxAni; // 총 애니메이션 개수
	unsigned short m_nFrame;
	float m_interval;
	int m_infoFrame[MAX_ANI];
	unsigned char m_aniType;

	float m_fDuration[MAX_ANI][MAX_ANI_FRAME];

	//left, right, top, bottom
	int left, width, top, height;

	RECT  m_rcCollision;

public:
	CMyAnimationSprite();
	virtual ~CMyAnimationSprite();

	float m_positionX = 100.0f;
	float m_positionY = 100.0f;

	//void y_MoveDown(DWORD deltaTime, float speed)
	//{
	//	m_positionY += (m_positionY * speed * deltaTime / 1000);
	//}

	void Create(LPDIRECT3DDEVICE9 pDevice, char *filename);
	void OnDraw();
	void OnUpdate(float time);

	BOOL isTrigger(RECT rect);
};

