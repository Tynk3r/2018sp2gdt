#include "NPC.h"

static const int moveDelayAmount = 2;	// Movement delay so movement is seamless

NPC::NPC()
{
	NPCS[NPC_WEATHER].setBox(Vector3(60, 0, 80), sizeOfBoxMove);
	NPCS[NPC_LORE].setBox(Vector3(100, 0, 0), sizeOfBoxMove);
	NPCS[NPC_HUNTING].setBox(Vector3(-120, 0, 140), sizeOfBoxMove);
	NPCS[NPC_RAISING].setBox(Vector3(-60, 0, -80), sizeOfBoxMove);
	NPCS[NPC_RACING].setBox(Vector3(-100, 0, 40), sizeOfBoxMove);
	NPCS[NPC_SHOP].setBox(Vector3(80, 0, -100), sizeOfBoxMove);

	for (int i = 0; i < numberOfNPCs; i++)
	{
		moveDirX[i] = MOVEDIR_BOTH;
		moveDirZ[i] = MOVEDIR_BOTH;
		moveAmt[numberOfNPCs][MOVEAXIS_X] = 0;
		moveAmt[numberOfNPCs][MOVEAXIS_Z] = 0;
		npcMoveDelay[i] = 0;
		npcDirectionDelay[i][MOVEAXIS_X] = 0;
		npcDirectionDelay[i][MOVEAXIS_Z] = 0;
	}
}

Vector3 NPC::GetCoord(int i)
{
	return NPCS[i].getPos();
}

void NPC::Update(double dt)
{
	for (int i = 0; i < numberOfNPCs; i++)
	{
		CheckForCollision(i);
	}
	// To move in the x and z direction
	for (int i = 0; i < numberOfNPCs; i++)
	{
		CheckForMinMaxMovement(i);
		if (npcMoveDelay[i] == moveDelayAmount)
		{
			// Generate random number that determines positive, negative or no movement
			int movement = ((rand() % 3) - 1);

			// Set travel direction if not set
			if ((npcDirectionDelay[i][MOVEAXIS_X] == 0) && (npcDirectionDelay[i][MOVEAXIS_Z] == 0))
			{
				// Generate random number that determines x or z axis
				int axis = (rand() % MOVEAXIS_TOTAL);

				// Generate random number that determines the movement amount required before switching
				int switching = (rand() % 100);
				if (switching >= 2)
				{
					switching = 0;
				}
				else
				{
					switching = 5;
				}

				if (axis == MOVEAXIS_X)
				{
					if (movement > 0)
					{
						npcDirectionDelay[i][MOVEAXIS_X] = switching;
					}
					else if (movement < 0)
					{
						npcDirectionDelay[i][MOVEAXIS_X] = -switching;
					}
				}
				else if (axis == MOVEAXIS_Z)
				{
					if (movement > 0)
					{
						npcDirectionDelay[i][MOVEAXIS_Z] = switching;
					}
					else if (movement < 0)
					{
						npcDirectionDelay[i][MOVEAXIS_Z] = -switching;
					}
				}

			}

			// Setting final position vector

			if (canMove[i] == true)
			{
				if (npcDirectionDelay[i][MOVEAXIS_X] > 0)
				{
					npcDirectionDelay[i][MOVEAXIS_X]--;
					if ((moveDirX[i] == MOVEDIR_BOTH) || (moveDirX[i] == MOVEDIR_POS))
					{
						moveAmt[i][MOVEAXIS_X]++;
						Vector3 finalPos = NPCS[i].getPos() + Vector3(movementSpeed, 0, 0);
						NPCS[i].setBox(finalPos, sizeOfBoxMove);
						npcMoveDelay[i] = 0;
					}
				}
				else if (npcDirectionDelay[i][MOVEAXIS_X] < 0)
				{
					npcDirectionDelay[i][MOVEAXIS_X]++;
					if ((moveDirX[i] == MOVEDIR_BOTH) || (moveDirX[i] == MOVEDIR_NEG))
					{
						moveAmt[i][MOVEAXIS_X]--;
						Vector3 finalPos = NPCS[i].getPos() + Vector3(-movementSpeed, 0, 0);
						NPCS[i].setBox(finalPos, sizeOfBoxMove);
						npcMoveDelay[i] = 0;
					}
				}
				else if (npcDirectionDelay[i][MOVEAXIS_Z] > 0)
				{
					npcDirectionDelay[i][MOVEAXIS_Z]--;
					if ((moveDirZ[i] == MOVEDIR_BOTH) || (moveDirZ[i] == MOVEDIR_POS))
					{
						moveAmt[i][MOVEAXIS_Z]++;
						Vector3 finalPos = NPCS[i].getPos() + Vector3(0, 0, movementSpeed);
						NPCS[i].setBox(finalPos, sizeOfBoxMove);
						npcMoveDelay[i] = 0;
					}
				}
				else if (npcDirectionDelay[i][MOVEAXIS_Z] < 0)
				{
					npcDirectionDelay[i][MOVEAXIS_Z]++;
					if ((moveDirZ[i] == MOVEDIR_BOTH) || (moveDirZ[i] == MOVEDIR_NEG))
					{
						moveAmt[i][MOVEAXIS_Z]--;
						Vector3 finalPos = NPCS[i].getPos() + Vector3(0, 0, -movementSpeed);
						NPCS[i].setBox(finalPos, sizeOfBoxMove);
						npcMoveDelay[i] = 0;
					}
				}
			}
		}
		else
		{
			npcMoveDelay[i]++;
		}
	}
}

void NPC::CheckForCollision(int i)
{
	// To check collision
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

void NPC::CheckForMinMaxMovement(int i)
{
	if (moveAmt[i][MOVEAXIS_X] == maxMoveAmt)
	{
		if (moveDirX[i] == MOVEDIR_BOTH)
		{
			moveDirX[i] = MOVEDIR_NEG;
		}
		else if (moveDirX[i] == MOVEDIR_POS)
		{
			moveDirX[i] = MOVEDIR_NONE;
		}
	}
	else if (moveAmt[i][MOVEAXIS_X] == minMoveAmt)
	{
		if (moveDirX[i] == MOVEDIR_BOTH)
		{
			moveDirX[i] = MOVEDIR_POS;
		}
		else if (moveDirX[i] == MOVEDIR_NEG)
		{
			moveDirX[i] = MOVEDIR_NONE;
		}
	}

	if (moveAmt[i][MOVEAXIS_Z] == maxMoveAmt)
	{
		if (moveDirZ[i] == MOVEDIR_BOTH)
		{
			moveDirZ[i] = MOVEDIR_NEG;
		}
		else if (moveDirZ[i] == MOVEDIR_POS)
		{
			moveDirZ[i] = MOVEDIR_NONE;
		}
	}
	else if (moveAmt[i][MOVEAXIS_Z] == minMoveAmt)
	{
		if (moveDirZ[i] == MOVEDIR_BOTH)
		{
			moveDirZ[i] = MOVEDIR_POS;
		}
		else if (moveDirZ[i] == MOVEDIR_NEG)
		{
			moveDirX[i] = MOVEDIR_NONE;
		}
	}
}

NPC::~NPC()
{
}
