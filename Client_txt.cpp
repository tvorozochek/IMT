#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

struct Person
{
    string name;
    int height;
    int weight;
};

int main()
{
    setlocale(LC_ALL, "Russian");

    const char* nameR = "G:\\for_serv\\Request.txt";
    const char* nameA = "G:\\for_serv\\Answer.txt";

    int prev_lines = 0;

    while (true)
    {
        Person A;
        cout << "Введите запрос: Фамилия Рост Вес\n";
        cin >> A.name >> A.height >> A.weight;

        // добавляем запись в конец реквест
        ofstream f_REQ(nameR, ios::app);
        f_REQ << A.name << " " << A.height << " " << A.weight << endl;
        f_REQ.close();

        // ждём ответ
        int lines_now = 0;
        string last_line;
        while (true)
        {
            ifstream fA(nameA);
            lines_now = 0;
            last_line.clear();

            string line;
            while (getline(fA, line))
            {
                lines_now++;
                last_line = line;
            }
            fA.close();

            if (lines_now > prev_lines)
            {
                cout << "Ответ сервера: " << last_line << endl;
                prev_lines = lines_now;
                break;
            }

            Sleep(500);
        }
    }

    return 0;
}
