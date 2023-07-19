#include "pch.h"
#include "Physics2D.h"
#include "Scene.h"
#include "Layer.h"
#include "GameObject.h"
#include "RectCollider2D.h"
#include "CircleCollider2D.h"

Physics2D::Physics2D(Scene* const scene)
	: mScene(scene)
{
}

Physics2D::~Physics2D()
{
}

// POINT/CIRCLE
static boolean pointCircle(Vector2 pointPos, Vector2 circlePos, float r) 
{	
	const Vector2& DIST = pointPos - circlePos;	

	return DIST.x * DIST.x + DIST.y * DIST.y <= r * r;
}

// LINE/POINT
static boolean linePoint(float x1, float y1, float x2, float y2, float px, float py) {

	// get distance from the point to the two ends of the line
	float d1 = Vector2::Distance(Vector2(px, py), Vector2(x1, y1)); //dist(px, py, x1, y1);
	float d2 = Vector2::Distance(Vector2(px, py), Vector2(x2, y2)); //dist(px, py, x2, y2);

	// get the length of the line
	float lineLen = Vector2::Distance(Vector2(x1, y1), Vector2(x2, y2));

	// since floats are so minutely accurate, add
	// a little buffer zone that will give collision
	float buffer = 0.1f;    // higher # = less accurate

	// if the two distances are equal to the line's
	// length, the point is on the line!
	// note we use the buffer here to give a range,
	// rather than one #
	if (d1 + d2 >= lineLen - buffer && d1 + d2 <= lineLen + buffer) {
		return true;
	}
	return false;
}

// LINE/CIRCLE
static boolean lineCircle(float x1, float y1, float x2, float y2, float cx, float cy, float r, 
	Collider2D* const collider, RayCast2DHitInfo* const outHitInfo)
{

	// is either end INSIDE the circle?
	// if so, return true immediately
	boolean inside1 = pointCircle(Vector2(x1, y1), Vector2(cx, cy), r);
	boolean inside2 = pointCircle(Vector2(x2, y2), Vector2(cx, cy), r);
	
	if (inside1)
	{
		outHitInfo->hitPos = Vector2(x1, y1);
		outHitInfo->collider = collider;
		return true;
	}

	// get length of the line
	Vector2 dist = Vector2(x1, y1) - Vector2(x2, y2);

	//float len = sqrt((distX * distX) + (distY * distY));

	// get dot product of the line and circle
	float dot = (((cx - x1) * (x2 - x1)) + ((cy - y1) * (y2 - y1))) / (dist.x * dist.x + dist.y * dist.y);

	// find the closest point on the line
	float closestX = x1 + (dot * (x2 - x1));
	float closestY = y1 + (dot * (y2 - y1));

	// is this point actually on the line segment?
	// if so keep going, but if not, return false
	boolean onSegment = linePoint(x1, y1, x2, y2, closestX, closestY);
	if (!onSegment && !inside2)
	{
		return false;
	}

	// get distance to closest point
	//distX = closestX - cx;
	//distY = closestY - cy;
	dist = Vector2(closestX, closestY) - Vector2(cx, cy);

	Vector2 directionNormal = Vector2(x2 - x1, y2 - y1);
	directionNormal.Normalize();

	const float interDist = sqrtf(r * r - ((dist.x * dist.x) + (dist.y * dist.y)));

	Vector2 hitPos = Vector2(closestX, closestY);
	hitPos -= directionNormal * interDist;

	if (interDist <= r || inside2)
	{
		outHitInfo->hitPos = hitPos;
		outHitInfo->collider = collider;

		return true;
	}
	return false;
}

bool Physics2D::RayCastHit2D(const Vector2& origin,
	const Vector2& direction,
	const float distance,
	const eLayerType layerType,
	RayCast2DHitInfo* const outHitInfo)
{
	Assert(mScene, WCHAR_IS_NULLPTR);
	Assert(outHitInfo, WCHAR_IS_NULLPTR);

	const Layer& layer = mScene->GetLayer(layerType);
	const std::vector<GameObject*>& gameObjects = layer.GetGameObjects();

	bool bColliison = false;

	for (GameObject* const gameObject : gameObjects)
	{
		Collider2D* const collider = gameObject->GetComponentOrNull<Collider2D>();

		if (nullptr == collider)
		{
			continue;
		}

		Vector2 normalDirection = direction;
		normalDirection.Normalize();

		const Vector2& a = origin;
		const Vector2& b = origin + normalDirection * distance;
		const Vector3& c = collider->GetColliderWorldMatrix().Translation();


		if (collider->GetCollideType() == eCollider2DType::Circle)
		{
			constexpr const Vector3 vertexPos = Vector3(0.5f, 0.0f, 0.f);
			const Vector3& RADIUS = XMVector3TransformNormal(vertexPos, collider->GetColliderWorldMatrix());

			bColliison = lineCircle(a.x, a.y, b.x, b.y, c.x, c.y, RADIUS.Length(), collider, outHitInfo);
		}

		if (bColliison)
		{
			break;
		}
	}

	return bColliison;
}
