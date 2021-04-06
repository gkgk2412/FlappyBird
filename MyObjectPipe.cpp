#include "MyObjectPipe.h"
#include <ctime>

CMyPipeSprite::CMyPipeSprite()
{
	m_nFrame = 0;
	m_interval = 0.0f;
	m_aniType = 0;
}


CMyPipeSprite::~CMyPipeSprite()
{
}

void CMyPipeSprite::Create(LPDIRECT3DDEVICE9 pDevice, char* filename)
{
	char imgname[128];
	int aniIndex, nFrame;

	float duration;

	FILE* fp = fopen(filename, "rt");

	if (fp == NULL)
		return;

	fscanf(fp, "%s", imgname);
	CMySprite::Create_Pipe(pDevice, imgname);

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
}

void CMyPipeSprite::OnDraw(float m_Y, int selection)
{
	RECT srcRect = m_rcFrame[m_aniType][m_nFrame];
	srcRect.bottom = srcRect.top + m_rcFrame[m_aniType][m_nFrame].bottom;
	srcRect.right = srcRect.left + m_rcFrame[m_aniType][m_nFrame].right;

	D3DXVECTOR3 vCenter(0.0f, 0.0f, 0.0f);
	//아래쪽 파이트 콜라이더
	for (int i = 0; i < 3; i++)
	{
		m_rcCollision[i].left = (int)positionX[i];
		m_rcCollision[i].top = (int)m_Y;
		m_rcCollision[i].right = m_rcCollision[i].left + m_rcFrame[m_aniType][m_nFrame].right;
		m_rcCollision[i].bottom = m_rcCollision[i].top + m_rcFrame[m_aniType][m_nFrame].bottom;
	}
	//위쪽 파이트 콜라이더
	for (int i = 3; i < 6; i++)
	{
		m_rcCollision[i].left = (int)positionX[i];
		m_rcCollision[i].top = (int)m_Y-250.0f;
		m_rcCollision[i].right = m_rcCollision[i].left + m_rcFrame[m_aniType][m_nFrame].right;
		m_rcCollision[i].bottom = m_rcCollision[i].top + m_rcFrame[m_aniType][m_nFrame].bottom;
	}

	if (selection == 1)
	{
		//아래쪽 파이프
		D3DXVECTOR3 vPosition(positionX[0], m_Y, 0.0f);
		D3DXVECTOR3 vPosition2(positionX[1], m_Y, 0.0f);
		D3DXVECTOR3 vPosition3(positionX[2], m_Y, 0.0f);

		m_pDonutSprite[4]->Begin(D3DXSPRITE_ALPHABLEND);
		m_pDonutSprite[5]->Begin(D3DXSPRITE_ALPHABLEND);
		m_pDonutSprite[6]->Begin(D3DXSPRITE_ALPHABLEND);

		m_pDonutSprite[4]->Draw(m_pDonutTexture[4],
			&srcRect,
			&vCenter,
			&vPosition,
			D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

		m_pDonutSprite[5]->Draw(m_pDonutTexture[5],
			&srcRect,
			&vCenter,
			&vPosition2,
			D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

		m_pDonutSprite[6]->Draw(m_pDonutTexture[6],
			&srcRect,
			&vCenter,
			&vPosition3,
			D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

		m_pDonutSprite[4]->End();
		m_pDonutSprite[5]->End();
		m_pDonutSprite[6]->End();
	}

	if (selection == 2)
	{
		//위쪽 파이프
		D3DXVECTOR3 vPosition4(positionX[3], m_Y - 250.0f, 0.0f);
		D3DXVECTOR3 vPosition5(positionX[4], m_Y - 250.0f, 0.0f);
		D3DXVECTOR3 vPosition6(positionX[5], m_Y - 250.0f, 0.0f);

		m_pDonutSprite[7]->Begin(D3DXSPRITE_ALPHABLEND);
		m_pDonutSprite[8]->Begin(D3DXSPRITE_ALPHABLEND);
		m_pDonutSprite[9]->Begin(D3DXSPRITE_ALPHABLEND);

		m_pDonutSprite[7]->Draw(m_pDonutTexture[7],
			&srcRect,
			&vCenter,
			&vPosition4,
			D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

		m_pDonutSprite[8]->Draw(m_pDonutTexture[8],
			&srcRect,
			&vCenter,
			&vPosition5,
			D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

		m_pDonutSprite[9]->Draw(m_pDonutTexture[9],
			&srcRect,
			&vCenter,
			&vPosition6,
			D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f));

		m_pDonutSprite[7]->End();
		m_pDonutSprite[8]->End();
		m_pDonutSprite[9]->End();

		bottomCol = m_rcFrame[0][0].bottom;
		leftCol = m_rcFrame[0][0].left;
		rightCol = m_rcFrame[0][0].right;
	}


	//for (int i = 4; i < 10; ++i)
	//{
	//	m_pDonutSprite[i]->Begin(D3DXSPRITE_ALPHABLEND);

	//	//m_pDonutSprite[4]->Begin(D3DXSPRITE_ALPHABLEND);
	//	//m_pDonutSprite[5]->Begin(D3DXSPRITE_ALPHABLEND);
	//	//m_pDonutSprite[6]->Begin(D3DXSPRITE_ALPHABLEND);
	//	//m_pDonutSprite[4]->Begin(D3DXSPRITE_ALPHABLEND);
	//	//m_pDonutSprite[5]->Begin(D3DXSPRITE_ALPHABLEND);
	//	//m_pDonutSprite[6]->Begin(D3DXSPRITE_ALPHABLEND);
	//}

	//for (int i = 4; i < 10; ++i)
	//{
	//	m_pDonutSprite[i]->End();

	//	//m_pDonutSprite[4]->End();
	//	//m_pDonutSprite[5]->End();
	//	//m_pDonutSprite[6]->End();
	//	//m_pDonutSprite[7]->End();
	//	//m_pDonutSprite[8]->End();
	//	//m_pDonutSprite[9]->End();
	//}
}

void CMyPipeSprite::OnUpdate(float timeE, float m_Y, int selection)
{
	m_interval += timeE;
	if (m_interval > m_fDuration[m_aniType][m_nFrame])
	{
		m_interval = 0.0f;
		m_nFrame++;
		if (m_nFrame >= m_infoFrame[m_aniType]) m_nFrame = 0;
	}

	for (int i = 0; i < MAX_PIPE; ++i)
	{
		if (positionX[i] <= -80.0f)
		{
			srand(time(NULL));

			int randTemp = rand() % (872 + 1 - 672) + 672;

			//int randTemp = rand() % 872 + 672;
			positionX[i] = randTemp;
		}		
	}

	//for (int i = 0; i < 6; ++i)
	//{
	//	positionX[i] = positionX[i] - 0.02f;
	//}
	
	OnDraw(m_Y, selection);
}
