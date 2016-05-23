#pragma once

#include "json/json.h"
class Unit;


// 모든 Unit을 관리
class UnitManager
{
public:
	static UnitManager* getInstance();

	void				summonUnit(std::string unitName, Vec2 position, DEF::PLAYER_KIND ownerPlayer);
	void				killUnitByTag(int tag);
	Unit*				getUnitByTag(int tag);
	Vector<Unit*>		findUnitByCondition(Unit* caller, std::function<bool(Unit* caller, Unit* other)> compare);
	void				deleteInstance();

	CC_SYNTHESIZE(Json::Value, _specData, SpecData);
private:
	UnitManager();
	static UnitManager* _instance;
	CC_SYNTHESIZE_READONLY(Node*,_unitList,UnitList);
};