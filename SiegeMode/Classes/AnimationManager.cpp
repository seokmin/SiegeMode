#include "pch.h"
#include "AnimationManager.h"
#include "json/json.h"

AnimationManager::AnimationManager()
{
	auto tmpData = FileUtils::getInstance()->getStringFromFile("Data/animations.json");
	Json::Value animData;
	Json::Reader reader;
	reader.parse(tmpData, animData);
	auto units = animData.getMemberNames();
	for (auto currentUnitName : units)
	{
		auto anims = animData.get(currentUnitName, "failed");
		for (auto currentAnim : anims)
		{
			auto animName = currentAnim.get("animName", "failed").asString();
			auto interval = currentAnim.get("interval", 0.f).asFloat();
			auto width = currentAnim.get("width", 0).asInt();
			auto height = currentAnim.get("height", 0).asInt();
			auto nFrame = currentAnim.get("nFrame", 0).asInt();
			auto fileName = "SpriteSource/" + currentUnitName + "/" + currentUnitName + "_" + animName + ".png";
			addAnimation(currentUnitName, animName, interval, fileName, width, height, nFrame);
		}
	}
}

AnimationManager* AnimationManager::_instance = nullptr;

Animation* AnimationManager::getAnimation(std::string actorName, std::string animName)
{
	auto rtnAnim = _animationMap.at(actorName + animName);
	if (rtnAnim != nullptr)
		return _animationMap.at(actorName + animName);
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
	_animationMap.insert(actorName + animName, anim);
}

void AnimationManager::addAnimation(std::string actorName, std::string animName, float interval, std::string fileName, unsigned width, unsigned height, unsigned nFrame)
{
	if (_animationMap.at(actorName + animName) != nullptr)
	{
		return;
	}
	Vector<SpriteFrame*> animFrames(nFrame);
	for (auto i = 1u; i <= nFrame; ++i)
	{
		auto frame = SpriteFrame::create(fileName, Rect((i - 1)*width, 0, width, height));
		animFrames.pushBack(frame);
	}

	auto anim = Animation::createWithSpriteFrames(animFrames, interval);
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