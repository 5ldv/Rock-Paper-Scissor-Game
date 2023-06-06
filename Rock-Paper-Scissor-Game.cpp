#include <iostream>
#include <cstdlib>
using namespace std;
enum enGameChoice { Stone = 1, Paper = 2, Scissor = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };
struct stGameResults {
	short gameRounds = 0;
	short player1WinTimes = 0;
	short computerWinTimes = 0;
	short drawTimes = 0;
	enWinner gameWinner;
	string winnerName = "";
};
struct stRoundInfo {
	short roundNumber = 0;
	enGameChoice player1Choice;
	enGameChoice computerChoice;
	enWinner winner;
	string winnerName; // why?
};
int randomNumber(int from, int to) {
	int number = rand() % (to - from + 1) + from;
	return number;
}
short readHowManyRounds() {
	short gameRounds = 1;
	do {
		cout << "Enter How Many Rounds You Want To Play [1/10]:\n";
		cin >> gameRounds;
	} while (gameRounds < 1 || gameRounds > 10);
	return gameRounds;
}
string winnerName(enWinner winner) {
	string arrWinnerName[3] = { "Player1","Computer","No Winner" };
	return arrWinnerName[winner - 1];
}
string choiceName(enGameChoice choice) {
	string arrGameChoice[3] = { "Stone", "Paper", "Scissor" };
	return arrGameChoice[choice - 1];
}
void setWinnerScreenColor(enWinner winner) {
	switch (winner) {

	case enWinner::Player1:
		system("color 2F"); //turn screen to Green
		break;
	case enWinner::Computer:
		system("color 4F"); //turn screen to Red
		cout << "\a";
		break;

	default:
		system("color 6F"); //turn screen to Yellowbreak
		break;
	}
}
enWinner whoWonTheRound(stRoundInfo roundInfo) {
	if (roundInfo.player1Choice == roundInfo.computerChoice) {
		return enWinner::Draw;
	}
	switch (roundInfo.player1Choice) {
	case enGameChoice::Stone:
		if (roundInfo.computerChoice == enGameChoice::Paper) {
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Paper:
		if (roundInfo.computerChoice == enGameChoice::Scissor) {
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Scissor:
		if (roundInfo.computerChoice == enGameChoice::Stone) {
			return enWinner::Computer;
		}
		break;
	}
	// if you reach here then Player1 is the Winner.
	return enWinner::Player1;
}
enWinner whoWonTheGame(short playerW1onTimes, short computerWonTimes) {
	if (playerW1onTimes > computerWonTimes)
		return enWinner::Player1;
	else if (playerW1onTimes < computerWonTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}
stGameResults fillGameResults(short gameRounds, short player1WinTimes, short computerWinTimes, short drawTimes) {
	stGameResults gameResults;

	gameResults.gameRounds == gameRounds;
	gameResults.player1WinTimes = player1WinTimes;
	gameResults.computerWinTimes = computerWinTimes;
	gameResults.drawTimes = drawTimes;
	gameResults.gameWinner = whoWonTheGame(player1WinTimes, computerWinTimes);
	gameResults.winnerName = winnerName(gameResults.gameWinner);

	return gameResults;
}
enGameChoice readPlayer1Choice() {
	short choice = 1;
	do {
		cout << "\nYour Choice: [1]Stone, [2]Paper, [3]Scissor: ";
		cin >> choice;
	} while (choice < 1 || choice > 3);

	return (enGameChoice)choice;
}
enGameChoice getComputerChoice() {
	return (enGameChoice)randomNumber(1, 3);
}
string tabs(short numberOfTabs) {
	string t = "";

	for (int i = 1; i < numberOfTabs; i++) {
		t = t + "\t";
		cout << t;
	}
	return t;
}
void showGameOverScreen() {

	cout << tabs(2) << "__________________________________________________________\n\n";
	cout << tabs(2) << "                 +++ G a m e  O v e r +++\n";
	cout << tabs(2) << "__________________________________________________________\n\n";

}
void showFinalGameResults(stGameResults gameResults) {
	cout << tabs(2) << "_____________________ [Game Results ]_____________________\n\n";
	cout << tabs(2) << "Game Rounds        : " << gameResults.gameRounds << endl;
	cout << tabs(2) << "Player1 won times  : " << gameResults.player1WinTimes << endl;
	cout << tabs(2) << "Computer won times : " << gameResults.computerWinTimes << endl;
	cout << tabs(2) << "Draw times         : " << gameResults.drawTimes << endl;
	cout << tabs(2) << "Final Winner       : " << gameResults.winnerName << endl;
	cout << tabs(2) << "___________________________________________________________\n";

	setWinnerScreenColor(gameResults.gameWinner);
}
void printRoundResults(stRoundInfo roundInfo) {

	cout << "\n____________Round [" << roundInfo.roundNumber << "] ____________\n\n";
	cout << "Player1  Choice: " << choiceName(roundInfo.player1Choice) << endl;
	cout << "Computer Choice: " << choiceName(roundInfo.computerChoice) << endl;
	cout << "Round Winner   : [" << roundInfo.winnerName << "] \n";
	cout << "__________________________________\n" << endl;
}
stGameResults playGame(short howManyRounds) {

	stRoundInfo roundInfo;
	short player1WinTimes = 0, computerWinTimes = 0, drawTimes = 0;

	for (short gameRound = 1; gameRound <= howManyRounds; gameRound++)
	{
		cout << "\nRounds [" << gameRound << "] begins:\n";
		roundInfo.roundNumber = gameRound;
		roundInfo.player1Choice = readPlayer1Choice();
		roundInfo.computerChoice = getComputerChoice();
		roundInfo.winner = whoWonTheRound(roundInfo);
		roundInfo.winnerName = winnerName(roundInfo.winner);

		if (roundInfo.winner == enWinner::Player1)
			player1WinTimes++;
		else if (roundInfo.winner == enWinner::Computer)
			computerWinTimes++;
		else
			drawTimes++;

		printRoundResults(roundInfo);
	}
	return fillGameResults(howManyRounds, player1WinTimes, computerWinTimes, drawTimes);
}
void resetScreen() {
	system("CLS");
	system("color 0F");
}
void startGame() {
	char playAgain = 'Y';
	do {
		resetScreen();
		stGameResults gameResults = playGame(readHowManyRounds());
		showGameOverScreen();
		showFinalGameResults(gameResults);

		cout << endl << tabs(3) << "Do You Want To Play Again [Y/N]?";
		cin >> playAgain;

	} while (playAgain == 'Y' || playAgain == 'y');
}

int main() {
	srand((unsigned)time(NULL));

	startGame();
	return 0;
}
