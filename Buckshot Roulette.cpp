#include <iostream>
#include <cstdlib> // для функций rand() и srand()
#include <ctime>   // для функции time()
#include <vector>
#include <algorithm> // для std::shuffle
#include <random>    // для std::default_random_engine

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
    int playerLives = 2; // жизни игрока
    int hostLives = 2; // жизни ведущего
    int round = 1; // текущий раунд
    bool isPlayerTurn = true; // определяем, чей ход (true - игрока, false - ведущего)
    char choice;

    while (playerLives > 0 && hostLives > 0) {
        std::vector<int> chamber;
        int bulletCount = (round == 1) ? 2 : 3; // количество патронов (2 в первом раунде, 3 во втором)
        int liveBulletCount = 1; // количество боевых патронов (1 в каждом раунде)
        int blankBulletCount = bulletCount - liveBulletCount; // количество холостых патронов

        // Заполняем барабан патронами
        for (int i = 0; i < liveBulletCount; ++i) {
            chamber.push_back(1); // 1 означает боевой патрон
        }
        for (int i = 0; i < blankBulletCount; ++i) {
            chamber.push_back(0); // 0 означает холостой патрон
        }

        // Перемешиваем патроны в барабане
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(chamber.begin(), chamber.end(), g);

        std::cout << "Round " << round << " starts. Player lives: " << playerLives << ", Host lives: " << hostLives << "\n";

        bool roundOver = false;
        while (!roundOver) {
            if (isPlayerTurn) {
                std::cout << "Your turn. Press 's' to spin the cylinder and pull the trigger or 'q' to quit: ";
                std::cin >> choice;

                if (choice == 's') {
                    int bullet = chamber.back(); // берем последний патрон
                    chamber.pop_back(); // удаляем его из барабана
                    if (bullet == 1) {
                        std::cout << "Bang! You lost a life.\n";
                        playerLives--;
                        roundOver = true; // раунд заканчивается
                    }
                    else {
                        std::cout << "Click! It was a blank. You get another turn.\n";
                        if (chamber.empty()) {
                            roundOver = true; // если патроны закончились, раунд заканчивается
                        }
                    }
                }
                else if (choice == 'q') {
                    std::cout << "You quit the game.\n";
                    return;
                }
                else {
                    std::cout << "Invalid input. Please try again.\n";
                }
            }
            else {
                std::cout << "Host's turn.\n";
                int bullet = chamber.back(); // берем последний патрон
                chamber.pop_back(); // удаляем его из барабана
                if (bullet == 1) {
                    std::cout << "Bang! The host lost a life.\n";
                    hostLives--;
                    roundOver = true; // раунд заканчивается
                }
                else {
                    std::cout << "Click! It was a blank. The host gets another turn.\n";
                    if (chamber.empty()) {
                        roundOver = true; // если патроны закончились, раунд заканчивается
                    }
                }
            }

            // Переключаем ход
            isPlayerTurn = !isPlayerTurn;
        }

        // Переход к следующему раунду
        round++;
    }

    // Определение победителя
    if (playerLives == 0) {
        std::cout << "You lost all your lives. The host wins!\n";
    }
    else if (hostLives == 0) {
        std::cout << "The host lost all their lives. You win!\n";
    }
}
