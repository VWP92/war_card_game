// War_CardGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cards.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

int playerCounter = 0; //Counts element position in playerDeck vector, reset when deck is shuffled 
int pcCounter = 0; //Counts element position in pcDeck vector, reset when deck is shuffled
int roundNum = 1; //Tracks number of rounds done in game


int randomNum(int i)//function to generate random integer
{
	return rand() % i;
}



void war(vector<Cards> &x, vector<Cards> &y, vector<Cards> &j, vector<Cards> &k) //War method begin
{
	int loopCount = 0; //Tracks number of times while loop completed

	if (j.size() != 0) //Makes sure player deck is not already shuffled
	{
		x.insert(x.begin(), x[playerCounter]); x.erase(x.begin() + (playerCounter + 1)); //insert cards that start war to beginning of deck before shuffle
		for (int i = 0; i < j.size(); i++) //Add Cards from gainedPlayerDeck to playerDeck
		{
			x.insert(x.end(), j[i]);
		}
		j.erase(j.begin(), j.begin() + j.size()); //erase elements from gainedPlayerDeck after shuffle
		random_shuffle(x.begin() + 1, x.end(), randomNum); //shuffle all except first element(war card)
		//cout << "*Player Deck Shuffled*" << endl;
		playerCounter = 0;
	}
	
	if (k.size() != 0) //Makes sure player deck is not already shuffled
	{
		y.insert(y.begin(), y[pcCounter]); y.erase(y.begin() + (pcCounter + 1)); //insert cards that start war to beginning of deck before shuffle
		for (int i = 0; i < k.size(); i++) //Add Cards from gainedPcDeck to pcDeck
		{
			y.insert(y.end(), k[i]);
		}
		k.erase(k.begin(), k.begin() + k.size()); //erase elements from gainedPcDeck after shuffle
		random_shuffle(y.begin() + 1, y.end(), randomNum); //shuffle all except first element(war card)
		//cout << "*PC Deck Shuffled*" << endl;
		pcCounter = 0;
	}
	
	while (x[playerCounter].CardValues.cardVal == y[pcCounter].CardValues.cardVal)
	{
		loopCount++; //increment each time loop runs
		int playerDeckSize = x.size(); //Holds size() of vector as signed integer since size() unsigned
		int pcDeckSize = y.size(); //Holds size() of vector as signed integer since size() unsigned
		if (playerDeckSize - 4 * loopCount < 0)
		{
			cout << endl << "****Player has lost the game!****";
			cin.get();
			cin.get();
			exit(0);
		}
		else if (pcDeckSize - 4 * loopCount < 0)
		{
			cout << endl << "****PC has lost the game!****";
			cin.get();
			cin.get();
			exit(0);
		}
		///*DEBUG*/cout << "DEBUG: " << playerDeckSize - 4 * loopCount << " " << pcDeckSize - 4 * loopCount << " loopCount = " << loopCount << endl; //Show Results of previous if else arguments

		if (loopCount < 2) //Soo counters increment to 4th position ([3]) from the [0] they we initialized to a few lines back, on first loop
		{
			playerCounter += 3;
			pcCounter += 3;
		}
		else
		{
			playerCounter += 4;
			pcCounter += 4;
		}
		cout << "Player draws 3 Cards + " << x[playerCounter].CardValues.cardnum << " of " << x[playerCounter].CardValues.cardType << endl;
		cout << "PC Draws 3 Cards + " << y[pcCounter].CardValues.cardnum << " of " << y[pcCounter].CardValues.cardType << endl;
		
		if (x[playerCounter].CardValues.cardVal < y[pcCounter].CardValues.cardVal) //If PC Wins WAR
		{
			cout << "***PC Wins WAR!***" << endl << endl;
			for (int i = 0; i < 4 * loopCount; i++)
			{
				k.insert(k.end(), x[playerCounter - i]);
				cout << "(" << k.back().CardValues.cardnum << " of " << k.back().CardValues.cardType << " was gained by PC.)" << endl; //Show card that was inserted into gainedPCDeck
			}
			x.erase(x.begin(), x.begin() + (4 * loopCount)); //Removes Cards player lost from deck.
			playerCounter -= 4 * loopCount; //compensate for element lost in vector due to losing a cards.
			break;
		}
		else if (x[playerCounter].CardValues.cardVal > y[pcCounter].CardValues.cardVal) //If Player Wins WAR
		{
			cout << "***Player Wins WAR!***" << endl << endl;
			for (int i = 0; i < 4 * loopCount; i++)
			{
				j.insert(j.end(), y[playerCounter - i]);
				cout << "(" << j.back().CardValues.cardnum << " of " << j.back().CardValues.cardType << " was gained by Player.)" << endl; //Show card that was inserted into gainedPCDeck
			}
			y.erase(y.begin(), y.begin() + (4 * loopCount)); //Removes Cards pc lost from deck.
			pcCounter -= 4 * loopCount; //compensate for element lost in vector due to losing a cards.
			break;
		}
	}
} // War method end



