#ifndef MATRICA_CPP
#define MATRICA_CPP

#include "Matrica.h"
#include <algorithm>
#include <stack>
#include <cmath>

//Vraca prioritet operacije
int PrioritetOperacije(char operacija)
{
    if(operacija == '+' || operacija == '-')
        return 1;
    if(operacija == '*')
        return 2;
    if(operacija == '^')
        return 3;
}

//Vraca rezultat za odgovarajucu operaciju
Matrica Rezultat(Matrica operand1, Matrica operand2, char operacija)
{
    if(operacija == '+')
    {
        //Ako pokusavamo sabrati matricu i broj baca izuzetak u suprotnom sabira dvije matrice ili dva broja
        try
        {
            if(operand1.da_li_je_matrica == false && operand2.da_li_je_matrica == true)
            {
                throw "Nije moguce sabrati matricu sa brojem!";
            }
            else if(operand2.da_li_je_matrica == false && operand1.da_li_je_matrica == true)
            {
                throw "Nije moguce sabrati matricu sa brojem!";
            }
        }
        catch(const char poruka [])
        {
            cout<<poruka<<endl;
            throw;
        }

        return operand1 + operand2;
    }
    if(operacija == '-')
    {
        //Ako pokusavamo oduzeti matricu i broj i ako je prvi operand broj baca izuzetak u suprotnom oduzima dvije matrice ili dva broja
        if(operand1.da_li_je_matrica == false && operand2.da_li_je_matrica == true)
        {
            //ako je prvi operand broj jednak 0 tj. ako imamo 0-matrica mijenja predznak elemenata u matrici u suprotnom baca izuzetak
            if(operand1.matrix[0][0] != 0)
                try
                {
                    throw "Nije moguce oduzeti matricu i broj!";
                }
                catch(const char poruka [])
                {
                    cout<<poruka<<endl;
                    throw;
                }
            else return -1*operand2;
        }
        //Ako pokusavamo oduzeti matricu i broj i ako je drugi operand (ovdje se ne provjerava matrica-0) broj baca izuzetak u suprotnom oduzima dvije matrice ili dva broja
        else if(operand2.da_li_je_matrica == false && operand1.da_li_je_matrica == true)
        {
            try
            {
                throw "Nije moguce oduzeti matricu i broj!";
            }
            catch(const char poruka [])
            {
                cout<<poruka<<endl;
                throw;
            }
        }
        return operand1 - operand2;
    }
    if(operacija == '*')
    {
        //Provjerava da li su oba operanda matrice ili je jedan od njih broj ili su oba broj - u svakom slucaju izvrsava mnozenje
        if(operand1.da_li_je_matrica == false && operand2.da_li_je_matrica == true)
        {
            double broj = operand1.matrix[0][0];
            return broj * operand2;
        }
        else if(operand2.da_li_je_matrica == false && operand1.da_li_je_matrica == true)
        {
            double broj = operand2.matrix[0][0];
            return operand1 * broj;
        }
        //Ako su oba operanda broj iz uslova da_li_je_matrica == false mnozi ih kao matrice 1x1
        return operand1 * operand2;
    }
    if(operacija == '^')
    {
        //Ako su oba operanda brojevi izvrsava standardno stepenovanje i vraca matricu 1x1 kod koje je uslov da_li_je_matrica == false
        if(operand1.da_li_je_matrica == false && operand2.da_li_je_matrica == false)
        {
            double broj1 = operand1.matrix[0][0];
            double broj2 = operand2.matrix[0][0];
            double rez = pow(broj1, broj2);
            Matrica broj(1, 1, rez);
            broj.da_li_je_matrica = false;
            return broj;
        }
        //Ako je prvi operand broj baca izuzetak
        else if(operand1.da_li_je_matrica == false && operand2.da_li_je_matrica == true)
        {
            try
            {
                throw "Nije moguce stepenovati broj matricom!";
            }
            catch(const char poruka [])
            {
                cout<<poruka<<endl;
                throw;
            }
        }
        //Ako je drugi operand broj izvrsava stepenovanje
        else if(operand2.da_li_je_matrica == false && operand1.da_li_je_matrica == true)
        {
            double broj = operand2.matrix[0][0];
            //Provjera da li je cijeli broj
            if(broj = int(broj))
                return operand1^broj;
            //Ako nije baca izuzetak
            try
            {
                throw "Stepen matrice mora biti cijeli broj!";
            }
            catch(const char poruka [])
            {
                cout<<poruka<<endl;
                throw;
            }
        }
        //Ako nije ni jedan od tri uslova (oba operanda su matrice) baca gresku
        else
        {
            try
            {
                throw "Nije moguce stepenovati matricu drugom matricom!";
            }
            catch(const char poruka [])
            {
                cout<<poruka<<endl;
                throw;
            }
        }
    }
}

