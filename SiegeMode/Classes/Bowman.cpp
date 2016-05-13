#include "pch.h"
#include "Bowman.h"
#include "UnitState_WalkAndSeek.h"
#include "AnimationManager.h"

bool Bowman::init(PLAYER_KIND playerKind)
{
	if (!Unit::init(playerKind))
		return false;
	_attackSpeed = 1.f;
	_moveSpeed = 30.f;
	_attackRange = 450.f;
	_sightRange = 500.f;
	_attackDelay = 0.4f;
	_attackPower = 12;
	_health = 30;
	_attackAccuracy = 0.75f;
	_arrowSpeed = 1500.f;

	this->setUnitName("bowman");
	if (this->getOwnerPlayer() == PLAYER_RED)
		AnimationManager::getInstance()->addAnimation(_unitName, "walk_red", 0.1f, "SpriteSource/bowman/bowman_walk_red.png", 30, 28, 6);
	else
		AnimationManager::getInstance()->addAnimation(_unitName, "walk_blue", 0.1f, "SpriteSource/bowman/bowman_walk_blue.png", 30, 28, 6);

	if (this->getOwnerPlayer() == PLAYER_RED)
		AnimationManager::getInstance()->addAnimation(_unitName, "attack_red", 0.2f, "SpriteSource/bowman/bowman_attack_red.png", 35, 28, 3);
	else
		AnimationManager::getInstance()->addAnimation(_unitName, "attack_blue", 0.2f, "SpriteSource/bowman/bowman_attack_blue.png", 35, 28, 3);

	this->changeState<UnitState_WalkAndSeek>();
	return true;
}

void Bowman::attackOnce()
{
	this->setAnchorPoint(Vec2(25.f / 43.f, 5.f / 30.f));

	runAction(Sequence::create(
		DelayTime::create(_attackDelay), CallFuncN::create(
			CC_CALLBACK_0(Bowman::shootArrow, this, getAttackTarget()->getPosition())), nullptr));

	startAnimate("attack", false);

	_arrowTime = _position.getDistance(getAttackTarget()->getPosition()) / _arrowSpeed;
	if (RandomHelper::random_real(0.f, 1.f) <= _attackAccuracy)
		getAttackTarget()->scheduleBeHit(_attackPower, _attackDelay + _arrowTime);
}
void Bowman::moveTo(Vec2 destination)
{
	this->setAnchorPoint(Vec2(20.f / 32.f, 4.f / 29.f));
	Unit::moveTo(destination);
}

void Bowman::shootArrow(Vec2 targetPos)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/bow_release.wav");
	targetPos += Vec2(0, 30);
	Sprite* arrow = Sprite::create("SpriteSource/bowman/bowman_arrow.png");
	auto parent = getParent()->getParent();
	parent->addChild(arrow);
	
	arrow->setPosition(getPosition() + Vec2(0, 10));

	arrow->getTexture()->setAliasTexParameters();
	arrow->setGlobalZOrder(100);
	arrow->setRotation(360.f - ccpToAngle(targetPos - _position) * 180.f / 3.141592f);
	arrow->setScale(1.5f);

	arrow->runAction(Sequence::create(MoveTo::create(_arrowTime, targetPos), DelayTime::create(0.05f), RemoveSelf::create(true), nullptr));

}

void Bowman::moveBy(Vec2 directionVec, float duration)
{
	this->setAnchorPoint(Vec2(20.f / 32.f, 4.f / 29.f));
	Unit::moveBy(directionVec, duration);
}