void gameplay(vector<Cards> &x, vector<Cards> &y, vector<Cards> &j, vector<Cards> &k) //main gameflow begin
{
	///*DEBUG*/cout << "DEBUG: " << playerCounter << "-" << x.size() << "/" << pcCounter << "-" << y.size() << endl;
	cout << "**Round #" << roundNum << "**" << endl;
	cout << "Player Cards " << x.size() + j.size() << "/" << y.size() + k.size() << " PC Cards" << endl << endl;

	if (playerCounter >= x.size()) //If reached end of initial playerDeck
	{
		for (int i = 0; i < j.size(); i++) //Add Cards from gainedPlayerDeck to playerDeck
		{
			x.insert(x.end(), j[i]);
		}
		j.erase(j.begin(), j.begin() + j.size()); //erase elements from gainedPlayerDeck after shuffle
		random_shuffle(x.begin(), x.end(), randomNum);
		cout << "*Player Deck Shuffled*" << endl;
		playerCounter = 0;
		///*DEBUG*/cout << "DEBUG: " << playerCounter << "-" << x.size() << "/" << pcCounter << "-" << y.size() << endl;
	}
	if (pcCounter >= y.size()) //If reached end of initial pcDeck
	{
		for (int i = 0; i < k.size(); i++) //Add Cards from gainedPcDeck to pcDeck
		{
			y.insert(y.end(), k[i]);
		}
		k.erase(k.begin(), k.begin() + k.size()); //erase elements from gainedPcDeck after shuffle
		random_shuffle(y.begin(), y.end(), randomNum);
		cout << "*PC Deck Shuffled*" << endl;
		pcCounter = 0;
		///*DEBUG*/cout << "DEBUG: " << playerCounter << "-" << x.size() << "/" << pcCounter << "-" << y.size() << endl;
	}

	cout << "Player draws " << x[playerCounter].CardValues.cardnum << " of " << x[playerCounter].CardValues.cardType << endl;
	cout << "PC draws " << y[pcCounter].CardValues.cardnum << " of " << y[pcCounter].CardValues.cardType << endl << endl;
	if (x[playerCounter].CardValues.cardVal < y[pcCounter].CardValues.cardVal)
	{
		cout << "***PC Wins!***" << endl;
		k.insert(k.end(), x[playerCounter]);
		cout << "(" << k.back().CardValues.cardnum << " of " << k.back().CardValues.cardType << " was gained by PC.)" << endl; //Show card that was inserted into gainedPCDeck
		x.erase(x.begin() + playerCounter); //Removes Card player lost from deck.
		pcCounter++;
		//playerCounter stays to compensate for element lost in vector due to losing a card.
		///*DEBUG*/cout << "DEBUG: " << playerCounter << "-" << x.size() << "/" << pcCounter << "-" << y.size() << endl;

	}
	else if (x[playerCounter].CardValues.cardVal > y[pcCounter].CardValues.cardVal)
	{
		cout << "***Player Wins!***" << endl;
		j.insert(j.end(), y[pcCounter]);
		cout << "(" << j.back().CardValues.cardnum << " of " << j.back().CardValues.cardType << " was gained by Player.)" << endl; //Show card that was inerted into gainedPlayerDeck
		y.erase(y.begin() + pcCounter); //Removes Card PC lost from deck.
		playerCounter++;
		//pcCounter stays to compensate for element lost in vector due to losing a card.
		///*DEBUG*/cout << "DEBUG: " << playerCounter << "-" << x.size() << "/" << pcCounter << "-" << y.size() << endl;
	}
	else
	{
		///*DEBUG*/cout << "DEBUG: " << playerCounter << "-" << x.size() << "/" << pcCounter << "-" << y.size() << endl;
		cout << "***WAR!***" << endl;
		war(x,y,j,k);
		///*DEBUG*/cout << "DEBUG: " << playerCounter << "-" << x.size() << "/" << pcCounter << "-" << y.size() << endl;
	}
	roundNum++;
} //main gameflow end



