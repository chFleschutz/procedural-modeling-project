#include "Game.h"


void CGame::Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash* psplash)
{
	m_root.Init(psplash);
	m_root.SetFrameRateMax(100.0f);
	m_frame.SetApiRender(eApiRender_DirectX11);
	m_frame.Init(hwnd, procOS);
	m_frame.AddDeviceKeyboard(&m_keyboard);
	m_camera.Init(THIRDPI);
	m_viewport.InitFull(&m_camera);

	m_scene.SetLightAmbient(Vektoria::CColor(1.0f, 0.9f, 0.9f));
	m_scene.SetLightAmbient(0.1f);
	m_scene.SetSkyOn(&m_cameraPlace);
	m_scene.SetSkyTimeOfDay(0.5f);
	m_scene.SetSkyFlowOn(0.0f);

	// Materials
	m_skyMat.LoadPreset("EnvChurchLowRes");
	m_root.AddMaterial(&m_skyMat);

	m_sphereMat.LoadPreset("HalloWeltLowRes");
	m_sphereMat.AlterEnvPath("..//..//lib//Materials//EnvChurchLowRes//EnvChurchLowResD.jpg", false);
	m_sphere.SetMaterial(&m_sphereMat);
	
	m_waterMat.LoadPreset("Blood");
	m_root.AddMaterial(&m_waterMat);

	m_groundMat.LoadPreset("RockSnowy");
	m_root.AddMaterial(&m_groundMat);

	m_beamMat.LoadPreset("PhongBlue");
	m_beamMat.SetShadingOff();
	m_beamMat.SetShadowsOff();
	m_beamMat.SetTransparency(0.5f);

	// Camera
	m_cameraPlace.RotateXDelta(HALFPI / 3.0f);
	m_cameraPlace.TranslateDelta(0.0f, 20.0f, 20.0f);

	// Light
	m_light.Init(CHVector(1.0f, 1.0f, 0.0f), CColor(1.0f, 0.7f, 0.7f));

	// Sphere
	m_sphere.Init(1.5F, &m_sphereMat, 50, 50);

	// Island
	m_island.setWaterMaterial(&m_waterMat);
	m_island.setGroundMaterial(&m_groundMat);
	m_island.initialize(m_scene, 100.0f, 100.0f);

	// UFO
	m_ufo.setBeamMaterial(&m_beamMat);
	m_ufo.initialize(m_scene, { 0.0f, 10.0f, 0.0f });

	// Building
	m_building.initialize(m_scene, { 0.0f, 1.0f, 0.0f });

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

void CGame::Tick(float time, float timeDelta)
{
	// Camera movement
	float timeScaled = timeDelta * 10.0f;
	m_keyboard.PlaceWASD(m_cameraPlace, timeScaled, true);

	// Lass die Kugel rotieren:
	m_spherePlace.RotateY(-time);
	m_spherePlace.RotateXDelta(0.8f * sinf(time * 0.2f));

	m_ufo.update(timeDelta);

	m_root.Tick(timeDelta);
}

void CGame::Fini()
{
	m_root.Fini();
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


