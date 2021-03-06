#include "object.h"
#include <vector>
using namespace std;

object* object::createObject()
{
	object* obj = new object();
	if (obj && obj->init())
	{
		obj->autorelease();
		obj->objectInit();
		return obj;
	}
	CC_SAFE_DELETE(obj);
	return NULL;
}
bool object::init()
{
	if (!Layer::init())
	{
		return false;
	}
	for (int i = 0; i <4000; i++)
	{
		int n = 0;
		use.push_back(n);
	}
	
	return true;
}
void object::objectInit()
{
	this->type = 0;
	enemy = Sprite::create("UI/gold.png");
	enemy->setPosition(Vec2(-100, -100));
	addChild(enemy);
	progressSprite = Sprite::create("UI/BloodLine.png");
	Loading = ProgressTimer::create(progressSprite);
	addChild(Loading);
	Loading->setType(kCCProgressTimerTypeBar);
	Loading->setScale(0.35f);
	Loading->setMidpoint(Vec2(0, 0));
	Loading->setBarChangeRate(Vec2(1.0, 0));
	Loading->setPercentage(100);
}
void object::start(int type, Vec2 position)
{
	this->type = type;
	if (type == 1)
	{
		enemy = Sprite::create("MAP/protect.png");
		addChild(enemy);
		enemy->setScale(0.3);
		//enemy->setScale(0.5f);
		maxBlood = 5000;
		blood = 5000;
		Aggressivity = 300;
		Armor = 0;
		attack_speed = 1.0;
		 magic=0;
		 magic_resistance=0;
		 speed=0;
		 level=18;
		 range=300;
		 exprience=10;
		 gold = 500;
	}
	if (type == 2)
	{
		enemy = Sprite::create("MAP/protect.png");
		CCRect rect = enemy->boundingBox();
		rect = CCRect(0, 0, 126, 167);
		addChild(enemy);
		enemy->setScale(0.3);
		maxBlood = 5000;
		blood = 5000;
		Aggressivity = 300;
		Armor = 0;
		attack_speed = 1.0;
		magic = 0;
		magic_resistance = 0;
		speed = 0;
		level = 18;
		range = 300;
		exprience = 10;
		gold = 500;
	}
	if (type == 3)
	{
		//��ս
		maxBlood = 250;
		blood = 250;
		Aggressivity = 50;
		Armor = 0;
		attack_speed = 1.4;
		magic = 0;
		magic_resistance = 0;
		speed = 50;
		level = 1;
		range = 75;
		exprience = 10;
		gold = 75;
	}
	if (type == 4)
	{
		//Զ��
		maxBlood = 150;
		blood = 150;
		Aggressivity = 75;
		Armor = 0;
		attack_speed = 1.4;
		magic = 0;
		magic_resistance = 0;
		speed = 50;
		level = 1;
		range = 275;
		exprience = 10;
		gold = 50;
	}
	if (type == 5)
	{
		//�ڳ�
		maxBlood = 500;
		blood = 500;
		Aggressivity = 75;
		Armor = 0;
		attack_speed = 1.4;
		magic = 0;
		magic_resistance = 0;
		speed = 50;
		level = 1;
		range = 200;
		exprience = 10;
		gold = 50;
	}
	if (type == 6)
	{
		//Ӣ��
		expsp = Sprite::create("UI/level.png");
		expcir = ProgressTimer::create(expsp);
		addChild(expcir);
		expcir->setType(kCCProgressTimerTypeRadial);
		expcir->setScale(0.35f);
		expcir->setPercentage(0);


		CCString* levCCStr = CCString::createWithFormat("%d", level);
		std::string levStr = levCCStr->getCString();
		lev = Label::create(levStr, "Arial", 30);
		addChild(lev);

		expcir->setPosition(Vec2(enemy->getPosition().x - 50, enemy->getPosition().y + 50));
		lev->setPosition(enemy->getPosition().x - 50, enemy->getPosition().y + 50);

		maxBlood = 2000;
		blood = 2000;
		Aggressivity = 75;
		Armor = 200;
		attack_speed = 1.4;
		magic = 0;
		magic_resistance = 200;
		speed = 50;
		level = 1;
		range = 200;
		exprience = 10;
		gold = 50;
	}
	enemy->setPosition(position);
	Loading->setPosition(Vec2(position.x,position.y+50));
}
void object::attactEnemy(Vec2 pos ,Vec2 Epos,int num)
{
	if (use[num] == 1) return;
	CCLOG("%d**   %d", use.size(),use[40]);
	float distance = getDistance(pos, Epos);
	auto delayTime = DelayTime::create(1.0f);
	auto hit = Sprite::create("AA.jpg");
	hit->setScale(1.0f);
	hit->setPosition(pos);
	addChild(hit);
	use[num] = 1;
	const int m = num;
	auto * move = MoveTo::create((float)distance / 2000, Epos);
	auto * remove = MoveTo::create(0, Vec2(-2000, -2000));
	auto funcall1 = CallFunc::create(CC_CALLBACK_0(object::finishRunAction, this, m));
	auto funcall2 = CallFunc::create(CC_CALLBACK_0(object::finishRunAction, this,m));
	auto * sequence = Sequence::create(move, remove, delayTime, funcall2, NULL);
	hit->runAction(sequence);
}
void object::finishRunAction(const int num)
{
	use[num] = 0;
}
float object::getDistance(Vec2 pos, Vec2 Epos)
{
	float x = pos.x - Epos.x;
	float y = pos.y - Epos.y;
	return sqrt(x * x + y * y);
}
void object::enemyDestory()
{
	if (blood > 0)
	{
		blood--;
	}
	else
	{
		CCLOG("dead");
		enemy->stopAllActions();
		enemy->setPosition(0, -200);
		type = 0;
	}
}