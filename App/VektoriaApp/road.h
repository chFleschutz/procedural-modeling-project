#pragma once

#include "Vektoria/Scene.h"
#include "Vektoria/PoseInfrastructure.h"

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
		scene.AddPlacement(&m_place);
		m_place.Translate(pos);

		// Hill side
		Vektoria::CHMats hillMatPointers;
		Vektoria::CHMat baseMat, topMat;
		baseMat.Scale(m_params.outerHillRadius, 0.0f, m_params.outerHillRadius);
		topMat.Scale(m_params.innerHillRadius - 0.01f, 0.0f, m_params.innerHillRadius - 0.01f);
		topMat.TranslateYDelta(m_params.hillHeight);
		hillMatPointers.Add(&baseMat);
		hillMatPointers.Add(&topMat);

		m_hillOutline.InitCircle(1.0f, 4 * m_params.quarterCircleSteps);
		m_hillSweep.SetTextureRepeat(10.0f, 0.5f);
		m_hillSweep.InitOutline(m_hillOutline, hillMatPointers, m_areaMat);
		m_hillPlace.AddGeo(&m_hillSweep);
		m_place.AddPlacement(&m_hillPlace);

		// Infrastructure
		float radius = m_params.roundaboutRadius;
		Vektoria::EKindWay wayType = Vektoria::eKindWay_Street1;

		m_infra.SetMaterialForWay(wayType, m_roadMat);
		m_infra.SetMaterialForCrossing(eKindCrossing_Street1, m_crossingMat);

		auto crossing1 = m_infra.MakeCrossing(radius, 0.0f, 0.0f);
		auto crossing2 = m_infra.MakeCrossing(0.0f, 0.0f, radius);
		auto crossing3 = m_infra.MakeCrossing(-radius, 0.0f, 0.0f);
		auto crossing4 = m_infra.MakeCrossing(0.0f, 0.0f, -radius);

		float mappingContraction = 0.1f;
		crossing1->SetMappingContraction(mappingContraction);
		crossing2->SetMappingContraction(mappingContraction);
		crossing3->SetMappingContraction(mappingContraction);
		crossing4->SetMappingContraction(mappingContraction);

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

		auto areaInner = m_infra.MakeArea(way1, crossing1, m_areaMat);
		areaInner->SetUV(20.0f, 20.0f);

		Vektoria::CHVectors hemline1;
		hemline1.AddList(crossing1->GetHemlineRight(way1));
		hemline1.AddList(way1->GetHemlineLeft());
		addQuarterCircle(hemline1, m_params.innerHillRadius, 0.0f, HALFPI, -1.0f);

		Vektoria::CHVectors hemline2;
		hemline2.AddList(crossing2->GetHemlineRight(way2));
		hemline2.AddList(way2->GetHemlineLeft());
		addQuarterCircle(hemline2, m_params.innerHillRadius, 0.0f, PI, -1.0f);

		Vektoria::CHVectors hemline3;
		hemline3.AddList(crossing3->GetHemlineRight(way3));
		hemline3.AddList(way3->GetHemlineLeft());
		addQuarterCircle(hemline3, m_params.innerHillRadius, 0.0f, PI + HALFPI, -1.0f);

		Vektoria::CHVectors hemline4;
		hemline4.AddList(crossing4->GetHemlineRight(way4));
		hemline4.AddList(way4->GetHemlineLeft());
		addQuarterCircle(hemline4, m_params.innerHillRadius, 0.0f, 0.0f, -1.0f);

		auto areaOuter1 = m_infra.MakeArea(hemline1, m_areaMat);
		areaOuter1->SetUV(20.0f, 20.0f);

		auto areaOuter2 = m_infra.MakeArea(hemline2, m_areaMat);
		areaOuter2->SetUV(20.0f, 20.0f);

		auto areaOuter3 = m_infra.MakeArea(hemline3, m_areaMat);
		areaOuter3->SetUV(20.0f, 20.0f);

		auto areaOuter4 = m_infra.MakeArea(hemline4, m_areaMat);
		areaOuter4->SetUV(20.0f, 20.0f);

		m_infra.Init();
		m_infra.TranslateY(m_params.hillHeight);
		m_place.AddPlacement(&m_infra);
	}

private:
	void addQuarterCircle(Vektoria::CHVectors& line, float radius, float height, float startOffset = 0.0f, float direction = 1.0f) const
	{
		float angleStep = HALFPI / (m_params.quarterCircleSteps - 1);
		for (int i = 0; i < m_params.quarterCircleSteps; i++)
		{
			float angle = startOffset + (angleStep * i * direction);
			float x = radius * cosf(angle);
			float z = radius * sinf(angle);
			line.Make(x, height, z, 1.0f);
		}
	}

	Parameters m_params;

	Vektoria::CPlacement m_place;
	Vektoria::CPoseInfrastructure m_infra;

	Vektoria::CPlacement m_hillPlace;
	Vektoria::CGeoSweep m_hillSweep;
	Vektoria::COutline m_hillOutline;

	// Materials
	Vektoria::CMaterial* m_roadMat = nullptr;
	Vektoria::CMaterial* m_crossingMat = nullptr;
	Vektoria::CMaterial* m_areaMat = nullptr;
};