#include "pch.h"
#include "AnimationManager.h"
#include "json/json.h"

AnimationManager* AnimationManager::_instance = nullptr;

AnimationManager::AnimationManager()
{
	// json 파싱
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

// 애니메이션을 찾아서 반환
Animation* AnimationManager::getAnimation(std::string actorName, std::string animName)
{
	auto rtnAnim = _animationMap.at(actorName + animName);
	if (rtnAnim != nullptr)
		return _animationMap.at(actorName + animName);

	//여기 들어왔으면 버그
	return nullptr;
}


// 애니메이션을 추가
// actorName		: 유닛 이름
// animName			: 애니메이션 이름
// interval			: 프레임 간 딜레이
// fileName			: 스프라이트 파일이름
// width, height	: 스프라이트 한 프레임당 넓이, 높이
// nFrame			: 스프라이트 프레임 수 
void AnimationManager::addAnimation(std::string actorName, std::string animName, float interval, std::string fileName, unsigned width, unsigned height, unsigned nFrame)
{
	// 이미 존재하는 조합이면 새로 추가 안함
	if (_animationMap.at(actorName + animName) != nullptr)
		return;


	Vector<SpriteFrame*> animFrames(nFrame);
	
	for (auto i = 1u; i <= nFrame; ++i)// 프레임을 하나씩 잘라서 벡터에 넣는다
	{
		auto frame = SpriteFrame::create(fileName, Rect((i - 1)*width, 0, width, height));
		animFrames.pushBack(frame);
	}

	auto anim = Animation::createWithSpriteFrames(animFrames, interval);
	for (auto i : anim->getFrames())//Alias 셋팅(도트 이미지이므로)
		i->getSpriteFrame()->getTexture()->setAliasTexParameters();

	anim->setDelayPerUnit(interval);
	_animationMap.insert(actorName + animName, anim);
}

// 싱글톤
AnimationManager* AnimationManager::getInstance()
{
	if (_instance == nullptr)
		_instance = new AnimationManager();
	return _instance;
}