#pragma once
#include "Actor.h"
class Unit :
	public Actor
{
public:
	virtual bool init();

	bool		touchCallback(Touch* touch, Event* event);
	Action*		getActionItem(const std::string& actionName);

	CREATE_FUNC(Unit);

protected:
	void	setCursor();
	inline void	setToAlias() { this->getTexture()->setAliasTexParameters(); }
	void		addActionItem(const std::string actionName, Action* action);
private:
	Actor*		_cursorUp = nullptr;
	Actor*		_cursorDown = nullptr;
	bool		_selected = false;


	CC_SYNTHESIZE(std::string*, _cursorNameUp, CursorNameUp);
	CC_SYNTHESIZE(std::string*, _cursorNameDown, CursorNameDown);
	std::map<const std::string, Action*> _actionList;

};