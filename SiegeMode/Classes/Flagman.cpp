#include "pch.h"
#include "Flagman.h"
#include "UnitState_Stay.h"
#include "AnimationManager.h"

bool Flagman::init(DEF::PLAYER_KIND playerKind)
{
	setUnitName("flagman");
	if (!Unit::init(playerKind))
		return false;
	if (_ownerPlayer == DEF::PLAYER_RED)
		this->setTexture("SpriteSource/flagman/flagman_walk_red.png");
	else
		this->setTexture("SpriteSource/flagman/flagman_walk_blue.png");

	setAnchorPoint(Vec2(15.f / 23.f, 3.f / 57.f));
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
	endingLabel->setGlobalZOrder(DEF::ZORDER_UI + 1);
	getParent()->getParent()->addChild(endingLabel);
	Director::getInstance()->pause();
	
}