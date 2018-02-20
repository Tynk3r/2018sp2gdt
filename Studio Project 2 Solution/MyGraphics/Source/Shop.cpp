#include "SHOP.h"

SHOP::SHOP()
{
	coord[SHOP_EXIT					].setBox(Vector3(150, 603, 0), 120, 60, 1);
	coord[SHOP_BUY_REDFRUIT			].setBox(Vector3(150, 331, 0), 120, 60, 1);
	coord[SHOP_BUY_BLUFRUIT			].setBox(Vector3(300, 331, 0), 120, 60, 1);
	coord[SHOP_BUY_MEAT				].setBox(Vector3(450, 331, 0), 120, 60, 1);
	coord[SHOP_BUY_TRAP				].setBox(Vector3(600, 331, 0), 120, 60, 1);
	coord[SHOP_BUY_INCUBATOR		].setBox(Vector3(750, 331, 0), 120, 60, 1);

	coord[SHOP_SELL_REDFRUIT		].setBox(Vector3(150, 467, 0), 120, 60, 1);
	coord[SHOP_SELL_BLUFRUIT		].setBox(Vector3(300, 467, 0), 120, 60, 1);
	coord[SHOP_SELL_MEAT			].setBox(Vector3(450, 467, 0), 120, 60, 1);
	coord[SHOP_SELL_TRAP			].setBox(Vector3(600, 467, 0), 120, 60, 1);
	coord[SHOP_SELL_INCUBATOR		].setBox(Vector3(750, 467, 0), 120, 60, 1);
	
	coord[SHOP_RESET_QUANTITY		].setBox(Vector3(1050, 399, 0), 120, 60, 1);
	coord[SHOP_INCREASE_QUANTITY_1	].setBox(Vector3(900, 331, 0), 120, 60, 1);
	coord[SHOP_DECREASE_QUANTITY_1	].setBox(Vector3(900, 467, 0), 120, 60, 1);
	coord[SHOP_INCREASE_QUANTITY_10	].setBox(Vector3(900, 263, 0), 120, 60, 1);
	coord[SHOP_DECREASE_QUANTITY_10	].setBox(Vector3(900, 535, 0), 120, 60, 1);
	coord[SHOP_INCREASE_QUANTITY_100].setBox(Vector3(900, 195, 0), 120, 60, 1);
	coord[SHOP_DECREASE_QUANTITY_100].setBox(Vector3(900, 603, 0), 120, 60, 1);


	cost[SHOP_BUY_REDFRUIT			] = 2;
	cost[SHOP_BUY_BLUFRUIT			] = 2;
	cost[SHOP_BUY_MEAT				] = 2;
	cost[SHOP_BUY_TRAP				] = 2;
	cost[SHOP_BUY_INCUBATOR			] = 2;

	cost[SHOP_SELL_REDFRUIT			] = 1;
	cost[SHOP_SELL_BLUFRUIT			] = 1;
	cost[SHOP_SELL_MEAT				] = 1;
	cost[SHOP_SELL_TRAP				] = 1;
	cost[SHOP_SELL_INCUBATOR		] = 1;
}

Vector3 SHOP::GetCoord(SHOP_ACTION action)
{
	return coord[action].getPos();
}

Vector3 SHOP::GetCoord(int i)
{
	return coord[i].getPos();
}
SHOP::~SHOP()
{
}
