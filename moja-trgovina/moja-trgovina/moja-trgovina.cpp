#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
using namespace std;
int main()
{
	unsigned long long int *barkod = new unsigned long long int[2000];
	string *naziv = new string[2000];
	double* cijena = new double[2000];
	int izbor, brArtikla=0;
	while (1)
	{
		system("cls");
		cout << "Moja Trgovina" << endl;
		cout << "1. Unos novog artikla" << endl;
		cout << "2. ispis svih podataka" << endl;
		cout << "3. inventura" << endl;
		cout << "4. pretraga prema nazivu artikla" << endl;
		cout << "5. brisanje artikla" << endl;
		cout << "6. izmjena podatka artikla" << endl;
		cout << "7. izlaz iz programa" << endl;
		cout << "Upisite vas izbor:" << endl;
		cin >> izbor;
		cout << endl;
		if (izbor == 1)
		{
			cout << "Unesite barkod proizvoda: ";
			cin >> barkod[brArtikla];
			cout << "unesite naziv proizvoda: ";
			cin.ignore();
				getline(cin, naziv[brArtikla]);
			cout << "unesite cijenu artikla: ";
			cin >> cijena[brArtikla];
			brArtikla++;

		}
		else if (izbor == 2)
		{
			for (int i = 0; i < brArtikla; i++)
			{
				cout << "Barkod "<< i+1 << ". proizvoda je " << barkod[i] << endl;
				cout << "Naziv " << i+1 << ". proizvoda je " << naziv[i] << endl;
				cout << "Cijena " << i+1 << ". proizvoda je " << cijena[i] << " kn"<< endl;
				cout << endl << endl;
			}
			system("pause");
		}
		else if (izbor == 3)
		{
			cout << "Zbroj svih cijena artikla je: " << accumulate(cijena, cijena + brArtikla, 0) << " kn" << endl;
			cout << "Naziv artikla s najmanjom cijenom: " << naziv[min_element(cijena, cijena + brArtikla) - cijena] << endl;
			cout << "Broj artikla s tom najmanjom cijenom: " << count(cijena, cijena + brArtikla, *min_element(cijena, cijena + brArtikla)) << endl;
			cout << "Broj artikla koji imaju cijenu manju od 500 kn: " << count_if(cijena, cijena + brArtikla, [] (double a) {return a < 500; }) << endl;
			
			system("pause");
		}
		else if (izbor == 4)
		{
			string trazeni;
			bool Postoji = false;
			cout << "Unesite ime trazenog artikla: ";
			cin.ignore();
			getline(cin, trazeni);
			for (int i = 0; i < brArtikla; i++)
			{
				if (trazeni == naziv[i])
					Postoji = true;
			}
			if (Postoji)
			{
				for (int i = 0; i < brArtikla; i++)
				{
					if (trazeni == naziv[i])
					{
						cout << "Barkod trazenog artikla: " << barkod[i] << endl;
						cout << "Cijena trazenog artikla: " << cijena[i] << endl;
					}
				}
			}
			else
			{
				cout << "Nema takvog artikla";
			}
			system("pause");
		}
		else if (izbor == 5)
		{

		}
		else if (izbor == 6)
		{

		}
		else
		{
			cout << "Krivi unos";
			break;
			return 0;
		}
	}
}