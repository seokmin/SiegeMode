#pragma once

class AnimationManager
{
public:


	Animation*	getAnimation(std::string actorName, std::string animName);
	void addAnimation(std::string actorName, std::string animName, float interval, std::initializer_list<std::string> frameName);

	static AnimationManager*	getInstance();
private:
	
	Map<std::string, Animation*> _animationMap;
	AnimationManager();
	static AnimationManager* _instance;

};