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

    cout << "Server is working..." << endl;

    // очистим файлы при запуске
    {
        ofstream clearR(nameR, ios::trunc);
        ofstream clearA(nameA, ios::trunc);
        clearA.close();
        clearR.close();
    }

    // запоминаем, сколько строк уже обработано
    int processed_lines = 0;

    while (true)
    {
        ifstream fR(nameR);
        string name;
        int height, weight;
        int current_line = 0;

        // читаем построчно
        while (fR >> name >> height >> weight)
        {
            current_line++;
            if (current_line <= processed_lines)
                continue; // пропускаем старые записи

            // обработка
            double IMT = weight / (0.01 * height) / (0.01 * height);
            string result;

            if (IMT < 18.5)
                result = "Недостаток веса";
            else if (IMT < 25)
                result = "Норма веса";
            else
                result = "Избыток веса";

            cout << "Получено: " << name << "  Рост: " << height << "  Вес: " << weight << "  IMT: " << IMT << endl;

            // записываем ответ
            ofstream fA(nameA, ios::app);
            fA << result << endl;
        }

        processed_lines = current_line;
        fR.close();

        Sleep(500); // проверяем файл каждые полсекунды
    }

    return 0;
}
