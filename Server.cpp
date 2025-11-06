#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

struct Person
{
    char name[25];
    int height;
    int weight;
} B;

int answer;
long size_pred;

int main()
{
    setlocale(LC_ALL, "Russian");

    const char* nameR = "G:\\for_serv\\Request.bin";
    const char* nameA = "G:\\for_serv\\Answer.bin";

    cout << "Server is working..." << endl;

    // очищаем старые данные при запуске
    {
        ofstream clearR(nameR, ios::binary | ios::trunc);
        ofstream clearA(nameA, ios::binary | ios::trunc);
        clearR.close();
        clearA.close();
    }

    // задаем стартовую позицию
    size_pred = 0;

    while (true)
    {
        ifstream fR(nameR, ios::binary);
        fR.seekg(0, ios::end);
        long new_size = fR.tellg();
        fR.close();

        // проверяем появилось ли чтото новое
        if (new_size > size_pred)
        {
            fR.open(nameR, ios::binary);
            fR.seekg(size_pred, ios::beg);
            fR.read((char*)&B, sizeof(B));
            size_pred = fR.tellg();
            fR.close();

            // обработка запроса
            double IMT = B.weight / (0.01 * B.height) / (0.01 * B.height);

            if (18.5 <= IMT && IMT < 25)
                answer = 1;  // Норма
            else if (IMT < 18.5)
                answer = 0;  // Недостаток
            else
                answer = 2;  // Избыток

            cout << "Получен запрос: " << B.name << " Рост: " << B.height << " Вес: " << B.weight << " IMT: " << IMT << endl;

            // записываем ответ
            ofstream fA(nameA, ios::binary | ios::app);
            fA.write((char*)&answer, sizeof(answer));
            fA.close();
        }

        Sleep(100);
    }

    return 0;
}