int main()
{
	srand(unsigned(time(0)));
	string choices;
	char choice = 'y'; //variable that is checked to play and continue game, uses first character of choices
	string answer = "b";
	int deckChoice; //variable to use for deck choice
	int deckElement; //variable to use for deck element
	
	cardObj.createdCards();

	//array made of Cards Objects
	vector<Cards> deck = { Card0, Card1, Card2, Card3, Card4, Card5, Card6, Card7, Card8, Card9,
		Card10, Card11, Card12, Card13, Card14, Card15, Card16, Card17, Card18, Card19, Card20,
		Card21, Card22, Card23, Card24, Card25, Card26, Card27, Card28, Card29, Card30, Card31,
		Card32, Card33, Card34, Card35, Card36, Card37, Card38, Card39, Card40, Card41, Card42,
		Card43, Card44, Card45, Card46, Card47, Card48, Card49, Card50, Card51 };
	vector<Cards> playerDeck;
	vector<Cards> pcDeck;
	vector<Cards> gainedPlayerDeck;
	vector<Cards> gainedPCDeck;

	random_shuffle(deck.begin(), deck.end(), randomNum); //shuffles deck vector

	while (true) //Shuffle and distribute cards to players decks
	{
		for (int i = 0; i < 26; i++) //deals cards to playerDeck
		{
			playerDeck.insert(playerDeck.end(), deck[i]);
		}
		deck.erase(deck.begin(), deck.begin() + 26); //delete elements given to playerDeck

		for (int i = 0; i < 26; i++) //deals cards to pcDeck
		{
			pcDeck.insert(pcDeck.end(), deck[i]);
		}
		deck.erase(deck.begin(), deck.begin() + 26); //delete elements given to pcDeck
		break;
	}


	while (true) //Game!
	{
		cout << "WAR CARD GAME" << endl; //Begin game
		cout << "Ready to play? (y/n): ";
		cin >> choices;
		choice = choices.at(0);
		while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') //trap wrong input
		{
			cout << "Please enter a y or n: ";
			cin >> choices;
			choice = choices.at(0);
		}
		cout << endl;

		while (choice == 'y' || choice == 'Y' || choice == 'a' || choice == 'A') //Gameplay Loop begin
		{
			gameplay(playerDeck, pcDeck, gainedPlayerDeck, gainedPCDeck);
			if (playerDeck.size() + gainedPlayerDeck.size() <= 0) //If player loses game
			{
				cout << endl << "****Player has lost the game!****";
				cin.get();
				cin.get();
				break;
			}
			else if (pcDeck.size() + gainedPCDeck.size() <= 0) //If PC loses game
			{
				cout << endl << "****PC has lost the game!****";
				cin.get();
				cin.get();
				break;
			}
			if (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N')
			{
				cout << "Play Again? (y/n or A): "; //'A' is for AUTOPLAY
				cin >> choices;
				choice = choices.at(0);
				while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N' && choice != 'a' && choice != 'A') //trap wrong input
				{
					cout << "Please enter a y, n or A: ";
					cin >> choices;
					choice = choices.at(0);
				}
			}
			cout << endl;
		} //Gameplay Loop end
		break;
	}
	return 0;
}
