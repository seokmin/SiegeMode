#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

class BattleScene : public LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    
	bool onSprTouchBegan(Touch* touch, Event* event);

    // implement the "static create()" method manually
    CREATE_FUNC(BattleScene);

private:

};

#endif // __HELLOWORLD_SCENE_H__