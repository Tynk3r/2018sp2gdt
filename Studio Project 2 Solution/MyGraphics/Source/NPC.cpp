#include "NPC.h"


NPC::NPC()
{
	NPCS[NPC_WEATHER] = Vector3(1, 1, 1);
	NPCS[NPC_LORE] = Vector3(10, 1, 1);
	NPCS[NPC_HUNTING] = Vector3(1, 1, 10);
	NPCS[NPC_RAISING] = Vector3(10, 1, 1);
	NPCS[NPC_RACING] = Vector3(5, 1, 5);
}

Vector3 NPC::getCoord(NPC_TYPE type)
{
	return NPCS[type];
}

NPC::~NPC()
{
}
