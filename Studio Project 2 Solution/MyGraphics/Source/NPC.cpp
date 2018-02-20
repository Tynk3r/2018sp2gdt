#include "NPC.h"

NPC::NPC()
{
	NPCS[NPC_WEATHER].setBox(Vector3(60, 0, 80), sizeOfBoxMove);
	NPCS[NPC_LORE].setBox(Vector3(100, 0, 0), sizeOfBoxMove);
	NPCS[NPC_HUNTING].setBox(Vector3(-120, 0, 140), sizeOfBoxMove);
	NPCS[NPC_RAISING].setBox(Vector3(-60, 0, -80), sizeOfBoxMove);
	NPCS[NPC_RACING].setBox(Vector3(-100, 0, 40), sizeOfBoxMove);
	NPCS[NPC_SHOP].setBox(Vector3(80, 0, -100), sizeOfBoxMove);

	for (int i = 0; i < NPC_TOTAL; i++)
	{
		moveDirX[i] = MOVEDIR_BOTH;
		moveDirZ[i] = MOVEDIR_BOTH;
	}
}

Vector3 NPC::GetCoord(int i)
{
	return NPCS[i].getPos();
}

void NPC::Update(double dt)
{
	int MOVEMENT_SPEED = 2;

	// To check collision
	for (int i = 0; i < numberOfNPCs; i++)
	{
		moveDirX[i] = MOVEDIR_BOTH;
		moveDirZ[i] = MOVEDIR_BOTH;
		for (int a = 0; a < numberOfNPCs; a++)
		{
			if (a != i)
			{
				if ((NPCS[i].maxX >= NPCS[a].minX) && (NPCS[i].maxX <= NPCS[a].maxX) &&
					(NPCS[i].getPos().z >= NPCS[a].minZ) && (NPCS[i].getPos().z <= NPCS[a].maxZ))
				{
					if (moveDirX[i] == MOVEDIR_POS)
					{
						moveDirX[i] = MOVEDIR_NONE;
					}
					else if (moveDirX[i] == MOVEDIR_BOTH)
					{
						moveDirX[i] = MOVEDIR_NEG;
					}
				}
				else if ((NPCS[i].minX >= NPCS[a].minX) && (NPCS[i].minX <= NPCS[a].maxX) &&
					(NPCS[i].getPos().z >= NPCS[a].minZ) && (NPCS[i].getPos().z <= NPCS[a].maxZ))
				{
					if (moveDirX[i] == MOVEDIR_NEG)
					{
						moveDirX[i] = MOVEDIR_NONE;
					}
					else if (moveDirX[i] == MOVEDIR_BOTH)
					{
						moveDirX[i] = MOVEDIR_POS;
					}
				}
				else if ((NPCS[i].maxZ >= NPCS[a].minZ) && (NPCS[i].maxZ <= NPCS[a].maxZ) &&
					(NPCS[i].getPos().x >= NPCS[a].minX) && (NPCS[i].getPos().x <= NPCS[a].maxX))
				{
					if (moveDirZ[i] == MOVEDIR_POS)
					{
						moveDirZ[i] = MOVEDIR_NONE;
					}
					else if (moveDirZ[i] == MOVEDIR_BOTH)
					{
						moveDirZ[i] = MOVEDIR_NEG;
					}
				}
				else if ((NPCS[i].minZ >= NPCS[a].minZ) && (NPCS[i].minZ <= NPCS[a].maxZ) &&
					(NPCS[i].getPos().x >= NPCS[a].minX) && (NPCS[i].getPos().x <= NPCS[a].maxX))
				{
					if (moveDirZ[i] == MOVEDIR_NEG)
					{
						moveDirZ[i] = MOVEDIR_NONE;
					}
					else if (moveDirZ[i] == MOVEDIR_BOTH)
					{
						moveDirZ[i] = MOVEDIR_POS;
					}
				}

				if (NPCS[i].getPos().x >= 130.0f)
				{
					if (moveDirX[i] == MOVEDIR_POS)
					{
						moveDirX[i] = MOVEDIR_NONE;
					}
					else if (moveDirX[i] == MOVEDIR_BOTH)
					{
						moveDirX[i] = MOVEDIR_NEG;
					}
				}
				if (NPCS[i].getPos().x <= -130.0f)
				{
					if (moveDirX[i] == MOVEDIR_NEG)
					{
						moveDirX[i] = MOVEDIR_NONE;
					}
					else if (moveDirX[i] == MOVEDIR_BOTH)
					{
						moveDirX[i] = MOVEDIR_POS;
					}
				}
				if (NPCS[i].getPos().z >= 150.0f)
				{

					if (moveDirZ[i] == MOVEDIR_POS)
					{
						moveDirZ[i] = MOVEDIR_NONE;
					}
					else if (moveDirZ[i] == MOVEDIR_BOTH)
					{
						moveDirZ[i] = MOVEDIR_NEG;
					}
				}
				if (NPCS[i].getPos().z <= -150.0f)
				{
					if (moveDirZ[i] == MOVEDIR_NEG)
					{
						moveDirZ[i] = MOVEDIR_NONE;
					}
					else if (moveDirZ[i] == MOVEDIR_BOTH)
					{
						moveDirZ[i] = MOVEDIR_POS;
					}
				}
			}
		}
	}

	// To move in the x and z direction
	for (int i = 0; i < NPC_TOTAL; i++)
	{
		int movement = (((rand() % 3) - 1) * MOVEMENT_SPEED);
		Vector3 finalPos = NPCS[i].getPos() + Vector3(movement, 0, 0);
		if (canMove[i] == true)
		{
			if ((moveDirX[i] == MOVEDIR_BOTH) ||
				(moveDirX[i] == MOVEDIR_POS && movement > 0) ||
				(moveDirX[i] == MOVEDIR_NEG && movement < 0))
			{
				NPCS[i].setBox(finalPos, sizeOfBoxMove);
			}

			movement = (((rand() % 3) - 1) * MOVEMENT_SPEED);
			finalPos = NPCS[i].getPos() + Vector3(0, 0, movement);

			if ((moveDirZ[i] == MOVEDIR_BOTH) ||
				(moveDirZ[i] == MOVEDIR_POS && movement > 0) ||
				(moveDirZ[i] == MOVEDIR_NEG && movement < 0))
			{
				NPCS[i].setBox(finalPos, sizeOfBoxMove);
			}
		}
	}
}


NPC::~NPC()
{
}
