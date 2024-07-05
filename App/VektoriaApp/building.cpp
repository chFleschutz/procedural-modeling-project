#include "building.h"

void Building::initialize(Vektoria::CScene& scene, const Vektoria::CHVector& pos)
{
	// Floor
	float innerRadius = m_params.baseOuterRadius - m_params.baseThickness;
	m_buildingFloor.SetTextureRepeat(10.0f, 10.0f);
	m_buildingFloor.InitStraight(innerRadius, m_params.baseOuterRadius, m_params.outerfloorHeight, m_buildingFloorMat, 100);
	m_buildingFloorPlace.AddGeo(&m_buildingFloor);
	m_buildingFloorPlace.TranslateY(0.5f * m_params.outerfloorHeight);

	m_innerFloor.SetTextureRepeat(20.0f, 20.0f);
	m_innerFloor.Init(innerRadius, m_params.innerFloorHeight, m_innerFloorMat, 100);
	m_innerFloorPlace.AddGeo(&m_innerFloor);

	// Walls
	m_baseWallPlace.TranslateY(m_params.outerfloorHeight - 0.001f);

	// Door	
	m_innerDoor.InitOvalArc(1.0f - m_params.doorFrameWidth, 1.0f - m_params.doorFrameHeight, false);

	m_doorFrame.AddGeoWindow(&m_innerDoor, 0.5f * m_params.doorFrameWidth, 0.0f);
	m_doorFrame.Init(1.0f, 1.0f, m_params.doorFrameThickness, m_doorFrameMat,
		false, false, false, false, true, true);

	Vektoria::CHMat doorFrameMat;
	doorFrameMat.TranslateZ(0.5f * m_params.wallThickness);
	m_doorFrame.Transform(doorFrameMat);

	m_door.AddGeoWall(&m_doorFrame);
	m_door.InitOvalArc(m_params.doorWidth, m_params.doorHeight, true);

	// Wall Geo
	float halfWallLength = m_params.baseOuterRadius * PI; // From: Circumference = 2 * pi * r
	int halfDoorCount = static_cast<int>(0.5f * m_params.doorCount);

	for (int i = 0; i < halfDoorCount; i++)
	{
		float doorPosX = i * (halfWallLength / halfDoorCount);
		m_baseWall.AddGeoWindow(&m_door, doorPosX, 0.0f);
	}

	m_baseWall.SetRoundingX(PI, m_params.roundingResolution);
	m_baseWall.SetTextureRepeat(10.0f, 10.0f);
	m_baseWall.Init(halfWallLength, m_params.baseHeight, m_params.wallThickness, m_wallMat,
		false, false, true, false, true, true);

	// Outer Wall
	m_outerWallPlaceLeft.RotateY(PI);
	m_outerWallPlaceLeft.AddGeo(&m_baseWall);

	m_outerWallPlaceRight.AddGeo(&m_baseWall);

	// Inner Wall
	float innerWallScale = (m_params.baseOuterRadius - m_params.baseThickness + m_params.wallThickness) / m_params.baseOuterRadius;
	m_innerWallPlaceLeft.RotateY(PI);
	m_innerWallPlaceLeft.ScaleDelta(innerWallScale, 1.0f, innerWallScale);
	m_innerWallPlaceLeft.AddGeo(&m_baseWall);

	m_innerWallPlaceRight.ScaleDelta(innerWallScale, 1.0f, innerWallScale);
	m_innerWallPlaceRight.AddGeo(&m_baseWall);

	// Roof
	float roofCircumference = 0.5f * m_params.baseThickness * PI;
	float midRadius = m_params.baseOuterRadius - (0.5f * m_params.baseThickness);

	m_roof.SetRoundingY(PI, m_params.roundingResolution);
	m_roof.SetTextureRepeat(20.0f, 10.0f);
	m_roof.Init(1.0f, roofCircumference + 0.01f, m_params.wallThickness + 0.01f, m_roofMat,
		false, false, true, true, true, true);

	m_roof.Subdivide(0.01f);
	m_roof.BendX(midRadius, TWOPI);

	m_roofPlace.TranslateY(m_params.baseHeight - 0.001f);
	m_roofPlace.RotateYDelta(PI);
	m_roofPlace.AddGeo(&m_roof);

	// Hierachy
	scene.AddPlacement(&m_place);
	m_place.Translate(pos);
	m_place.AddPlacement(&m_baseFloorPlace);

	m_baseFloorPlace.AddPlacement(&m_buildingFloorPlace);
	m_baseFloorPlace.AddPlacement(&m_innerFloorPlace);
	m_baseFloorPlace.AddPlacement(&m_baseWallPlace);

	m_baseWallPlace.AddPlacement(&m_outerWallPlaceLeft);
	m_baseWallPlace.AddPlacement(&m_outerWallPlaceRight);
	m_baseWallPlace.AddPlacement(&m_innerWallPlaceLeft);
	m_baseWallPlace.AddPlacement(&m_innerWallPlaceRight);
	m_baseWallPlace.AddPlacement(&m_roofPlace);
}
