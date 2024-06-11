#pragma once

#include "Vektoria/GeoTerrain.h"

#include <limits>

using namespace Vektoria;

class Island
{
public:
	Island() = default;

	void initialize(CScene& scene, float width = 100.0f, float height = 100.0f)
	{
		int vertexCount = 1000;
		int seed = 5;

		CPerlin perlin = CPerlin(seed, 
			3.0f, 10, 0.5f, 20.0f, 
			0.0f, 0.0f, 
			ePerlinInterpol_Standard, false);

		CBlob blob = CBlob(0.5f, 0.5f,
			0.5f, 0.5f, 10.0f,
			eBlobShapeGround_Radial,
			eBlobShapeSide_Dome,
			&perlin);

		CCut waterCut;
		waterCut.SetHeightLimits(std::numeric_limits<float>::lowest(), 0.1f);
		waterCut.SetFlattenLowerOn();
		waterCut.SetFlattenSmartOn();

		m_blueprint.AddBlob(&blob);
		m_blueprint.CreateField(width, height, vertexCount, vertexCount, 0.0f, 0.0f, 10.0f, 10.0f);

		m_terrain.AddCut(&waterCut);
		m_terrain.InitFromOther(m_blueprint, m_groundMat);

		m_waterGeo.SetTextureRepeat(100.0f, 100.0f);
		m_waterGeo.Init(width / 2.0f, 0.1f, m_waterMat, 100);

		m_place.AddGeo(&m_terrain);
		m_place.AddGeo(&m_waterGeo);
		scene.AddPlacement(&m_place);
	}

	void setWaterMaterial(CMaterial* material) { m_waterMat = material; }
	void setGroundMaterial(CMaterial* material) { m_groundMat = material; }

private:
	CPlacement m_place;
	CGeoTerrain m_terrain;
	CGeoTerrain m_blueprint;
	CGeoCylinder m_waterGeo;

	CMaterial* m_waterMat = nullptr;
	CMaterial* m_groundMat = nullptr;
};