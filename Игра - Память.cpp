#include <time.h>
#include <iostream>
using namespace std;

const char chars[8] = { '!', '@', '$', '%', '^', '&', '*', '0'};

void InitGameField(char gameField[][4], bool user)
{
    int randInt = 0;
    int countOfAnyChar[8];
    for (int i = 0; i < 8; i++)
    {
        countOfAnyChar[i] = 0;
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (!user)
            {
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
                gameField[i][j] = '#';
            }
        }
    }
}

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
    char userField[4][4] = {};

    InitGameField(gameField, false);
    PrintGameField(gameField);

    cout << endl;

    InitGameField(userField, true);
    PrintGameField(userField);
}
