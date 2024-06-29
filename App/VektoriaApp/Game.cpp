#include "Game.h"


void CGame::Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash* psplash)
{
	m_root.Init(psplash);
	m_root.SetFrameRateMax(100.0f);
	m_frame.SetApiRender(eApiRender_DirectX11);
	m_frame.Init(hwnd, procOS);
	m_frame.AddDeviceKeyboard(&m_keyboard);
	m_viewport.InitFull(&m_camera);

	m_root.AddFrame(&m_frame);
	m_root.AddScene(&m_scene);
	m_frame.AddViewport(&m_viewport);

	// Scene
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
	m_camera.Init(THIRDPI);
	m_cameraPlace.SetRotationSensitivity(1.5f);
	m_cameraPlace.SetTranslationSensitivity(15.0f);
	m_cameraPlace.RotateXDelta(UM_DEG2RAD(42));
	m_cameraPlace.TranslateDelta(0.0f, 40.0f, 40.0f);
	m_cameraPlace.AddCamera(&m_camera);
	m_scene.AddPlacement(&m_cameraPlace);

	// Light
	m_light.Init(CHVector(1.0f, 1.0f, 0.0f), CColor(1.0f, 0.7f, 0.7f));
	m_scene.AddLightParallel(&m_light);

	// Island
	m_island.setWaterMaterial(&m_waterMat);
	m_island.setGroundMaterial(&m_groundMat);
	m_island.initialize(m_scene);

	// Building
	Vektoria::CHVector buildingPos(9.0f, 0.0f, 7.0f);
	m_building.initialize(m_scene, buildingPos);
	m_cameraPlace.TranslateDelta(buildingPos);

	// UFO
	m_ufo.setBeamMaterial(&m_beamMat);
	m_ufo.initialize(m_scene, buildingPos + Vektoria::CHVector(0.0f, 15.0f, 0.0f));

	// Sphere
	m_sphere.Init(1.0f, &m_sphereMat, 50, 50);
	m_sphereRotator.AddGeo(&m_sphere);
	m_spherePlace.Translate(buildingPos + Vektoria::CHVector(0.0f, 1.0f, 0.0f));
	m_spherePlace.AddPlacement(&m_sphereRotator);
	m_scene.AddPlacement(&m_spherePlace);
}

void CGame::Tick(float time, float timeDelta)
{
	// Camera movement
	m_keyboard.PlaceWASD(m_cameraPlace, timeDelta, true);

	// Rotate sphere
	m_sphereRotator.RotateY(-time);
	m_sphereRotator.RotateXDelta(0.8f * sinf(time * 0.2f));

	// Rotate UFO
	m_ufo.update(timeDelta);

	// Render
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


