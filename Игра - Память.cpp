#include <time.h>
#include <windows.h>
#include <iostream>
using namespace std;

//Символы вынесены чтобы быть доступными для всей программы
const char chars[8] = { '!', '@', '#', '$', '%', '^', '&', '*'};
int countOfGuessed = 0;

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
    cout << "Количество угаданных: " << countOfGuessed << endl << endl;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << gameField[i][j] << " ";
        }

        cout << endl;
    }
}

void OpenCell(const char gameField[][4], char userGameField[][4], int previosX = -1, int previosY = -1)
{
    int X, Y;
    char tempGameField[4][4] = {};
    InitGameField(tempGameField, 1, userGameField);

    PrintGameField(userGameField);
    cout << "\nВведите X ячейки: ";
    cin >> X;
    cout << "Введите Y ячейки: ";
    cin >> Y;

    system("cls");
    tempGameField[Y][X] = gameField[Y][X];
    PrintGameField(tempGameField, X, Y);
    Sleep(1000);
    system("cls");

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

    char gameField[4][4] = {};
    char userGameField[4][4] = {};

    InitGameField(userGameField, 0);
    InitGameField(gameField, 2);

    while (countOfGuessed < 8)
    {
        OpenCell(gameField, userGameField);
    }

    PrintGameField(userGameField);

    return 0;
}
