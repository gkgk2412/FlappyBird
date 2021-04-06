//-----------------------------------------------------------------------------
//           Name: dx9_d3dxsprite.cpp
//         Author: Kevin Harris
//  Last Modified: 02/01/05
//    Description: This sample demonstrates how to create a animated 2D sprite 
//                 using D3DXSprite which is hardware accelerated and fully 
//                 compatible with 3D generated content.
//-----------------------------------------------------------------------------

#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <mmsystem.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "resource.h"
#include "MyAnimationSprite.h"
#include <stdio.h>
#include "MyFloor.h"
#include "MyBack.h"
#include "MyObjectPipe.h"
#include <MMSystem.h> //playsound함수사용위해
#include "Digitalv.h" //mci 사용위해

//사운드사용위해서(playsound, mci)
/*========================================*/
#pragma comment(lib, "winmm.lib" ) 

MCI_OPEN_PARMS m_mciOpenParms;
MCI_PLAY_PARMS m_mciPlayParms;
DWORD m_dwDeviceID;
MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;

MCI_OPEN_PARMS mciOpen2;
MCI_PLAY_PARMS mciPlay2;

//메인사운드 조절
int soundplayCheck;
/*===========================================================*/


//-----------------------------------------------------------------------------
// GLOBALS
//-----------------------------------------------------------------------------
HWND                    g_hWnd          = NULL;
LPDIRECT3D9             g_pD3D          = NULL;
LPDIRECT3DDEVICE9       g_pd3dDevice    = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;

float  g_fElpasedTime;
double g_dCurTime;
double g_dLastTime;
float  g_fMoveSpeed = 50.0f;
float  g_fSpinX = 0.0f;
float  g_fSpinY = 0.0f;


int gameState = 0;
int exitBox;
bool isTopCheck = false;

DWORD tick; DWORD deltatime;

CMyAnimationSprite g_aniSprite;
CMyFloorSprite g_aniSpriteFloor;
CMyBackSprite g_aniSpriteTitle;
CMyBackSprite g_aniSpriteBack;
CMyBackSprite g_aniSpriteBackEnd;
CMyPipeSprite g_aniSpritePipe;
CMyPipeSprite g_aniSpritePipe2;

#define D3DFVF_CUSTOMVERTEX ( D3DFVF_XYZ | D3DFVF_TEX1 )

struct Vertex
{
    float x, y, z;
    float tu, tv;
};

Vertex g_quadVertices[] =
{
	{-1.0f, 1.0f, 0.0f,  0.0f,0.0f },
	{ 1.0f, 1.0f, 0.0f,  1.0f,0.0f },
	{-1.0f,-1.0f, 0.0f,  0.0f,1.0f },
	{ 1.0f,-1.0f, 0.0f,  1.0f,1.0f }
};

