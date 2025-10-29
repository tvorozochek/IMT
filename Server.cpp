#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

struct Person {
    char name[25];
    int height;
    int weight;
} B;

int main() {
    setlocale(LC_ALL, "Russian");
    const char* nameR = R"(G:\for_serv\Request.bin)";
    const char* nameA = R"(G:\for_serv\Answer.bin)";

    cout << "Server is working..." << endl;

    long size_pred = 0;
    int answer;

    while (true) {
        ifstream fR(nameR, ios::binary);
        fR.seekg(0, ios::end);
        long size_now = fR.tellg();
        fR.close();

        if (size_now > size_pred) {
            ifstream fR2(nameR, ios::binary);
            fR2.seekg(size_pred, ios::beg);
            fR2.read((char*)&B, sizeof(B));
            fR2.close();

            size_pred = size_now;

            double IMT = B.weight / ((0.01 * B.height) * (0.01 * B.height));
            if (IMT < 18.5) answer = 0;
            else if (IMT < 25) answer = 1;
            else answer = 2;

            ofstream fA(nameA, ios::binary | ios::app);
            fA.write((char*)&answer, sizeof(answer));
            fA.close();

            cout << "Запрос обработан: " << B.name << " IMT=" << IMT << endl;
        }

        Sleep(100);
    }
}
