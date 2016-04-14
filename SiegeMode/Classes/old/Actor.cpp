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

bool Actor::screenTouchCallback(Touch* touch, Event* event)
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
	Image* strokeImg = new Image();

	//스트로크 칠할 스프라이트에서 파일이름을 뽑아와서 이미지를 읽는다.
	strokeImg->initWithImageFile(settings::PATHNAME_SPRITE_FOLDER +  "/" + this->_fileName);

	auto x = 3;
	if (strokeImg->hasAlpha())
		x = 4;
	auto pixelData = new unsigned char[strokeImg->getDataLen()*x];
	pixelData = strokeImg->getData();

	//알파값 놔두고 싹 밀어버린다.
	for (int j = 0; j < strokeImg->getWidth(); ++j)
	{
		for (int i = 0; i < strokeImg->getHeight(); ++i)
		{
			auto pixel = pixelData + (i + j*strokeImg->getWidth()) * x;
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


	//생성한 이미지를 8장 깐다.
	auto newTexture = new Texture2D();
	newTexture->initWithImage(strokeImg);
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
}

void Actor::touchThisCallback()
{

}

