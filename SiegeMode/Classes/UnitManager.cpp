#include "pch.h"
#include "UnitManager.h"
#include "Swordman.h"
#include "Bowman.h"
#include "Flagman.h"
#include "Balistar.h"


UnitManager* UnitManager::_instance = nullptr;

UnitManager* UnitManager::getInstance()
{
	if (!_instance)
		_instance = new UnitManager();
	return _instance;
}

void UnitManager::summonUnit(std::string unitName, Vec2 position, DEF::PLAYER_KIND ownerPlayer)
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
	else if (unitName == "flagman")
	{
		newUnit = Flagman::create(ownerPlayer);
	}
	else if (unitName == "balistar")
	{
		newUnit = Balistar::create(ownerPlayer);
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

Vector<Unit*> UnitManager::findUnitByCondition(Unit* caller, bool(*compare)(Unit* caller, Unit* other))
{
	auto children = _unitList->getChildren();
	Vector<Unit*> returnVec;
	for (auto i : children)
	{
		auto currentUnit = static_cast<Unit*>(i);
		//비교후 저장
		if (compare(caller, currentUnit))
			returnVec.pushBack(currentUnit);
	}
	return returnVec;
}

void UnitManager::deleteInstance()
{
	delete _instance;
	_instance = nullptr;
}

UnitManager::UnitManager()
{
	_unitList = Node::create();
	_unitList->retain();
}