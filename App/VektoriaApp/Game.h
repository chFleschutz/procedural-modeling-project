#pragma once


#ifdef _WIN64
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug64.lib")
#pragma comment (lib, "VektoriaMath_Debug64.lib")
#else
#pragma comment (lib, "Vektoria_Release64.lib")
#pragma comment (lib, "VektoriaMath_Release64.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug.lib")
#pragma comment (lib, "VektoriaMath_Debug.lib")
#else
#pragma comment (lib, "Vektoria_Release.lib")
#pragma comment (lib, "VektoriaMath_Release.lib")
#endif
#endif


#include "Vektoria\Root.h"
#include "island.h"
#include "ufo.h"
#include "building.h"
#include "road.h"

using namespace Vektoria;


class CGame
{
public:
	// Wird vor Begin einmal aufgerufen (Konstruktor):
	CGame(void) = default;

	// Wird nach Ende einmal aufgerufen (Destruktor):
	~CGame(void) = default;

	// Wird zu Begin einmal aufgerufen:
	void Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash);	

	// Wird während der Laufzeit bei jedem Bildaufbau aufgerufen:
	void Tick(float fTime, float fTimeDelta);						

	// Wird am Ende einmal aufgerufen:
	void Fini();																				

	// Wird immer dann aufgerufen, wenn der Benutzer die Fenstergröße verändert hat:
	void WindowReSize(int iNewWidth, int iNewHeight);											

	// Holt das minimale Zeitdelta zur eventuellen Frame-Rate-Beschränkung:
	float GetTimeDeltaMin();																	

	// Holt die Versionsnummer:
	float GetVersion();

private:
	CRoot m_root;
	CFrame m_frame;
	CViewport m_viewport;
	CDeviceKeyboard m_keyboard;
	
	CScene m_scene;
	CLightParallel m_light;

	CCamera m_camera;
	CPlacement m_cameraPlace;

	CGeoCube m_theCube;
	CPlacement m_itemPlace;
	CPlacement m_itemRotator;

	UFO m_ufo;				// Special Object
	Building m_building;	// Building
	Island m_island;		// Terrain 
	Road m_road;			// Infrastructure

	// Materials
	CMaterial m_waterMat;
	CMaterial m_groundMat;
	CMaterial m_skyMat;
	CMaterial m_beamMat;
	CMaterial m_roadMaterial;
	CMaterial m_crossingMaterial;
	CMaterial m_brickMat;
	CMaterial m_ufoCockpitMat;
	CMaterial m_marbleMat;

	CMaterial m_brushedMetalMat;
	CTexture m_brushedMetalAlbedoTexture;
	CTexture m_brushedMetalSpecularTexture;
	CTexture m_brushedMetalNormalTexture;
	CTexture m_brushedMetalHeightTexture;
	CImage m_brushedMetalAlbedo;
	CImage m_brushedMetalSpecular;
	CImage m_brushedMetalNormal;
	CImage m_brushedMetalHeight;
};


