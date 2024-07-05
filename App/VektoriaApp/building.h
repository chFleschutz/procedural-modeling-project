#pragma once

#include "Vektoria/GeoCylinder.h"
#include "Vektoria/GeoTube.h"
#include "Vektoria/GeoWall.h"
#include "Vektoria/Placement.h"
#include "Vektoria/Scene.h"

class Building
{
public:
	struct Parameters
	{
		float baseHeight = 3.0f;
		float baseThickness = 2.0f;
		float baseOuterRadius = 10.0f;

		float wallThickness = 0.2f;

		float roofHeight = 2.0f;
		float roundingResolution = 0.1f;

		int doorCount = 24; // Must be even
		float doorWidth = 2.0f;
		float doorHeight = 2.5f;

		float doorFrameWidth = 0.1f; // Must be less than 1
		float doorFrameHeight = 0.05f; // Must be less than 1
		float doorFrameThickness = 0.5f; // Must be less than 1

		float outerfloorHeight = 0.5f;
		float innerFloorHeight = 0.3f;
	};

	Building() = default;
	~Building() = default;

	void setParameters(const Building::Parameters& params) { m_params = params; }
	const Building::Parameters& parameters() const { return m_params; }

	void setOuterFloorMaterial(Vektoria::CMaterial* mat) { m_buildingFloorMat = mat; }
	void setInnerFloorMaterial(Vektoria::CMaterial* mat) { m_innerFloorMat = mat; }
	void setWallMaterial(Vektoria::CMaterial* mat) { m_wallMat = mat; }
	void setRoofMaterial(Vektoria::CMaterial* mat) { m_roofMat = mat; }
	void setDoorFrameMaterial(Vektoria::CMaterial* mat) { m_doorFrameMat = mat; }

	void initialize(Vektoria::CScene& scene, const Vektoria::CHVector& pos = {});

private:
	Building::Parameters m_params;

	// Placements
	Vektoria::CPlacement m_place;

	Vektoria::CPlacement m_baseFloorPlace;
	Vektoria::CPlacement m_buildingFloorPlace;
	Vektoria::CPlacement m_innerFloorPlace;

	Vektoria::CPlacement m_baseWallPlace;
	Vektoria::CPlacement m_outerWallPlaceLeft;
	Vektoria::CPlacement m_outerWallPlaceRight;
	Vektoria::CPlacement m_innerWallPlaceLeft;
	Vektoria::CPlacement m_innerWallPlaceRight;

	Vektoria::CPlacement m_roofPlace;

	// Geos
	Vektoria::CGeoTube m_buildingFloor;
	Vektoria::CGeoCylinder m_innerFloor;
	Vektoria::CGeoWall m_doorFrame;
	Vektoria::CGeoWindow m_innerDoor;
	Vektoria::CGeoWindow m_door;
	Vektoria::CGeoWall m_baseWall;
	Vektoria::CGeoWall m_roof;

	// Materials
	Vektoria::CMaterial* m_buildingFloorMat = nullptr;
	Vektoria::CMaterial* m_innerFloorMat = nullptr;
	Vektoria::CMaterial* m_wallMat = nullptr;
	Vektoria::CMaterial* m_roofMat = nullptr;
	Vektoria::CMaterial* m_doorFrameMat = nullptr;
};