//-----------------------------------------------------------------------------
// PROTOTYPES
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void init(void);
void shutDown(void);
void render(void);

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
int WINAPI WinMain(	HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR     lpCmdLine,
					int       nCmdShow )
{
	WNDCLASSEX winClass; 
	MSG        uMsg;

    memset(&uMsg,0,sizeof(uMsg));

	winClass.lpszClassName = "MY_WINDOWS_CLASS";
	winClass.cbSize        = sizeof(WNDCLASSEX);
	winClass.style         = CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc   = WindowProc;
	winClass.hInstance     = hInstance;
	winClass.hIcon	       = LoadIcon(hInstance, (LPCTSTR)IDI_DIRECTX_ICON);
    winClass.hIconSm	   = LoadIcon(hInstance, (LPCTSTR)IDI_DIRECTX_ICON);
	winClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winClass.lpszMenuName  = NULL;
	winClass.cbClsExtra    = 0;
	winClass.cbWndExtra    = 0;

	if( !RegisterClassEx(&winClass) )
		return E_FAIL;

	g_hWnd = CreateWindowEx( NULL, "MY_WINDOWS_CLASS", 
		                     "Direct3D (DX9) - Creating 2D Sprites with D3DXSPRITE",
						     WS_OVERLAPPEDWINDOW | WS_VISIBLE,
					         0, 0, 640, 480, NULL, NULL, hInstance, NULL );

	if( g_hWnd == NULL )
		return E_FAIL;

    ShowWindow( g_hWnd, nCmdShow );
    UpdateWindow( g_hWnd );

	init();

	//사운드
/*=====================================================================*/

	mciOpen.lpstrElementName = "./MainSound.mp3";
	mciOpen.lpstrDeviceType = "mpegvideo";

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
		(DWORD)(LPVOID)&mciOpen);

	soundplayCheck = mciOpen.wDeviceID;

	mciSendCommand(soundplayCheck, MCI_PLAY, MCI_DGV_PLAY_REPEAT,
		(DWORD)(LPVOID)&m_mciPlayParms);


	/*=====================================================================*/


	tick = GetTickCount();
	while( uMsg.message != WM_QUIT )
	{
		if( PeekMessage( &uMsg, NULL, 0, 0, PM_REMOVE ) )
		{ 
			TranslateMessage( &uMsg );
			DispatchMessage( &uMsg );
		}
        else
		{
			g_dCurTime     = timeGetTime();
			g_fElpasedTime = (float)((g_dCurTime - g_dLastTime) * 0.001);
			g_dLastTime    = g_dCurTime;

			DWORD curTick = GetTickCount();
			deltatime = curTick - tick;

			render();

	
			tick = curTick;
		}
	}

	shutDown();

    UnregisterClass( "MY_WINDOWS_CLASS", winClass.hInstance );

	return uMsg.wParam;
}

//-----------------------------------------------------------------------------
// Name: WindowProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT CALLBACK WindowProc( HWND   hWnd, 
							 UINT   msg, 
							 WPARAM wParam, 
							 LPARAM lParam )
{
	static POINT ptLastMousePosit;
	static POINT ptCurrentMousePosit;
	static bool bMousing;

    switch( msg )
	{	
        case WM_KEYDOWN:
		{
			switch( wParam )
			{
				case VK_ESCAPE:
					PostQuitMessage(0);
					break;
			}
		}
        break;

		case WM_LBUTTONDOWN:
		{
			ptLastMousePosit.x = ptCurrentMousePosit.x = LOWORD (lParam);
            ptLastMousePosit.y = ptCurrentMousePosit.y = HIWORD (lParam);
			bMousing = true;
			
			if(gameState == 0)
				gameState = 1;

			if (gameState == 1)
			{
				sndPlaySoundA("./jumpsound.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC); //점프
				g_aniSprite.m_positionY -= 35;
			}
	
		}
		break;

		case WM_LBUTTONUP:
		{
			bMousing = false;
		}
		break;

		case WM_MOUSEMOVE:
		{
			ptCurrentMousePosit.x = LOWORD (lParam);
			ptCurrentMousePosit.y = HIWORD (lParam);

			if( bMousing )
			{
				g_fSpinX -= (ptCurrentMousePosit.x - ptLastMousePosit.x);
				g_fSpinY -= (ptCurrentMousePosit.y - ptLastMousePosit.y);
			}
			
			ptLastMousePosit.x = ptCurrentMousePosit.x;
            ptLastMousePosit.y = ptCurrentMousePosit.y;
		}
		break;
		
		case WM_CLOSE:
		{
			PostQuitMessage(0);	
		}
		
        case WM_DESTROY:
		{
            PostQuitMessage(0);
		}
        break;

		default:
		{
			return DefWindowProc( hWnd, msg, wParam, lParam );
		}
		break;
	}

	if (g_aniSprite.isTrigger(g_aniSpritePipe.m_rcCollision[0]) == TRUE ||
		g_aniSprite.isTrigger(g_aniSpritePipe.m_rcCollision[1]) == TRUE ||
		g_aniSprite.isTrigger(g_aniSpritePipe.m_rcCollision[2]) == TRUE ||
		g_aniSprite.isTrigger(g_aniSpritePipe2.m_rcCollision[3]) == TRUE ||
		g_aniSprite.isTrigger(g_aniSpritePipe2.m_rcCollision[4]) == TRUE ||
		g_aniSprite.isTrigger(g_aniSpritePipe2.m_rcCollision[5]) == TRUE)
	{
		gameState = 2;
	}

	if (exitBox == 1)
	{
		mciSendCommandW(soundplayCheck, MCI_CLOSE, 0, NULL); //메인음악을 종료하고
		sndPlaySoundA("./fail.wav", SND_ASYNC | SND_NODEFAULT | SND_ASYNC); //퀘스트실패

		if (MessageBox(hWnd, "새가 죽었습니다", "게임 오버", MB_OK) == IDOK) //RETRY버튼을 누르면
			exit(0);
	}

	return 0;
}


//-----------------------------------------------------------------------------
// Name: init()
// Desc: 
//-----------------------------------------------------------------------------
void init( void )
{
    g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

	D3DCAPS9 d3dCaps;
	g_pD3D->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dCaps );

    D3DDISPLAYMODE d3ddm;
    g_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm );

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
	
    d3dpp.Windowed               = TRUE;
	d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat       = d3ddm.Format;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;

    g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
                          D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                          &d3dpp, &g_pd3dDevice );

	
	g_pd3dDevice->CreateVertexBuffer( 4*sizeof(Vertex), D3DUSAGE_WRITEONLY, 
                                      D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, 
                                      &g_pVertexBuffer, NULL );
    void *pVertices = NULL;

    g_pVertexBuffer->Lock( 0, sizeof(g_quadVertices), (void**)&pVertices, 0 );
    memcpy( pVertices, g_quadVertices, sizeof(g_quadVertices) );
    g_pVertexBuffer->Unlock();

    D3DXMATRIX matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DXToRadian( 45.0f ), 
                                640.0f / 480.0f, 0.1f, 100.0f );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );

	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	g_aniSpriteBack.Create(g_pd3dDevice, "backGround.txt");
	g_aniSprite.Create(g_pd3dDevice, "bird.txt");
	g_aniSpriteFloor.Create(g_pd3dDevice, "floor.txt");
	g_aniSpritePipe.Create(g_pd3dDevice, "pipe.txt");
	g_aniSpritePipe2.Create(g_pd3dDevice, "pipe2.txt");
	g_aniSpriteTitle.Create(g_pd3dDevice, "backGround_Title.txt");
	g_aniSpriteBackEnd.Create(g_pd3dDevice, "backGround_E.txt");
}