//Uzima prve dvije matrice sa stacka i prvu operaciju i poziva funkciju Rezultat
void IzvrsiOperaciju(stack<Matrica> &matrice, stack<char> &zagrade_i_operacije)
{
    //Ako je stack operacija i zagrada prazan baca izuzetak; Isto radi ako stack matrica sadrzi jednu ili nula matrica
    try
    {
        if(zagrade_i_operacije.empty())
            throw "Greska, provjerite unos!";
        if(matrice.size() < 2)
            throw "Greska, provjerite unos!";
    }
    catch(const char poruka [])
    {
        cout<<poruka<<endl;
        throw;
    }
    char operacija = zagrade_i_operacije.top();
    zagrade_i_operacije.pop();

    Matrica operand2;
    operand2 = matrice.top();
    matrice.pop();

    Matrica operand1;
    operand1 = matrice.top();
    matrice.pop();

    matrice.push(Rezultat(operand1, operand2, operacija));
}

//Vraca da li je char znak otvorena zagrada
bool DaLiJeOtvorena(char znak)
{
    return znak == '(' || znak == '{';
}

//Vraca da li je char znak zatvorena zagrada
bool DaLiJeZatvorena(char znak)
{
    return znak == ')' || znak == '}';
}

//Vraca da li je char znak cifra
bool DaLiJeCifra(char znak)
{
    return znak >= '0' && znak <= '9';
}

//Vraca da li je char znak operacija
bool DaLiJeOperacija(char znak)
{
    return znak == '+' || znak == '-' || znak == '*' || znak == '^';
}

//Za odgovarajucu zatvorenu vraca otvorenu zagradu
char OtvorenaZagrada(char znak)
{
    if(znak == ')')
        return '(';
    if(znak == '}')
        return '{';
}

//Provjerava da li je string matrica
bool DaLiJeMatrica(string m)
{
    for(int i = 0; i < m.size(); i++)
    {
        if((m[i] >= '0' && m[i] <= '9') ||  m[i] == '.' || m[i] == ';' ||  m[i] == ' ' ||  m[i] == '-') continue;
        else return false;
    }

    return true;
}

//Ako je string matrica kreira matricu od stringa
Matrica NapraviMatricu(string m)
{
    Matrica temp;
    vector <double> red_matrice;
    for(int i = 0; i < m.size(); i++)
    {
        if((m[i] >= '0' && m[i] <= '9') || m[i] == '-')
        {
            string broj = "";
            while(m[i] != ' ' && m[i] != ';')
            {
                //Ako je element stringa minus provjeravmo da li je predhodni space i da li je poslije broj
                if(m[i] == '-' && m[i-1] == ' ' && DaLiJeCifra(m[i+1]))
                {
                    broj += "-";
                    i++;
                }
                //Ako nije baca se izuzetak
                else if(m[i] == '-' && (m[i-1] == ' ' || !DaLiJeCifra(m[i+1])))
                    throw "Pogresno unese predznak -!";
                broj += m[i];
                i++;
            }
            //Funkcija stod -> string to double
            double b = stod(broj);
            red_matrice.push_back(b);
        }
        if(m[i] == ';' || i == m.size()-1)
        {
            if(temp.matrix.size() == 0)
            {
                temp.matrix.push_back(red_matrice);
            }
            else
            {
                if(temp.matrix.size() > 0 && red_matrice.size() == temp.matrix[0].size())
                {
                    temp.matrix.push_back(red_matrice);
                }
                else throw "Nepravilan unos matrice!";

            }
            red_matrice.clear();
        }
    }
    return temp;
}

