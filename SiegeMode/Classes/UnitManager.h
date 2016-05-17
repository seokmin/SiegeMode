#pragma once

class Unit;

class UnitManager
{
public:
	static UnitManager* getInstance();

	void				summonUnit(std::string unitName, Vec2 position, DEF::PLAYER_KIND ownerPlayer);
	void				killUnitByTag(int tag);
	Unit*				getUnitByTag(int tag);
	Vector<Unit*>		findUnitByCondition(Unit * caller, bool(*compare)(Unit *caller, Unit *other));
private:
	UnitManager();
	static UnitManager* _instance;
	CC_SYNTHESIZE_READONLY(Node*,_unitList,UnitList);
};