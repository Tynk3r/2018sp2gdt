#include "NPC.h"

static const int sizeOfBoxMove = 10;
static const int sizeOfBoxText = 30;

NPC::NPC()
{
	NPCS[NPC_WEATHER] = Vector3(60, 10, 80);
	NPCS[NPC_LORE] = Vector3(100, 10, 0);
	NPCS[NPC_HUNTING] = Vector3(80, 10, -100);
	NPCS[NPC_RAISING] = Vector3(-60, 10, -80);
	NPCS[NPC_RACING] = Vector3(-100, 10, 40);

	for (int i = 0; i < numberOfNPCs; i++)
	{
		moveCollisions[i] = Box(NPCS[i], sizeOfBoxMove);
	}

	for (int i = 0; i < numberOfNPCs; i++)
	{
		textCollisions[i] = Box(NPCS[i], sizeOfBoxText);
	}
}

Vector3 NPC::getCoord(NPC_TYPE type)
{
	return NPCS[type];
}

Vector3 NPC::getCoord(int i)
{
	return NPCS[i];
}
NPC::~NPC()
{
}
