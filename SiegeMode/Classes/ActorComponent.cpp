#include "pch.h"
#include "ActorComponent.h"


ActorComponent::ActorComponent()
{
}


ActorComponent::~ActorComponent()
{
}

ActorComponent* ActorComponent::create()
{
	ActorComponent *pRet = new(std::nothrow) ActorComponent();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool ActorComponent::init()
{
	return true;
}
