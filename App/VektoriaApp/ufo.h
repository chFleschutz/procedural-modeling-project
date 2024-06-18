#pragma once

#include "Vektoria/Scene.h"
#include "Vektoria/Placement.h"
#include "Vektoria/GeoBezierTable.h"

#include <vector>

class UFO
{
public:
	struct Parameter
	{
		// Ufo Body
		float ufoRadius = 2.0f;
		float ufoHeightRadius = 0.3f;
		uint32_t ufoLongitudeSubdivs = 100;
		uint32_t ufoLattitudeSubdivs = 24;

		// Cockpit
		float cockpitRadius = 0.3f;
		float cockpitHeightRadius = 0.3f;

		// Rotating Outer Cubes
		int outerCubesCount = 30;
		float outerCubeSize = 0.1f;
		float outerRadiusOffset = 0.07f;
		float outerRotationSpeed = 1.0f;
	};

	UFO() = default;
	~UFO() = default;

	void initialize(Vektoria::CScene& scene, const Vektoria::CHVector& pos = {})
	{
		float ufoHeightScale = m_params.ufoHeightRadius / m_params.ufoRadius;
		float cockpitHeightScale = m_params.cockpitHeightRadius / m_params.cockpitRadius;

		// Hierachy
		scene.AddPlacement(&m_place);
		m_place.Translate(pos);
		m_place.AddPlacement(&m_bodyPlace);
		m_place.AddPlacement(&m_topPlace);
		m_place.AddPlacement(&m_outerCubesPlace);

		// Body
		m_body.Init(m_params.ufoRadius, nullptr, m_params.ufoLongitudeSubdivs, m_params.ufoLattitudeSubdivs);
		Vektoria::CHMat bodyMat;
		bodyMat.ScaleY(ufoHeightScale);
		m_body.Transform(bodyMat);
		m_bodyPlace.AddGeo(&m_body);

		// Top Cockpit
		m_top.Init(m_params.cockpitRadius, nullptr);
		Vektoria::CHMat topMat;
		topMat.ScaleY(cockpitHeightScale);
		m_top.Transform(topMat);
		m_topPlace.TranslateY(m_params.ufoHeightRadius);
		m_topPlace.AddGeo(&m_top);

		// Outer Cubes
		m_outerCube.Init(m_params.outerCubeSize, nullptr);
		m_outerCubePlaces.resize(m_params.outerCubesCount);
		for (int i = 0; i < m_params.outerCubesCount; i++)
		{
			auto& place = m_outerCubePlaces[i];
			place.AddGeo(&m_outerCube);

			place.TranslateX(m_params.ufoRadius - m_params.outerRadiusOffset);
			place.RotateYDelta((TWOPI / m_params.outerCubesCount) * i);
			m_outerCubesPlace.AddPlacement(&place);
		}
	}

	void update(float timeDelta)
	{
		m_outerCubesPlace.RotateYDelta(m_params.outerRotationSpeed * timeDelta);
	}

private:
	Parameter m_params;

	Vektoria::CPlacement m_place;

	Vektoria::CGeoSphere m_body;
	Vektoria::CPlacement m_bodyPlace;

	Vektoria::CGeoSphere m_top;
	Vektoria::CPlacement m_topPlace;

	Vektoria::CGeoCube m_outerCube;
	Vektoria::CPlacement m_outerCubesPlace;
	std::vector<Vektoria::CPlacement> m_outerCubePlaces;
};