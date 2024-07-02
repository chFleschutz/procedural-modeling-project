#pragma once

#include "Vektoria/Scene.h"
#include "Vektoria/PoseInfrastructure.h"

class Road
{
public:
	struct Parameters
	{
		float roundaboutRadius = 25.0f;
	};

	Road() = default;
	~Road() = default;

	void setParameters(const Parameters& params) { m_params = params; }
	const Parameters& parameters() const { return m_params; }

	void setRoadMaterial(Vektoria::CMaterial* mat) { m_roadMat = mat; }
	void setCrossingMaterial(Vektoria::CMaterial* mat) { m_crossingMat = mat; }
	void setAreaMaterial(Vektoria::CMaterial* mat) { m_areaMat = mat; }

	void initialize(Vektoria::CScene& scene, const Vektoria::CHVector& pos = {})
	{
		float radius = m_params.roundaboutRadius;
		Vektoria::EKindWay wayType = Vektoria::eKindWay_Street1;

		m_infra.SetMaterialForWay(wayType, m_roadMat);
		m_infra.SetMaterialForCrossing(eKindCrossing_Street1, m_crossingMat);
		//m_infra.SetColorOfStripes(Vektoria::CColor(0.5f, 0.2f, 1.0f));

		auto crossing1 = m_infra.MakeCrossing(radius, 0.0f, 0.0f);
		auto crossing2 = m_infra.MakeCrossing(0.0f, 0.0f, radius);
		auto crossing3 = m_infra.MakeCrossing(-radius, 0.0f, 0.0f);
		auto crossing4 = m_infra.MakeCrossing(0.0f, 0.0f, -radius);

		auto way1 = m_infra.MakeWay(crossing1, crossing2, wayType);
		auto way2 = m_infra.MakeWay(crossing2, crossing3, wayType);
		auto way3 = m_infra.MakeWay(crossing3, crossing4, wayType);
		auto way4 = m_infra.MakeWay(crossing4, crossing1, wayType);

		float junctionLength = 0.2f * radius;
		crossing1->SetJunctionLengthAll(junctionLength);
		crossing3->SetJunctionLengthAll(junctionLength);
		crossing2->SetJunctionLengthAll(junctionLength);
		crossing4->SetJunctionLengthAll(junctionLength);

		m_infra.CreateNet();

		auto area1 = m_infra.MakeArea(way1, crossing1, m_areaMat);
		area1->SetUV(20.0f, 20.0f);

		m_infra.Init();
		m_infra.Translate(pos);
		scene.AddPlacement(&m_infra);
	}

private:
	Parameters m_params;

	Vektoria::CPoseInfrastructure m_infra;

	// Materials
	Vektoria::CMaterial* m_roadMat = nullptr;
	Vektoria::CMaterial* m_crossingMat = nullptr;
	Vektoria::CMaterial* m_areaMat = nullptr;
};