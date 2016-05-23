#pragma once

// ∏ﬁ¿Œ ∞‘¿”æ¿
class BattleScene : public LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(Ref* pSender);

	void update(float delta);
    CREATE_FUNC(BattleScene);

private:
};