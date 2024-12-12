#define _CRT_SECURE_NO_WARNINGS
#include <time.h> //Для функции rand()
#include <windows.h> //Для функции Sleep()
#include <iostream>
using namespace std;

//Символы вынесены чтобы быть доступными для всей программы
int charsVariant = 1;
int currentCharsSize = 8;
char chars[32] = { '`', '~', '!', '@', '"', '#', '№', '$', ';', '%', '^', ':', '&', '*', '(', ')', '-', '_', '=', '+', '[', '{', ']', '}', '\'', '\\', '|', '/', ',', '<', '.', '>' };
const char chars1[32] = { '`', '~', '!', '@', '"', '#', '№', '$', ';', '%', '^', ':', '&', '*', '(', ')', '-', '_', '=', '+', '[', '{', ']', '}', '\'', '\\', '|', '/', ',', '<', '.', '>' };
const char chars2[10] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
const char chars3[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
int countOfGuessed = 0;

//Размеры поля
int fieldSizeX = 4;
int fieldSizeY = 4;
int oldFieldSizeX = 4;
int oldFieldSizeY = 4;

//Количество ходов
int constCountOfTurns = fieldSizeX * fieldSizeY * 3;
int countOfTurns = constCountOfTurns;

//Функция сравнения игровых полей (Возвращает количество ячеек, которые совпадают в обоих полях)
int GameFieldCMP(char** gameField, char** secondField)
{
    int countOfMatches = 0;
    for (int i = 0; i < fieldSizeY; i++)
    {
        for (int j = 0; j < fieldSizeX; j++)
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
void InitGameField(char** gameField, int mode, char** secondField = nullptr)
{
    int randInt = 0;
    int* countOfAnyChar = new int[fieldSizeX * fieldSizeY / 2]; //Эта переменная хранит в себе количество каждого символа в игровом поле

    //Этим условием выполнена небольшая оптимизация, так как эта переменная не используется когда заполняется игровое поле игрока
    if (mode == 2)
    {
        for (int i = 0; i < fieldSizeX * fieldSizeY / 2; i++)
        {
            countOfAnyChar[i] = 0;
        }
    }

    for (int i = 0; i < fieldSizeY; i++)
    {
        for (int j = 0; j < fieldSizeX; j++)
        {
            if (mode == 2)
            {
                //Этот цикл не даёт повторяться одному символу больше 2 раз
                while (true)
                {
                    randInt = rand() % (fieldSizeX * fieldSizeY / 2);
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

    delete[] countOfAnyChar;
}

//Вывод игрового поля в консоль
void PrintGameField(char** gameField, int X = -1, int Y = -1)
{
    cout << "---ИГРА ПАМЯТЬ---";
    cout << "\n--Игра--\n";
    cout << "\nКоличество угаданных пар: " << countOfGuessed;
    cout << "\nКоличество оставшихся ходов: " << countOfTurns << endl << endl;

    for (int i = 0; i < fieldSizeY + 1; i++)
    {
        for (int j = 0; j < fieldSizeX + 1; j++)
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

void OpenCell(char** gameField, char** userGameField, int previosX = -1, int previosY = -1)
{
    if (countOfTurns > 0)
    {
        int X, Y, user;

        char** tempGameField = new char* [fieldSizeY];
        for (int i = 0; i < fieldSizeY; i++)
        {
            tempGameField[i] = new char[fieldSizeX];
        }

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
                                    //Защита от отрицательных чисел
                PrintGameField(gameField);
                Sleep(2000);

                break;

            case 2:

                system("cls");
                for (int i = 0; i < fieldSizeY; i++)
                {
                    for (int j = 0; j < fieldSizeX; j++)
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
                                    //Защита от отрицательных чисел
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

        if (X < 0 || Y < 0 || X >= fieldSizeX || Y >= fieldSizeY)
        {
            system("cls");
            return;
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
        if (previosX != -1 && previosY != -1)
        {
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
        else
        {
            OpenCell(gameField, userGameField, X, Y);
        }

        //Удаление памяти

        for (int i = 0; i < fieldSizeY; i++)
        {
            delete[] tempGameField[i];
        }
        delete[] tempGameField;
    }
}

int main()
{
    setlocale(0, "");
    srand(time(nullptr));

    //Создание 2-ух игровых полей

    char** gameField = new char* [fieldSizeY];
    for (int i = 0; i < fieldSizeY; i++)
    {
        gameField[i] = new char[fieldSizeX];
    }

    char** userGameField = new char* [fieldSizeY];
    for (int i = 0; i < fieldSizeY; i++)
    {
        userGameField[i] = new char[fieldSizeX];
    }

    int user = 0;

    while (user != 5)
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
        cout << "\n[2] - Ввести размеры игрового поля [Сейчас: X = " << fieldSizeX << ", Y = " << fieldSizeY << "];";
        cout << "\n[3] - Ввести количество ходов [Сейчас: " << constCountOfTurns << "];";
        cout << "\n[4] - Выбрать тематику карточек [Сейчас: " << (charsVariant == 1 ? "Спец.символы( `, ~, !, @, \", #, №, $, ;, %,...)" : charsVariant == 2 ? "Цифры(1, 2, 3, 4, 5, 6, 7, 8, 9, 0)" : charsVariant == 3 ? "Буквы(A, B, C, D, E, F, G, H, I, J,...)" : "Ручной ввод") << "];";
        cout << "\n[5] - Закрыть программу.";
        cout << "\n>> Ваш выбор: ";
        cin >> user;

        switch (user)
        {
        case 1:

            //Перевыделение памяти

            for (int i = 0; i < oldFieldSizeY; i++)
            {
                delete[] gameField[i];
            }
            delete[] gameField;

            for (int i = 0; i < oldFieldSizeY; i++)
            {
                delete[] userGameField[i];
            }
            delete[] userGameField;

            gameField = new char* [fieldSizeY];
            for (int i = 0; i < fieldSizeY; i++)
            {
                gameField[i] = new char[fieldSizeX];
            }

            userGameField = new char* [fieldSizeY];
            for (int i = 0; i < fieldSizeY; i++)
            {
                userGameField[i] = new char[fieldSizeX];
            }

            oldFieldSizeX = fieldSizeX;
            oldFieldSizeY = fieldSizeY;

            system("cls");

            countOfGuessed = 0;
            countOfTurns = constCountOfTurns;

            //Заполнение игрового поля
            InitGameField(userGameField, 0);
            InitGameField(gameField, 2);

            //Цикл игры
            while (countOfGuessed < fieldSizeX * fieldSizeY / 2 && countOfTurns > 0)
            {
                OpenCell(gameField, userGameField);
            }

            //Окончание игры
            PrintGameField(userGameField);
            cout << "Игра окончена!\n\n";
            if (countOfGuessed == fieldSizeX * fieldSizeY / 2)
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

            int tempFieldSizeX, tempFieldSizeY;

            system("cls");
            cout << "---ИГРА ПАМЯТЬ---";
            Sleep(500);
            cout << "\n--Ввод размеров игрового поля--\n";
            cout << "\n>> Размер по X: ";
            cin >> tempFieldSizeX;
            cout << ">> Размер по Y: ";
            cin >> tempFieldSizeY;

            if (tempFieldSizeX * tempFieldSizeY > 64)
            {
                system("cls");
                cout << "---ИГРА ПАМЯТЬ---";
                cout << "\n--Ввод размеров игрового поля--\n";
                Sleep(500);
                cout << "\nОШИБКА: Слишком большое поле! (Максимум 8 на 8)\n";
                Sleep(2000);
            }
            else
            {
                if (tempFieldSizeX * tempFieldSizeY % 2 != 0)
                {
                    system("cls");
                    cout << "---ИГРА ПАМЯТЬ---";
                    cout << "\n--Ввод размеров игрового поля--\n";
                    Sleep(500);
                    cout << "\nОШИБКА: Количество пар ячеек на поле не может быть нечётным!\nПопробуйте ввести другие числа.\n";
                    Sleep(2000);
                }
                else
                {
                    fieldSizeX = (tempFieldSizeX == 0 ? 2 : tempFieldSizeX > 0 ? tempFieldSizeX : tempFieldSizeX * -1);
                    fieldSizeY = (tempFieldSizeY == 0 ? 2 : tempFieldSizeY > 0 ? tempFieldSizeY : tempFieldSizeY * -1);
                                                        //Защита от неправильных чисел

                    system("cls");
                    cout << "---ИГРА ПАМЯТЬ---";
                    cout << "\n--Ввод размеров игрового поля--\n";
                    Sleep(250);
                    cout << "\nРазмеры игрового поля успешно введены!\n";

                    if (constCountOfTurns != fieldSizeX * fieldSizeY * 3)
                    {
                        constCountOfTurns = fieldSizeX * fieldSizeY * 3;
                        Sleep(400);
                        cout << "Количество ходов изменено на: " << constCountOfTurns << endl;
                    }

                    if (charsVariant != 1 && (fieldSizeX * fieldSizeY / 2 > currentCharsSize))
                    {
                        for (int i = 0; i < currentCharsSize; i++)
                        {
                            chars[i] = chars1[i];
                        }
                        
                        charsVariant = 1;
                        Sleep(400);
                        cout << "Спец. символы успешно выбраны в качестве тематики карточек!\n";
                    }

                    Sleep(2000);
                }
            }

            break;

        case 3:

            system("cls");
            cout << "---ИГРА ПАМЯТЬ---";
            Sleep(500);
            cout << "\n--Ввод количества ходов--\n";
            cout << "\n>> Ваш выбор: ";
            cin >> constCountOfTurns;
            constCountOfTurns = (constCountOfTurns == 0 ? 1 : constCountOfTurns > 0 ? constCountOfTurns : constCountOfTurns * -1);
                                                    //Защита от неправильных чисел

            system("cls");
            cout << "---ИГРА ПАМЯТЬ---";
            cout << "\n--Ввод количества ходов--\n";
            Sleep(250);
            cout << "\nКоличество ходов успешно введено!\n";
            Sleep(2000);

            break;

        case 4:

            system("cls");
            cout << "---ИГРА ПАМЯТЬ---";
            Sleep(500);
            cout << "\n--Выбор тематики карточек--\n";
            cout << "\n[1] - Спец.символы(`, ~, !, @, \", #, №, $, ;, %, ^, :, &, *, (, ), -, _, =, +, [, {, ], }, ', \\, |, /, ,, <, ., >);";
            cout << "\n[2] - Цифры(1, 2, 3, 4, 5, 6, 7, 8, 9, 0);";
            cout << "\n[3] - Буквы(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z);";
            cout << "\n[4] - Ручной ввод.";
            cout << "\n>> Ваш выбор: ";
            cin >> charsVariant;

            switch (charsVariant)
            {
            case 1:

                system("cls");
                cout << "---ИГРА ПАМЯТЬ---";
                cout << "\n--Выбор тематики карточек--\n";
                currentCharsSize = 32;
                Sleep(250);

                for (int i = 0; i < currentCharsSize; i++)
                {
                    chars[i] = chars1[i];
                }

                cout << "\nСпец. символы успешно выбраны в качестве тематики карточек!\n";
                Sleep(2000);

                break;

            case 2:

                system("cls");
                cout << "---ИГРА ПАМЯТЬ---";
                cout << "\n--Выбор тематики карточек--\n";
                currentCharsSize = 10;
                Sleep(250);

                for (int i = 0; i < currentCharsSize; i++)
                {
                    chars[i] = chars2[i];
                }

                cout << "\nЦифры успешно выбраны в качестве тематики карточек!\n";

                if (fieldSizeX * fieldSizeY / 2 > currentCharsSize)
                {
                    fieldSizeX = 4;
                    fieldSizeY = 5;

                    Sleep(400);
                    cout << "Размеры игрового поля успешно изменены (X = 4, Y = 5)!\n";

                    if (constCountOfTurns != fieldSizeX * fieldSizeY * 3)
                    {
                        constCountOfTurns = fieldSizeX * fieldSizeY * 3;
                        Sleep(400);
                        cout << "Количество ходов изменено на: " << constCountOfTurns << endl;
                    }
                }

                Sleep(2000);

                break;

            case 3:

                system("cls");
                cout << "---ИГРА ПАМЯТЬ---";
                cout << "\n--Выбор тематики карточек--\n";
                currentCharsSize = 26;
                Sleep(250);

                for (int i = 0; i < currentCharsSize; i++)
                {
                    chars[i] = chars2[i];
                }

                cout << "\nБуквы успешно выбраны в качестве тематики карточек!\n";

                if (fieldSizeX * fieldSizeY / 2 > currentCharsSize)
                {
                    fieldSizeX = 4;
                    fieldSizeY = 13;

                    Sleep(400);
                    cout << "Размеры игрового поля успешно изменены (X = 4, Y = 13)!\n";

                    if (constCountOfTurns != fieldSizeX * fieldSizeY * 3)
                    {
                        constCountOfTurns = fieldSizeX * fieldSizeY * 3;
                        Sleep(400);
                        cout << "Количество ходов изменено на: " << constCountOfTurns << endl;
                    }
                }

                Sleep(2000);

                break;

            case 4:

                system("cls");
                cout << "---ИГРА ПАМЯТЬ---";
                cout << "\n--Выбор тематики карточек--";
                cout << "\n(Учтите, что символы не должны повторяться!)\n\n";
                currentCharsSize = fieldSizeX * fieldSizeY / 2;

                Sleep(250);

                for (int i = 0; i < currentCharsSize; i++)
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

        case 5:

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

    //Удаление памяти

    for (int i = 0; i < fieldSizeY; i++)
    {
        delete[] gameField[i];
    }
    delete[] gameField;

    for (int i = 0; i < fieldSizeY; i++)
    {
        delete[] userGameField[i];
    }
    delete[] userGameField;

    return 0;
}
