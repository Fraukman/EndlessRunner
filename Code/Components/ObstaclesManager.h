// Copyright 2017-2020 Crytek GmbH / Crytek Group. All rights reserved.
#pragma once

#include <CryEntitySystem/IEntityComponent.h>

#include <DefaultComponents/Input/InputComponent.h>
#include <DefaultComponents/Physics/CharacterControllerComponent.h>



class CObstaclesManagerComponent final : public IEntityComponent
{	
public:
	CObstaclesManagerComponent() = default;
	virtual ~CObstaclesManagerComponent() = default;

	// IEntityComponent
	virtual void Initialize() override;

	virtual Cry::Entity::EventFlags GetEventMask() const override;
	virtual void ProcessEvent(const SEntityEvent& event) override;	
	// ~IEntityComponent

	// Reflect type to set a unique identifier for this component
	static void ReflectType(Schematyc::CTypeDesc<CObstaclesManagerComponent>& desc)
	{
		desc.SetGUID("{E019950B-544C-4612-99C2-AA63E2AB1D7B}"_cry_guid);
		desc.AddMember(&CObstaclesManagerComponent::m_obstaclesNames, 'msn', "meshname", "mesh name", "mesh name", Schematyc::CArray<Schematyc::GeomFileName>());

	}	
	

	void spawnObstacle(Vec3 spawnPosition);
protected:	

private:	
	
	Schematyc::CArray<Schematyc::GeomFileName> m_obstaclesNames;
	int m_spawnedObjects = 0;
	
};
