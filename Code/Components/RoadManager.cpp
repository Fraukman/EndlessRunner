// Copyright 2017-2020 Crytek GmbH / Crytek Group. All rights reserved.
#include "StdAfx.h"
#include "RoadManager.h"
#include "GamePlugin.h"

#include <CryRenderer/IRenderAuxGeom.h>
#include <CrySchematyc/Env/Elements/EnvComponent.h>
#include <CryCore/StaticInstanceList.h>
#include <CryNetwork/Rmi.h>

namespace
{
	static void RegisterRoadManagerComponent(Schematyc::IEnvRegistrar& registrar)
	{
		Schematyc::CEnvRegistrationScope scope = registrar.Scope(IEntity::GetEntityScopeGUID());
		{
			Schematyc::CEnvRegistrationScope componentScope = scope.Register(SCHEMATYC_MAKE_ENV_COMPONENT(CRoadManagerComponent));
		}
	}

	CRY_STATIC_AUTO_REGISTER_FUNCTION(&RegisterRoadManagerComponent);
}

void CRoadManagerComponent::Initialize()
{
	
}


Cry::Entity::EventFlags CRoadManagerComponent::GetEventMask() const
{
	return Cry::Entity::EEvent::Reset | Cry::Entity::EEvent::Update | Cry::Entity::EEvent::GameplayStarted;
}

void CRoadManagerComponent::ProcessEvent(const SEntityEvent& event)
{
	const float frameTime = event.fParam[0];
	switch (event.event)
	{
	case Cry::Entity::EEvent::GameplayStarted:
	{
		for (int i = 0; i < 10; i++)
		{
			spawnRoad(Vec3(i * 10.0f,0.0f,0.0f));
		}
	}
	break;
	case Cry::Entity::EEvent::Update:
	{
		
	}
	break;
	case Cry::Entity::EEvent::Reset:
	{
		
	}
	break;	
	}
}

void CRoadManagerComponent::spawnRoad(Vec3 position)
{
	SEntitySpawnParams spawnParams;
	std::string enemySh = "schematyc::blueprints::road";
	spawnParams.pClass = gEnv->pEntitySystem->GetClassRegistry()->FindClass(enemySh.c_str());
	// Spawn the enemy entity
	if (IEntity* pEntity = gEnv->pEntitySystem->SpawnEntity(spawnParams))
	{
		Matrix34 etm = m_pEntity->GetWorldTM();

		etm.AddTranslation(position);

		pEntity->SetWorldTM(etm);
	}
}

