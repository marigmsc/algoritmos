#include <iostream>
using namespace std;
void mais(int& a){
    a++;

}
void maiserrado(int a){
    a++;
}



int main() {
    int a;
    cin >> a;
    cout << "Antes:" << a << endl;
    mais(a);
    cout << "Depois:"<< a << endl;
    maiserrado(a);
    cout << "Depois errado:"<< a << endl;


   return 0;
}