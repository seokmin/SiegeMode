#include "pch.h"
#include "UnitManager.h"
#include "Swordman.h"


UnitManager* UnitManager::_instance = nullptr;

UnitManager* UnitManager::getInstance()
{
	if (!_instance)
		_instance = new UnitManager();
	return _instance;
}

void UnitManager::summonUnit(std::string unitName, Vec2 position, PLAYER_KIND ownerPlayer)
{
	Unit* newUnit = nullptr;
	if (unitName == "swordman")
	{
		newUnit = Swordman::create(ownerPlayer);
	}

	newUnit->setPosition(position);
	_unitList->addChild(newUnit);
}

UnitManager::UnitManager()
{
	_unitList = Node::create();
	_unitList->retain();
}
