#pragma once

#include "Vektoria/GeoSign.h"
#include "Vektoria/GeoSweep.h"
#include "Vektoria/PoseInfrastructure.h"
#include "Vektoria/Scene.h"

class Road
{
public:
	struct Parameters
	{
		float roundaboutRadius = 20.0f;

		float innerHillRadius = 21.0f;
		float outerHillRadius = 25.0f;
		float hillHeight = 2.0f;

		int quarterCircleSteps = 32;

		float signOffsetx = 1.0f;
		float signOffsetz = 4.5f;
		float signScale = 0.75f;

		Vektoria::EKindWay wayType = Vektoria::eKindWay_Street1;
		Vektoria::EKindCrossing crossingType = Vektoria::eKindCrossing_Street1;
	};

	Road() = default;
	~Road() = default;

	void setParameters(const Parameters& params) { m_params = params; }
	const Parameters& parameters() const { return m_params; }

	void setRoadMaterial(Vektoria::CMaterial* mat) { m_roadMat = mat; }
	void setCrossingMaterial(Vektoria::CMaterial* mat) { m_crossingMat = mat; }
	void setAreaMaterial(Vektoria::CMaterial* mat) { m_areaMat = mat; }

	void initialize(Vektoria::CScene& scene, const Vektoria::CHVector& pos = {});

private:
	void addQuarterCircle(Vektoria::CHVectors& line, float radius, float height, float startOffset = 0.0f, float direction = 1.0f) const;

	Parameters m_params;

	Vektoria::CPlacement m_place;
	Vektoria::CPoseInfrastructure m_infra;

	Vektoria::CPlacement m_hillPlace;
	Vektoria::CGeoSweep m_hillSweep;
	Vektoria::COutline m_hillOutline;

	Vektoria::CGeoSign m_sign;
	Vektoria::CPlacement m_signPlace1;
	Vektoria::CPlacement m_signPlace2;
	Vektoria::CPlacement m_signPlace3;
	Vektoria::CPlacement m_signPlace4;

	Vektoria::CPlacement m_signPlace5;
	Vektoria::CPlacement m_signPlace6;
	Vektoria::CPlacement m_signPlace7;
	Vektoria::CPlacement m_signPlace8;	

	// Materials
	Vektoria::CMaterial* m_roadMat = nullptr;
	Vektoria::CMaterial* m_crossingMat = nullptr;
	Vektoria::CMaterial* m_areaMat = nullptr;
};