#ifndef MATRICA_H
#define MATRICA_H

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

class Matrica
{
protected:

    vector<vector<double>> matrix;
    bool da_li_je_matrica;

    friend Matrica Rezultat(Matrica operand1, Matrica operand2, char operacija);
    friend void IzvrsiOperaciju(stack<Matrica> &matrice, stack<char> &zagrade_i_operacije);
    friend Matrica NapraviMatricu(string m);
    friend Matrica AlgoritamZaMnozenje(Matrica A, Matrica B, int n);

public:
    Matrica():da_li_je_matrica(true) {}
    Matrica(int red, int kolona, double vrijednost = 0):matrix(red, vector<double>(kolona, vrijednost)), da_li_je_matrica(true) {}

    bool Kvadratna() const { return this->GetRed() == this->GetKolona(); }
    int GetRed() const { return this->matrix.size(); }
    int GetKolona() const { if(!this->matrix.empty()) return this->matrix[0].size(); return 0; }
    double Det();
    void Jedinicna(int n = 0);
    void Transponuj();
    void Inverse();
    void operator+=(Matrica &rhs);
    void operator*=(Matrica &rhs);

    friend Matrica operator+(const Matrica &lhs, const Matrica &rhs);
    friend Matrica operator-(const Matrica &lhs, const Matrica &rhs);
    friend Matrica operator*(double faktor, const Matrica &rhs);
    friend Matrica operator*(const Matrica &lhs, double faktor);
    friend Matrica operator*(const Matrica &lhs, const Matrica &rhs);
    friend Matrica operator^(const Matrica &lhs, int stepen);
    friend ostream& operator<<(ostream& ispis, const Matrica& matrica);
    friend istream& operator>>(istream& unos, Matrica& m);
};

#endif // MATRICA_H
