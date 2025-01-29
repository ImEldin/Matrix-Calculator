#include <iostream>
#include <string>
#include <vector>
#include "Matrica.h"

using namespace std;

int main()
{
    //[1 2;3 4]
    //[5 6;7 8]
    Matrica m;
    Matrica n;

    while(true)
    {
        cout << "Unesite matricu ili neki izraz:" << endl;
        cin >> m;
        n = m;
        cout << "Rezultat: "<< endl << n;
        cout << "Determinanta matrice je:" << endl;
        cout << m.Det() << endl;
        cout << "Transponovana matrica je:" << endl;
        n.Transponuj();
        cout << n;
        if(m.Det() != 0)
        {
            m.Inverse();
            cout << "Inverzna matrica je:"<<endl;
            cout << m;
        }
        else cout << "Matrica nema inverz!" <<endl;
    }

    return 0;
}