//Strassenov algoritam za mnozenje - Podijeli pa vladaj O(n^2.83)
Matrica AlgoritamZaMnozenje(Matrica A, Matrica B, int dimenzija)
{
    Matrica C(dimenzija, dimenzija);
    //Za matrice 1x1 samo mnozi elemente
    if (dimenzija == 1)
    {
        C.matrix[0][0]= A.matrix[0][0] * B.matrix[0][0];
    }
    //Rekurivni poziv;
    else
    {
        //Podjela matrice na 4 matrice dimenzija n/2
        int index = dimenzija/2;

        Matrica A00(index, index);
        Matrica A01(index, index);
        Matrica A10(index, index);
        Matrica A11(index, index);

        Matrica B00(index, index);
        Matrica B01(index, index);
        Matrica B10(index, index);
        Matrica B11(index, index);

        //Prepisivanje elemenata iz orginalne matrice
        for(int i = 0; i < index; i++)
        {
            for(int j = 0; j < index; j++)
            {
                A00.matrix[i][j] = A.matrix[i][j];
                A01.matrix[i][j] = A.matrix[i][j+index];
                A10.matrix[i][j] = A.matrix[i+index][j];
                A11.matrix[i][j] = A.matrix[i+index][j+index];

                B00.matrix[i][j] = B.matrix[i][j];
                B01.matrix[i][j] = B.matrix[i][j+index];
                B10.matrix[i][j] = B.matrix[i+index][j];
                B11.matrix[i][j] = B.matrix[i+index][j+index];

            }
        }
        //Formule Strassenovog algoritma
        Matrica p = AlgoritamZaMnozenje(A00, B01 - B11, index);

        Matrica q = AlgoritamZaMnozenje(A00 + A01, B11, index);

        Matrica r = AlgoritamZaMnozenje(A10 + A11, B00, index);

        Matrica s = AlgoritamZaMnozenje(A11, B10 - B00, index);

        Matrica t = AlgoritamZaMnozenje(A00 + A11, B00 + B11, index);

        Matrica u = AlgoritamZaMnozenje(A01 - A11, B10 + B11, index);

        Matrica v = AlgoritamZaMnozenje(A00 - A10, B00 + B01, index);

        Matrica C00 = (t + s + u - q);
        Matrica C01 = (p + q);
        Matrica C10 = (r + s);
        Matrica C11 = (t + p - r - v);

        //Dodavanje elemenata u matricu C
        for(int i = 0; i < index; i++)
        {
            for(int j = 0; j < index; j++)
            {
                C.matrix[i][j] = C00.matrix[i][j];
                C.matrix[i][j+index] = C01.matrix[i][j];
                C.matrix[i+index][j] = C10.matrix[i][j];
                C.matrix[i+index][j+index] = C11.matrix[i][j];

            }
        }
        //Clear-a sve pomocne matrice;
        A00.matrix.clear();
        A01.matrix.clear();
        A10.matrix.clear();
        A11.matrix.clear();

        B00.matrix.clear();
        B01.matrix.clear();
        B10.matrix.clear();
        B11.matrix.clear();

        p.matrix.clear();
        q.matrix.clear();
        r.matrix.clear();
        s.matrix.clear();
        t.matrix.clear();
        u.matrix.clear();
        v.matrix.clear();

        C00.matrix.clear();
        C01.matrix.clear();
        C10.matrix.clear();
        C11.matrix.clear();
    }
    return C;
}

//Determinanta matrice
double Matrica::Det()
{
    //Provjera da li je matrica kvadratna ili prazna mattrica
    try
    {
        if(!Kvadratna())
            throw "Nije moguce izracunati determinantu za ne kvadratnu matricu!";
        else if(this->matrix.empty())
            throw "Nije moguce izracunati determinantu prazne matrice!";
    }
    catch(const char poruka [])
    {
        cout<<poruka<<endl;
        throw;
    }

    Matrica temp = *this;
    double determinanta = 1;
    //Provjera da li je prvi element u matrici 0; Ako jeste mijenja ga sa redom ciji je prvi elemetn != 0 ako takav postoji;
    for(int i = 1; i < temp.GetRed(); i++)
    {
        if(temp.matrix[i-1][0] == 0 && temp.matrix[i][0] != 0 && i != 0)
        {
            swap(temp.matrix[0], temp.matrix[i]);
            determinanta *= -1;
            break;
        }
    }
    //Vektor nula koji ce se koristiti za provjeru
    vector<double> nule(temp.GetRed(), 0);
    //Gaussov metod eliminacije-svodjenje na gornju trougaonu matricu;
    for(int i = 0; i < temp.GetRed() - 1; i++)
    {
        for(int j = i+1; j < temp.GetRed(); j++)
        {
            double faktor;
            //Ako je element na dijagonali 0 faktor se postavlja na nulu kako bi se izbjeglo dijenje sa nulom u temp.matrix[j][i]/temp.matrix[i][i]
            if(temp.matrix[i][i] != 0)
                faktor = temp.matrix[j][i]/temp.matrix[i][i];
            else faktor = 0;
            for(int k = 0; k < temp.GetRed(); k++)
            {
                temp.matrix[j][k] -= temp.matrix[i][k] * faktor;
            }
            //Ako se desi da u redu imamo sve nule odmah vratimo nulu
            if(temp.matrix[j] == nule) return 0;
        }
        //Ako se na dijagonali pojavi 0 mijenjamo red sa redom ispod njega koji na toj poziciji ima broj razlicit od nule ako takav red postoji
        for(int l = 1; l < temp.GetRed(); l++)
        {

            if(temp.matrix[l][l] == 0)
            {
                for(int m = l; m < temp.GetRed(); m++)
                    if(temp.matrix[m][l] != 0)
                    {
                        swap(temp.matrix[m], temp.matrix[l]);
                        determinanta *= -1;
                        break;
                    }
            }
        }
    }

    //Mnozi elemente na dijagonali
    for(int i = 0; i < temp.GetRed(); i++)
    {
        determinanta *= temp.matrix[i][i];
    }

    if(determinanta == -0) return 0;
    return determinanta;
}

