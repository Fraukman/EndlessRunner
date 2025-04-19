// Copyright 2017-2020 Crytek GmbH / Crytek Group. All rights reserved.
#include "StdAfx.h"
#include "ObstaclesManager.h"
#include "GamePlugin.h"

#include <CryRenderer/IRenderAuxGeom.h>
#include <CrySchematyc/Env/Elements/EnvComponent.h>
#include <CryCore/StaticInstanceList.h>
#include <CryNetwork/Rmi.h>
#include "CryMath/Random.h"
#include "DefaultComponents/Geometry/StaticMeshComponent.h"

namespace
{
	static void RegisterCObstaclesManagerComponent(Schematyc::IEnvRegistrar& registrar)
	{
		Schematyc::CEnvRegistrationScope scope = registrar.Scope(IEntity::GetEntityScopeGUID());
		{
			Schematyc::CEnvRegistrationScope componentScope = scope.Register(SCHEMATYC_MAKE_ENV_COMPONENT(CObstaclesManagerComponent));
		}
	}

	CRY_STATIC_AUTO_REGISTER_FUNCTION(&RegisterCObstaclesManagerComponent);
}

void CObstaclesManagerComponent::Initialize()
{
	/*spawnObstacle(Vec3(5, 5, 0));
	spawnObstacle(Vec3(15, 5, 0));
	spawnObstacle(Vec3(25, 5, 0));
	spawnObstacle(Vec3(35, 5, 0));*/
}


Cry::Entity::EventFlags CObstaclesManagerComponent::GetEventMask() const
{
	return Cry::Entity::EEvent::Reset | Cry::Entity::EEvent::Update | Cry::Entity::EEvent::GameplayStarted;
}

void CObstaclesManagerComponent::ProcessEvent(const SEntityEvent& event)
{
	const float frameTime = event.fParam[0];
	switch (event.event)
	{
	case Cry::Entity::EEvent::GameplayStarted:
	{	
			
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

void CObstaclesManagerComponent::spawnObstacle(Vec3 spawnPosition)
{
	if (cry_random(0.0f, 1.0f) > 0.5f || m_spawnedObjects >= 3)
	{
		return;
	}
	m_spawnedObjects++;
	SEntitySpawnParams spawnParams;
	std::string enemySh = "schematyc::blueprints::obstacle";
	spawnParams.pClass = gEnv->pEntitySystem->GetClassRegistry()->FindClass(enemySh.c_str());
	// Spawn the enemy entity
	if (IEntity* pEntity = gEnv->pEntitySystem->SpawnEntity(spawnParams))
	{
		Cry::DefaultComponents::CStaticMeshComponent* meshcomp = pEntity->GetComponent<Cry::DefaultComponents::CStaticMeshComponent>();
		if (meshcomp)
		{
			meshcomp->SetObject(m_obstaclesNames.At(cry_random(0, (int)m_obstaclesNames.Size()-1)).value);
			m_pEntity->AttachChild(pEntity);
			Matrix34 etm = m_pEntity->GetWorldTM();

			etm.AddTranslation(spawnPosition);

			pEntity->SetWorldTM(etm);
		}
	}

}

