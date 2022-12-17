#include <iostream>
#include "NetworkManager.h"
#include <string>
#include <conio.h>
#include <ctime>

using namespace std;

int main()
{
	// Some things still aren't visible and I increased stamina because it sometimes disappears for some unknown reason,
	// but the effects of the invisible choices can be seen in the hps/stamina reveal screen so it's good enough. It
	// doesn't loop anymore and I'm not sure what else I can do to improve it without a massive rewrite. - ZS

	NetworkManager::GetInstance()->Init();

	NetworkManager::GetInstance()->CreateTCPSockets();

	const int SERVER = 1;
	cout << "Choose a role:" << endl;
	cout << "\t1) Server" << endl;
	cout << "\t2) Client" << endl;
	int choice;
	cin >> choice;

	if (choice == SERVER)
	{
		NetworkManager::GetInstance()->BindTCP();
		NetworkManager::GetInstance()->ListenTCP();
	}
	else
	{
		NetworkManager::GetInstance()->ConnectTCP();
	}


	int playerHitPoints = 20;
	int enemyHitPoints = 30;
	int stamina = 20;
	int MAX_STAMINA = 20;
	float dodgeSuccess = 50.0f;
	float parrySuccess = 30.0f;

	int childhoodActivityChoice = 0;
	bool bookSmart = false;
	bool bullStrength = false;

	int buildChoice = 0;
	bool ogreStrength = false;

	int heightChoice = 0;

	char favouriteLetter = 'D';

	srand(time(0));

	bool playerFound = false;
	string myMsg;
	while (true)
	{
		if (choice != SERVER)
		{
			if (_kbhit())
			{
				getline(cin, myMsg);
				if (myMsg.length() > 0)
				{
					NetworkManager::GetInstance()->SendDataTCP(myMsg.c_str());
				}
			}

			char rcvMessage[NetworkManager::MAX_MESSAGE];
			int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);

			if (size > 0)
			{
				cout << rcvMessage << endl << endl;
			}
		}

		if (choice == SERVER)
		{
			while (playerFound == false)
			{
				NetworkManager::GetInstance()->AcceptConnectionsTCP(playerFound);
				NetworkManager::GetInstance()->SendDataTCP("Type \"start\" to begin the game.\n\n");
			}

			char rcvMessage[NetworkManager::MAX_MESSAGE];
			int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);

			if (strcmp("start", rcvMessage) == 0 && childhoodActivityChoice == 0)
			{
				NetworkManager::GetInstance()->SendDataTCP("What was your favourite activity as a child?\n\t1)\tEating\n\t2)\tDancing\n\t3)\tReading\n\t4)\tFighting\n\t5)\tPlaying\n\t6)\tWorking\n\n");
				while (childhoodActivityChoice == 0)
				{
					char rcvMessage[NetworkManager::MAX_MESSAGE];
					int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
					if (strcmp("1", rcvMessage) == 0)
					{
						NetworkManager::GetInstance()->SendDataTCP("You spent much of your childhood eating like a pig.\n\nWhat type of build do you have?\n\t1)\tEctomorphic\n\t2)\tEcto-Meso\n\t3)\tMesomorphic\n\t4)\tEndo-Meso\n\t5)\tEndomorphic\n\n");
						playerHitPoints += 5;
						childhoodActivityChoice = 1;
					}
					else if (strcmp("2", rcvMessage) == 0)
					{
						NetworkManager::GetInstance()->SendDataTCP("You spent much of your childhood dancing with various girls around town.\n\nWhat type of build do you have?\n\t1)\tEctomorphic\n\t2)\tEcto-Meso\n\t3)\tMesomorphic\n\t4)\tEndo-Meso\n\t5)\tEndomorphic\n\n");
						parrySuccess += 15.0;
						childhoodActivityChoice = 2;
					}
					else if (strcmp("3", rcvMessage) == 0)
					{
						NetworkManager::GetInstance()->SendDataTCP("You spent your childhood reading and learning about countless topics\n\nWhat type of build do you have?\n\t1)\tEctomorphic\n\t2)\tEcto-Meso\n\t3)\tMesomorphic\n\t4)\tEndo-Meso\n\t5)\tEndomorphic\n\n");
						bookSmart = true;
						childhoodActivityChoice = 3;
					}
					else if (strcmp("4", rcvMessage) == 0)
					{
						NetworkManager::GetInstance()->SendDataTCP("You spent your childhoot getting into fights.\n\nWhat type of build do you have?\n\t1)\tEctomorphic\n\t2)\tEcto-Meso\n\t3)\tMesomorphic\n\t4)\tEndo-Meso\n\t5)\tEndomorphic\n\n");
						bullStrength = true;
						childhoodActivityChoice = 4;
					}
					else if (strcmp("5", rcvMessage) == 0)
					{
						NetworkManager::GetInstance()->SendDataTCP("You spent your childhood playing with \'The Boys\'.\n\nWhat type of build do you have?\n\t1)\tEctomorphic\n\t2)\tEcto-Meso\n\t3)\tMesomorphic\n\t4)\tEndo-Meso\n\t5)\tEndomorphic\n\n");
						dodgeSuccess += 10;
						childhoodActivityChoice = 5;
					}
					else if (strcmp("6", rcvMessage) == 0)
					{
						NetworkManager::GetInstance()->SendDataTCP("You spent your childhood helping the townsfolk with physical labour.\n\nWhat type of build do you have?\n\t1)\tEctomorphic\n\t2)\tEcto-Meso\n\t3)\tMesomorphic\n\t4)\tEndo-Meso\n\t5)\tEndomorphic\n\n");
						MAX_STAMINA += 5;
						stamina += 5;
						childhoodActivityChoice = 6;
					}
				}
			}
			if (childhoodActivityChoice != 0 && buildChoice == 0)
			{
				while (buildChoice == 0)
				{
					char rcvMessage[NetworkManager::MAX_MESSAGE];
					int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
					if (strcmp("1", rcvMessage) == 0)
					{
						NetworkManager::GetInstance()->SendDataTCP("Your body is lithe and difficult to hit.\n\nHow tall are you?\n\t1)\tShort\n\t2)\tMedium\n\t3)\tTall\n\n");
						playerHitPoints += 5;
						buildChoice = 1;
					}
					else if (strcmp("2", rcvMessage) == 0)
					{
						NetworkManager::GetInstance()->SendDataTCP("Your body has is nicely toned.\n\nHow tall are you?\n\t1)\tShort\n\t2)\tMedium\n\t3)\tTall\n\n");
						parrySuccess += 15.0;
						buildChoice = 2;
					}
					else if (strcmp("3", rcvMessage) == 0)
					{
						NetworkManager::GetInstance()->SendDataTCP("You are built like a bull on steroids.\n\nHow tall are you?\n\t1)\tShort\n\t2)\tMedium\n\t3)\tTall\n\n");
						ogreStrength = true;
						buildChoice = 3;
					}
					else if (strcmp("4", rcvMessage) == 0)
					{
						NetworkManager::GetInstance()->SendDataTCP("You are the living embodiment of a brick wall.\n\nHow tall are you?\n\t1)\tShort\n\t2)\tMedium\n\t3)\tTall\n\n");
						MAX_STAMINA += 5;
						stamina += 5;
						buildChoice = 4;
					}
					else if (strcmp("5", rcvMessage) == 0)
					{
						NetworkManager::GetInstance()->SendDataTCP("Your body is thick and durable.\n\nHow tall are you?\n\t1)\tShort\n\t2)\tMedium\n\t3)\tTall\n\n");
						playerHitPoints += 5;
						buildChoice = 5;
					}
				}
			}

			if (buildChoice != 0 && heightChoice == 0)
			{
				while (heightChoice == 0)
				{
					char rcvMessage[NetworkManager::MAX_MESSAGE];
					int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
					if (strcmp("1", rcvMessage) == 0)
					{
						NetworkManager::GetInstance()->SendDataTCP("You are a manlet.\n\nsend any character to continue\n");
						dodgeSuccess += 10;
						bool cont = false;
						while (cont == false)
						{
							char rcvMessage[NetworkManager::MAX_MESSAGE];
							int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
							if (size >= 0)
							{
								cont = true;
							}
						}
						heightChoice = 1;
					}
					else if (strcmp("2", rcvMessage) == 0)
					{
						NetworkManager::GetInstance()->SendDataTCP("You are average height.\n\nsend any character to continue\n");
						MAX_STAMINA += 5;
						stamina += 5;
						bool cont = false;
						while (cont == false)
						{
							char rcvMessage[NetworkManager::MAX_MESSAGE];
							int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
							if (size >= 0)
							{
								cont = true;
							}
						}
						heightChoice = 2;
					}
					else if (strcmp("3", rcvMessage) == 0)
					{
						NetworkManager::GetInstance()->SendDataTCP("You are enormous.\n\nsend any character to continue\n");
						playerHitPoints += 5;
						bool cont = false;
						while (cont == false)
						{
							char rcvMessage[NetworkManager::MAX_MESSAGE];
							int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
							if (size >= 0)
							{
								cont = true;
							}
						}
						heightChoice = 3;
					}
				}
			}

			int enemyMove = 0;
			int enemyStrikeLocation = 0;
			int successfulDodges = 0;
			int coins = 1;
			bool enemyKnowsBetter = false;
			if (heightChoice != 0)
			{
				while (playerHitPoints > 0 && enemyHitPoints > 0)
				{
					do
					{
						enemyMove = (rand() % 9) + 1; // Deciding opponent's action.
						// Light attacks countered with defensive options.
						if (enemyMove >= 1 && enemyMove <= 4)
						{
							enemyStrikeLocation = (rand() % 3) + 1; // Deciding light attack text.
							if (enemyStrikeLocation == 1) // High strike location.
							{
								if (bookSmart == true)
								{
									NetworkManager::GetInstance()->SendDataTCP("your opponent raises his sword next to his head, his movements relatively quick.\n\nHow will you respond?\n\t1)\tLight Attack\n\t2)\tStrong Attack\n\t3)\tParry\n\t4)\tBlock\n\t5)\tDodge\n\n");
								}
								else
								{
									NetworkManager::GetInstance()->SendDataTCP("Your opponent raises his sword next to his head.\n\nHow will you respond?\n\t1)\tLight Attack\n\t2)\tStrong Attack\n\t3)\tParry\n\t4)\tBlock\n\t5)\tDodge\n\n");
								}
							}
							else if (enemyStrikeLocation == 2) // Middle strike location.
							{
								if (bookSmart == true)
								{
									NetworkManager::GetInstance()->SendDataTCP("your opponent moves his sword to his side, his movements relatively quick.\n\nHow will you respond?\n\t1)\tLight Attack\n\t2)\tStrong Attack\n\t3)\tParry\n\t4)\tBlock\n\t5)\tDodge\n\n");
								}
								else
								{
									NetworkManager::GetInstance()->SendDataTCP("Your opponent moves his sword to his side.\n\nHow will you respond?\n\t1)\tLight Attack\n\t2)\tStrong Attack\n\t3)\tParry\n\t4)\tBlock\n\t5)\tDodge\n\n");
								}
							}
							else if (enemyStrikeLocation == 3) // Low strike location.
							{
								if (bookSmart == true)
								{
									NetworkManager::GetInstance()->SendDataTCP("your opponent lowers his sword to his waist, his movements are relatively quick.\n\nHow will you respond?\n\t1)\tLight Attack\n\t2)\tStrong Attack\n\t3)\tParry\n\t4)\tBlock\n\t5)\tDodge\n\n");

								}
								else
								{
									NetworkManager::GetInstance()->SendDataTCP("Your opponent lowers his sword to his waist.\n\nHow will you respond?\n\t1)\tLight Attack\n\t2)\tStrong Attack\n\t3)\tParry\n\t4)\tBlock\n\t5)\tDodge\n\n");
								}
							}

							int playerMoveChoice = 0;

							while (playerMoveChoice == 0)
							{
								char rcvMessage[NetworkManager::MAX_MESSAGE];
								int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
								if (strcmp("1", rcvMessage) == 0) // Light attack vs.light attack.
								{
									NetworkManager::GetInstance()->SendDataTCP("You strike quickly at your opponent with your sword, but he, already being mid-swing, landed his attack first, cutting your flesh and stopping your attack.\n\nsend any character to continue\n");
									playerHitPoints--;
									bool cont = false;
									while (cont == false)
									{
										char rcvMessage[NetworkManager::MAX_MESSAGE];
										int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
										if (size >= 0)
										{
											cont = true;
										}
									}
									playerMoveChoice = -1;
								}
								else if (strcmp("2", rcvMessage) == 0) // Strong attack vs. light attack.
								{
									if (stamina < 2)
									{
										NetworkManager::GetInstance()->SendDataTCP("Being too tired to make your attack, the opponent\'s strike lands unabated, cutting your flesh.\n\nsend any character to continue\n");
										playerHitPoints--;
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									else
									{
										NetworkManager::GetInstance()->SendDataTCP("You strike at your opponent powerfully with your sword, but he, already being mid-swing, landed his attack first, cutting your flesh and stopping your attack.\n\nsend any character to continue\n");
										playerHitPoints--;
										stamina -= 2;
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									playerMoveChoice = -1;
								}
								else if (strcmp("3", rcvMessage) == 0) // Parry vs. light attack. (good)
								{
									if ((rand() % 80) + 1 <= parrySuccess)
									{
										NetworkManager::GetInstance()->SendDataTCP("Your opponent attacks you with his sword, but you skillfully deflect the attack with your own weapon.\n\nsend any character to continue\n");
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									else
									{
										NetworkManager::GetInstance()->SendDataTCP("Your opponent lands their attack, cutting your flesh, despite your attempt to deflect it.\n\nsend any character to continue\n");
										playerHitPoints--;
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									playerMoveChoice = -1;
								}
								else if (strcmp("4", rcvMessage) == 0) // Block vs. light attack. (good)
								{
									if (stamina < 2)
									{
										NetworkManager::GetInstance()->SendDataTCP("Being too tired to block, your opponent\'s attack breaks through your guard, cutting your flesh, despite your attempt to block the attack with your shield.\n\nsend any character to continue\n");
										playerHitPoints--;
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									else
									{
										NetworkManager::GetInstance()->SendDataTCP("Your opponent attacks you with his sword, but you block the attack with your shield.\n\nsend any character to continue\n");
										stamina--;
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									playerMoveChoice = -1;
								}
								else if (strcmp("5", rcvMessage) == 0) // Dodge vs. light attack. (good)
								{
									if ((rand() % 100) + 1 <= dodgeSuccess)
									{
										NetworkManager::GetInstance()->SendDataTCP("Your opponent attacks you with his sword, but you dodge the attack.\n\nsend any character to continue\n");
										stamina -= 3;
										successfulDodges++;
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									else if (stamina < 3)
									{
										NetworkManager::GetInstance()->SendDataTCP("Being too tired to dodge, your opponent\'s attack lands unabated, cutting your flesh.\n\nsend any character to continue\n");
										playerHitPoints--;
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									else
									{
										NetworkManager::GetInstance()->SendDataTCP("Your opponent attacks you with his sword, cutting your flesh, despite your attempt to dodge the attack.\n\nsend any character to continue\n");
										playerHitPoints--;
										stamina -= 3;
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									playerMoveChoice = -1;
								}
							}

						}

						// Strong attacks countered with light attacks.
						else if (enemyMove == 5 || enemyMove == 6)
						{
							enemyStrikeLocation = (rand() % 3) + 1; // Deciding strong attack text.
							if (enemyStrikeLocation == 1) // High strike location.
							{

								if (bookSmart == true)
								{
									NetworkManager::GetInstance()->SendDataTCP("your opponent raises his sword high above his head, his body shaking with power.\n\nHow will you respond?\n\t1)\tLight Attack\n\t2)\tStrong Attack\n\t3)\tParry\n\t4)\tBlock\n\t5)\tDodge\n\n");
								}
								else
								{
									NetworkManager::GetInstance()->SendDataTCP("Your opponent raises his sword high above his head.\n\nHow will you respond?\n\t1)\tLight Attack\n\t2)\tStrong Attack\n\t3)\tParry\n\t4)\tBlock\n\t5)\tDodge\n\n");
								}

							}
							else if (enemyStrikeLocation == 2) // Middle strike location/
							{
								if (bookSmart == true)
								{
									NetworkManager::GetInstance()->SendDataTCP("Your opponent twists his body as he moves his sword to his side, his body shaking with power.\n\nHow will you respond?\n\t1)\tLight Attack\n\t2)\tStrong Attack\n\t3)\tParry\n\t4)\tBlock\n\t5)\tDodge\n\n");
								}
								else
								{
									NetworkManager::GetInstance()->SendDataTCP("Your opponent twists his body as he moves his sword to his side.\n\nHow will you respond?\n\t1)\tLight Attack\n\t2)\tStrong Attack\n\t3)\tParry\n\t4)\tBlock\n\t5)\tDodge\n\n");
								}
							}
							else if (enemyStrikeLocation == 3) // Low strike location.
							{
								if (bookSmart == true)
								{
									NetworkManager::GetInstance()->SendDataTCP("your opponent sticks the tip of his sword in the ground, his body shaking with power.\n\nHow will you respond?\n\t1)\tLight Attack\n\t2)\tStrong Attack\n\t3)\tParry\n\t4)\tBlock\n\t5)\tDodge\n\n");
								}
								else
								{
									NetworkManager::GetInstance()->SendDataTCP("your opponent sticks the tip of his sword in the ground.\n\nHow will you respond?\n\t1)\tLight Attack\n\t2)\tStrong Attack\n\t3)\tParry\n\t4)\tBlock\n\t5)\tDodge\n\n");
								}
							}

							int playerMoveChoice = 0;

							while (playerMoveChoice == 0)
							{
								char rcvMessage[NetworkManager::MAX_MESSAGE];
								int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
								if (strcmp("1", rcvMessage) == 0) // Light attack vs. strong attack. (good)
								{
									NetworkManager::GetInstance()->SendDataTCP("You strike quickly at your opponent with your sword, cutting their flesh and stopping his attack before it could land.\n\nsend any character to continue\n");
									if (bullStrength == true || ogreStrength == true)
									{
										enemyHitPoints -= 2;
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									else if (bullStrength == true && ogreStrength == true)
									{
										enemyHitPoints -= 3;
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									else
									{
										enemyHitPoints--;
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									playerMoveChoice = -1;
								}
								else if (strcmp("2", rcvMessage) == 0) // Strong attack vs. strong attack.
								{
									if (stamina < 2)
									{
										NetworkManager::GetInstance()->SendDataTCP("Being too tired to make your attack, your opponent\'s strike lands unabated, cleaving your flesh.\n\nsend any character to continue\n");
										playerHitPoints -= 3;
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									else
									{
										NetworkManager::GetInstance()->SendDataTCP("You strike at your opponent powerfully with your sword, but he, already being mid-swing, landed his attack first, cleaving your flesh and stopping your attack\n\nsend any character to continue\n");
										playerHitPoints -= 3;
										stamina -= 2;
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									playerMoveChoice = -1;
								}
								else if (strcmp("3", rcvMessage) == 0) // Parry vs. strong attack.
								{
									if ((rand() % 100) + 1 <= parrySuccess)
									{
										NetworkManager::GetInstance()->SendDataTCP("Your opponent attacks you with his sword, but you skillfully deflect the attack with your own weapon.\n\nsend any character to continue\n");
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									else
									{
										NetworkManager::GetInstance()->SendDataTCP("Your opponent lands their attack, cleaving your flesh, despite your attempt to deflect it.\n\nsend any character to continue\n");
										playerHitPoints -= 3;
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									playerMoveChoice = -1;

								}
								else if (strcmp("4", rcvMessage) == 0) // Block vs. strong attack.
								{
									if (stamina < 3)
									{
										NetworkManager::GetInstance()->SendDataTCP("Being too tired to block, your opponent\'s attack breaks through your guard, cleaving your flesh, despite your attempt to block the attack with your shield.\n\nsend any character to continue\n");
										playerHitPoints -= 3;
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									else
									{
										NetworkManager::GetInstance()->SendDataTCP("Your opponent attacks you with his sword, but you block the attack with your shield.\n\nsend any character to continue\n");
										stamina -= 3;
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									playerMoveChoice = -1;
								}
								else if (strcmp("5", rcvMessage) == 0) // Dodge vs. strong attack.
								{
									if ((rand() % 100) + 1 <= dodgeSuccess && stamina > 2)
									{
										NetworkManager::GetInstance()->SendDataTCP("Your opponent attacks you with his sword, but you dodge the attack.\n\nsend any character to continue\n");
										stamina -= 3;
										successfulDodges++;
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									else if (stamina < 3)
									{
										NetworkManager::GetInstance()->SendDataTCP("Being too tired to dodge, your opponent\'s attack lands unabated, cleaving your flesh.\n\nsend any character to continue\n");
										playerHitPoints -= 3;
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									else
									{
										NetworkManager::GetInstance()->SendDataTCP("Your opponent attacks you with his sword, cleaving your flesh, despite your attempt to dodge the attack.\n\nsend any character to continue\n");
										playerHitPoints -= 3;
										stamina -= 3;
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									playerMoveChoice = -1;
								}
							}
						}

						// Blocks countered with strong attack.
						else
						{
							if (bookSmart == true)
							{
								NetworkManager::GetInstance()->SendDataTCP("Your opponent holds their sword out in front of them, assuming a defensive stance.\n\nHow will you respond?\n\t1)\tLight Attack\n\t2)\tStrong Attack\n\t3)\tParry\n\t4)\tBlock\n\t5)\tDodge\n\n");
							}
							else
							{
								NetworkManager::GetInstance()->SendDataTCP("Your opponent holds their sword out in front of them.\n\nHow will you respond?\n\t1)\tLight Attack\n\t2)\tStrong Attack\n\t3)\tParry\n\t4)\tBlock\n\t5)\tDodge\n\n");
							}

							int playerMoveChoice = 0;

							while (playerMoveChoice == 0)
							{
								char rcvMessage[NetworkManager::MAX_MESSAGE];
								int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
								if (strcmp("1", rcvMessage) == 0) // Light attack vs. block.
								{
									NetworkManager::GetInstance()->SendDataTCP("You strike quickly at your opponent with your sword, but he blocks your attack with his sword.\n\nsend any character to continue\n");
									bool cont = false;
									while (cont == false)
									{
										char rcvMessage[NetworkManager::MAX_MESSAGE];
										int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
										if (size >= 0)
										{
											cont = true;
										}
									}
									playerMoveChoice = -1;
								}
								else if (strcmp("2", rcvMessage) == 0) // Strong attack vs. block. (good)
								{
									if (stamina < 2)
									{
										NetworkManager::GetInstance()->SendDataTCP("Being too tired to make your attack, your opponent watches you carefully for a moment before the battle continues.\n\nsend any character to continue\n");
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									else
									{
										NetworkManager::GetInstance()->SendDataTCP("You strike at your opponent powerfully with your sword, breaking his guard and cleaving his flesh, despite his attempt to block your attack with his sword.\n\nsend any character to continue\n");
										if (bullStrength == true || ogreStrength == true)
										{
											enemyHitPoints -= 4;
											stamina -= 2;
											bool cont = false;
											while (cont == false)
											{
												char rcvMessage[NetworkManager::MAX_MESSAGE];
												int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
												if (size >= 0)
												{
													cont = true;
												}
											}
										}
										else if (bullStrength == true && ogreStrength == true)
										{
											enemyHitPoints -= 5;
											stamina -= 2;
											bool cont = false;
											while (cont == false)
											{
												char rcvMessage[NetworkManager::MAX_MESSAGE];
												int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
												if (size >= 0)
												{
													cont = true;
												}
											}
										}
										else
										{
											enemyHitPoints -= 3;
											stamina -= 2;
											bool cont = false;
											while (cont == false)
											{
												char rcvMessage[NetworkManager::MAX_MESSAGE];
												int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
												if (size >= 0)
												{
													cont = true;
												}
											}
										}
									}
									playerMoveChoice = -1;
								}
								else if (strcmp("3", rcvMessage) == 0) // Parry vs. block.
								{
									NetworkManager::GetInstance()->SendDataTCP("Preparing to parry his next strike, you stare each other down, neither combatant making a move.\n\nsend any character to continue\n");
									bool cont = false;
									while (cont == false)
									{
										char rcvMessage[NetworkManager::MAX_MESSAGE];
										int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
										if (size >= 0)
										{
											cont = true;
										}
									}
									playerMoveChoice = -1;
								}
								else if (strcmp("4", rcvMessage) == 0) // Block vs. block.
								{
									NetworkManager::GetInstance()->SendDataTCP("Preparing to block his next strike with your shield, you stare each other down, neither combatant making a move.\n\nsend any character to continue\n");
									bool cont = false;
									while (cont == false)
									{
										char rcvMessage[NetworkManager::MAX_MESSAGE];
										int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
										if (size >= 0)
										{
											cont = true;
										}
									}
									playerMoveChoice = -1;
								}
								else if (strcmp("5", rcvMessage) == 0) // Dodge vs. block.
								{
									NetworkManager::GetInstance()->SendDataTCP("Preparing to dodge his next strike, you stare each other down, neither combatant making a move.\n\nsend any character to continue\n");
									bool cont = false;
									while (cont == false)
									{
										char rcvMessage[NetworkManager::MAX_MESSAGE];
										int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
										if (size >= 0)
										{
											cont = true;
										}
									}
									playerMoveChoice = -1;
								}
							}
						}

						// HP and stamina message.
						if (stamina >= MAX_STAMINA)
						{
							char mess[200];
							sprintf_s(mess, "Hit Points Remaining: %d%s%d%s%d%s", playerHitPoints, "\nStamina Remaining: ", stamina, "\nEnemy Hit Points Remaining: ", enemyHitPoints, "\n\nsend any character to continue\n");
							NetworkManager::GetInstance()->SendDataTCP(mess);
							bool cont = false;
							while (cont == false)
							{
								char rcvMessage[NetworkManager::MAX_MESSAGE];
								int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
								if (size >= 0)
								{
									cont = true;
								}
							}
						}
						else
						{
							stamina++;
							char mess[200];
							sprintf_s(mess, "Hit Points Remaining: %d%s%d%s%d%s", playerHitPoints, "\nStamina Remaining: ", stamina, "\nEnemy Hit Points Remaining: ", enemyHitPoints, "\n\nsend any character to continue\n");
							NetworkManager::GetInstance()->SendDataTCP(mess);
							bool cont = false;
							while (cont == false)
							{
								char rcvMessage[NetworkManager::MAX_MESSAGE];
								int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
								if (size >= 0)
								{
									cont = true;
								}
							}
						}
					} while (successfulDodges != 3 && successfulDodges != 4 && playerHitPoints > 0 && enemyHitPoints > 0);

					if (successfulDodges == 3 && enemyKnowsBetter == false) // Li'l easter egg, attack this turn for next turn's attack to deal triple damage.
					{
						if (bookSmart == true)
						{
							NetworkManager::GetInstance()->SendDataTCP("your opponent assumes a strange, clumsy-looking stance.\n\nHow will you respond?\n\t1)\tLight Attack\n\t2)\tStrong Attack\n\t3)\tParry\n\t4)\tBlock\n\t5)\tDodge\n\n");
						}
						else
						{
							NetworkManager::GetInstance()->SendDataTCP("Your opponent assumes a stance you haven't seen before.\n\nHow will you respond?\n\t1)\tLight Attack\n\t2)\tStrong Attack\n\t3)\tParry\n\t4)\tBlock\n\t5)\tDodge\n\n");
						}
						//////////////////////////////////////////////////////////HERE


						int playerMoveChoice = 0;

						while (playerMoveChoice == 0)
						{
							char rcvMessage[NetworkManager::MAX_MESSAGE];
							int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
							if (strcmp("1", rcvMessage) == 0) // Light attack vs. crit chance. (best)
							{
								NetworkManager::GetInstance()->SendDataTCP("You strike quickly at your opponent with your sword, but he leaps out of the path of your attack, shouting in pain as he hits the ground.\n\nsend any character to continue\n");
								enemyHitPoints--;
								successfulDodges++;
								bool cont = false;
								while (cont == false)
								{
									char rcvMessage[NetworkManager::MAX_MESSAGE];
									int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
									if (size >= 0)
									{
										cont = true;
									}
								}
								playerMoveChoice = -1;
							}
							else if (strcmp("2", rcvMessage) == 0) // Strong attack vs. crit chance. (good)
							{
								if (stamina < 2)
								{
									NetworkManager::GetInstance()->SendDataTCP("Being too tired to make your attack, your opponent stands motionless as the two of you stare at each other before he reassumes his regular combat stance, his dissappointment clear as day.\n\nsend any character to continue\n");
									successfulDodges--;
									bool cont = false;
									while (cont == false)
									{
										char rcvMessage[NetworkManager::MAX_MESSAGE];
										int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
										if (size >= 0)
										{
											cont = true;
										}
									}
								}
								else
								{
									NetworkManager::GetInstance()->SendDataTCP("You strike at your opponent powerfully with your sword, but he leaps out of the path of your attack, shouting in pain as he hits the ground.\n\nsend any character to continue\n");
									enemyHitPoints--;
									stamina -= 2;
									successfulDodges++;
									bool cont = false;
									while (cont == false)
									{
										char rcvMessage[NetworkManager::MAX_MESSAGE];
										int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
										if (size >= 0)
										{
											cont = true;
										}
									}
								}
								playerMoveChoice = -1;
							}
							else if (strcmp("3", rcvMessage) == 0) // Parry vs. crit chance.
							{
								NetworkManager::GetInstance()->SendDataTCP("Your opponent stands motionless as the two of you stare at each other before he reassumes his regular combat stance, his dissappointment clear as day.\n\nsend any character to continue\n");
								successfulDodges--;
								bool cont = false;
								while (cont == false)
								{
									char rcvMessage[NetworkManager::MAX_MESSAGE];
									int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
									if (size >= 0)
									{
										cont = true;
									}
								}
								playerMoveChoice = -1;
							}
							else if (strcmp("4", rcvMessage) == 0) // Block vs. crit chance.
							{
								NetworkManager::GetInstance()->SendDataTCP("Your opponent stands motionless as the two of you stare at each other before he reassumes his regular combat stance, his dissappointment clear as day.\n\nsend any character to continue\n");
								successfulDodges--;
								bool cont = false;
								while (cont == false)
								{
									char rcvMessage[NetworkManager::MAX_MESSAGE];
									int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
									if (size >= 0)
									{
										cont = true;
									}
								}
								playerMoveChoice = -1;
							}
							else if (strcmp("5", rcvMessage) == 0) // Dodge vs. crit chance.
							{
								NetworkManager::GetInstance()->SendDataTCP("Your opponent stands motionless as the two of you stare at each other before he reassumes his regular combat stance, his dissappointment clear as day.\n\nsend any character to continue\n");
								successfulDodges--;
								bool cont = false;
								while (cont == false)
								{
									char rcvMessage[NetworkManager::MAX_MESSAGE];
									int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
									if (size >= 0)
									{
										cont = true;
									}
								}
								playerMoveChoice = -1;
							}
						}

						// Player HP and stamina message.
						if (stamina >= MAX_STAMINA)
						{
							char mess[200];
							sprintf_s(mess, "Hit Points Remaining: %d%s%d%s%d%s", playerHitPoints, "\nStamina Remaining: ", stamina, "\nEnemy Hit Points Remaining: ", enemyHitPoints, "\n\nsend any character to continue\n");
							NetworkManager::GetInstance()->SendDataTCP(mess);
							bool cont = false;
							while (cont == false)
							{
								char rcvMessage[NetworkManager::MAX_MESSAGE];
								int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
								if (size >= 0)
								{
									cont = true;
								}
							}
						}
						else
						{
							stamina++;
							char mess[200];
							sprintf_s(mess, "Hit Points Remaining: %d%s%d%s%d%s", playerHitPoints, "\nStamina Remaining: ", stamina, "\nEnemy Hit Points Remaining: ", enemyHitPoints, "\n\nsend any character to continue\n");
							NetworkManager::GetInstance()->SendDataTCP(mess);
							bool cont = false;
							while (cont == false)
							{
								char rcvMessage[NetworkManager::MAX_MESSAGE];
								int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
								if (size >= 0)
								{
									cont = true;
								}
							}
						}
					}

					if (successfulDodges == 4)
					{
						NetworkManager::GetInstance()->SendDataTCP("Your opponent is struggling to stand back up.\n\nHow will you respond?\n\t1)\tLight Attack\n\t2)\tStrong Attack\n\t3)\tParry\n\t4)\tBlock\n\t5)\tDodge\n\n");
						////////////////////////////////////////////////AND HERE

						int playerMoveChoice = 0;

						while (playerMoveChoice == 0)
						{
							char rcvMessage[NetworkManager::MAX_MESSAGE];
							int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
							if (strcmp("1", rcvMessage) == 0) // Light attack vs. free damage. (good)
							{
								NetworkManager::GetInstance()->SendDataTCP("You strike your opponent as he attempts to stand up.\nCRITICAL HIT\n\nsend any character to continue\n");
								if (bullStrength == true || ogreStrength == true)
								{
									enemyHitPoints -= 6;
									bool cont = false;
									while (cont == false)
									{
										char rcvMessage[NetworkManager::MAX_MESSAGE];
										int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
										if (size >= 0)
										{
											cont = true;
										}
									}
								}
								else if (bullStrength == true && ogreStrength == true)
								{
									enemyHitPoints -= 9;
									bool cont = false;
									while (cont == false)
									{
										char rcvMessage[NetworkManager::MAX_MESSAGE];
										int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
										if (size >= 0)
										{
											cont = true;
										}
									}
								}
								else
								{
									enemyHitPoints -= 3;
									bool cont = false;
									while (cont == false)
									{
										char rcvMessage[NetworkManager::MAX_MESSAGE];
										int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
										if (size >= 0)
										{
											cont = true;
										}
									}
								}
								successfulDodges = 0;
								enemyKnowsBetter = true;
								playerMoveChoice = -1;
							}
							else if (strcmp("2", rcvMessage) == 0) // Strong attack vs. free damage. (best)
							{
								if (stamina < 2)
								{
									NetworkManager::GetInstance()->SendDataTCP("Too tired to make your attack, your opponent stands up without resistance.\n\nsend any character to continue\n");
									successfulDodges++;
									bool cont = false;
									while (cont == false)
									{
										char rcvMessage[NetworkManager::MAX_MESSAGE];
										int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
										if (size >= 0)
										{
											cont = true;
										}
									}
								}
								else
								{
									NetworkManager::GetInstance()->SendDataTCP("You strike your opponent as he attempts to stand up.\nCRITICAL HIT\n\nsend any character to continue\n");
									if (bullStrength == true || ogreStrength == true)
									{
										enemyHitPoints -= 12;
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									else if (bullStrength == true && ogreStrength == true)
									{
										enemyHitPoints -= 15;
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									else
									{
										enemyHitPoints -= 9;
										bool cont = false;
										while (cont == false)
										{
											char rcvMessage[NetworkManager::MAX_MESSAGE];
											int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
											if (size >= 0)
											{
												cont = true;
											}
										}
									}
									stamina -= 2;
									successfulDodges++;
									enemyKnowsBetter = true;
								}
								playerMoveChoice = -1;
							}
							else if (strcmp("3", rcvMessage) == 0) // Parry vs. free damage.
							{
								NetworkManager::GetInstance()->SendDataTCP("Your opponent stands back up without resistance.\n\nsend any character to continue\n");
								successfulDodges++;
								bool cont = false;
								while (cont == false)
								{
									char rcvMessage[NetworkManager::MAX_MESSAGE];
									int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
									if (size >= 0)
									{
										cont = true;
									}
								}
								playerMoveChoice = -1;
							}
							else if (strcmp("4", rcvMessage) == 0) // Block vs. free damage.
							{
								NetworkManager::GetInstance()->SendDataTCP("Your opponent stands back up without resistance.\n\nsend any character to continue\n");
								successfulDodges++;
								bool cont = false;
								while (cont == false)
								{
									char rcvMessage[NetworkManager::MAX_MESSAGE];
									int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
									if (size >= 0)
									{
										cont = true;
									}
								}
								playerMoveChoice = -1;
							}
							else if (strcmp("5", rcvMessage) == 0) // Dodge vs. free damage.
							{
								NetworkManager::GetInstance()->SendDataTCP("Your opponent stands back up without resistance.\n\nsend any character to continue\n");
								successfulDodges++;
								bool cont = false;
								while (cont == false)
								{
									char rcvMessage[NetworkManager::MAX_MESSAGE];
									int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
									if (size >= 0)
									{
										cont = true;
									}
								}
								playerMoveChoice = -1;
							}
						}

						// Player HP and stamina message.
						if (stamina >= MAX_STAMINA)
						{
							char mess[200];
							sprintf_s(mess, "Hit Points Remaining: %d%s%d%s%d%s", playerHitPoints, "\nStamina Remaining: ", stamina, "\nEnemy Hit Points Remaining: ", enemyHitPoints, "\n\nsend any character to continue\n");
							NetworkManager::GetInstance()->SendDataTCP(mess);
							bool cont = false;
							while (cont == false)
							{
								char rcvMessage[NetworkManager::MAX_MESSAGE];
								int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
								if (size >= 0)
								{
									cont = true;
								}
							}
						}
						else
						{
							stamina++;
							char mess[200];
							sprintf_s(mess, "Hit Points Remaining: %d%s%d%s%d%s", playerHitPoints, "\nStamina Remaining: ", stamina, "\nEnemy Hit Points Remaining: ", enemyHitPoints, "\n\nsend any character to continue\n");
							NetworkManager::GetInstance()->SendDataTCP(mess);
							bool cont = false;
							while (cont == false)
							{
								char rcvMessage[NetworkManager::MAX_MESSAGE];
								int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
								if (size >= 0)
								{
									cont = true;
								}
							}
						}
					}
				}

				if (playerHitPoints <= 0) // Lose condition.
				{
					NetworkManager::GetInstance()->SendDataTCP("You died.\n\nsend any character to continue\n");
					bool cont = false;
					while (cont == false)
					{
						char rcvMessage[NetworkManager::MAX_MESSAGE];
						int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
						if (size >= 0)
						{
							cont = true;
						}
					}
				}

				if (enemyHitPoints <= 0) // Win condition.
				{
					NetworkManager::GetInstance()->SendDataTCP("As your opponent falls dead to the ground the crowd around you erupts into cheers and an elderly man makes his way to your position.\n\n\"For winning this tournament you have earned the covetous Golden \'D\'.\"\nThe old man gives you the D.\n\"You also earned this prize money!\"\nYou count out your earnings\n1,\n2,\n3,\n4,\n5,\n6,\n7,\n8,\n9,\n10 coins total\n\nYOU WIN\n\nsend any character to continue\n");
					bool cont = false;
					while (cont == false)
					{
						char rcvMessage[NetworkManager::MAX_MESSAGE];
						int size = NetworkManager::GetInstance()->ReceiveDataTCP(rcvMessage);
						if (size >= 0)
						{
							cont = true;
						}
					}
				}
			}
			if (size > 0)
			{
				if (choice == SERVER)
				{
					NetworkManager::GetInstance()->SendDataTCP(rcvMessage);
				}
				cout << rcvMessage << endl << endl;
			}
		}
	}

	NetworkManager::GetInstance()->Shutdown();

	return 0;
}