//-----------------------------------------------------------------------------
// Name: shutDown()
// Desc: 
//-----------------------------------------------------------------------------
void shutDown( void )
{
    if( g_pVertexBuffer != NULL ) 
        g_pVertexBuffer->Release(); 

    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )
        g_pD3D->Release();
}

//-----------------------------------------------------------------------------
// Name: render()
// Desc: 
//-----------------------------------------------------------------------------
void render( void )
{
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                         D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0 );

	g_pd3dDevice->BeginScene();

	if (gameState == 0)
	{
		g_aniSpriteTitle.OnUpdate(g_fElpasedTime, 2);
	}

	if (gameState == 1)
	{
		g_aniSpriteBack.OnUpdate(g_fElpasedTime, 1);
		g_aniSprite.OnUpdate(g_fElpasedTime);
		g_aniSpriteFloor.OnUpdate(g_fElpasedTime);
		g_aniSpritePipe.OnUpdate(g_fElpasedTime, 250.0f, 1);
		g_aniSpritePipe2.OnUpdate(g_fElpasedTime, 250.0f, 2);

		g_aniSpriteFloor.Move(deltatime, 120.0f);
		g_aniSpritePipe.Move(deltatime, 120.0f);
		g_aniSpritePipe2.Move(deltatime, 120.0f);
		//g_aniSprite.y_MoveDown(deltatime, 0.85f);

		if (g_aniSprite.m_positionY <= 0.0f)
		{
			g_aniSprite.m_positionY = 0.0f;
		}

		if (g_aniSprite.m_positionY >= 285.0f)
		{
			gameState = 2;
		}
	}

	if (gameState == 2)
	{
		g_aniSpriteBackEnd.OnUpdate(g_fElpasedTime, 3);

		exitBox = 1;
	}

    g_pd3dDevice->EndScene();

    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}
