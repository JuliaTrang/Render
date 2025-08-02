#include "cResource.h"
cResource sauce;
cResource::cResource() : map1(19, 8) {
	playerMoney = 100;
	type1.loadFromFile("LogicGame/Project1/DesignPx/Animation/type1.png");
	type2.loadFromFile("LogicGame/Project1/DesignPx/Animation/type2.png");
	type3.loadFromFile("LogicGame/Project1/DesignPx/Animation/type3.png");
	type4.loadFromFile("LogicGame/Project1/DesignPx/Animation/type4.png");
}
