// Copyright 2017-2020 Crytek GmbH / Crytek Group. All rights reserved.
#pragma once

#include <CryEntitySystem/IEntityComponent.h>

#include <DefaultComponents/Input/InputComponent.h>
#include <DefaultComponents/Physics/CharacterControllerComponent.h>



class CRoadManagerComponent final : public IEntityComponent
{	
public:
	CRoadManagerComponent() = default;
	virtual ~CRoadManagerComponent() = default;

	// IEntityComponent
	virtual void Initialize() override;

	virtual Cry::Entity::EventFlags GetEventMask() const override;
	virtual void ProcessEvent(const SEntityEvent& event) override;	
	// ~IEntityComponent

	// Reflect type to set a unique identifier for this component
	static void ReflectType(Schematyc::CTypeDesc<CRoadManagerComponent>& desc)
	{
		desc.SetGUID("{F9B9EE21-794B-4B73-884C-A7FC8F3CFF32}"_cry_guid);
		//desc.AddMember(&CPlayerComponent::m_movementSpeed, 'pms', "playermovespeed", "Player move Speed", "Player move Speed", 10);
	}	
	

	void spawnRoad();
protected:	

private:
	int lastIndex = -1;
	
};
