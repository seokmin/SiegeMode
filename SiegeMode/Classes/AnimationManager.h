#pragma once

// 蜡粗 局聪皋捞记阑 包府
// 教臂沛
class AnimationManager
{
public:
	Animation*					getAnimation(std::string actorName, std::string animName);
	void						addAnimation(std::string actorName, std::string animName, float interval, std::string fileName, unsigned width, unsigned height, unsigned frameCount);
	static AnimationManager*	getInstance();
private:
	Map<std::string, Animation*>	_animationMap;
	static AnimationManager*		_instance;
	AnimationManager();

};