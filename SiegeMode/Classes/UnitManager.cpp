#include "pch.h"
#include "UnitManager.h"
#include "Swordman.h"
#include "Bowman.h"


UnitManager* UnitManager::_instance = nullptr;

UnitManager* UnitManager::getInstance()
{
	if (!_instance)
		_instance = new UnitManager();
	return _instance;
}

void UnitManager::summonUnit(std::string unitName, Vec2 position, PLAYER_KIND ownerPlayer)
{
	static int tagid = 1;
	Unit* newUnit = nullptr;
	if (unitName == "swordman")
	{
		newUnit = Swordman::create(ownerPlayer);
	}
	else if (unitName == "bowman")
	{
		newUnit = Bowman::create(ownerPlayer);
	}

	newUnit->setTag(++tagid);
	newUnit->setPosition(position);
	_unitList->addChild(newUnit);
}

void UnitManager::killUnitByTag(int tag)
{

}

Unit* UnitManager::getUnitByTag(int tag)
{
	return static_cast<Unit*>(_unitList->getChildByTag(tag));
}

UnitManager::UnitManager()
{
	_unitList = Node::create();
	_unitList->retain();
}