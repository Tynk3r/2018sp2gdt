#include "NPC.h"
static const int moveDelayAmount = 2;	// Movement delay so movement is seamless


NPC::NPC()
{
	NPCS[NPC_RACING].setBox(Vector3(60, 4, 80), sizeOfBoxMove);
	NPCS[NPC_LORE].setBox(Vector3(100, 4, 0), sizeOfBoxMove);
	NPCS[NPC_JOKER].setBox(Vector3(-120, 4, 140), sizeOfBoxMove);
	NPCS[NPC_FACTION_SPEED].setBox(Vector3(-60, 4, -80), sizeOfBoxMove);
	NPCS[NPC_FACTION_GIANT].setBox(Vector3(-100, 4, 40), sizeOfBoxMove);
	NPCS[NPC_SHOP].setBox(Vector3(80, 4, -100), 70, 10, 40);

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

void NPC::UpdateAll()
{
	// Check and set all collision data
	for (int i = 0; i < numberOfNPCs; i++)
	{
		if (i != NPC_SHOP)
		{
			CheckForCollision(i);
		}
	}
	// To move in the x and z direction
	for (int i = 0; i < numberOfNPCs; i++)
	{
		Update(i);
	}

	// To move the speed faction npc more
	for (int loop = 0; loop < 3; loop++)
	{
		for (int i = 0; i < numberOfNPCs; i++)
		{
			if (i != NPC_SHOP)
			{
				CheckForCollision(i);
			}
		}
		Update(NPC_FACTION_SPEED);
	}		
}

void NPC::Update(int NPC_TYPE)
{
	if (NPC_TYPE != NPC_SHOP)
	{
		CheckForMinMaxMovement(NPC_TYPE);
		if (npcMoveDelay[NPC_TYPE] == moveDelayAmount)
		{
			// Generate random number that determines positive, negative or no movement
			int movement = ((rand() % 3) - 1);

			// Set travel direction if not set
			if ((npcDirectionDelay[NPC_TYPE][MOVEAXIS_X] == 0) && (npcDirectionDelay[NPC_TYPE][MOVEAXIS_Z] == 0))
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
						npcDirectionDelay[NPC_TYPE][MOVEAXIS_X] = switching;
					}
					else if (movement < 0)
					{
						npcDirectionDelay[NPC_TYPE][MOVEAXIS_X] = -switching;
					}
				}
				else if (axis == MOVEAXIS_Z)
				{
					if (movement > 0)
					{
						npcDirectionDelay[NPC_TYPE][MOVEAXIS_Z] = switching;
					}
					else if (movement < 0)
					{
						npcDirectionDelay[NPC_TYPE][MOVEAXIS_Z] = -switching;
					}
				}

			}

			// Setting final position vector
			if (canMove[NPC_TYPE] == true)
			{
				if (npcDirectionDelay[NPC_TYPE][MOVEAXIS_X] > 0)
				{
					if ((npcFacingRotaion[NPC_TYPE] % 360) == 90)
					{
						npcDirectionDelay[NPC_TYPE][MOVEAXIS_X]--;
						if ((moveDirX[NPC_TYPE] == MOVEDIR_BOTH) || (moveDirX[NPC_TYPE] == MOVEDIR_POS))
						{
							moveAmt[NPC_TYPE][MOVEAXIS_X]++;
							Vector3 finalPos = NPCS[NPC_TYPE].getPos() + Vector3(movementSpeed, 0, 0);
							NPCS[NPC_TYPE].setBox(finalPos, sizeOfBoxMove);
							npcMoveDelay[NPC_TYPE] = 0;
						}
					}
					else
					{
						RotationUpdate(NPC_TYPE, 90);
					}
				}
				else if (npcDirectionDelay[NPC_TYPE][MOVEAXIS_X] < 0)
				{
					if ((npcFacingRotaion[NPC_TYPE] % 360) == 270)
					{
						npcDirectionDelay[NPC_TYPE][MOVEAXIS_X]++;
						if ((moveDirX[NPC_TYPE] == MOVEDIR_BOTH) || (moveDirX[NPC_TYPE] == MOVEDIR_NEG))
						{
							moveAmt[NPC_TYPE][MOVEAXIS_X]--;
							Vector3 finalPos = NPCS[NPC_TYPE].getPos() + Vector3(-movementSpeed, 0, 0);
							NPCS[NPC_TYPE].setBox(finalPos, sizeOfBoxMove);
							npcMoveDelay[NPC_TYPE] = 0;
						}
					}
					else
					{
						RotationUpdate(NPC_TYPE, 270);
					}
				}
				else if (npcDirectionDelay[NPC_TYPE][MOVEAXIS_Z] > 0)
				{
					if ((npcFacingRotaion[NPC_TYPE] % 360) == 0)
					{
						npcDirectionDelay[NPC_TYPE][MOVEAXIS_Z]--;
						if ((moveDirZ[NPC_TYPE] == MOVEDIR_BOTH) || (moveDirZ[NPC_TYPE] == MOVEDIR_POS))
						{
							moveAmt[NPC_TYPE][MOVEAXIS_Z]++;
							Vector3 finalPos = NPCS[NPC_TYPE].getPos() + Vector3(0, 0, movementSpeed);
							NPCS[NPC_TYPE].setBox(finalPos, sizeOfBoxMove);
							npcMoveDelay[NPC_TYPE] = 0;
						}
					}
					else
					{
						RotationUpdate(NPC_TYPE, 0);
					}
				}
				else if (npcDirectionDelay[NPC_TYPE][MOVEAXIS_Z] < 0)
				{
					if ((npcFacingRotaion[NPC_TYPE] % 360) == 180)
					{
						npcDirectionDelay[NPC_TYPE][MOVEAXIS_Z]++;
						if ((moveDirZ[NPC_TYPE] == MOVEDIR_BOTH) || (moveDirZ[NPC_TYPE] == MOVEDIR_NEG))
						{
							moveAmt[NPC_TYPE][MOVEAXIS_Z]--;
							Vector3 finalPos = NPCS[NPC_TYPE].getPos() + Vector3(0, 0, -movementSpeed);
							NPCS[NPC_TYPE].setBox(finalPos, sizeOfBoxMove);
							npcMoveDelay[NPC_TYPE] = 0;
						}
					}
					else
					{
						RotationUpdate(NPC_TYPE, 180);
					}
				}
			}
		}
		else
		{
			npcMoveDelay[NPC_TYPE]++;
		}
	}
}

void NPC::RotationUpdate(int i, int angle)
{
	for (;npcFacingRotaion[i] < 0;)
	{
		npcFacingRotaion[i] += 360;
	}
	for (;npcFacingRotaion[i] > 360;)
	{
		npcFacingRotaion[i] -= 360;
	}

	double posAngle;

	if (angle > npcFacingRotaion[i])
	{
		posAngle = angle - npcFacingRotaion[i];
	}
	else
	{
		posAngle = 360 + angle - npcFacingRotaion[i];
	}

	double negAngle = 360 - posAngle;

	if (posAngle <= negAngle)
	{
		npcFacingRotaion[i] += 15;
	}
	else
	{
		npcFacingRotaion[i] -= 15;
	}
}

void NPC::CheckForCollision(int i)
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