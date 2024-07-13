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

// Функция для получения случайной фразы из списка
std::string getRandomPhrase(const std::vector<std::string>& phrases) {
    int index = std::rand() % phrases.size();
    return phrases[index];
}

void playGame() {
    int playerLives = 2; // жизни игрока в первом раунде
    int hostLives = 2; // жизни ведущего в первом раунде
    int round = 1; // текущий раунд
    int playerScore = 0; // очки игрока
    int hostScore = 0; // очки ведущего
    bool isPlayerTurn = true; // определяем, чей ход (true - игрока, false - ведущего)
    char choice;

    // Фразы для разных событий
    std::vector<std::string> survivePhrases = {
        "You survived, it's funny.", // Вы выжили, это смешно.
        "Lucky you, still alive!", // Везет вам, вы еще живы!
        "Click! No bullet this time.", // Щелчок! Патронов нет.
        "You're safe... for now." // Вы в безопасности... пока что.
    };

    std::vector<std::string> bangPhrases = {
        "Bang! That must've hurt, right?", // Выстрел! Это должно быть больно, не так ведь?
        "Boom! You lost a life.", // Бах! Вы потеряли жизнь.
        "Boom! One life less.", // Бум! Одной жизнью меньше.
        "Oh no, you got hit!" // О нет, вы получили удар!
    };

    std::vector<std::string> hostSurvivePhrases = {
        "The host got lucky, but will they be lucky again?", // Ведущему повезло, но повезет ли еще раз?
        "Click! The host is still alive.", // Щелчок! Ведущий все еще жив.
        "The host got lucky this time.", // Ведущему повезло в этот раз.
        "The host is safe... for now." // Ведущий в безопасности... пока что.
    };

    std::vector<std::string> hostBangPhrases = {
        "The host got the worst luck, must've hurt, right?", // Ведущему повезло меньше всех, должно быть больно, да?
        "Bang! The host lost a life.", // Бах! Ведущий потерял жизнь.
        "Boom! The host lost one life.", // Бум! Ведущий потерял одну жизнь.
        "Oh no, the host got hit!" // О нет, ведущий получил удар!
    };

    std::vector<std::string> jamPhrases = {
        "It's a pity that the gun jammed, it would have been a show.", // Жаль что пистолет заклинило, было бы зрелище.
        "Oops! The gun jammed.", // Упс! Пистолет заклинило.
        "The gun jammed. Better luck next time.", // Пистолет застрял. В следующий раз повезет.
        "No shot this time, gun jammed." // В этот раз не выстрелил, пистолет заклинило.
    };

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
                            std::cout << getRandomPhrase(bangPhrases) << "\n"; // случайная фраза при выстреле боевым патроном
                            playerLives--;
                            hostScore++; // ведущий получает очко
                            roundOver = true; // раунд заканчивается
                        }
                        else if (bullet == 0) {
                            std::cout << getRandomPhrase(survivePhrases) << "\n"; // случайная фраза при выстреле холостым патроном
                            playerScore++; // игрок получает очко за успешный выстрел холостым патроном
                            if (chamber.empty()) {
                                roundOver = true; // если патроны закончились, раунд заканчивается
                            }
                        }
                        else if (bullet == 2) {
                            std::cout << getRandomPhrase(jamPhrases) << "\n"; // случайная фраза при клине патрона
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
                        std::cout << getRandomPhrase(hostBangPhrases) << "\n"; // случайная фраза при выстреле боевым патроном ведущим
                        hostLives--;
                        playerScore++; // игрок получает очко
                        roundOver = true; // раунд заканчивается
                    }
                    else if (bullet == 0) {
                        std::cout << getRandomPhrase(hostSurvivePhrases) << "\n"; // случайная фраза при выстреле холостым патроном ведущим
                        hostScore++; // ведущий получает очко за успешный выстрел холостым патроном
                        if (chamber.empty()) {
                            roundOver = true; // если патроны закончились, раунд заканчивается
                        }
                    }
                    else if (bullet == 2) {
                        std::cout << getRandomPhrase(jamPhrases) << "\n"; // случайная фраза при клине патрона
                        std::shuffle(chamber.begin(), chamber.end(), g); // перемешиваем патроны снова
                        if (rand() % 3 == 0) {
                            roundOver = true; // если вероятность 33%, раунд заканчивается
                        }
                    }
                }
                isPlayerTurn = !isPlayerTurn; // смена хода
            }

            std::cout << "End of Level " << level << ". Player lives: " << playerLives << ", Host lives: " << hostLives << "\n"; // Конец уровня level. Жизни игрока: playerLives, Жизни ведущего: hostLives

            if (playerLives <= 0) {
                std::cout << "You lost all your lives. Game over.\n"; // Вы потеряли все свои жизни. Игра окончена.
                return;
            }
            else if (hostLives <= 0) {
                std::cout << "The host lost all their lives. You move to the next round.\n"; // Ведущий потерял все свои жизни. Вы переходите в следующий раунд.
                round++;
                break;
            }
        }
    }
}
