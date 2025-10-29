#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

struct Person {
    char name[25];
    int height;
    int weight;
} A;    //создаем структуру А

int main() {
    setlocale(LC_ALL, "Russian");
    const char* nameR = R"(G:\for_serv\Request.bin)";
    const char* nameA = R"(G:\for_serv\Answer.bin)";

    while (true) {
        cout << "Введите запрос (Фамилия Рост Вес): ";
        cin >> A.name >> A.height >> A.weight;

        ofstream f_REQ(nameR, ios::binary | ios::app);  //открываем бинарный файл в режиме добавления (app)
        f_REQ.write((char*)&A, sizeof(A));  //сперва говорим с чем работать, потом указываем размер этой работы 
        f_REQ.close();

        long pred_size; //запоминаем размер файла с ответами
        {
            ifstream f_ANS(nameA, ios::binary);
            f_ANS.seekg(0, ios::end);
            pred_size = f_ANS.tellg();
            f_ANS.close();
        }

        long size_now = pred_size;
        while (size_now <= pred_size) { //ждем пока размер файла с ответами поменяется 
            Sleep(100);
            ifstream f_ANS(nameA, ios::binary);
            f_ANS.seekg(0, ios::end);
            size_now = f_ANS.tellg();
            f_ANS.close();
        }

        int answer;
        ifstream f_ANS(nameA, ios::binary);
        f_ANS.seekg(pred_size, ios::beg);   //открываем файл с последнего ответа
        f_ANS.read((char*)&answer, sizeof(answer)); //читаем ответ
        f_ANS.close();

        switch (answer) {
        case 0: cout << "Недостаток веса" << endl; break;
        case 1: cout << "Норма веса" << endl; break;
        case 2: cout << "Избыток веса" << endl; break;
        }
    }
}
