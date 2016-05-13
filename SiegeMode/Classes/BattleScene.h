#pragma once

class BattleScene : public LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    
	bool onSprTouchBegan(Touch* touch, Event* event);
/*	bool onMouseTouchBegan(EventMouse* event);*/

	void update(float delta);
    // implement the "static create()" method manually
    CREATE_FUNC(BattleScene);

private:
};