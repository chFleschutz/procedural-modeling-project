#include "ufo.h"

void UFO::initialize(Vektoria::CScene& scene, const Vektoria::CHVector& pos)
{
	createUfo();
	createBeam();
	createRings();

	// Hierachy
	scene.AddPlacement(&m_place);
	m_place.Translate(pos);
	m_place.AddPlacement(&m_ufoRotator);
	m_ufoRotator.AddPlacement(&m_beamPlace);
	m_ufoRotator.AddPlacement(&m_ufoBase);
	m_ufoBase.AddPlacement(&m_bodyPlace);
	m_ufoBase.AddPlacement(&m_cockpitPlace);
	m_ufoBase.AddPlacement(&m_ringsPlace);
	m_ufoBase.RotateDelta(1.0f, 0.0f, 1.0f, m_params.tiltAngle);
}

void UFO::update(float timeDelta)
{
	m_ufoRotator.RotateYDelta(m_params.rotationSpeed * timeDelta);

	for (auto& ring : m_rings)
	{
		ring.place.RotateYDelta(ring.config.rotationSpeed * timeDelta);
	}
}

void UFO::createUfo()
{
	// Outline for the UFO body
	// { height, radius }
	std::vector<Vektoria::C2dVector> points{
		{ 0.961919f, 0.000000f},
		{ 0.961919f, 0.752423f},
		{ 1.000000f, 0.752423f},
		{ 1.000000f, 0.753580f},
		{ 1.000000f, 0.843599f},
		{ 1.000000f, 0.845288f},
		{ 0.999113f, 0.847429f},
		{ 0.594528f, 1.824023f},
		{ 0.593969f, 1.825371f},
		{ 0.593808f, 1.827060f},
		{ 0.575201f, 2.021953f},
		{ 0.557738f, 2.221083f},
		{ 0.532169f, 2.422601f},
		{ 0.500017f, 2.622952f},
		{ 0.462805f, 2.818582f},
		{ 0.422053f, 3.005934f},
		{ 0.379286f, 3.181453f},
		{ 0.336024f, 3.341585f},
		{ 0.293791f, 3.482773f},
		{ 0.254108f, 3.601464f},
		{ 0.218498f, 3.694100f},
		{ 0.188483f, 3.757128f},
		{ 0.165586f, 3.786991f},
		{ 0.131987f, 3.697482f},
		{ 0.131144f, 3.786666f},
		{ 0.129582f, 3.951794f},
		{ 0.126363f, 4.023073f},
		{ 0.119708f, 4.100248f},
		{ 0.110307f, 4.181112f},
		{ 0.098848f, 4.263461f},
		{ 0.086022f, 4.345088f},
		{ 0.072517f, 4.423789f},
		{ 0.059023f, 4.497357f},
		{ 0.046230f, 4.563586f},
		{ 0.034826f, 4.620272f},
		{ 0.025502f, 4.665208f},
		{ 0.018946f, 4.696189f},
		{ 0.015848f, 4.711010f},
		{ 0.010546f, 4.738489f},
		{ 0.005117f, 4.765763f},
		{-0.000364f, 4.792530f},
		{-0.005825f, 4.818491f},
		{-0.011195f, 4.843347f},
		{-0.016399f, 4.866796f},
		{-0.021366f, 4.888540f},
		{-0.026024f, 4.908278f},
		{-0.030298f, 4.925710f},
		{-0.034118f, 4.940536f},
		{-0.037409f, 4.952457f},
		{-0.040100f, 4.961172f},
		{-0.063521f, 4.924375f},
		{-0.074828f, 4.961172f},
		{-0.074828f, 5.042081f},
		{-0.076714f, 5.074157f},
		{-0.082324f, 5.089999f},
		{-0.091586f, 5.113923f},
		{-0.104428f, 5.143902f},
		{-0.120778f, 5.177908f},
		{-0.140564f, 5.213913f},
		{-0.163714f, 5.249890f},
		{-0.190157f, 5.283809f},
		{-0.219820f, 5.313644f},
		{-0.252633f, 5.337366f},
		{-0.288521f, 5.352948f},
		{-0.307968f, 5.357827f},
		{-0.327415f, 5.358361f},
		{-0.335834f, 5.351654f},
		{-0.344254f, 5.336234f},
		{-0.353601f, 5.309584f},
		{-0.362949f, 5.273708f},
		{-0.382875f, 5.176167f},
		{-0.403408f, 5.048991f},
		{-0.423921f, 4.897563f},
		{-0.443790f, 4.727264f},
		{-0.462389f, 4.543476f},
		{-0.479094f, 4.351581f},
		{-0.493278f, 4.156960f},
		{-0.504316f, 3.964996f},
		{-0.511584f, 3.781070f},
		{-0.514450f, 3.610898f},
		{-0.514456f, 3.610563f},
		{-0.514603f, 3.610213f},
		{-0.523739f, 3.588453f},
		{-0.549404f, 3.526848f},
		{-0.588187f, 3.428242f},
		{-0.636825f, 3.295133f},
		{-0.692054f, 3.130015f},
		{-0.750611f, 2.935384f},
		{-0.809232f, 2.713735f},
		{-0.864654f, 2.467565f},
		{-0.913614f, 2.199368f},
		{-0.952847f, 1.911641f},
		{-0.979090f, 1.606880f},
		{-0.989018f, 1.289581f},
		{-0.989081f, 1.287579f},
		{-0.989081f, 1.286157f},
		{-0.989081f, 0.830970f},
		{-0.989081f, 0.829845f},
		{-0.937838f, 0.829845f},
		{-0.937838f, 0.773446f},
		{-0.971910f, 0.773446f},
		{-0.971910f, 0.771453f},
		{-0.971910f, 0.000000f},
	};

	// Calculate width and height of the outline
	auto minHeight = std::min_element(points.begin(), points.end(),
		[](const Vektoria::C2dVector& a, const Vektoria::C2dVector& b) {
			return a.x < b.x;
		});

	auto maxHeight = std::max_element(points.begin(), points.end(),
		[](const Vektoria::C2dVector& a, const Vektoria::C2dVector& b) {
			return a.x < b.x;
		});

	auto maxRadius = std::max_element(points.begin(), points.end(),
		[](const Vektoria::C2dVector& a, const Vektoria::C2dVector& b) {
			return a.y < b.y;
		});

	float outlineHeight = maxHeight->x - minHeight->x;
	float outlineRadius = maxRadius->y; // The outline is rotated around the origin -> minX = 0

	// Create outline from points vector
	for (auto& point : points)
	{
		m_bodyOutline.Add(&point);
	}

	std::vector<Vektoria::CHMat> transformMats(m_params.ufoSweepSteps);
	Vektoria::CHMats bodyMatPointers;
	for (int i = 0; i < m_params.ufoSweepSteps; i++)
	{
		Vektoria::CHMat mat;
		mat.RotateX((TWOPI / (m_params.ufoSweepSteps - 1)) * i);
		transformMats[i] = mat;
		bodyMatPointers.Add(&transformMats[i]);
	}

	// Create UFO body from outline
	float heightScale = m_params.ufoHeight / outlineHeight;
	float widthScale = m_params.ufoRadius / outlineRadius;

	m_bodySweep.InitOutline(m_bodyOutline, bodyMatPointers, m_bodyMat);
	m_bodyPlace.AddGeo(&m_bodySweep);
	m_bodyPlace.RotateZ(HALFPI);
	m_bodyPlace.ScaleDelta(widthScale, heightScale, widthScale);

	// Cockpit
	m_cockpit.Init(m_params.cockpitRadius, m_cockpitMat, m_params.cockpitSubdivisions, m_params.cockpitSubdivisions);

	Vektoria::CHMat cockpitTransform;
	cockpitTransform.ScaleY(m_params.cockpitHeight / m_params.cockpitRadius);
	m_cockpit.Transform(cockpitTransform);

	m_cockpitPlace.AddGeo(&m_cockpit);
	m_cockpitPlace.TranslateYDelta((0.5f * m_params.ufoHeight) + m_params.cockpitHeightOffset);
}

