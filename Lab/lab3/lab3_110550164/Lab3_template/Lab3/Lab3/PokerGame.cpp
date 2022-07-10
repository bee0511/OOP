#include "PokerGame.h"

PokerGame::PokerGame() {
	//TO_DO: initial constructor
}

void PokerGame::distribute(bool usedCards[52]) {
	//TO_DO: Random generate five cards to player
	//Hint: Use usedCards to record which card have been distributed
	srand(time(NULL));
	int random;
	for (int i = 0; i < 5; i++) {
		random = rand() % 51;	//generate random number between 0 to 51.
		while (usedCards[random] == true) {	//If the card has been distributed.
			random = rand() % 51;	//generate new random number until the card has not been used.
		}
		usedCards[random] = true;
		playerCards.push_back(random);
	}
}

void PokerGame::set(vector<int> cards) {
	//TO_DO: Set the cards to player
	for (int i = 0; i < 5; i++) {
		playerCards.push_back(cards[i]);
	}
}

void PokerGame::printCards() {
	int shape, number;
	cout << "Player cards:" << endl;
	for (int i = 0; i < 5; i++) {
		//TO_DO: Print the player's cards.
		// For example: "C1" "S2" "H3" ...
		shape = playerCards[i] / 13;
		number = playerCards[i] % 13 + 1;
		switch (shape) {
		case 0:
			cout << "C";
			break;
		case 1:
			cout << "D";
			break;
		case 2:
			cout << "H";
			break;
		case 3:
			cout << "S";
			break;
		default:
			break;
		}
		cout << number << "\t";
	}

	cout << endl;
}

void PokerGame::sortCards() {
	//TO_DO: Sort the cards accroding to their number
	int temp;
	for (int i = 0; i < 5; i++) {	//bubble sort.
		for (int j = i + 1; j < 5; j++) {
			if (playerCards[i] % 13 > playerCards[j] % 13) {	//different number.
				temp = playerCards[i];
				playerCards[i] = playerCards[j];
				playerCards[j] = temp;
			}
			else if (playerCards[i] % 13 == playerCards[j] % 13 && playerCards[i] / 13 > playerCards[j] / 13) {	//same number, different shape.
				temp = playerCards[i];
				playerCards[i] = playerCards[j];
				playerCards[j] = temp;
			}
		}
	}
}

void PokerGame::evaluate() {
	sortCards();
	if (this->isStraight() && this->isFlush()) {
		type = StraightFlush;
	}
	else if (this->isFourOfKind()) {
		type = FourOfKind;
	}
	else if (this->isFullHouse()) {
		type = FullHouse;
	}
	else if (this->isFlush()) {
		type = Flush;
	}
	else if (this->isStraight()) {
		type = Straight;
	}
	else if (this->isThreeOfKind()) {
		type = ThreeOfKind;
	}
	else if (this->isTwoPairs()) {
		type = TwoPairs;
	}
	else if (this->isOnePair()) {
		type = OnePair;
	}
	else {
		type = HighCard;
		//TO_DO: Set the maxNumber
		maxNumber = -1;
		for (int i = 0; i < 5; i++) {
			if (playerCards[i] > maxNumber)
				maxNumber = playerCards[i];
		}
	}
}

int PokerGame::getType() {
	return type;
}

int PokerGame::getMaxNumber() {
	return maxNumber;
}

void PokerGame::compare(int type_, int maxNumber_) {
	//TO_DO: Compare the type and output who is winner
	//Compare the type of card first. If types are the same, compare which is max the number of card.
	//If the max number is the same, compare the suit of card.
	if (type > type_) {
		cout << "Player1 win" << endl;
	}
	else if (type < type_) {
		cout << "Player2 win" << endl;
	}
	else {
		if (maxNumber % 13 > maxNumber_ % 13) {
			cout << "Player1 win" << endl;
		}
		else if (maxNumber % 13 < maxNumber_ % 13) {
			cout << "Player2 win" << endl;
		}
		else {
			if (maxNumber / 13 > maxNumber_ / 13) {
				cout << "Player1 win" << endl;
			}
			else if (maxNumber / 13 < maxNumber_ / 13) {
				cout << "Player2 win" << endl;
			}
		}
	}
}

bool PokerGame::isStraight() {
	//TO_DO: Check whether the hand of cards is Straight or not and set the maxNumber
	if ((playerCards[0] + 1) % 13 == (playerCards[1]) % 13
		&& (playerCards[1] + 1) % 13 == (playerCards[2]) % 13
		&& (playerCards[2] + 1) % 13 == (playerCards[3]) % 13
		&& (playerCards[3] + 1) % 13 == (playerCards[4]) % 13) {
		maxNumber = playerCards[4];
		return true;
	}
	return false;
}

bool PokerGame::isFlush() {
	//TO_DO: Check whether the hand of cards is Flush or not and set the maxNumber
	int FlushType = playerCards[0] / 13;
	for (int i = 1; i < 5; i++) {
		if (playerCards[i] / 13 != FlushType) {
			return false;
		}
	}
	maxNumber = playerCards[4];
	return true;
}

bool PokerGame::isFourOfKind() {
	//TO_DO: Check whether the hand of cards is FourOfaKind or not and set the maxNumber
	if (playerCards[0] % 13 == playerCards[1] % 13
		&& playerCards[1] % 13 == playerCards[2] % 13
		&& playerCards[2] % 13 == playerCards[3] % 13) {
		maxNumber = playerCards[3];
		return true;
	}
	else if(playerCards[1] % 13 == playerCards[2] % 13
		&& playerCards[2] % 13 == playerCards[3] % 13
		&& playerCards[3] % 13 == playerCards[4] % 13) {
		maxNumber = playerCards[4];
		return true;
	}
	return false;
}

bool PokerGame::isFullHouse() {
	//TO_DO: Check whether the hand of cards is FullHouse or not and set the maxNumber
	if (playerCards[0] % 13 == playerCards[1] % 13
		&& playerCards[1] % 13 == playerCards[2] % 13
		&& playerCards[3] % 13 == playerCards[4] % 13) {
		maxNumber = playerCards[2];
		return true;
	}
		
	else if (playerCards[0] % 13 == playerCards[1] % 13
		&& playerCards[2] % 13 == playerCards[3] % 13
		&& playerCards[3] % 13 == playerCards[4] % 13) {
		maxNumber = playerCards[4];
		return true;
	}
	return false;
}

bool PokerGame::isThreeOfKind() {
	//TO_DO: Check whether the hand of cards is ThreeOfaKind or not and set the maxNumber
	for (int i = 0; i < 3; i++) {
		if (playerCards[i] % 13 == playerCards[i + 1] % 13
			&& playerCards[i + 1] % 13 == playerCards[i + 2] % 13) {
			maxNumber = playerCards[i + 2];
			return true;
		}
	}
	return false;
}

bool PokerGame::isTwoPairs() {
	//TO_DO: Check whether the hand of cards is TwoPairs or not and set the maxNumber
	int pair = 0;
	for (int i = 0; i < 4; i++) {
		if (playerCards[i] % 13 == playerCards[i + 1] % 13) {
			pair++;
		}
		if (pair == 2) {
			maxNumber = playerCards[i + 1];
			return true;
		}
	}
	return false;
}

bool PokerGame::isOnePair() {
	//TO_DO: Check whether the hand of cards is OnePair or not and set the maxNumber
	int pair = 0;
	for (int i = 0; i < 4; i++) {
		if (playerCards[i] % 13== playerCards[i + 1] % 13) {
			pair++;
		}
		if (pair == 1) {
			maxNumber = playerCards[i + 1];
			return true;
		}
	}
	return false;
}