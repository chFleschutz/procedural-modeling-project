#pragma once

#include "Vektoria/Scene.h"
#include "Vektoria/Placement.h"
#include "Vektoria/GeoWall.h"

class Building
{
public:
	struct Parameters
	{
		float baseHeight = 2.0f;
		float baseThickness = 2.0f;
		float baseOuterRadius = 6.0f;
	};

	Building() = default;
	~Building() = default;

	void initialize(Vektoria::CScene& scene, const Vektoria::CHVector& pos = {})
	{
		float halfBodyLength = m_params.baseOuterRadius * PI; // From: Circumference = 2 * pi * r

		// Body
		m_halfBody.SetRoundingX(PI, 0.1f);
		m_halfBody.Init(halfBodyLength, m_params.baseHeight, m_params.baseThickness, nullptr);

		m_bodyPlaceLeft.RotateY(PI);
		m_bodyPlaceLeft.AddGeo(&m_halfBody);
		m_bodyPlaceRight.AddGeo(&m_halfBody);

		m_place.AddPlacement(&m_bodyPlaceLeft);
		m_place.AddPlacement(&m_bodyPlaceRight);
		scene.AddPlacement(&m_place);

		// Roof
		m_halfRoof.SetRoundingX(PI, 0.1f);
		m_halfRoof.init

		m_testCube.Init(1.0f, nullptr);
		m_place.AddGeo(&m_testCube);
	}

private:
	Building::Parameters m_params;
	Vektoria::CPlacement m_place;

	Vektoria::CGeoWall m_halfBody;
	Vektoria::CPlacement m_bodyPlaceLeft;
	Vektoria::CPlacement m_bodyPlaceRight;

	Vektoria::CGeoWall m_halfRoof;

	Vektoria::CGeoCube m_testCube;
};