void UFO::createBeam()
{
	m_beamOutline.InitCircle(m_params.upperBeamRadius, 100);

	Vektoria::CHMat upperBeamMat, lowerBeamMat;
	lowerBeamMat.Scale(m_params.lowerBeamRadius / m_params.upperBeamRadius);
	lowerBeamMat.TranslateYDelta(-m_params.beamLength);

	Vektoria::CHMats beamMatPointers;
	beamMatPointers.Add(&upperBeamMat);
	beamMatPointers.Add(&lowerBeamMat);

	m_beamSweep.InitOutline(m_beamOutline, beamMatPointers, m_beamMat);
	m_beamSweep.Flip(); // Vertices from circle outline are in the wrong order
	m_beamPlace.AddGeo(&m_beamSweep);

	m_beamLight.Init(m_params.beamLightColor, UM_DEG2RAD(10.0f), UM_DEG2RAD(45.0f), m_params.beamLightIntensity);
	m_beamLightPlace.AddLightSpot(&m_beamLight);
	m_beamLightPlace.RotateX(-HALFPI); // Point downwards
	m_beamPlace.AddPlacement(&m_beamLightPlace);

	m_beamLightRadial.Init(m_params.beamLightColor * 0.01f, 1.0f);
	m_beamLightPlace.AddLightRadial(&m_beamLightRadial);
}

void UFO::createRings()
{
	// dummy geo
	m_cube.Init(0.1f, nullptr);
	auto sphere = new Vektoria::CGeoSphere();
	sphere->Init(0.2f, nullptr, 32, 32);
	Vektoria::CHMat sphereTransform;
	sphereTransform.Scale(1.0f, 0.5f, 1.0f);
	sphere->Transform(sphereTransform);

	for (auto& ring : m_rings)
	{
		int objectCount = ring.config.objectCount;
		ring.objectPlaces.resize(objectCount);
		for (int i = 0; i < objectCount; i++)
		{
			auto& objectPlace = ring.objectPlaces[i];
			objectPlace.AddGeo(sphere); // TODO: Add different geos
			objectPlace.Scale(ring.config.objectScale);
			objectPlace.TranslateDelta(ring.config.orbitRadius, ring.config.orbitHeight, 0.0f);
			objectPlace.RotateYDelta((TWOPI / objectCount) * i);
			ring.place.AddPlacement(&objectPlace);
		}

		m_ringsPlace.AddPlacement(&ring.place);
	}
}
