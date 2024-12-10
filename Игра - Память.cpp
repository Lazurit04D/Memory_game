#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <windows.h> //Для функции Sleep()
#include <iostream>
using namespace std;

//Символы вынесены чтобы быть доступными для всей программы
char chars[8] = { '!', '@', '#', '$', '%', '^', '&', '*' };
const char chars1[8] = { '!', '@', '#', '$', '%', '^', '&', '*' };
const char chars2[8] = { '1', '2', '3', '4', '5', '6', '7', '8' };
const char chars3[8] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
int countOfGuessed = 0;

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
    cout << "\nКоличество угаданных пар: " << countOfGuessed << endl << endl;

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
    unsigned int X, Y;
    char tempGameField[4][4] = {};
    InitGameField(tempGameField, 1, userGameField);
    //Создание временного игрового поля и копирование в него уже существующего

    //Ввод координат ячейки
    PrintGameField(userGameField);
    cout << "Введите координату «X» у вашей ячейки\n(1-4, включительно): ";
    cin >> X;
    cout << "Введите координату «Y» у вашей ячейки\n(1-4, включительно): ";
    cin >> Y;

    X--;
    Y--;
    //Отсчёт идёт не от 0, а от 1
    system("cls"); //Очиска консоли
    tempGameField[Y][X] = gameField[Y][X]; //Копирование во временное игровое поле значение из основного игрового поля
    PrintGameField(tempGameField, X, Y); //Вывод игрового поля в консоль
    Sleep(1000);
    system("cls");
    //Очиска консоли спустя некоторое время

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

int main()
{
    setlocale(0, "");
    srand(time(nullptr));

    //Создание 2-ух игровых полей
    char gameField[4][4] = {};
    char userGameField[4][4] = {};
    int user = 0;

    while (user != 3)
    {
        system("cls");
        cout << "---ИГРА ПАМЯТЬ---";
        Sleep(250);
        cout << "\n[0] Загрузка...";
        Sleep(1000);
        system("cls");
        cout << "---ИГРА ПАМЯТЬ---";
        cout << "\n--Главное меню--\n";
        cout << "\n[1] - Начать игру;\n[2] - Выбрать тематику карточек;\n[3] - Закрыть программу;\n>> Ваш выбор: ";
        cin >> user;

        switch (user)
        {
        case 1:

            system("cls");

            countOfGuessed = 0;

            //Заполнение игрового поля
            InitGameField(userGameField, 0);
            InitGameField(gameField, 2);

            //Цикл игры
            while (countOfGuessed != 8)
            {
                OpenCell(gameField, userGameField);
            }

            //Окончание игры
            PrintGameField(userGameField);
            cout << "Игра окончена!\n\n";
            cout << "ВЫ УГАДАЛИ ВСЕ ЯЧЕЙКИ!\n\n";
            cout << "Поздравляем!\n";
            Sleep(5000);

            break;

        case 2:

            system("cls");
            cout << "---ИГРА ПАМЯТЬ---";
            Sleep(500);
            cout << "\n--Выбор тематики карточек--\n";
            int user2;
            cout << "\n[1] - Спец. символы (!, @, #, $, %, ^, &, *);\n[2] - Цифры (1, 2, 3, 4, 5, 6, 7, 8);\n[3] - Буквы (A, B, C, D, E, F, G, H);\n[4] - Ручной ввод;\n>> Ваш выбор: ";
            cin >> user2;

            switch (user2)
            {
            case 1:

                system("cls");
                cout << "---ИГРА ПАМЯТЬ---";
                cout << "\n--Выбор тематики карточек--\n";
                Sleep(250);
                strcpy(chars, chars1);
                cout << "\nСпец. символы успешно выбраны!\n";
                Sleep(2000);
                break;

            case 2:

                system("cls");
                cout << "---ИГРА ПАМЯТЬ---";
                cout << "\n--Выбор тематики карточек--\n";
                Sleep(250);
                strcpy(chars, chars2);
                cout << "\nЦифры успешно выбраны!\n";
                Sleep(2000);
                break;

            case 3:

                system("cls");
                cout << "---ИГРА ПАМЯТЬ---";
                cout << "\n--Выбор тематики карточек--\n";
                Sleep(250);
                strcpy(chars, chars3);
                cout << "\nБуквы успешно выбраны!\n";
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

        case 3:

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
