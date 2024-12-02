#include <time.h>
#include <windows.h> //Для функции Sleep()
#include <iostream>
using namespace std;

//Символы вынесены чтобы быть доступными для всей программы
const char chars[8] = { '!', '@', '#', '$', '%', '^', '&', '*' };
int countOfGuessed = 0;

//Функция сравнения игровых полей (На данный момент не используется)
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
    cout << "Количество угаданных пар: " << countOfGuessed << endl << endl;

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
            countOfGuessed++;
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

    return 0;
}
