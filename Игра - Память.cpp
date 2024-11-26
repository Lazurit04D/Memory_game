#include <time.h>
#include <iostream>
using namespace std;

int main()
{
    srand(time(nullptr));

    char arr[4][4] = {};
    char arrUser[4][4] = {};
    char chars[8] = { '!', '@', '#', '$', '%', '^', '&', '*' };
    int countOfChars[8] = { 0,0,0,0,0,0,0,0 };
    int countOfGuessed = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int randInt = rand() % 8;
            while (true)
            {
                randInt = rand() % 8;
                if (countOfChars[randInt] < 2)
                {
                    break;
                }
            }
            arr[i][j] = chars[randInt];
            countOfChars[randInt]++;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            arrUser[i][j] = '_';
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << arrUser[i][j] << " ";
        }
        cout << endl;
    }

    //while (countOfGuessed < 8)
    //{
    //    int x1, y1, x2, y2;
    //    cout << "Введите координаты 1-ой ячейки: ";
    //    cin >> x1 >> y1;
    //    cout << "Введите координаты 2-ой ячейки: ";
    //    cin >> x2 >> y2;
    //}
}
