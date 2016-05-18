#include "pch.h"
#include "AnimationManager.h"

AnimationManager::AnimationManager()
{

}

AnimationManager* AnimationManager::_instance = nullptr;

Animation* AnimationManager::getAnimation(std::string actorName, std::string animName)
{
	auto rtnAnim = _animationMap.at(actorName+animName);
	if (rtnAnim != nullptr)
		return _animationMap.at(actorName+animName);
	//여기 들어왔으면 버그
	return nullptr;
}

void AnimationManager::addAnimation(std::string actorName, std::string animName, float interval, std::initializer_list<std::string> frameName)
{
	if (_animationMap.at(actorName + animName) != nullptr)
	{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		//Beep(1000, 100);
#endif
		return;
	}

	auto anim = Animation::create();
	anim->setDelayPerUnit(interval);
	for (auto iter : frameName)
	{
		anim->addSpriteFrameWithFile(iter);
	}
	for (auto i : anim->getFrames())
	{
		i->getSpriteFrame()->getTexture()->setAliasTexParameters();
	}
	_animationMap.insert(actorName+animName,anim);
}

void AnimationManager::addAnimation(std::string actorName, std::string animName, float interval, std::string fileName, unsigned width, unsigned height, unsigned frameCount)
{
	if (_animationMap.at(actorName + animName) != nullptr)
	{
		return;
	}
	Vector<SpriteFrame*> animFrames(frameCount);
	for (auto i = 1u; i <= frameCount; ++i)
	{
		auto frame = SpriteFrame::create(fileName, Rect((i - 1)*width, 0, width, height));
		animFrames.pushBack(frame);
	}

	auto anim = Animation::createWithSpriteFrames(animFrames,interval);
	anim->setDelayPerUnit(interval);
	

	for (auto i : anim->getFrames())
	{
		i->getSpriteFrame()->getTexture()->setAliasTexParameters();
	}
	_animationMap.insert(actorName + animName, anim);
}

AnimationManager* AnimationManager::getInstance()
{
	if (_instance == nullptr)
		_instance = new AnimationManager();
	return _instance;
}