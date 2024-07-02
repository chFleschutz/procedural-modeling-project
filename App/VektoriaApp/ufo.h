#pragma once

#include "Vektoria/GeoBezierTable.h"
#include "Vektoria/GeoCube.h"
#include "Vektoria/GeoSphere.h"
#include "Vektoria/GeoSweep.h"
#include "Vektoria/Placement.h"
#include "Vektoria/Scene.h"
#include "VektoriaMath/HMats.h"

#include <algorithm>
#include <vector>

class UFO
{
public:
	struct Ring
	{
		struct Config
		{
			int objectCount = 10;
			float orbitRadius = 12.0f;
			float orbitHeight = 0.0f;
			float rotationSpeed = 2.0f;
			float objectScale = 1.0f;
		};

		Ring(const Ring::Config& config) : config(config) {}

		Ring::Config config;
		Vektoria::CPlacement place;
		std::vector<Vektoria::CPlacement> objectPlaces;
	};

	struct Parameter
	{
		// Ufo
		float rotationSpeed = -1.0f;
		float tiltAngle = UM_DEG2RAD(5.0f);

		// Ufo Body
		float ufoRadius = 10.0f;
		float ufoHeight = 4.0f;
		int ufoSweepSteps = 100;

		float cockpitRadius = 1.5f;
		float cockpitHeight = 1.0f;
		float cockpitHeightOffset = -0.5f;
		float cockpitSubdivisions = 32;

		// Beam
		float upperBeamRadius = 0.5f;
		float lowerBeamRadius = 3.0f;
		float beamLength = 20.0f;

		Vektoria::CColor beamLightColor = Vektoria::CColor(0.0f, 0.0f, 1.0f);
		float beamLightIntensity = 4.0f;
	};

	UFO() = default;
	~UFO() = default;

	void setParameters(const Parameter& params) { m_params = params; }
	const Parameter& parameters() const { return m_params; }

	void addRing(const Ring::Config& config) { m_rings.push_back(Ring(config)); }

	void initialize(Vektoria::CScene& scene, const Vektoria::CHVector& pos = {});
	void update(float timeDelta);

	// Materials
	void setBodyMaterial(Vektoria::CMaterial* material) { m_bodyMat = material; }
	void setCockPitMaterial(Vektoria::CMaterial* material) { m_cockpitMat = material; }
	void setBeamMaterial(Vektoria::CMaterial* material) { m_beamMat = material; }

private:
	void createUfo();
	void createBeam();
	void createRings();

	Parameter m_params;

	std::vector<Ring> m_rings;

	// Placements
	Vektoria::CPlacement m_place;
	Vektoria::CPlacement m_ufoRotator;
	Vektoria::CPlacement m_ufoBase;
	Vektoria::CPlacement m_bodyPlace;
	Vektoria::CPlacement m_cockpitPlace;
	Vektoria::CPlacement m_beamPlace;
	Vektoria::CPlacement m_beamLightPlace;
	Vektoria::CPlacement m_ringsPlace;

	// Geos
	Vektoria::CGeoSweep m_bodySweep;
	Vektoria::COutline m_bodyOutline;

	Vektoria::CGeoSphere m_cockpit;

	Vektoria::COutline m_beamOutline;
	Vektoria::CGeoSweep m_beamSweep;
	Vektoria::CLightSpot m_beamLight;
	Vektoria::CLightRadial m_beamLightRadial;

	Vektoria::CGeoCube m_cube;

	// Materials
	Vektoria::CMaterial* m_bodyMat = nullptr;
	Vektoria::CMaterial* m_cockpitMat = nullptr;
	Vektoria::CMaterial* m_beamMat = nullptr;
};