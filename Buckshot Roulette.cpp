#include <iostream>
#include <cstdlib> // для функций rand() и srand()
#include <ctime>   // для функции time()
#include <vector>
#include <algorithm> // для функции std::shuffle
#include <random>    // для std::default_random_engine

void playGame();

int main() {
    std::srand(std::time(0)); // инициализация генератора случайных чисел

    std::cout << "Welcome to 'Buckshot Roulette'!\n"; // Добро пожаловать в 'Buckshot Roulette'!
    std::cout << "You are playing against the host. Each of you will take turns spinning the cylinder and pulling the trigger.\n"; // Вы играете против ведущего. Вы по очереди будете вращать барабан и нажимать на спусковой крючок.

    char choice;
    do {
        playGame();

        std::cout << "Do you want to play again? (Press 'y' for yes, 'q' for quit): "; // Хотите сыграть еще раз? (Нажмите 'y' для продолжения, 'q' для выхода):
        std::cin >> choice;
        std::cin.ignore(); // очистка буфера ввода

    } while (choice == 'y');

    std::cout << "Thanks for playing 'Buckshot Roulette'!\n"; // Спасибо за игру 'Buckshot Roulette'!

    return 0;
}

void playGame() {
    int playerLives = 2; // жизни игрока в первом раунде
    int hostLives = 2; // жизни ведущего в первом раунде
    int round = 1; // текущий раунд
    int playerScore = 0; // очки игрока
    int hostScore = 0; // очки ведущего
    bool isPlayerTurn = true; // определяем, чей ход (true - игрока, false - ведущего)
    char choice;

    while (true) {
        // Определяем жизни в зависимости от раунда
        if (round == 2) {
            playerLives = 4;
            hostLives = 4;
        }

        for (int level = 1; level <= 2; ++level) { // уровни 1 и 2
            int bulletCount = (round - 1) * 2 + level * 2; // количество патронов
            if (bulletCount > 8) bulletCount = 8; // ограничение на максимальное количество патронов (8)
            int liveBulletCount = bulletCount / 2; // количество боевых патронов
            int blankBulletCount = bulletCount - liveBulletCount; // количество холостых патронов

            std::vector<int> chamber;
            // Заполняем барабан патронами
            for (int i = 0; i < liveBulletCount; ++i) {
                chamber.push_back(1); // 1 означает боевой патрон
            }
            for (int i = 0; i < blankBulletCount; ++i) {
                chamber.push_back(0); // 0 означает холостой патрон
            }
            chamber.push_back(2); // 2 означает клин патрона

            // Перемешиваем патроны в барабане
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(chamber.begin(), chamber.end(), g);

            std::cout << "Round " << round << ", Level " << level << " starts. Player lives: " << playerLives << ", Host lives: " << hostLives << "\n"; // Начинается раунд round, уровень level. Жизни игрока: playerLives, Жизни ведущего: hostLives
            std::cout << "Bullets: ";
            for (int bullet : chamber) {
                std::cout << (bullet == 1 ? "Live " : bullet == 0 ? "Blank " : "Jam ");
            }
            std::cout << "\n";

            bool roundOver = false;
            while (!roundOver) {
                if (isPlayerTurn) {
                    std::cout << "Your turn. Press 's' to spin the cylinder and pull the trigger or 'q' to quit: "; // Ваш ход. Нажмите 's' чтобы вращать барабан и нажать на спусковой крючок или 'q' для выхода:
                    std::cin >> choice;

                    if (choice == 's') {
                        int bullet = chamber.back(); // берем последний патрон
                        chamber.pop_back(); // удаляем его из барабана
                        if (bullet == 1) {
                            std::cout << "Bang! You lost a life.\n"; // Бах! Вы потеряли жизнь.
                            playerLives--;
                            hostScore++; // ведущий получает очко
                            roundOver = true; // раунд заканчивается
                        }
                        else if (bullet == 0) {
                            std::cout << "Click! It was a blank. You get another turn.\n"; // Щелчок! Это был холостой патрон. Ваш ход снова.
                            playerScore++; // игрок получает очко за успешный выстрел холостым патроном
                            if (chamber.empty()) {
                                roundOver = true; // если патроны закончились, раунд заканчивается
                            }
                        }
                        else if (bullet == 2) {
                            std::cout << "Jam! The gun jammed. You lose your turn.\n"; // Клин! Патрон застрял. Вы пропускаете ход.
                            std::shuffle(chamber.begin(), chamber.end(), g); // перемешиваем патроны снова
                            if (rand() % 3 == 0) {
                                roundOver = true; // если вероятность 33%, раунд заканчивается
                            }
                        }
                    }
                    else if (choice == 'q') {
                        std::cout << "You quit the game.\n"; // Вы вышли из игры.
                        return;
                    }
                    else {
                        std::cout << "Invalid input. Please try again.\n"; // Неверный ввод. Пожалуйста, попробуйте снова.
                    }
                }
                else {
                    std::cout << "Host's turn.\n"; // Ход ведущего.
                    int bullet = chamber.back(); // берем последний патрон
                    chamber.pop_back(); // удаляем его из барабана
                    if (bullet == 1) {
                        std::cout << "Bang! The host lost a life.\n"; // Бах! Ведущий потерял жизнь.
                        hostLives--;
                        playerScore++; // игрок получает очко
                        roundOver = true; // раунд заканчивается
                    }
                    else if (bullet == 0) {
                        std::cout << "Click! It was a blank. The host gets another turn.\n"; // Щелчок! Это был холостой патрон. Ход ведущего снова.
                        hostScore++; // ведущий получает очко за успешный выстрел холостым патроном
                        if (chamber.empty()) {
                            roundOver = true; // если патроны закончились, раунд заканчивается
                        }
                    }
                    else if (bullet == 2) {
                        std::cout << "Jam! The gun jammed. The host loses their turn.\n"; // Клин! Патрон застрял. Ведущий пропускает ход.
                        std::shuffle(chamber.begin(), chamber.end(), g); // перемешиваем патроны снова
                        if (rand() % 3 == 0) {
                            roundOver = true; // если вероятность 33%, раунд заканчивается
                        }
                    }
                }

                // Переключаем ход
                isPlayerTurn = !isPlayerTurn;
            }

            if (playerLives == 0 || hostLives == 0) {
                break; // если у кого-то закончились жизни, уровень заканчивается
            }
        }

        // Определение победителя текущего раунда
        if (playerLives == 0) {
            std::cout << "You lost all your lives. The host wins!\n"; // Вы потеряли все свои жизни. Ведущий победил!
            std::cout << "Final Score - Player: " << playerScore << ", Host: " << hostScore << "\n"; // Итоговый счет - Игрок: playerScore, Ведущий: hostScore
            break;
        }
        else if (hostLives == 0) {
            std::cout << "The host lost all their lives. You win this round!\n"; // Ведущий потерял все свои жизни. Вы выиграли этот раунд!
            round++;
            std::cout << "Starting Round " << round << ".\n"; // Начинается раунд round.
        }
    }
}
