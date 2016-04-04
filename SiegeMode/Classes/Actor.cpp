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

void Actor::setSpriteFromFileName(const char* fileName)
{
	this->initWithSpriteFrameName(fileName);
}

void Actor::refreshStroke()
{
	Image* testImg = new Image();

	testImg->initWithImageFile(settings::PATHNAME_SPRITE_FOLDER +  "/" + this->_fileName);

	auto x = 3;
	if (testImg->hasAlpha())
		x = 4;
	auto pixelData = new unsigned char[testImg->getDataLen()*x];
	pixelData = testImg->getData();
	for (int j = 0; j < testImg->getWidth(); ++j)
	{
		for (int i = 0; i < testImg->getHeight(); ++i)
		{
			auto pixel = pixelData + (i + j*testImg->getWidth()) * x;
			auto r = pixel;
			auto g = (pixel + 1);
			auto b = (pixel + 2);
			auto a = (pixel + 3);
			if (*a > 0)
			{
				*r = 0;
				*g = 255;
				*b = 0;
			}
		}
	}

	auto newTexture = new Texture2D();
	newTexture->initWithImage(testImg);
	newTexture->setAliasTexParameters();
	for (auto i : _strokeArray)
	{
		i->initWithTexture(newTexture);
		i->setAnchorPoint(Vec2(0, 0));
	}
	auto strokeSizeInPixel = _strokeSize / this->getScale();
	_strokeArray[0]->setPosition(Vec2(+strokeSizeInPixel, +strokeSizeInPixel));
	_strokeArray[1]->setPosition(Vec2(+strokeSizeInPixel, 0));
	_strokeArray[2]->setPosition(Vec2(+strokeSizeInPixel, -strokeSizeInPixel));
	_strokeArray[3]->setPosition(Vec2(-strokeSizeInPixel, +strokeSizeInPixel));
	_strokeArray[4]->setPosition(Vec2(-strokeSizeInPixel, 0));
	_strokeArray[5]->setPosition(Vec2(-strokeSizeInPixel, -strokeSizeInPixel));
	_strokeArray[6]->setPosition(Vec2(0, +strokeSizeInPixel));
	_strokeArray[7]->setPosition(Vec2(0, -strokeSizeInPixel));

	//Director::getInstance()->getScheduler()->performFunctionInCocosThread(filesaveFunc);
	//this->scheduleOnce(schedule_selector(filesaveFunc), 1.f);

	// 	Image* img = r->newImage();
	// 	int x = 3;
	// 	if (img->hasAlpha())
	// 		x = 4;
	// 	unsigned char *pixelData = new unsigned char[img->getDataLen()*x];
	// 	pixelData = img->getData();
	// 	log("%s", pixelData);


		// 	for (auto& i : _strokeArray)
		// 	{
		// 		i->initWithSpriteFrame(this->getSpriteFrame());
		// 		i->setColor(Color3B(0,255,0));
		// 		i->setPosition(Vec2(100, 100));
		//  	}
			//죽은 코드


		/*_stroke = Sprite::createWithSpriteFrame(this->getSpriteFrame());

		const int sizeStroke = 3;
		const Color3B newColor = Color3B(0, 255, 0);
		const GLubyte newOpacity = 255;

		RenderTexture* rt = RenderTexture::create(
			_stroke->getTexture()->getContentSize().width + sizeStroke * 2,
			_stroke->getTexture()->getContentSize().height + sizeStroke * 2
			);

		Point originPos = _stroke->getPosition();
		Color3B originColor = _stroke->getColor();
		GLubyte originOpacity = _stroke->getOpacity();
		bool originVisibility = _stroke->isVisible();

		_stroke->setColor(newColor);
		_stroke->setOpacity(newOpacity);
		_stroke->setVisible(true);

		ccBlendFunc newBlend = { GL_SRC_ALPHA, GL_ONE };
		_stroke->setBlendFunc(newBlend);

		Point bottomLeft = Point(
			_stroke->getTexture()->getContentSize().width * _stroke->getAnchorPoint().x + sizeStroke,
			_stroke->getTexture()->getContentSize().height*_stroke->getAnchorPoint().y + sizeStroke
			);
		Point positionOffset = Point(
			-_stroke->getTexture()->getContentSize().width / 2,
			-_stroke->getTexture()->getContentSize().height / 2);

		Point position = ccpSub(originPos, positionOffset);

		rt->begin();

		this->addChild(_stroke);
		this->addChild(rt, this->getLocalZOrder() - 1);
		for (int i = 0; i < 360; ++i)
		{
			//_stroke->setPosition(Vec2(bottomLeft.x + sin(CC_DEGREES_TO_RADIANS(i))*sizeStroke, bottomLeft.y + cos(CC_DEGREES_TO_RADIANS(i))*sizeStroke));
			_stroke->visit();
		}
		rt->end();

		rt->getSprite()->getTexture()->setAntiAliasTexParameters();
		rt->setPosition(position);*/



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
