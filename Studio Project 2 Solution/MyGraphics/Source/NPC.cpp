#include "NPC.h"

static const int sizeOfBoxMove = 10;
static const int sizeOfBoxText = 30;

NPC::NPC()
{
	NPCS[NPC_WEATHER].setBox(Vector3(60, 0, 80), sizeOfBoxMove);
	NPCS[NPC_LORE].setBox(Vector3(100, 0, 0), sizeOfBoxMove);
	NPCS[NPC_HUNTING].setBox(Vector3(80, 0, -100), sizeOfBoxMove);
	NPCS[NPC_RAISING].setBox(Vector3(-60, 0, -80), sizeOfBoxMove);
	NPCS[NPC_RACING].setBox(Vector3(-100, 0, 40), sizeOfBoxMove);
}

Vector3 NPC::getCoord(NPC_TYPE type)
{
	return NPCS[type].getPos();
}

Vector3 NPC::getCoord(int i)
{
	return NPCS[i].getPos();
}
NPC::~NPC()
{
}
