#include <time.h>
#include <iostream>
using namespace std;
//1234567890-

//Символы вынесены чтобы быть доступными для всей программы
const char chars[8] = { '!', '@', '$', '%', '^', '&', '*', '0'};

//Заполнение игрового поля
void InitGameField(char gameField[][4], bool user)
{
    int randInt = 0;
    int countOfAnyChar[8]; //Эта переменная хранит в себе количество каждого символа в игровом поле
    //Этим условием выполнена небольшая оптимизация, так как эта переменная не используется когда заполняется игровое поле игрока
    if (!user)
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
            if (!user)
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
            else
            {
                //Заполнение пустого игрового поля игрока
                gameField[i][j] = '#';
            }
        }
    }
}

//Вывод игрового поля в консоль
void PrintGameField(const char gameField[][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << gameField[i][j] << " ";
        }

        cout << endl;
    }
}

int main()
{
    setlocale(0, "");
    srand(time(nullptr));

    char gameField[4][4] = {};
    char userGameField[4][4] = {};

    InitGameField(gameField, false);
    PrintGameField(gameField);

    cout << endl;

    InitGameField(userGameField, true);
    PrintGameField(userGameField);
}
