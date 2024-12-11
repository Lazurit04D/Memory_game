#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <windows.h> //Для функции Sleep()
#include <iostream>
using namespace std;

//Символы вынесены чтобы быть доступными для всей программы
int charsVariant = 1;
char chars[8] = { '!', '@', '#', '$', '%', '^', '&', '*' };
const char chars1[8] = { '!', '@', '#', '$', '%', '^', '&', '*' };
const char chars2[8] = { '1', '2', '3', '4', '5', '6', '7', '8' };
const char chars3[8] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
int countOfGuessed = 0;

//Количество ходов
int constCountOfTurns = 48;
int countOfTurns = 48;

//Функция сравнения игровых полей
int GameFieldCMP(const char gameField[][4], const char secondField[][4])
{
    int countOfMatches = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (gameField[i][j] == secondField[i][j])
            {
                countOfMatches++;
            }
        }
    }
    return countOfMatches;
}

//Заполнение игрового поля
void InitGameField(char gameField[][4], int mode, const char secondField[][4] = nullptr)
{
    int randInt = 0;
    int countOfAnyChar[8]; //Эта переменная хранит в себе количество каждого символа в игровом поле
    //Этим условием выполнена небольшая оптимизация, так как эта переменная не используется когда заполняется игровое поле игрока
    if (mode == 2)
    {
        for (int i = 0; i < 8; i++)
        {
            countOfAnyChar[i] = 0;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (mode == 2)
            {
                //Этот цикл не даёт повторяться одному символу больше 2 раз
                while (true)
                {
                    randInt = rand() % 8;
                    if (countOfAnyChar[randInt] < 2)
                    {
                        break;
                    }
                }

                gameField[i][j] = chars[randInt];
                countOfAnyChar[randInt]++;
            }
            else if (mode == 1)
            {
                //Копирование одного поле в другое
                gameField[i][j] = secondField[i][j];
            }
            else
            {
                //Заполнение пустого игрового поля игрока
                gameField[i][j] = '?';
            }
        }
    }
}

//Вывод игрового поля в консоль
void PrintGameField(const char gameField[][4], int X = -1, int Y = -1)
{
    cout << "---ИГРА ПАМЯТЬ---";
    cout << "\n--Игра--\n";
    cout << "\nКоличество угаданных пар: " << countOfGuessed;
    cout << "\nКоличество оставшихся ходов: " << countOfTurns << endl << endl;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (i == 0)
            {
                cout << "[" << j << "] ";
            }
            else
            {
                if (j == 0)
                {
                    cout << "[" << i << "] ";
                }
                else
                {
                    if (gameField[i - 1][j - 1] == '?')
                    {
                        cout << "|" << gameField[i - 1][j - 1] << "| ";
                    }
                    else
                    {
                        //Тернарный оператор определяет, какая ячейка была выбрана последней, для того, чтобы её выделить
                        cout << (X + 1 == j && Y + 1 == i ? ">" : "[") << gameField[i - 1][j - 1] << (X + 1 == j && Y + 1 == i ? "< " : "] ");
                    }
                }
            }
        }

        cout << endl << endl;
    }
}

