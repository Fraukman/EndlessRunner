// Copyright 2017-2020 Crytek GmbH / Crytek Group. All rights reserved.
#pragma once

#include <CryEntitySystem/IEntityComponent.h>

#include <CryRenderer/IRenderAuxGeom.h>
#include "RoadManager.h"


class CTriggerRoadComponent final : public IEntityComponent
{	
public:
	CTriggerRoadComponent() = default;
	virtual ~CTriggerRoadComponent() = default;

	// IEntityComponent
	virtual void Initialize() override;

	virtual Cry::Entity::EventFlags GetEventMask() const override;
	virtual void ProcessEvent(const SEntityEvent& event) override;	
	// ~IEntityComponent

	// Reflect type to set a unique identifier for this component
	static void ReflectType(Schematyc::CTypeDesc<CTriggerRoadComponent>& desc)
	{
		desc.SetGUID("{0723512D-2B34-4E3F-990B-693D67B70851}"_cry_guid);	
		desc.AddMember(&CTriggerRoadComponent::m_triggerSize, 'ets', "enemytriggersize", "Enemy trigger size", "sets the enemy trigger size", Vec3(1.0f));
		desc.AddMember(&CTriggerRoadComponent::m_triggerPosition, 'etp', "enemytriggerposition", "Enemy trigger offset position", "sets the enemy offset position", Vec3(1.0f));
	}	
	

protected:	
	void RenderDebugCubeFromAABB(const AABB& aabb, const ColorF& color = 0xFF0000FF);

private:
	CRoadManagerComponent* m_pRoadManager = nullptr;
	IEntityTriggerComponent* pTriggerComponent;
	Vec3 m_triggerSize = Vec3(1.0f);
	Vec3 m_triggerPosition = Vec3(1.0f);

	bool collided = false;
};
