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
		// Ufo
		float rotationSpeed = -1.0f;
		float tiltAngle = UM_DEG2RAD(5.0f);

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
		float outerRotationSpeed = 2.0f;

		// Beam
		float lowerBeamRadius = 2.0f;
		float beamLength = 15.0f;
	};

	UFO() = default;
	~UFO() = default;

	void setParameters(const Parameter& params) { m_params = params; }
	const Parameter& parameters() const { return m_params; }

	void initialize(Vektoria::CScene& scene, const Vektoria::CHVector& pos = {})
	{
		float ufoHeightScale = m_params.ufoHeightRadius / m_params.ufoRadius;
		float cockpitHeightScale = m_params.cockpitHeightRadius / m_params.cockpitRadius;

		// Hierachy
		scene.AddPlacement(&m_place);
		m_place.Translate(pos);
		m_place.AddPlacement(&m_ufoBase);
		m_ufoBase.AddPlacement(&m_beamPlace);
		m_ufoBase.AddPlacement(&m_bodyPlace);
		m_bodyPlace.AddPlacement(&m_topPlace);
		m_bodyPlace.AddPlacement(&m_outerCubesPlace);
		m_bodyPlace.RotateDelta(1.0f, 0.0f, 1.0f, m_params.tiltAngle);

		// Body
		m_body.Init(m_params.ufoRadius, m_bodyMat, m_params.ufoLongitudeSubdivs, m_params.ufoLattitudeSubdivs);
		Vektoria::CHMat bodyMat;
		bodyMat.ScaleY(ufoHeightScale);
		m_body.Transform(bodyMat);
		m_bodyPlace.AddGeo(&m_body);

		// Top Cockpit
		m_top.Init(m_params.cockpitRadius, m_cockpitMat);
		Vektoria::CHMat topMat;
		topMat.ScaleY(cockpitHeightScale);
		m_top.Transform(topMat);
		m_topPlace.TranslateY(m_params.ufoHeightRadius);
		m_topPlace.AddGeo(&m_top);

		// Outer Cubes
		m_outerCube.Init(m_params.outerCubeSize, m_outerCubeMat);
		m_outerCubePlaces.resize(m_params.outerCubesCount);
		for (int i = 0; i < m_params.outerCubesCount; i++)
		{
			auto& place = m_outerCubePlaces[i];
			place.AddGeo(&m_outerCube);

			place.TranslateX(m_params.ufoRadius - m_params.outerRadiusOffset);
			place.RotateYDelta((TWOPI / m_params.outerCubesCount) * i);
			m_outerCubesPlace.AddPlacement(&place);
		}

		// Beam
		m_beam.Init(m_params.lowerBeamRadius, m_params.beamLength, m_beamMat, 50);
		m_beamPlace.TranslateY(-m_params.beamLength);
		m_beamPlace.AddGeo(&m_beam);
	}

	void update(float timeDelta)
	{
		m_outerCubesPlace.RotateYDelta(m_params.outerRotationSpeed * timeDelta);
		m_ufoBase.RotateYDelta(m_params.rotationSpeed * timeDelta);
	}

	void setBodyMaterial(Vektoria::CMaterial* material) { m_bodyMat = material; }
	void setCockPitMaterial(Vektoria::CMaterial* material) { m_cockpitMat = material; }
	void setOuterCubeMaterial(Vektoria::CMaterial* material) { m_outerCubeMat = material; }
	void setBeamMaterial(Vektoria::CMaterial* material) { m_beamMat = material; }

private:
	Parameter m_params;

	Vektoria::CPlacement m_place;
	Vektoria::CPlacement m_ufoBase;

	Vektoria::CGeoSphere m_body;
	Vektoria::CPlacement m_bodyPlace;

	Vektoria::CGeoSphere m_top;
	Vektoria::CPlacement m_topPlace;

	Vektoria::CGeoCube m_outerCube;
	Vektoria::CPlacement m_outerCubesPlace;
	std::vector<Vektoria::CPlacement> m_outerCubePlaces;

	Vektoria::CGeoCone m_beam;
	Vektoria::CPlacement m_beamPlace;

	// Materials
	Vektoria::CMaterial* m_bodyMat = nullptr;
	Vektoria::CMaterial* m_cockpitMat = nullptr;
	Vektoria::CMaterial* m_outerCubeMat = nullptr;
	Vektoria::CMaterial* m_beamMat = nullptr;
};