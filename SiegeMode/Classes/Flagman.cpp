#include "pch.h"
#include "Flagman.h"
#include "UnitState_Stay.h"
#include "AnimationManager.h"

bool Flagman::init(DEF::PLAYER_KIND playerKind)
{
	if (!Unit::init(playerKind))
		return false;
	if (_ownerPlayer == DEF::PLAYER_RED)
		this->setTexture("SpriteSource/flagman/flagman_walk_red.png");
	else
		this->setTexture("SpriteSource/flagman/flagman_walk_blue.png");


	_attackSpeed = 0.f;
	_moveSpeed = 0.f;
	_attackRange = 0.f;
	_sightRange = 0.f;
	_attackDelay = 0.f;
	_attackPower = 0.f;
	_maxHealth = 200;
	_health = _maxHealth;
	_attackAccuracy = 0.f;
	setAnchorPoint(Vec2(15.f / 23.f, 3.f / 57.f));
	this->setUnitName("flagman");

	this->changeState<UnitState_Stay>();
	this->getTexture()->setAliasTexParameters();
	return true;
}

void Flagman::kill()
{
	std::string endingMsg;
	if (_ownerPlayer == DEF::PLAYER_BLUE)
		endingMsg = "You Win!!!";
	else
		endingMsg = "You Lose...";
	auto endingLabel = Label::createWithTTF(endingMsg, "fonts/Marker Felt.ttf", 100);
	endingLabel->setPosition(DEF::SCREEN_WIDTH / 2.f, DEF::SCREEN_HEIGHT / 2.f);
	getParent()->getParent()->addChild(endingLabel);
	Director::getInstance()->pause();
	
}