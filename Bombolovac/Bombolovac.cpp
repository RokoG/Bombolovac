#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <random>

using namespace std;

const int MAX_VELICINA_PLOCE = 10;
const char SKRIVENO = '#';
const char BOMBA = '*';

char ploca[MAX_VELICINA_PLOCE][MAX_VELICINA_PLOCE];
bool otkriveno[MAX_VELICINA_PLOCE][MAX_VELICINA_PLOCE];
bool oznaceno[MAX_VELICINA_PLOCE][MAX_VELICINA_PLOCE];
int velPloce;
int brojBombi;

void inicijalizacijaPloce()
{
    for (int i = 0; i < velPloce; ++i)
    {
        for (int j = 0; j < velPloce; ++j)
        {
            ploca[i][j] = SKRIVENO;
            otkriveno[i][j] = false;
            oznaceno[i][j] = false;
        }
    }
}

void postaviBombe(int brojBombi)
{
    int count = 0;
    while (count < brojBombi)
    {
        int x = rand() % velPloce;
        int y = rand() % velPloce;

        if (ploca[x][y] != BOMBA)
        {
            ploca[x][y] = BOMBA;
            ++count;
        }
    }
}

void prikaziPlocu()
{
    cout << endl;
    for (int i = 0; i < velPloce; ++i)
    {
        for (int j = 0; j < velPloce; ++j)
        {
            if (otkriveno[i][j])
            {
                cout << ploca[i][j] << ' ';
            }
            else if (oznaceno[i][j])
            {
                cout << "F ";
            }
            else
            {
                cout << SKRIVENO << ' ';
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool jeDobraPozicija(int x, int y)
{
    return (x >= 0 && x < velPloce && y >= 0 && y < velPloce);
}

bool igrajPonovo()
{
    char izbor;
    cout << "Zelite li ponovno igrati? (D/N): ";
    cin >> izbor;
    return (izbor == 'D' || izbor== 'd');
}

void otkrijPolje(int x, int y)
{
    if (!jeDobraPozicija(x, y) || otkriveno[x][y] || oznaceno[x][y])
    {
        return;
    }

     otkriveno[x][y] = true;

    if (ploca[x][y] == BOMBA)
    {
        cout << "Kraj igre! Pogodio si bombu." << endl;
        
        if (igrajPonovo())
        {
            inicijalizacijaPloce();
            postaviBombe(brojBombi);
            return;
        }
        else
        {
            exit(0);
        }
    }

    int brojac = 0;
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            int nx = x + dx;
            int ny = y + dy;

            if (jeDobraPozicija(nx, ny) && ploca[nx][ny] == BOMBA)
            {
                brojac++;
            }
        }
    }

    if (brojac > 0)
    {
        ploca[x][y] = '0' + brojac;
    }
    else
    {
        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                int nx = x + dx;
                int ny = y + dy;

                if (jeDobraPozicija(nx, ny) && !otkriveno[nx][ny])
                {
                    otkrijPolje(nx, ny);
                }
            }
        }
    }
}

void oznaciPolje(int x, int y)
{
    if (jeDobraPozicija(x, y))
    {
        oznaceno[x][y] = !oznaceno[x][y];
    }
}

bool jeIgraGotova()
{
    for (int i = 0; i < velPloce; ++i)
    {
        for (int j = 0; j < velPloce; ++j)
        {
            if (!otkriveno[i][j] && ploca[i][j] != BOMBA)
            {
                return false;
            }
        }
    }
    return true;
}

void spremiIgru(const string& filename)
{
    ofstream file(filename, ios::binary);

    file.write(reinterpret_cast<const char*>(&velPloce), sizeof(velPloce));
    file.write(reinterpret_cast<const char*>(ploca), sizeof(ploca));
    file.write(reinterpret_cast<const char*>(otkriveno), sizeof(otkriveno));
    file.write(reinterpret_cast<const char*>(oznaceno), sizeof(oznaceno));

    file.close();

    cout << "Igra je uspjesno spremljena." << endl;
}

