#include "Game.h"

#include <cassert>

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
	m_scene.SetLightAmbient(0.2f);
	m_scene.SetSkyOn(&m_cameraPlace);
	m_scene.SetSkyTimeOfDay(0.5f);
	m_scene.SetSkyFlowOn(0.0f);

	// Materials
	assert(m_skyMat.LoadPreset("EnvChurchLowRes"));
	m_root.AddMaterial(&m_skyMat);

	assert(m_sphereMat.LoadPreset("HalloWeltLowRes"));
	m_sphereMat.AlterEnvPath("..//..//lib//Materials//EnvChurchLowRes//EnvChurchLowResD.jpg", false);
	m_sphere.SetMaterial(&m_sphereMat);

	assert(m_waterMat.LoadPreset("Blood"));
	m_root.AddMaterial(&m_waterMat);

	assert(m_groundMat.LoadPreset("RockSnowy"));
	m_groundMat.SetHeightStrength(0.0f);
	m_root.AddMaterial(&m_groundMat);

	assert(m_beamMat.LoadPreset("PhongBlue"));
	m_beamMat.SetShadingOff();
	m_beamMat.SetShadowsOff();
	m_beamMat.SetTransparency(0.5f);

	assert(m_roadMaterial.LoadPreset("WayRoad2Cracked"));
	m_root.AddMaterial(&m_roadMaterial);

	assert(m_crossingMaterial.LoadPreset("CrossingRoad2Cracked"));
	m_root.AddMaterial(&m_crossingMaterial);

	assert(m_brickMat.LoadPreset("BricksClinker"));
	m_root.AddMaterial(&m_brickMat);

	assert(m_ufoCockpitMat.LoadPreset("EyeAlien"));
	m_root.AddMaterial(&m_ufoCockpitMat);

	assert(m_marbleMat.LoadPreset("MarbleWhite"));
	m_root.AddMaterial(&m_marbleMat);

	m_brushedMetalAlbedo.Init("textures/brushed-metal/brushed-metal-albedo.jpg");
	m_brushedMetalNormal.Init("textures/brushed-metal/brushed-metal-normal.jpg");
	m_brushedMetalAlbedoTexture.Init(&m_brushedMetalAlbedo, eKindTexture_Diffuse);
	m_brushedMetalNormalTexture.Init(&m_brushedMetalNormal, eKindTexture_Bump);
	m_brushedMetalMat.SetTextureDiffuse(&m_brushedMetalAlbedoTexture);
	m_brushedMetalMat.SetTextureBump(&m_brushedMetalNormalTexture);
	m_root.AddMaterial(&m_brushedMetalMat);

	// Camera
	m_camera.Init(THIRDPI);
	m_cameraPlace.SetRotationSensitivity(1.5f);
	m_cameraPlace.SetTranslationSensitivity(15.0f);
	m_cameraPlace.RotateXDelta(UM_DEG2RAD(38));
	m_cameraPlace.TranslateDelta(0.0f, 50.0f, 50.0f);
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
	Vektoria::CHVector buildingPos(9.0f, 0.0f, -3.0f);
	m_building.setWallMaterial(&m_brickMat);
	m_building.setRoofMaterial(&m_brickMat);
	m_building.setOuterFloorMaterial(&m_marbleMat);
	m_building.setInnerFloorMaterial(&m_marbleMat);
	m_building.initialize(m_scene, buildingPos + Vektoria::CHVector(0.0f, 2.0f, 0.0f));
	m_cameraPlace.TranslateDelta(buildingPos);

	// UFO
	m_ufo.setBeamMaterial(&m_beamMat);
	m_ufo.setCockPitMaterial(&m_ufoCockpitMat);
	m_ufo.setBodyMaterial(&m_brushedMetalMat);
	m_ufo.addRing(UFO::Ring::Config{ 10, 5.0f, 1.2f, 1.5f, 1.0f });
	m_ufo.addRing(UFO::Ring::Config{ 30, 8.0f, 0.4f, 0.5f, 1.0f });
	m_ufo.addRing(UFO::Ring::Config{ 20, 12.0f, 0.0f, 2.0f, 1.5f });
	m_ufo.addRing(UFO::Ring::Config{ 20, 6.0f, -1.5f, -1.0f, 1.0f });
	m_ufo.initialize(m_scene, buildingPos + Vektoria::CHVector(0.0f, 20.0f, 0.0f));

	// Sphere
	float sphereRadius = 1.0f;
	m_sphere.Init(sphereRadius, &m_sphereMat, 50, 50);
	m_sphereRotator.AddGeo(&m_sphere);
	m_spherePlace.TranslateY(sphereRadius);
	m_spherePlace.AddPlacement(&m_sphereRotator);
	m_building.itemPlace().AddPlacement(&m_spherePlace);

	// Road
	m_road.setAreaMaterial(&m_groundMat);
	m_road.setRoadMaterial(&m_roadMaterial);
	m_road.setCrossingMaterial(&m_crossingMaterial);
	m_road.initialize(m_scene, buildingPos + Vektoria::CHVector{ 0.0f, 0.2f, 0.0f });
}

void CGame::Tick(float time, float timeDelta)
{
	if (m_keyboard.KeyDown(DIK_0))
		m_viewport.StyleOff();
	else if (m_keyboard.KeyDown(DIK_1))
		m_viewport.StylePainting();
	else if (m_keyboard.KeyDown(DIK_2))
		m_viewport.StylePencil();
	else if (m_keyboard.KeyDown(DIK_3))
		m_viewport.StyleCartoon();
	else if (m_keyboard.KeyDown(DIK_4))
		m_viewport.StylePurpleHaze();
	else if (m_keyboard.KeyDown(DIK_5))
		m_viewport.StyleToon();
	else if (m_keyboard.KeyDown(DIK_6))
		m_viewport.StylePopArt();

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