void OpenCell(const char gameField[][4], char userGameField[][4], int previosX = -1, int previosY = -1)
{
    if (countOfTurns > 0)
    {
        int X, Y, user;
        char tempGameField[4][4] = {};
        InitGameField(tempGameField, 1, userGameField);
        //Создание временного игрового поля и копирование в него уже существующего

        //Ввод координат ячейки
        PrintGameField(userGameField);
        cout << "(Для использования спец. способностей введите координаты [X = 0, Y = 0])\n";
        cout << "\nВведите координату «X» у вашей ячейки\n(1-4, включительно): ";
        cin >> X;
        cout << "Введите координату «Y» у вашей ячейки\n(1-4, включительно): ";
        cin >> Y;

        if (X == 0 && Y == 0)
        {
            int X1 = 0, Y1 = 0, X2 = 1, Y2 = 0;
            char neededChar = '?';

            system("cls");
            cout << "---ИГРА ПАМЯТЬ---";
            Sleep(200);
            cout << "\n--Выбор спец. способностей--\n";
            Sleep(200);
            cout << "\nКоличество угаданных пар: " << countOfGuessed;
            cout << "\nКоличество оставшихся ходов: " << countOfTurns << endl;
            Sleep(200);
            cout << "\n[1] - Открыть всё поле (Стоимость: 5 ходов);";
            cout << "\n[2] - Открыть случайную пару (Стоимость: 3 хода).";
            cout << "\n>> Ваш выбор: ";
            cin >> user;

            switch (user)
            {
            case 1:

                system("cls");
                countOfTurns = (countOfTurns - 5 > 0 ? countOfTurns - 5 : 0);
                PrintGameField(gameField);
                Sleep(2000);

                break;

            case 2:

                system("cls");
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        if (neededChar == '?')
                        {
                            if (userGameField[i][j] == '?')
                            {
                                X1 = j;
                                Y1 = i;
                                neededChar = gameField[i][j];
                            }
                        }
                        else
                        {
                            if (gameField[i][j] == neededChar)
                            {
                                X2 = j;
                                Y2 = i;
                                break;
                            }
                        }
                    }
                }
                tempGameField[Y1][X1] = gameField[Y1][X1];
                tempGameField[Y2][X2] = gameField[Y2][X2];
                countOfTurns = (countOfTurns - 3 > 0 ? countOfTurns - 3 : 0);
                PrintGameField(tempGameField);
                Sleep(2000);

                break;

            default:

                system("cls");
                cout << "---ИГРА ПАМЯТЬ---";
                cout << "\n--Выбор спец. способностей--\n";
                cout << "\nКоличество угаданных пар: " << countOfGuessed;
                cout << "\nКоличество оставшихся ходов: " << countOfTurns << endl;
                Sleep(500);
                cout << "\nОШИБКА: Такого варианта нет в списке!\n";
                Sleep(2000);

                break;

            }
        }

        X--;
        Y--;

        if (X < 0 || Y < 0)
        {
            system("cls");
            return ;
        }

        //Отсчёт идёт не от 0, а от 1
        system("cls"); //Очиска консоли
        tempGameField[Y][X] = gameField[Y][X]; //Копирование во временное игровое поле значение из основного игрового поля
        PrintGameField(tempGameField, X, Y); //Вывод игрового поля в консоль
        Sleep(1000);
        system("cls");
        //Очиска консоли спустя некоторое время

        countOfTurns--;

        //Проверка на соответствие игрового поля с предыдущим игровым полем
        if (gameField[previosY][previosX] != gameField[Y][X])
        {
            OpenCell(gameField, userGameField, X, Y);
        }
        else
        {
            if (previosX == X && previosY == Y)
            {
                OpenCell(gameField, userGameField, X, Y);
            }
            else
            {
                userGameField[Y][X] = gameField[Y][X];
                userGameField[previosY][previosX] = gameField[previosY][previosX];
                countOfGuessed = GameFieldCMP(userGameField, gameField) / 2;
                //Сравнение полей для чёткого определения количества соответствий
            }
        }
    }
}

