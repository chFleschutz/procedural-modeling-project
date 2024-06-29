#pragma once

#include "Vektoria/Scene.h"
#include "Vektoria/Placement.h"
#include "Vektoria/GeoWall.h"

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

		float doorWidth = 2.0f;
		float doorHeight = 2.5f;
		int doorCount = 24; // Must be even

	};

	Building() = default;
	~Building() = default;

	void setParameters(const Building::Parameters& params) { m_params = params; }
	const Building::Parameters& parameters() const { return m_params; }

	void initialize(Vektoria::CScene& scene, const Vektoria::CHVector& pos = {})
	{
		// Door	
		m_door.InitOvalArc(m_params.doorWidth, m_params.doorHeight, true);

		// Wall Geo
		float halfWallLength = m_params.baseOuterRadius * PI; // From: Circumference = 2 * pi * r
		int halfDoorCount = 0.5f * m_params.doorCount;

		for (int i = 0; i < halfDoorCount; i++)
		{
			float doorPosX = i * (halfWallLength / halfDoorCount);
			m_baseWall.AddGeoWindow(&m_door, doorPosX, 0.0f);
		}

		m_baseWall.SetRoundingX(PI, m_params.roundingResolution);
		m_baseWall.Init(halfWallLength, m_params.baseHeight, m_params.wallThickness, nullptr,
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
		m_roof.Init(1.0f, roofCircumference + 0.01f, m_params.wallThickness + 0.01f, nullptr,
			false, false, true, true, true, true);

		m_roof.Subdivide(0.01f);
		m_roof.BendX(midRadius, TWOPI);
		
		m_roofPlace.TranslateY(m_params.baseHeight - 0.001f);
		m_roofPlace.RotateYDelta(PI);
		m_roofPlace.AddGeo(&m_roof);

		// Hierachy
		m_place.AddPlacement(&m_outerWallPlaceLeft);
		m_place.AddPlacement(&m_outerWallPlaceRight);
		m_place.AddPlacement(&m_innerWallPlaceLeft);
		m_place.AddPlacement(&m_innerWallPlaceRight);
		m_place.AddPlacement(&m_roofPlace);
		scene.AddPlacement(&m_place);
	}

private:
	Building::Parameters m_params;
	Vektoria::CPlacement m_place;

	Vektoria::CGeoWall m_baseWall;
	Vektoria::CPlacement m_outerWallPlaceLeft;
	Vektoria::CPlacement m_outerWallPlaceRight;
	Vektoria::CPlacement m_innerWallPlaceLeft;
	Vektoria::CPlacement m_innerWallPlaceRight;

	Vektoria::CGeoWall m_roof;
	Vektoria::CPlacement m_roofPlace;

	Vektoria::CGeoWindow m_door;

	Vektoria::CGeoCube m_testCube;
};