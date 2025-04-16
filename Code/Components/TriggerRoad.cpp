// Copyright 2017-2020 Crytek GmbH / Crytek Group. All rights reserved.
#include "StdAfx.h"
#include "TriggerRoad.h"
#include "GamePlugin.h"

#include <CryRenderer/IRenderAuxGeom.h>
#include <CrySchematyc/Env/Elements/EnvComponent.h>
#include <CryCore/StaticInstanceList.h>
#include <CryNetwork/Rmi.h>
#include "Player.h"

namespace
{
	static void RegisterTriggerRoadComponent(Schematyc::IEnvRegistrar& registrar)
	{
		Schematyc::CEnvRegistrationScope scope = registrar.Scope(IEntity::GetEntityScopeGUID());
		{
			Schematyc::CEnvRegistrationScope componentScope = scope.Register(SCHEMATYC_MAKE_ENV_COMPONENT(CTriggerRoadComponent));
		}
	}

	CRY_STATIC_AUTO_REGISTER_FUNCTION(&RegisterTriggerRoadComponent);
}

void CTriggerRoadComponent::Initialize()
{
	pTriggerComponent = m_pEntity->CreateComponent<IEntityTriggerComponent>();
	AABB triggerBounds = AABB(m_triggerSize * -0.5f, m_triggerSize * 0.5f);
	triggerBounds.Move(m_triggerPosition);
	pTriggerComponent->SetTriggerBounds(triggerBounds);

	if (IEntity* pEntity = gEnv->pEntitySystem->FindEntityByName("RoadManager")) {
		m_pRoadManager = pEntity->GetComponent<CRoadManagerComponent>();
	}
}


Cry::Entity::EventFlags CTriggerRoadComponent::GetEventMask() const
{
	return Cry::Entity::EEvent::Reset | Cry::Entity::EEvent::Update | Cry::Entity::EEvent::GameplayStarted | Cry::Entity::EEvent::EntityEnteredThisArea |
		Cry::Entity::EEvent::EntityLeftThisArea;
}

void CTriggerRoadComponent::ProcessEvent(const SEntityEvent& event)
{
	const float frameTime = event.fParam[0];
	switch (event.event)
	{
	case Cry::Entity::EEvent::GameplayStarted:
	{
		if(IEntity* pEntity = gEnv->pEntitySystem->FindEntityByName("RoadManager")){
			m_pRoadManager = pEntity->GetComponent<CRoadManagerComponent>();
		}
	}
	break;
	case Cry::Entity::EEvent::Update:
	{
		AABB triggerBounds = AABB(m_triggerSize * -0.5f, m_triggerSize * 0.5f);
		triggerBounds.Move(m_triggerPosition);
		pTriggerComponent->SetTriggerBounds(triggerBounds);


		AABB triggerBounds2;
		pTriggerComponent->GetTriggerBounds(triggerBounds2);
		RenderDebugCubeFromAABB(triggerBounds2, Col_Blue);
	}
	break;
	case Cry::Entity::EEvent::EntityEnteredThisArea:
	{
		const EntityId enteredEntity = static_cast<EntityId>(event.nParam[0]);
		IEntity* entity = gEnv->pEntitySystem->GetEntity(enteredEntity);
		if (entity) {

			if (CPlayerComponent* playerComp = entity->GetComponent<CPlayerComponent>())
			{
				CryLog("player entered");
				collided = true;
				if (m_pRoadManager)
				{
					m_pRoadManager->spawnRoad();
				}
				//gEnv->pEntitySystem->RemoveEntity(m_pEntity->GetId());
			}
		}
	}break;

	case Cry::Entity::EEvent::EntityLeftThisArea:
	{
		if (collided)
		{
			CryLog("player left");
			gEnv->pEntitySystem->RemoveEntity(m_pEntity->GetId());
		}	
		
	}break;
	case Cry::Entity::EEvent::Reset:
	{
		
	}
	break;	
	}
}

void CTriggerRoadComponent::RenderDebugCubeFromAABB(const AABB& aabb, const ColorF& color /*= 0xFF0000FF*/)
{
	IRenderAuxGeom* pRenderAuxGeom = gEnv->pRenderer->GetIRenderAuxGeom();
	pRenderAuxGeom->DrawAABB(aabb, m_pEntity->GetWorldTM(), false, color, EBoundingBoxDrawStyle::eBBD_Faceted);
}
