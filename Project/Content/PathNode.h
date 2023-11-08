#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"
#include <Engine/EnumLayer.h>

REGISTER_SCRIPTCOMPONENT_TYPE(PathNode);

class PathNode : public ScriptComponent
{
public:
	PathNode();
	virtual ~PathNode();
	PathNode(const PathNode&) = delete;
	PathNode& operator=(const PathNode&) = delete;

	void SetType(const eLayerType type) { mType = type; }
	void SetIdx(const int idx) { mIdx = idx; }

	const eLayerType GetType() const { return mType; }
	const int GetIdx() const { return mIdx; }

	Vector2 GetPosition() const;

	Vector3 GetLineStartPosition() const;
	Vector3 GetLineEndPosition() const;


private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;


private:
	eLayerType mType;
	int mIdx;
};
