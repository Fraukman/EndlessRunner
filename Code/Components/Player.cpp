// Copyright 2017-2020 Crytek GmbH / Crytek Group. All rights reserved.
#include "StdAfx.h"
#include "Player.h"
#include "GamePlugin.h"

#include <CryRenderer/IRenderAuxGeom.h>
#include <CrySchematyc/Env/Elements/EnvComponent.h>
#include <CryCore/StaticInstanceList.h>
#include <CryNetwork/Rmi.h>

namespace
{
	static void RegisterPlayerComponent(Schematyc::IEnvRegistrar& registrar)
	{
		Schematyc::CEnvRegistrationScope scope = registrar.Scope(IEntity::GetEntityScopeGUID());
		{
			Schematyc::CEnvRegistrationScope componentScope = scope.Register(SCHEMATYC_MAKE_ENV_COMPONENT(CPlayerComponent));
		}
	}

	CRY_STATIC_AUTO_REGISTER_FUNCTION(&RegisterPlayerComponent);
}

void CPlayerComponent::Initialize()
{
	m_pCharacterControllerComponent = m_pEntity->GetOrCreateComponent<Cry::DefaultComponents::CCharacterControllerComponent>();
	m_pCharacterControllerComponent->SetTransformMatrix(Matrix34::Create(Vec3(1.f), IDENTITY, Vec3(0, 0, 1.0f)));

	m_pInputComponent = m_pEntity->GetOrCreateComponent<Cry::DefaultComponents::CInputComponent>();

	HandleInput();
}


Cry::Entity::EventFlags CPlayerComponent::GetEventMask() const
{
	return Cry::Entity::EEvent::Reset | Cry::Entity::EEvent::Update;
}

void CPlayerComponent::ProcessEvent(const SEntityEvent& event)
{
	const float frameTime = event.fParam[0];
	switch (event.event)
	{
	case Cry::Entity::EEvent::Update:
	{
		updatePlayerPos(frameTime);
	}
	break;
	case Cry::Entity::EEvent::Reset:
	{
		m_movementDelta = ZERO;
	}
	break;	
	}
}



void CPlayerComponent::updatePlayerPos(float frametime)
{
	if(m_pCharacterControllerComponent->IsOnGround()){
		m_movementDelta.x = 1.0f;
	}
	Vec3 normalizedVel = m_movementDelta.Normalize() * m_movementSpeed;
	m_pCharacterControllerComponent->AddVelocity(normalizedVel * frametime);
	m_movementDelta = ZERO;
}


void CPlayerComponent::HandleInput()
{
	m_pInputComponent->RegisterAction("player", "moveleft", [this](int activationMode, float value) { 
			m_movementDelta.y = value;
		});
	m_pInputComponent->BindAction("player", "moveleft", eAID_KeyboardMouse, EKeyId::eKI_A);
	m_pInputComponent->BindAction("player", "moveleft", eAID_XboxPad, eKI_XI_DPadLeft);


	m_pInputComponent->RegisterAction("player", "moveright", [this](int activationMode, float value) { 
		m_movementDelta.y = -value;
		});
	m_pInputComponent->BindAction("player", "moveright", eAID_KeyboardMouse, EKeyId::eKI_D);
	m_pInputComponent->BindAction("player", "moveright", eAID_XboxPad, eKI_XI_DPadRight);
}