//Od poslane matrice (ako je kvadratna) pravi jedinicnu ili pravi jedinicnu matricu dimentija nxn
void Matrica::Jedinicna(int n)
{
    //Provjera da li je matrica kvadratna
    if(this->GetRed() != this->GetKolona() && n == 0)
        try
        {
            throw "Nije moguce napraviti jedinicnu matricu od ne kvadratne matrice!";
        }
        catch(const char poruka [])
        {
            cout<<poruka<<endl;
            throw;
        }
    //Ako n nije unesno onda se postavlja na red matrice
    if(n == 0) n = this->GetRed();

    Matrica I(n, n);

    //Dodavanje jedinica na dijagonalu nove matrice
    for(int i = 0; i < n; i++) I.matrix[i][i] = 1;

    this->matrix = I.matrix;
}

//Transponuje matricu
void Matrica::Transponuj()
{
    Matrica transponovana(this->GetKolona(), this->GetRed());

    for(int i = 0; i < this->GetKolona(); i++)
    {
        for(int j = 0; j < this->GetRed(); j++)
        {
            transponovana.matrix[i][j] = this->matrix[j][i];
        }
    }

    this->matrix = transponovana.matrix;
}

//Inverzna matrica - Gauss-Jordanovom metodom
void Matrica::Inverse()
{
    //Provjera da li je matrica kvadratna i da li je determinanta razlicita od nule
    try
    {
        if(this->GetKolona() != this->GetRed())
            throw "Nije moguce izracunati inverz ne kvadratne matrice!";
        else if(this->Det() == 0)
            throw "Ne postoji inverzna matrica date matrice";
    }
    catch(const char poruka [])
    {
        cout<<poruka<<endl;
        throw;
    }

    Matrica jedinicna(this->GetRed(), this->GetKolona());
    //Jedinicna matrica koja ce postati inverzna
    jedinicna.Jedinicna();

    //Provjera da li je prvi element u matrici 0; Ako jeste mijenja ga sa redom ciji je prvi elemetn != 0 ako takav postoji;
    for(int i = 1; i < this->GetRed(); i++)
    {
        if(this->matrix[i-1][0] == 0 && this->matrix[i][0] != 0 && i != 0)
        {
            swap(this->matrix[0], this->matrix[i]);
            swap(jedinicna.matrix[0], jedinicna.matrix[i]);
            break;
        }
    }

    //Svodjenje na gornju trougaonu
    for(int i = 0; i < this->GetRed() - 1; i++)
    {
        for(int j = i+1; j < this->GetRed(); j++)
        {
            double faktor = this->matrix[j][i] / this->matrix[i][i];

            for(int k = 0; k < this->GetRed(); k++)
            {
                this->matrix[j][k] -= this->matrix[i][k] * faktor;
                jedinicna.matrix[j][k] -= jedinicna.matrix[i][k] * faktor;
            }
        }

        //Ako se na dijagonali pojavi 0 mijenjamo red sa redom ispod njega koji na toj poziciji ima broj razlicit od nule ako takav red postoji
        for(int l = 1; l < this->GetRed(); l++)
        {

            if(this->matrix[l][l] == 0)
            {
                for(int m = l; m < this->GetRed(); m++)
                    if(this->matrix[m][l] != 0)
                    {
                        swap(this->matrix[m], this->matrix[l]);
                        swap(jedinicna.matrix[m], jedinicna.matrix[l]);
                        break;
                    }
            }
        }
    }

    //Postavljanje elemenata na dijagonali na 1
    for(int i = 0; i < this->GetRed(); i++)
    {
        double faktor = this->matrix[i][i];
        for(int j=0; j<this->GetRed(); j++)
        {
            if(this->matrix[i][j] != 0)
                this->matrix[i][j] /= faktor;
            if(jedinicna.matrix[i][j] != 0)
                jedinicna.matrix[i][j] /= faktor;
        }
    }

    //Svodenje na donju trougaonu gdje se faktori spasavaju u vektor
    vector <double> _faktori;
    for(int i = this->GetRed() - 2; i >= 0; i--)
    {
        for(int j = this->GetRed() - 1; j >= 0; j--)
        {
            double faktor;
            if(i + 1 == j)
            {
                for(int k = i; k >= 0; k--)
                {
                    faktor = this->matrix[k][j] / matrix[i+1][j];
                    _faktori.push_back(faktor);
                    this->matrix[k][j] -= this->matrix[i+1][j] * faktor;
                }
            }

        }
    }

    //Primjena operacija koje su koristene prilikom svodjenja na donju trougaonu na jedincnu matricu (zbog toga mi je trebao vektor faktora sa kojim se dijelilo)
    int index = 0;
    for(int i = this->GetRed() - 2; i >= 0; i--)
    {
        for(int k = i; k >= 0; k--)
        {
            for(int j = 0; j < this->GetRed(); j++)
            {
                jedinicna.matrix[k][j] -= jedinicna.matrix[i+1][j] * _faktori[index];
            }
            index++;
        }
    }

    this->matrix = jedinicna.matrix;
}

