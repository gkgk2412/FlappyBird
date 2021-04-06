#include "MyFloor.h"
#include <ctime>  

CMyFloorSprite::CMyFloorSprite()
{
	m_nFrame = 0;
	m_interval = 0.0f;
	m_aniType = 0;
}


CMyFloorSprite::~CMyFloorSprite()
{
}

void CMyFloorSprite::Create(LPDIRECT3DDEVICE9 pDevice, char *filename)
{
	char imgname[128];
	int aniIndex, nFrame;
	int left, top, width, height;
	float duration;

	FILE *fp = fopen(filename, "rt");

	if (fp == NULL)
		return;

	fscanf(fp, "%s", imgname);
	CMySprite::Create_floor(pDevice, imgname);

	fscanf(fp, "%d", &m_maxAni); //2

	for (int ani = 0; ani < m_maxAni; ++ani)
	{
		fscanf(fp, "%d %d", &aniIndex, &nFrame);

		//0¹øÂ° ÀÎµ¦½º´Â ÃÑ 8ÇÁ·¹ÀÓ
		m_infoFrame[ani] = nFrame;

		for (int i = 0; i < nFrame; ++i)
		{
			fscanf(fp, "%d %d %d %d %d", &left, &top, &width, &height, &duration);
			SetRect(&m_rcFrame[aniIndex][i], left, top, width, height);
			m_fDuration[aniIndex][i] = duration;
		}
	}

	fclose(fp);
}

void CMyFloorSprite::OnDraw()
{
	RECT srcRect = m_rcFrame[m_aniType][m_nFrame];
	srcRect.bottom = srcRect.top + m_rcFrame[m_aniType][m_nFrame].bottom;
	srcRect.right = srcRect.left + m_rcFrame[m_aniType][m_nFrame].right;

	D3DXVECTOR3 vCenter(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vPosition(positionX, 350.0f, 0.0f);
	D3DXVECTOR3 vPosition2(positionX2, 350.0f, 0.0f);

	m_pDonutSprite[2]->Begin(D3DXSPRITE_ALPHABLEND);
	m_pDonutSprite[3]->Begin(D3DXSPRITE_ALPHABLEND);

	m_pDonutSprite[2]->Draw(m_pDonutTexture[2],
		&srcRect,
		&vCenter,
		&vPosition,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

	m_pDonutSprite[3]->Draw(m_pDonutTexture[3],
		&srcRect,
		&vCenter,
		&vPosition2,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

	m_pDonutSprite[2]->End();
	m_pDonutSprite[3]->End();
}

void CMyFloorSprite::OnUpdate(float timeE)
{
	m_interval += timeE;
	if (m_interval > m_fDuration[m_aniType][m_nFrame])
	{
		m_interval = 0.0f;
		m_nFrame++;
		if (m_nFrame >= m_infoFrame[m_aniType]) m_nFrame = 0;
	}

	//positionX = positionX - 0.02f;
	//positionX2 = positionX2 - 0.02f;

	if (positionX <= -668.0f)
		positionX = 668.0f;

	if (positionX2 <= -668.0f)
		positionX2 = 668.0f;

	OnDraw();
}
