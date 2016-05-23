#include "pch.h"
#include "UnitManager.h"
#include "Swordman.h"
#include "Bowman.h"
#include "Flagman.h"
#include "Balistar.h"

UnitManager* UnitManager::_instance = nullptr;

// 싱글톤
UnitManager* UnitManager::getInstance()
{
	if (!_instance)
		_instance = new UnitManager();
	return _instance;
}

// 유닛 이름을 받아서 소환한다.
// 템플릿으로 구현하지 않고 문자열을 받는 이유는 호출하는 쪽에서 유닛 종류에 대한 include를 피하기 위함
void UnitManager::summonUnit(std::string unitName, Vec2 position, DEF::PLAYER_KIND ownerPlayer)
{
	// 태그 기반으로 유닛목록을 관리한다
	static int tagid = 1;
	Unit* newUnit = nullptr;
	
	if (unitName == "swordman")			newUnit = Swordman::create	(ownerPlayer);
	else if (unitName == "bowman")		newUnit = Bowman::	create	(ownerPlayer);
	else if (unitName == "flagman")		newUnit = Flagman::	create	(ownerPlayer);
	else if (unitName == "balistar")	newUnit = Balistar::create	(ownerPlayer);

	newUnit->setTag(++tagid);
	newUnit->setPosition(position);
	_unitList->addChild(newUnit);
}

Unit* UnitManager::getUnitByTag(int tag)
{
	return static_cast<Unit*>(_unitList->getChildByTag(tag));
}

// 조건식을 받아서 조건에 맞는 유닛을 반환함
Vector<Unit*> UnitManager::findUnitByCondition(Unit* caller, std::function<bool(Unit* caller, Unit* other)> compare)
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
	_unitList->release();
	delete _instance;
	_instance = nullptr;
}

UnitManager::UnitManager()
{
	_unitList = Node::create();
	_unitList->retain();

	// json 데이터를 미리 파싱해놓는다.
	auto tmpData = FileUtils::getInstance()->getStringFromFile("Data/unit_spec.json");
	Json::Reader reader;
	reader.parse(tmpData, _specData);
}