int main()
{
    setlocale(0, "");
    srand(time(nullptr));

    //Создание 2-ух игровых полей
    char gameField[4][4] = {};
    char userGameField[4][4] = {};
    int user = 0;

    while (user != 4)
    {
        system("cls");
        cout << "---ИГРА ПАМЯТЬ---";
        Sleep(250);
        cout << "\n[0] Загрузка...";
        Sleep(1000);
        system("cls");
        cout << "---ИГРА ПАМЯТЬ---";
        cout << "\n--Главное меню--\n";
        cout << "\n[1] - Начать игру;";
        cout << "\n[2] - Ввести количество ходов [Сейчас: " << constCountOfTurns << "];";
        cout << "\n[3] - Выбрать тематику карточек [Сейчас: " << (charsVariant == 1 ? "Спец.символы(!, @, #, $, %, ^, &, *)" : charsVariant == 2 ? "Цифры(1, 2, 3, 4, 5, 6, 7, 8)" : charsVariant == 3 ? "Буквы(A, B, C, D, E, F, G, H)" : "Ручной ввод") << "];";
        cout << "\n[4] - Закрыть программу.";
        cout << "\n>> Ваш выбор: ";
        cin >> user;

        switch (user)
        {
        case 1:

            system("cls");

            countOfGuessed = 0;
            countOfTurns = constCountOfTurns;

            //Заполнение игрового поля
            InitGameField(userGameField, 0);
            InitGameField(gameField, 2);

            //Цикл игры
            while (countOfGuessed < 8 && countOfTurns > 0)
            {
                OpenCell(gameField, userGameField);
            }

            //Окончание игры
            PrintGameField(userGameField);
            cout << "Игра окончена!\n\n";
            if (countOfGuessed == 8)
            {
                cout << "ВЫ УГАДАЛИ ВСЕ ПАРЫ!\n\n";
                cout << "Поздравляем!\n";
            }
            else
            {
                cout << "Вы не смогли угадать все пары.\n\n";
                cout << "Вы проиграли :(\n";
            }
            Sleep(5000);

            break;

        case 2:

            system("cls");
            cout << "---ИГРА ПАМЯТЬ---";
            Sleep(500);
            cout << "\n--Ввод количества ходов--\n";
            cout << "\n>> Ваш выбор: ";
            cin >> constCountOfTurns;
            constCountOfTurns = (constCountOfTurns == 0 ? 1 : constCountOfTurns > 0 ? constCountOfTurns : constCountOfTurns * -1);

            break;

        case 3:

            system("cls");
            cout << "---ИГРА ПАМЯТЬ---";
            Sleep(500);
            cout << "\n--Выбор тематики карточек--\n";
            cout << "\n[1] - Спец. символы (!, @, #, $, %, ^, &, *);";
            cout << "\n[2] - Цифры (1, 2, 3, 4, 5, 6, 7, 8);";
            cout << "\n[3] - Буквы (A, B, C, D, E, F, G, H);";
            cout << "\n[4] - Ручной ввод.";
            cout << "\n>> Ваш выбор: ";
            cin >> charsVariant;

            switch (charsVariant)
            {
            case 1:

                system("cls");
                cout << "---ИГРА ПАМЯТЬ---";
                cout << "\n--Выбор тематики карточек--\n";
                Sleep(250);
                strcpy(chars, chars1);
                cout << "\nСпец. символы успешно выбраны в качестве тематики карточек!\n";
                Sleep(2000);

                break;

            case 2:

                system("cls");
                cout << "---ИГРА ПАМЯТЬ---";
                cout << "\n--Выбор тематики карточек--\n";
                Sleep(250);
                strcpy(chars, chars2);
                cout << "\nЦифры успешно выбраны в качестве тематики карточек!\n";
                Sleep(2000);

                break;

            case 3:

                system("cls");
                cout << "---ИГРА ПАМЯТЬ---";
                cout << "\n--Выбор тематики карточек--\n";
                Sleep(250);
                strcpy(chars, chars3);
                cout << "\nБуквы успешно выбраны в качестве тематики карточек!\n";
                Sleep(2000);

                break;

            case 4:

                system("cls");
                cout << "---ИГРА ПАМЯТЬ---";
                cout << "\n--Выбор тематики карточек--";
                cout << "\n(Учтите, что символы не должны повторяться!)\n\n";
                Sleep(250);
                for (int i = 0; i < 8; i++)
                {
                    cout << "Введите символ №" << i + 1 << ": ";
                    cin >> chars[i];
                }
                cout << "\nВы успешно ввели символы вручную!\n";
                Sleep(2000);

                break;

            default:

                system("cls");
                cout << "---ИГРА ПАМЯТЬ---";
                cout << "\n--Выбор тематики карточек--\n";
                Sleep(500);
                cout << "\nОШИБКА: Такого варианта нет в списке!\n";
                Sleep(2000);

                break;
            }

            break;

        case 4:

            system("cls");
            cout << "---ИГРА ПАМЯТЬ---";
            cout << "\n--Главное меню--\n";
            Sleep(250);
            cout << "\nПрограмма успешно закрыта!\n";

            break;

        default:

            system("cls");
            cout << "---ИГРА ПАМЯТЬ---";
            cout << "\n--Главное меню--\n";
            Sleep(500);
            cout << "\nОШИБКА: Такого варианта нет в списке!\n";
            Sleep(2000);

            break;

        }
    }

    return 0;
}
