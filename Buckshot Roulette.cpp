#include <iostream>
#include <cstdlib> // для функций rand() и srand()
#include <ctime>   // для функции time()

void playGame();

int main() {
    std::srand(std::time(0)); // инициализация генератора случайных чисел

    std::cout << "Welcome to 'Buckshot Roulette'!\n";
    std::cout << "You are playing against the host. Each of you will take turns spinning the cylinder and pulling the trigger.\n";

    char choice;
    do {
        playGame();

        std::cout << "Do you want to play again? (Press 'y' for yes, 'q' for quit): ";
        std::cin >> choice;
        std::cin.ignore(); // очистка буфера ввода

    } while (choice == 'y');

    std::cout << "Thanks for playing 'Buckshot Roulette'!\n";

    return 0;
}

void playGame() {
    int chamberCount = 6; // количество камер в револьвере
    int bulletPosition = std::rand() % chamberCount; // случайная позиция пули
    int playerPosition = 0; // текущая позиция
    char choice;
    bool isGameOver = false;
    bool isPlayerTurn = true; // определяем, чей ход (true - игрока, false - ведущего)

    while (!isGameOver) {
        if (isPlayerTurn) {
            std::cout << "Your turn. Press 's' to spin the cylinder and pull the trigger or 'q' to quit: ";
            std::cin >> choice;

            if (choice == 's') {
                playerPosition = std::rand() % chamberCount; // прокрутка барабана
                if (playerPosition == bulletPosition) {
                    std::cout << "Bang! You lost.\n";
                    isGameOver = true;
                }
                else {
                    std::cout << "Click! You're still alive. Now it's the host's turn.\n";
                    isPlayerTurn = false;
                }
            }
            else if (choice == 'q') {
                std::cout << "You quit the game.\n";
                isGameOver = true;
            }
            else {
                std::cout << "Invalid input. Please try again.\n";
            }
        }
        else {
            std::cout << "Host's turn.\n";
            playerPosition = std::rand() % chamberCount; // прокрутка барабана ведущим
            if (playerPosition == bulletPosition) {
                std::cout << "Bang! The host lost. You win!\n";
                isGameOver = true;
            }
            else {
                std::cout << "Click! The host is still alive. Now it's your turn.\n";
                isPlayerTurn = true;
            }
        }
    }
}
