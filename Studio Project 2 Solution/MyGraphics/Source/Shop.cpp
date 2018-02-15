#include "SHOP.h"

SHOP::SHOP()
{
	coord[SHOP_EXIT					].setBox(Vector3(1050, 400, 0), 120, 60, 1);
	coord[SHOP_BUY_FRUIT			].setBox(Vector3(150, 332, 0), 120, 60, 1);
	coord[SHOP_BUY_MEAT				].setBox(Vector3(300, 332, 0), 120, 60, 1);
	coord[SHOP_BUY_TRAP				].setBox(Vector3(450, 332, 0), 120, 60, 1);
	coord[SHOP_SELL_FRUIT			].setBox(Vector3(150, 468, 0), 120, 60, 1);
	coord[SHOP_SELL_MEAT			].setBox(Vector3(300, 468, 0), 120, 60, 1);
	coord[SHOP_SELL_TRAP			].setBox(Vector3(450, 468, 0), 120, 60, 1);
	coord[SHOP_RESET_QUANTITY		].setBox(Vector3(750, 400, 0), 120, 60, 1);
	coord[SHOP_INCREASE_QUANTITY_1	].setBox(Vector3(600, 332, 0), 120, 60, 1);
	coord[SHOP_DECREASE_QUANTITY_1	].setBox(Vector3(600, 468, 0), 120, 60, 1);
	coord[SHOP_INCREASE_QUANTITY_10	].setBox(Vector3(600, 264, 0), 120, 60, 1);
	coord[SHOP_DECREASE_QUANTITY_10	].setBox(Vector3(600, 536, 0), 120, 60, 1);
	coord[SHOP_INCREASE_QUANTITY_100].setBox(Vector3(600, 196, 0), 120, 60, 1);
	coord[SHOP_DECREASE_QUANTITY_100].setBox(Vector3(600, 604, 0), 120, 60, 1);

	cost[SHOP_EXIT					] = 0;
	cost[SHOP_BUY_FRUIT				] = 2;
	cost[SHOP_BUY_MEAT				] = 2;
	cost[SHOP_BUY_TRAP				] = 2;
	cost[SHOP_SELL_FRUIT			] = 1;
	cost[SHOP_SELL_MEAT				] = 1;
	cost[SHOP_SELL_TRAP				] = 1;
	cost[SHOP_RESET_QUANTITY		] = 0;
	cost[SHOP_INCREASE_QUANTITY_1	] = 0;
	cost[SHOP_DECREASE_QUANTITY_1	] = 0;
	cost[SHOP_INCREASE_QUANTITY_10	] = 0;
	cost[SHOP_DECREASE_QUANTITY_10	] = 0;
	cost[SHOP_INCREASE_QUANTITY_100	] = 0;
	cost[SHOP_DECREASE_QUANTITY_100	] = 0;

}

Vector3 SHOP::getCoord(SHOP_ACTION action)
{
	return coord[action].getPos();
}

Vector3 SHOP::getCoord(int i)
{
	return coord[i].getPos();
}
SHOP::~SHOP()
{
}
