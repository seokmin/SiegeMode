#include "pch.h"
#include "Actor.h"

bool Actor::init()
{
	/*
	 * 부모 클래스의 init()도 예의상 호출해준다.
	 */
	if (!this->Node::init())
		return false;

	this->setAnchorPoint(Vec2(0.5f, 0.5f));

	
	for (auto& i : _strokeArray)
	{
		i = Sprite::create();
		this->addChild(i, this->getLocalZOrder() - 1);
	}
	return true;
}

bool Actor::touchCallback(Touch* touch, Event* event)
{
	auto target = event->getCurrentTarget();
	Point pos = target->convertToNodeSpace(touch->getLocation());
	Rect rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);
	if (!rect.containsPoint(pos))
		return false;
	return true;
}

void Actor::refreshStroke()
{

// 	for (auto& i : _strokeArray)
// 	{
// 		i->initWithSpriteFrame(this->getSpriteFrame());
// 		i->setColor(Color3B(0,255,0));
// 		i->setPosition(Vec2(100, 100));
//  	}
	//죽은 코드
	{
		const int sizeStroke = 3;
		const Color3B newColor = Color3B(0, 255, 0);
		const GLubyte newOpacity = 50;

		RenderTexture* rt = RenderTexture::create(
			this->getTexture()->getContentSize().width + sizeStroke * 2,
			this->getTexture()->getContentSize().height + sizeStroke * 2
			);

		Point originPos = this->getPosition();
		Color3B originColor = this->getColor();
		GLubyte originOpacity = this->getOpacity();
		bool originVisibility = this->isVisible();

		this->setColor(newColor);
		this->setOpacity(newOpacity);
		this->setVisible(true);

		ccBlendFunc originalBlend = this->getBlendFunc();
		ccBlendFunc newBlend = { GL_SRC_ALPHA, GL_ONE };
		this->setBlendFunc(newBlend);

		Point bottomLeft = Point(
			this->getTexture()->getContentSize().width * this->getAnchorPoint().x + sizeStroke,
			this->getTexture()->getContentSize().height*this->getAnchorPoint().y + sizeStroke
			);
		Point positionOffset = Point(
			-this->getTexture()->getContentSize().width / 2,
			-this->getTexture()->getContentSize().height / 2);
		
		Point position = ccpSub(originPos, positionOffset);

		rt->begin();
		for (int i = 0; i < 360; i += 15)
		{
			this->setPosition(
				Vec2(bottomLeft.x + sin(CC_DEGREES_TO_RADIANS(i))*sizeStroke, bottomLeft.y + cos(CC_DEGREES_TO_RADIANS(i))*sizeStroke));
			this->visit();
		}
		rt->end();

		this->setPosition(originPos);
		this->setColor(originColor);
		this->setBlendFunc(originalBlend);
		this->setVisible(originVisibility);
		this->setOpacity(originOpacity);

		rt->getSprite()->getTexture()->setAntiAliasTexParameters();
		rt->setPosition(position);
		
		this->addChild(rt,this->getLocalZOrder()-1);
	}

	//죽은 코드 2
	/*const auto sizeBorder = 2;

	_stroke->initWithSpriteFrame(this->getSpriteFrame());
	_stroke->setPosition(Vec2(getContentSize().width*getAnchorPoint().x,getContentSize().height*getAnchorPoint().y));
	_stroke->setAnchorPoint(getAnchorPoint());
	const auto scaleFactor = this->getScale();
	const auto sizeOrigin = this->getContentSize();

// 	_stroke->setScale(Size((
// 		sizeOrigin.width*scaleFactor+sizeBorder)/sizeOrigin.width,
// 		(sizeOrigin.height*scaleFactor+sizeBorder)/sizeOrigin.height
// 		));
	_stroke->setScale(1.2f);*/


}