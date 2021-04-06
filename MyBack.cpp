#include "MyBack.h"

CMyBackSprite::CMyBackSprite()
{
	m_nFrame = 0;
	m_interval = 0.0f;
	m_aniType = 0;
}


CMyBackSprite::~CMyBackSprite()
{
}

void CMyBackSprite::Create(LPDIRECT3DDEVICE9 pDevice, char* filename)
{
	char imgname[128];
	int aniIndex, nFrame;
	int left, top, width, height;
	float duration;

	FILE* fp = fopen(filename, "rt");

	if (fp == NULL)
		return;

	fscanf(fp, "%s", imgname);
	CMySprite::Create_Back(pDevice, imgname);

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

void CMyBackSprite::OnDraw(int selection)
{
	RECT srcRect = m_rcFrame[m_aniType][m_nFrame];
	srcRect.bottom = srcRect.top + m_rcFrame[m_aniType][m_nFrame].bottom;
	srcRect.right = srcRect.left + m_rcFrame[m_aniType][m_nFrame].right;

	D3DXVECTOR3 vCenter(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vPosition(0.0f, -40.0f, 0.0f);

	if (selection == 1)
	{
		m_pDonutSprite[0]->Begin(D3DXSPRITE_ALPHABLEND);

		m_pDonutSprite[0]->Draw(m_pDonutTexture[0],
			&srcRect,
			&vCenter,
			&vPosition,
			D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

		m_pDonutSprite[0]->End();
	}

	if (selection == 2)
	{
		m_pDonutSprite[10]->Begin(D3DXSPRITE_ALPHABLEND);

		m_pDonutSprite[10]->Draw(m_pDonutTexture[10],
			&srcRect,
			&vCenter,
			&vPosition,
			D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

		m_pDonutSprite[10]->End();
	}

	if(selection == 3)
	{
		m_pDonutSprite[11]->Begin(D3DXSPRITE_ALPHABLEND);

		m_pDonutSprite[11]->Draw(m_pDonutTexture[11],
			&srcRect,
			&vCenter,
			&vPosition,
			D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

		m_pDonutSprite[11]->End();
	}
}

void CMyBackSprite::OnUpdate(float time, int selection)
{
	m_interval += time;
	if (m_interval > m_fDuration[m_aniType][m_nFrame])
	{
		m_interval = 0.0f;
		m_nFrame++;
		if (m_nFrame >= m_infoFrame[m_aniType]) m_nFrame = 0;
	}

	OnDraw(selection);
}
