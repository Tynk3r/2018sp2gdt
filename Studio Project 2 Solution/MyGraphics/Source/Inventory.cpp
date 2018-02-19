#include "Inventory.h"
#include "Application.h"

Inventory * Inventory::INVENTORY_instance = nullptr;

Inventory::Inventory()
{
	showInventory = false;

	for (int i = 0; i < ITEMS_TOTAL; i++)
	{
		items[i] = 0;
	}
}

Inventory* Inventory::instance(void)
{
	if (Inventory::INVENTORY_instance == nullptr)
	{
		Inventory::INVENTORY_instance = new Inventory();
	}
	return Inventory::INVENTORY_instance;
}

void Inventory::Update(double dt)
{
	if (Application::IsKeyPressed('I'))
	{
		showInventory = true;
	}
	else
	{
		showInventory = false;
	}
}