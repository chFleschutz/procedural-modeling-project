#pragma once

#include "Vektoria/Scene.h"
#include "Vektoria/PoseInfrastructure.h"

class Road
{
public:
	struct Parameters
	{
		float roundaboutRadius = 20.0f;
	};

	Road() = default;
	~Road() = default;

	void initialize(Vektoria::CScene& scene, const Vektoria::CHVector& pos = {})
	{
		float radius = m_params.roundaboutRadius;

		auto crossing1 = m_infra.MakeCrossing(-radius, 0.0f, 0.0f);
		auto crossing2 = m_infra.MakeCrossing(radius, 0.0f, 0.0f);

		auto way1 = m_infra.MakeWay(crossing1, crossing2, eKindWay_Street1);
		auto way2 = m_infra.MakeWay(crossing2, crossing1, eKindWay_Street1);
		auto way3 = m_infra.MakeWay(crossing1, crossing2, eKindWay_Street1);

		way1->AddMidPointBetween(0.0f, 0.0f, radius);

		way2->AddMidPointBetween(0.0f, 0.0f, -radius);

		way3->AddMidPointBetween(-20.0f, 2.0f, 40.0f);
		way3->AddMidPointBetween(20.0f, 2.0f, 40.0f);

		m_infra.CreateNet();

		auto area1 = m_infra.MakeArea(way2, crossing1, nullptr);
		auto area2 = m_infra.MakeArea(way3, crossing2, nullptr);

		m_infra.Init();
		m_infra.Translate(pos);
		scene.AddPlacement(&m_infra);
	}

private:
	Parameters m_params;

	Vektoria::CPoseInfrastructure m_infra;
};