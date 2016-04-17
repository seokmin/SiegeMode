#pragma once

class Unit;

class UnitManager
{
public:
	static UnitManager* getInstance();

	void				summonUnit(std::string unitName, Vec2 position, PLAYER_KIND ownerPlayer);
private:
	UnitManager();
	static UnitManager* _instance;
	CC_SYNTHESIZE_READONLY(Node*,_unitList,UnitList);
};