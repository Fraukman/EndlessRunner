// Copyright 2017-2020 Crytek GmbH / Crytek Group. All rights reserved.
#pragma once

#include <CryEntitySystem/IEntityComponent.h>

#include <DefaultComponents/Input/InputComponent.h>
#include <DefaultComponents/Physics/CharacterControllerComponent.h>



class CPlayerComponent final : public IEntityComponent
{	
public:
	CPlayerComponent() = default;
	virtual ~CPlayerComponent() = default;

	// IEntityComponent
	virtual void Initialize() override;

	virtual Cry::Entity::EventFlags GetEventMask() const override;
	virtual void ProcessEvent(const SEntityEvent& event) override;	
	// ~IEntityComponent

	// Reflect type to set a unique identifier for this component
	static void ReflectType(Schematyc::CTypeDesc<CPlayerComponent>& desc)
	{
		desc.SetGUID("{63F4C0C6-32AF-4ACB-8FB0-57D45DD14725}"_cry_guid);
		desc.AddMember(&CPlayerComponent::m_movementSpeed, 'pms', "playermovespeed", "Player move Speed", "Player move Speed", 10);
	}	
	
protected:	
	void HandleInput();

	void updatePlayerPos(float frametime);
	void handleLateralMoviment(float frametime);
	void updateScore();

private:
	Cry::DefaultComponents::CCharacterControllerComponent* m_pCharacterControllerComponent;
	Cry::DefaultComponents::CInputComponent* m_pInputComponent = nullptr;

	float m_movementSpeed = 10;
	float m_startXPos = 0.0f;
	float m_startYPos = 0.0f;
	float m_distanceTraveled = 0.0f;
	float m_speedBump = 0.5f;
	bool m_lateralMoving = false;
	Vec2 m_movementDelta = ZERO;
	Vec3 m_velocity = ZERO;
	Vec3 m_startPos = ZERO;
	Vec3 m_movementStep = ZERO;
	
};
