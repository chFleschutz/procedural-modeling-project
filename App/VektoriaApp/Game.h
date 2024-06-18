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
	CLightParallel m_light;
	CScene m_scene;
	CCamera m_camera;

	CDeviceKeyboard m_keyboard;

	// Materials
	CMaterial m_waterMat;
	CMaterial m_groundMat;
	CMaterial m_sphereMat;
	CMaterial m_skyMat;

	CPlacement m_cameraPlace;

	CPlacement m_spherePlace;
	CGeoSphere m_sphere;

	CPlacement m_skyPlace;
	CGeoSphere m_skydome;

	Island m_island;
	UFO m_ufo;
};