//Sabiranje matrica
Matrica operator+(const Matrica &lhs, const Matrica &rhs)
{
    //Provjera da li su matrice istih dimenzija
    try
    {
        if(lhs.GetRed() != rhs.GetRed() || lhs.GetKolona() != rhs.GetKolona())
        {
            throw "Nije moguce sabirati matrice razlicitih dimenzija!";
        }
    }
    catch(const char poruka [])
    {
        cout<<poruka<<endl;
        throw;
    }
    Matrica zbir(lhs.GetRed(), lhs.GetKolona());
    zbir.matrix = lhs.matrix;

    for(int i = 0; i < lhs.GetRed(); i++)
    {
        for(int j = 0; j < lhs.GetKolona(); j++)
        {
            zbir.matrix[i][j] += rhs.matrix[i][j];
        }
    }

    return zbir;
}

//Oduzimanje matrica
Matrica operator-(const Matrica &lhs, const Matrica &rhs)
{
    //Provjera da li su dimenzije matrica iste
    try
    {
        if(lhs.GetRed() != rhs.GetRed() || lhs.GetKolona() != rhs.GetKolona())
        {
            throw "Nije moguce oduzimati matrice razlicitih dimenzija!";
        }
    }
    catch(const char poruka [])
    {
        cout<<poruka<<endl;
        throw;
    }
    Matrica razlika(lhs.GetRed(), lhs.GetKolona());
    razlika.matrix = lhs.matrix;

    for(int i = 0; i < lhs.GetRed(); i++)
    {
        for(int j = 0; j < lhs.GetKolona(); j++)
        {
            razlika.matrix[i][j] -= rhs.matrix[i][j];
        }
    }

    return razlika;
}

//Mnozenje matrice sa brojem
Matrica operator*(double faktor, const Matrica &rhs)
{
    Matrica proizvod(rhs.GetRed(), rhs.GetKolona());
    proizvod.matrix = rhs.matrix;

    for(int i = 0; i < rhs.GetRed(); i++)
    {
        for(int j = 0; j < rhs.GetKolona(); j++)
        {
            proizvod.matrix[i][j] *= faktor;
        }
    }
    return proizvod;
}

//Mnozenje matrice sa brojem
Matrica operator*(const Matrica &lhs, double faktor)
{
    Matrica proizvod(lhs.GetRed(), lhs.GetKolona());
    proizvod.matrix = lhs.matrix;

    for(int i = 0; i < lhs.GetRed(); i++)
    {
        for(int j = 0; j < lhs.GetKolona(); j++)
        {
            proizvod.matrix[i][j] *= faktor;
        }
    }
    return proizvod;
}