void ucitajIgru(const string& filename)
{
    ifstream file(filename, ios::binary);

    if (!file)
    {
        cout << "Nije moguce otvoriti datoteku." << endl;
        return;
    }

    file.read(reinterpret_cast<char*>(&velPloce), sizeof(velPloce));
    file.read(reinterpret_cast<char*>(ploca), sizeof(ploca));
    file.read(reinterpret_cast<char*>(otkriveno), sizeof(otkriveno));
    file.read(reinterpret_cast<char*>(oznaceno), sizeof(oznaceno));

    file.close();

    cout << "Igra je uspjesno ucitana." << endl;
}

void ispisiMeni()
{
    cout << "Meni:" << endl;
    cout << "1. Otkrij polje" << endl;
    cout << "2. Oznaci polje" << endl;
    cout << "3. Spremi igru" << endl;
    cout << "4. Ucitaj igru" << endl;
    cout << "5. Izlaz" << endl;
    cout << "Unesite svoj izbor: ";
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "Dobrodosli u BOMBOLOVAC!!!!" << endl;

    while (true)
    {
        cout << "Meni:" << endl;
        cout << "1. Nova igra" << endl;
        cout << "2. Ucitaj igru" << endl;
        cout << "3. Izlaz" << endl;
        cout << "Unesite svoj izbor: ";

        int izbor1;
        cin >> izbor1;

        if (izbor1 == 1)
        {
            string imeIgraca;
            cout << "Unesite ime igraca: ";
            cin.ignore();
            getline(cin, imeIgraca);
            ofstream imeIgracaFile("ime_igraca.txt");
            if (imeIgracaFile.is_open())
            {
                imeIgracaFile << imeIgraca;
                imeIgracaFile.close();
                cout << "Ime igraca je uspjesno spremljeno." << endl;
            }
            else
            {
                cout << "Nije moguce otvoriti datoteku." << endl;
            }

            cout << "Unesite velicinu ploce (4 - 10): ";
            cin >> velPloce;

            if (velPloce < 4 || velPloce > 10)
            {
                cout << "Neispravan unos. Postavljanje velicine ploce na 5." << endl;
                velPloce = 5;
            }

            cout << "Unesite broj bombi: ";
            cin >> brojBombi;

            inicijalizacijaPloce();
            postaviBombe(brojBombi);

            cout << "Nova igra je pokrenuta. Sretno, " << imeIgraca << "!" << endl;
        }
        else if (izbor1 == 2)
        {
            string spremiFile;
            cout << "Unesite ime datoteke koju zelite ucitati: ";
            cin >> spremiFile;
            ucitajIgru(spremiFile);
        }
        else if (izbor1 == 3)
        {
            cout << "Dovidjenja!" << endl;
            break;
        }
        else
        {
            cout << "Neispravan unos. Molimo pokusajte ponovo." << endl;
        }

        while (!jeIgraGotova())
        {
            prikaziPlocu();
            ispisiMeni();

            cin >> izbor1;

            if (izbor1 == 1)
            {
                int x, y;
                cout << "Unesite koordinate (x, y): ";
                cin >> x >> y;
                otkrijPolje(x, y);
            }
            else if (izbor1 == 2)
            {
                int x, y;
                cout << "Unesite koordinate (x, y): ";
                cin >> x >> y;
                oznaciPolje(x, y);
            }
            else if (izbor1 == 3)
            {
                string spremiFile;
                cout << "Unesite ime datoteke koju zelite spremiti: ";
                cin >> spremiFile;
                spremiIgru(spremiFile);
            }
            else if (izbor1 == 4)
            {
                string ucitajFile;
                cout << "Unesite ime datoteke koju zelite ucitati: ";
                cin >> ucitajFile;
                ucitajIgru(ucitajFile);
            }
            else if (izbor1 == 5)
            {
                cout << "Izlaz iz igre..." << endl;
                break;
            }
            else
            {
                cout << "Neispravan unos. Molimo pokusajte ponovo." << endl;
            }
        }

        if (jeIgraGotova())
        {
            cout << "Pobijedili ste! Igra je zavrsena!" << endl;

            if (igrajPonovo())
            {
                inicijalizacijaPloce();
                postaviBombe(brojBombi);
                continue;
            }
            else
            {
                break;
            }
        }

        if (!igrajPonovo())
        {
            cout << "Izlaz iz igre..." << endl;
            break;
        }
    }

    return 0;
}

