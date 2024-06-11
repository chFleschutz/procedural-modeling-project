#include "Game.h"

CGame::CGame(void)
{
}

CGame::~CGame(void)
{
}

void CGame::Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash* psplash)
{
	m_root.Init(psplash);
	m_frame.SetApiRender(eApiRender_DirectX11);
	m_root.SetFrameRateMax(100.0f);
	m_camera.Init(THIRDPI);
	m_frame.Init(hwnd, procOS);
	m_frame.AddDeviceKeyboard(&m_keyboard);
	m_viewport.InitFull(&m_camera);

	// Camera
	m_cameraPlace.TranslateZ(7.0f);

	// Light
	m_light.Init(CHVector(1.0f, 1.0f, 1.0f), CColor(1.0f, 1.0f, 1.0f));

	// Skydome and sky
	m_skydome.Init(1000.0F, nullptr, 20, 20);
	m_skydome.Flip();
	m_skyPlace.SetSky();
	m_skyPlace.AddGeo(&m_skydome);
	m_skyMat.LoadPreset("EnvChurchLowRes");
	m_skydome.SetMaterial(&m_skyMat);
	m_root.AddMaterial(&m_skyMat);

	// Sphere
	m_sphere.Init(1.5F, nullptr, 50, 50);
	m_sphereMat.LoadPreset("HalloWeltLowRes");
	m_sphereMat.AlterEnvPath("..//..//lib//Materials//EnvChurchLowRes//EnvChurchLowResD.jpg", false);
	m_root.AddMaterial(&m_sphereMat);
	m_sphere.SetMaterial(&m_sphereMat);

	// Scene Hierachy
	m_root.AddFrame(&m_frame);
	m_root.AddScene(&m_scene);
	m_frame.AddViewport(&m_viewport);

	m_scene.AddPlacement(&m_spherePlace);
	m_scene.AddPlacement(&m_cameraPlace);
	m_cameraPlace.AddCamera(&m_camera);

	m_scene.AddLightParallel(&m_light);
	m_spherePlace.AddGeo(&m_sphere);
	m_scene.AddPlacement(&m_skyPlace);
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	// Camera movement
	float timeScaled = fTimeDelta * 5.0f;
	m_keyboard.PlaceWASD(m_cameraPlace, timeScaled, true);

	// Lass die Kugel rotieren:
	m_spherePlace.RotateY(-fTime);
	m_spherePlace.RotateXDelta(0.8f * sinf(fTime * 0.2f));

	m_root.Tick(fTimeDelta);
}

void CGame::Fini()
{
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	m_frame.ReSize(iNewWidth, iNewHeight);
}

float CGame::GetTimeDeltaMin()
{
	return m_root.GetTimeDeltaMin();
}

float CGame::GetVersion()
{
	return m_root.GetVersion();
}