//Mnozenje matrica
Matrica operator*(const Matrica &lhs, const Matrica &rhs)
{
    //Da li je moguce mnozenje
    try
    {
        if(lhs.GetKolona() != rhs.GetRed()) throw "Pogresne dimenzije matrice!";
    }
    catch(const char poruka [])
    {
        cout<<poruka<<endl;
        throw;
    }

    if(lhs.GetRed() == lhs.GetKolona() == rhs.GetRed() == rhs.GetKolona() == 1) return AlgoritamZaMnozenje(lhs, rhs, 1);
    else
    {
        //Da li su dimenzije matrice stepen broja 2
        int red1 = lhs.GetRed() & (lhs.GetRed() - 1);
        int kolona1 = lhs.GetKolona() & (lhs.GetKolona() - 1);
        int red2 = rhs.GetRed() & (rhs.GetRed() - 1);
        int kolona2 = rhs.GetKolona() & (rhs.GetKolona() - 1);

        //Ako nisu stepen broja dva, postavljaju se na najblizi broj vec od dimenzije koji je stepen broja dva
        int rez;
        if(red1 != 0)
        {
            rez = 1;

            while (rez < lhs.GetRed()) rez <<= 1;
            red1 = rez;
        }
        else red1 = lhs.GetRed();
        if(kolona1 != 0)
        {
            rez = 1;

            while (rez < lhs.GetKolona()) rez <<= 1;
            kolona1 = rez;
        }
        else kolona1 = lhs.GetKolona();
        if(red2 != 0)
        {
            rez = 1;

            while (rez < rhs.GetRed()) rez <<= 1;
            red2 = rez;
        }
        else red2 = rhs.GetRed();
        if(kolona2 != 0)
        {
            rez = 1;

            while (rez < rhs.GetKolona()) rez <<= 1;
            kolona2 = rez;
        }
        else kolona2 = rhs.GetKolona();
        int dimenzija = max(max(red1, kolona1), max(red2, kolona2));

        //Dodavanje nula kako bi matrice bile kvadratne sa dimenzijom stepana broja 2
        Matrica A(dimenzija, dimenzija);
        for(int i = 0; i < lhs.GetRed(); i++)
        {
            for(int j = 0; j < lhs.GetKolona(); j++)
            {
                A.matrix[i][j] = lhs.matrix[i][j];
            }
        }
        Matrica B(dimenzija, dimenzija);
        for(int i = 0; i < rhs.GetRed(); i++)
        {
            for(int j = 0; j < rhs.GetKolona(); j++)
            {
                B.matrix[i][j] = rhs.matrix[i][j];
            }
        }
        //Strassen algoritam za mnozenje matrica
        A = AlgoritamZaMnozenje(A, B, dimenzija);

        Matrica rezultat(lhs.GetRed(), rhs.GetKolona());
        //Prepisivanje rezultata u novi matricu odgovarajucih dimenzija (kako bi se rijesili nula koje smo dodali)
        for(int i = 0; i < lhs.GetRed(); i++)
        {
            for(int j = 0; j < rhs.GetKolona(); j++)
            {
                rezultat.matrix[i][j] = A.matrix[i][j];
            }
        }
        return rezultat;
    }
}

//Operator +=
void Matrica::operator+=(Matrica &rhs)
{
    *this = *this + rhs;
}

//Operator *=
void Matrica::operator*=(Matrica &rhs)
{
    *this = *this * rhs;
}

//Stepenovanje
Matrica operator^(const Matrica &lhs, int stepen)
{
    //Prvojera da li je matrica kvadratna i da li je stepen manji od -1
    try
    {
        if(lhs.GetRed() != lhs.GetKolona()) throw "Nije moguce stepenovati ne kvadratnu matricu!";
        if(stepen < -1) throw "Stepen matrice mora biti pozitivan broj ili -1!";
    }
    catch(const char poruka [])
    {
        cout<<poruka<<endl;
        throw;
    }
    Matrica rezultat(lhs);

    //Ako je stepen -1 vraca inverznu matricu;
    if(stepen == -1)
    {
        rezultat.Inverse();
        return rezultat;
    }
    //Ako je stepen 0 vraca jedinicnu matricu
    else if(stepen == 0)
    {
        rezultat.Jedinicna();
        return rezultat;
    }
    //Uzastopno mnozenje
    for(int i = 0; i < stepen - 1; i++)
    {
        rezultat = rezultat * lhs;
    }
    return rezultat;
}

//Ispis
ostream& operator<<(ostream& ispis, const Matrica& matrica)
{
    for(int i = 0; i < matrica.GetRed(); i++)
    {
        for(int j = 0; j < matrica.GetKolona(); j++)
        {
            if(matrica.matrix[i][j] >= 0) ispis << " " << matrica.matrix[i][j] << " ";
            else ispis << matrica.matrix[i][j] << " ";
        }
        ispis << endl;
    }
    return ispis;
}

