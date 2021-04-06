#include "MyAnimationSprite.h"



CMyAnimationSprite::CMyAnimationSprite()
{
	m_nFrame = 0;
	m_interval = 0.0f;
	m_aniType = 0;
}


CMyAnimationSprite::~CMyAnimationSprite()
{
}

void CMyAnimationSprite::Create(LPDIRECT3DDEVICE9 pDevice, char *filename)
{
	char imgname[128];
	int aniIndex, nFrame;
	float duration;

	FILE *fp = fopen(filename, "rt");

	if (fp == NULL)
		return;	

	fscanf(fp, "%s", imgname);
	CMySprite::Create(pDevice, imgname, 465, 155); // 465 155

	fscanf(fp, "%d", &m_maxAni); //2

	for (int ani = 0; ani < m_maxAni; ++ani)
	{
		fscanf(fp, "%d %d", &aniIndex, &nFrame);

		//0번째 인덱스는 총 8프레임
		m_infoFrame[ani] = nFrame;

		for (int i = 0; i < nFrame; ++i)
		{
			fscanf(fp, "%d %d %d %d %d", &left, &top, &width, &height, &duration);
			SetRect(&m_rcFrame[aniIndex][i], left, top, width, height);
			m_fDuration[aniIndex][i] = duration;
		}
	}

	fclose(fp);


	/*
	< fly.txt format >
	fly.png			//이미지 파일명
	2				//애니메이션 종류의 수
	0 6				//0번째 애니메이션의 프레임수 		
	16 12 130 112	//0번째 애니메이션의 영역 데이터 저장 시작
	172 12 130 112
	...6번째 까지
	1 6		//1번째 애니메이션의 프레임수
	...6번째 까지
	*/

	//txt 파일을 받아와서 출력...

	//SetRect(&m_rcFrame[0], 16, 12, 130, 112);
	//SetRect(&m_rcFrame[1], 172, 12, 130, 112);
	//SetRect(&m_rcFrame[2], 329, 12, 130, 112);
	//SetRect(&m_rcFrame[3], 16, 145, 130, 112);
	//SetRect(&m_rcFrame[4], 174, 145, 130, 112);
	//SetRect(&m_rcFrame[5], 16, 276, 130, 112);
}

void CMyAnimationSprite::OnDraw()
{
	RECT srcRect = m_rcFrame[m_aniType][m_nFrame];
	srcRect.bottom = srcRect.top + m_rcFrame[m_aniType][m_nFrame].bottom;
	srcRect.right = srcRect.left + m_rcFrame[m_aniType][m_nFrame].right;

	D3DXVECTOR3 vCenter(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vPosition(m_positionX, m_positionY, 0.0f);
	//D3DXVECTOR3 vRotation(0.0f, 180.0f, 0.0f);

	m_rcCollision.left = (int)m_positionX;
	m_rcCollision.top = (int)m_positionY;
	m_rcCollision.right = m_rcCollision.left + m_rcFrame[m_aniType][m_nFrame].right;
	m_rcCollision.bottom = m_rcCollision.top + m_rcFrame[m_aniType][m_nFrame].bottom;

	m_pDonutSprite[1]->Begin(D3DXSPRITE_ALPHABLEND);

	m_pDonutSprite[1]->Draw(m_pDonutTexture[1],
		&srcRect,
		&vCenter,
		&vPosition,
		D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

	m_pDonutSprite[1]->End();
}

void CMyAnimationSprite::OnUpdate(float time)
{
	m_interval += time;
	if (m_interval > m_fDuration[m_aniType][m_nFrame])
	{
		m_interval = 0.0f;
		m_nFrame++;
		if (m_nFrame >= m_infoFrame[m_aniType]) m_nFrame = 0;
	}

	m_positionY += 0.02f;

	OnDraw();
}

BOOL CMyAnimationSprite::isTrigger(RECT rect)
{
	if (m_rcCollision.left < rect.right &&
		m_rcCollision.top < rect.bottom &&
		m_rcCollision.right > rect.left &&
		m_rcCollision.bottom > rect.top)
		return true;
	return false;
}