//Operator >>
istream& operator>>(istream& unos, Matrica& m)
{
    stack<char> zagrade_i_operacije;
    stack<Matrica> matrice;
    char predhodni = '(';

    while(unos.peek() != '\n')
    {
        char znak = unos.peek();
        //Provjerava da li je poslije znaka [ matrica
        if(znak == '[')
        {
            try
            {
                if(DaLiJeZatvorena(predhodni))
                    throw "Ne moze matrica nakon zatvorene zagrade";
                unos.get();
                //String u koji se stvljaju svi elementi izmedju []
                string matrica = " ";
                while(unos.peek() != ']')
                {
                    //Ako dodjemo do \n i nismo naisli na zatvroenu zagradu ] baca se izuzetak
                    if(unos.peek() == '\n') throw "Pogresan unos, zagrada [ nikada nije zatvorena!";
                    znak = unos.get();
                    matrica += znak;
                }
                matrica += " ";
                //Poziva se funkcija da li je matrica koja vraca bool
                if(DaLiJeMatrica(matrica))
                {
                    //Ako je true pravi matricu i stavlja je na stack
                    Matrica temp = NapraviMatricu(matrica);
                    matrice.push(temp);
                }
                else throw "Pogresan unos!";
                znak = unos.get();
                predhodni = ']';
            }
            catch(const char poruka [])
            {
                cout<<poruka<<endl;
                throw;
            }
        }
        //Da li je znak ( ili {
        else if(DaLiJeOtvorena(znak))
        {
            if(DaLiJeZatvorena(predhodni) || DaLiJeCifra(predhodni))
                throw "Ne moze ici otvorena zagrada nakon zatvorene zagrade ili broja";
            zagrade_i_operacije.push(znak);
            predhodni = unos.get();
        }
        //Da li je znak ) ili }
        else if(DaLiJeZatvorena(znak))
        {
            if(DaLiJeOperacija(predhodni) || DaLiJeOtvorena(predhodni))
                try
                {
                    throw "Ne moze ici zatvorena zagrada nakon operacije ili otvorene zagrade";
                }
                catch(const char poruka [])
                {
                    cout<<poruka<<endl;
                    throw;
                }
            //Dok god je stack zagrada i operacija ne prazan i dok je na vrhu njega operacija izvrsava operaciju
            while(!zagrade_i_operacije.empty() && DaLiJeOperacija(zagrade_i_operacije.top()))
            {
                IzvrsiOperaciju(matrice,zagrade_i_operacije);
            }
            //Ako je stack prazan ili na vrhu nije otvorena zagrada poslije zatvorene baca izuzetak
            if(zagrade_i_operacije.empty() || zagrade_i_operacije.top() != OtvorenaZagrada(znak))
                try
                {
                    throw "Zagrade nisu u dobrom poretku";
                }
                catch(const char poruka [])
                {
                    cout<<poruka<<endl;
                    throw;
                }
            else zagrade_i_operacije.pop();
            predhodni = unos.get();
        }
        //Da li je znak +,-,* ili ^
        else if(DaLiJeOperacija(znak))
        {
            //Ako imamo slucaj ^-1 ili ^-neki broj
            if(znak == '-' &&  predhodni == '^')
            {
                unos.get();
                char temp = unos.peek();
                //Ako je poslije ^ neki znak koji nije cifra ili ako je razlicito od 1 a na vrhu stacka matrica je matrica a ne broj baca izuzetak
                if((!DaLiJeCifra(temp) || temp != '1') && matrice.top().da_li_je_matrica == true)
                    try
                    {
                        throw "Eksponent matrice moze biti samo pozitivan broj i -1";
                    }
                    catch(const char poruka [])
                    {
                        cout<<poruka<<endl;
                        throw;
                    }
                //Ako je na vrhu stacka matrica dodje se broj -1 u obliku matrice 1x1 na stack
                if(matrice.top().da_li_je_matrica == true)
                {
                    Matrica broj(1, 1, -1);
                    broj.da_li_je_matrica = false;
                    matrice.push(broj);

                    predhodni = temp;
                    znak = unos.get();
                }
                //Ako je na vrhu stacka broj onda poslije ^ moze ici bilo koji negativan broj jer se izvrsava stepenovanje broja brojem
                else if(matrice.top().da_li_je_matrica == false)
                {
                    double stepen;
                    unos >> stepen;
                    //Posto ne kupim minus dodajem -broj u matricu
                    Matrica broj(1,1,-stepen);
                    //Posto dodajemo broj kao matricu 1x1 da_li_je_matrica se postavlja na false
                    broj.da_li_je_matrica = false;
                    matrice.push(broj);
                    predhodni = temp;
                    znak = temp;
                }
                //Ako stack zagrada i operacija nije prazan i ako je na vrhu tog stacka operacija sa vecim prioritetom izvrsavamo operaciju
                while(!zagrade_i_operacije.empty() && DaLiJeOperacija(zagrade_i_operacije.top()) && PrioritetOperacije(znak) <= PrioritetOperacije(zagrade_i_operacije.top()))
                {
                    IzvrsiOperaciju(matrice, zagrade_i_operacije);
                }
            }
            //Ako je broj - poslije otvorene zagrade na stack se dodaje matrica 1x1 koja predstavlja broj 0
            else if(znak == '-' &&  DaLiJeOtvorena(predhodni))
            {
                unos.get();
                char temp = unos.peek();
                if(!DaLiJeCifra(temp) && temp != '[')
                    try
                    {
                        throw "Pogresno unesen znak -";
                    }
                    catch(const char poruka [])
                    {
                        cout<<poruka<<endl;
                        throw;
                    }
                Matrica broj(1, 1, 0);
                broj.da_li_je_matrica = false;
                matrice.push(broj);
                //Ako stack zagrada i operacija nije prazan i ako je na vrhu tog stacka operacija sa vecim prioritetom izvrsavamo operaciju
                while(!zagrade_i_operacije.empty() && DaLiJeOperacija(zagrade_i_operacije.top()) && PrioritetOperacije(znak) <= PrioritetOperacije(zagrade_i_operacije.top()))
                    IzvrsiOperaciju(matrice, zagrade_i_operacije);
                zagrade_i_operacije.push(znak);
                predhodni = temp;
            }
            //Provjeravamo da li nakon otvorene zagrade ide neka druga operacija osim -
            else if(DaLiJeOperacija(predhodni) || DaLiJeOtvorena(predhodni))
            {
                try
                {
                    throw "Ne moze operacija nakon otvorene zagrade ili druge operacije";
                }
                catch(const char poruka [])
                {
                    cout<<poruka<<endl;
                    throw;
                }
            }
            else
            {
                //Ako stack zagrada i operacija nije prazan i ako je na vrhu tog stacka operacija sa vecim prioritetom izvrsavamo operaciju
                while(!zagrade_i_operacije.empty() && DaLiJeOperacija(zagrade_i_operacije.top()) && PrioritetOperacije(znak) <= PrioritetOperacije(zagrade_i_operacije.top()))
                    IzvrsiOperaciju(matrice, zagrade_i_operacije);
                zagrade_i_operacije.push(znak);
                predhodni = unos.get();
            }

        }
        //Provjera da li je znak neka cifra
        else if(DaLiJeCifra(znak))
        {
            //Ako je prije bila zatvorena zagrada baca se izuzetak
            if(DaLiJeZatvorena(predhodni))
                try
                {
                    throw "Ne moze broj nakon zatvorene zagrade";
                }
                catch(const char poruka [])
                {
                    cout<<poruka<<endl;
                    throw;
                }
            //Kupimo broj sa unosa
            double b;
            unos >> b;
            //Ako je predhodni znak bio I ne dodajemo broj nego jedinicnu matricu dimenzija toga broja
            if(predhodni == 'I')
            {
                Matrica jedinicna;
                jedinicna.Jedinicna(b);
                matrice.push(jedinicna);
            }
            //U suprotnom dodajemo broj kao matricu 1x1
            else
            {
                Matrica broj(1, 1, b);
                broj.da_li_je_matrica = false;
                matrice.push(broj);
                predhodni = '0';
            }

        }
        //Ako je znak T provjeravamo sta je predhodni
        else if(znak == 'T')
        {
            //Ako predhodni nije ^ baca se izuzetak
            if(znak == 'T' && predhodni != '^')
                try
                {
                    throw "Znak T moze slijediti samo nakon operacije ^";
                }
                catch(const char poruka [])
                {
                    cout<<poruka<<endl;
                    throw;
                }
            matrice.top().Transponuj();
            //Posto smo transponovali uklonimo operaciju ^ sa stacka
            zagrade_i_operacije.pop();
            predhodni = unos.get();
        }
        //Ako je znak I i predhodni nije operacija ili otvorena zagrada baca se izuzetak
        else if(znak == 'I')
        {
            if(!DaLiJeOperacija(predhodni) && !DaLiJeOtvorena(predhodni))
                try
                {
                    throw "Jedinicna matrica moze ici samo nakon operacije ili otvorene zagrade";
                }
                catch(const char poruka [])
                {
                    cout<<poruka<<endl;
                    throw;
                }
            predhodni = unos.get();
        }
        //Ako nije ni jedan od uslova iznad baca se izuzetak
        else
            try
            {
                throw "Nedozvoljen znak";
            }
            catch(const char poruka [])
            {
                cout<<poruka<<endl;
                throw;
            }
    }
    //Dok god stack zagrada i operacija nije prazan i dok god je na vrhu tog stacka operacija ona se izvrsava
    while(!zagrade_i_operacije.empty())
    {
        if(!DaLiJeOperacija(zagrade_i_operacije.top()))
            try
            {
                throw "Fali zatvorenih zagrada";
            }
            catch(const char poruka [])
            {
                cout<<poruka<<endl;

                throw;
            }
        IzvrsiOperaciju(matrice, zagrade_i_operacije);
    }
    //Ako stack matrica ima samo jedan element baca se izuzetak
    if(matrice.size() != 1)
        try
        {
            throw "Izraz nije dobro napisan";
        }
        catch(const char poruka [])
        {
            cout<<poruka<<endl;

            throw;
        }
    else m = matrice.top();

    unos.ignore(10000,'\n');

    return unos;
}

#endif // MATRICA_CPP
