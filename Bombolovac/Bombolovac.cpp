#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

const int SIZE = 5;

void prikaziPolje(const vector<vector<char>>& polje) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			cout << polje[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void postaviMine(vector<vector<char>>& polje, int brojMina) {
	srand(time(0));
	int postavljeneMine = 0;

	while (postavljeneMine < brojMina) {
		int redak = rand() % SIZE;
		int stupac = rand() % SIZE;

		if (polje[redak][stupac] != '*') {
			polje[redak][stupac] = '*';
			postavljeneMine++;
		}
	}
}

bool provjeriUnos(int redak, int stupac) {
	return redak >= 0 && redak < SIZE&& stupac >= 0 && stupac < SIZE;
}

bool otkrijPolje(vector<vector<char>>& polje, int redak, int stupac) {
	if (!provjeriUnos(redak, stupac)) {
		return false;
	}

	if (polje[redak][stupac] == '*') {
		return false;
	}

	polje[redak][stupac] = '#';
	return true;
}

void spremiStanjeIgre(const vector<vector<char>>& polje, const string& imeDatoteke) {
	ofstream datoteka(imeDatoteke, ios::binary);
	if (datoteka.is_open()) {
		for (int i = 0; i < SIZE; i++) {
			datoteka.write(reinterpret_cast<const char*>(polje[i].data()), SIZE);
		}
		cout << "Stanje igre je spremljeno u binarnu datoteku." << endl;
	}
	else {
		cout << "Nemoguce spremiti stanje igre." << endl;
	}
}

void ucitajStanjeIgre(vector<vector<char>>& polje, const string& imeDatoteke) {
	ifstream datoteka(imeDatoteke, ios::binary);
	if (datoteka.is_open()) {
		for (int i = 0; i < SIZE; i++) {
			datoteka.read(reinterpret_cast<char*>(polje[i].data()), SIZE);
		}
		cout << "Stanje igre je ucitano iz binarne datoteke." << endl;
	}
	else {
		cout << "Nemoguce ucitati stanje igre." << endl;
	}
}

int main() {
	vector<vector<char>> polje(SIZE, vector<char>(SIZE, '#'));
	vector<vector<char>> otkrivenoPolje(SIZE, vector<char>(SIZE, ' '));

	int brojMina;
	cout << "Unesite broj mina: ";
	cin >> brojMina;

	postaviMine(polje, brojMina);

	int redak, stupac;
	char odabir;

	while (true) {
		prikaziPolje(otkrivenoPolje);
		cout << "Odaberite redak (0-" << SIZE - 1 << "): ";
		cin >> redak;
		cout << "Odaberite stupac (0-" << SIZE - 1 << "): ";
		cin >> stupac;

		if (!provjeriUnos(redak, stupac)) {
			cout << "Pogresan unos! Molimo unesite ispravne vrijednosti." << endl;
			continue;
		}

		if (!otkrijPolje(polje, redak, stupac)) {
			cout << "BOMBA! Igrac 1 je pobjednik!" << endl;
			break;
		}

		otkrivenoPolje[redak][stupac] = ' ';

		cout << "Zelite li spremiti trenutno stanje igre? (D/N): ";
		cin >> odabir;

		if (odabir == 'D' || odabir == 'd') {
			string imeDatoteke;
			cout << "Unesite ime datoteke: ";
			cin >> imeDatoteke;
			spremiStanjeIgre(polje, imeDatoteke);
		}
		else if (odabir == 'N' || odabir == 'n') {
			cout << "Zelite li ucitati prethodno spremljeno stanje igre? (D/N): ";
			cin >> odabir;
			if (odabir == 'D' || odabir == 'd') {
				string imeDatoteke;
				cout << "Unesite ime datoteke: ";
				cin >> imeDatoteke;
				ucitajStanjeIgre(polje, imeDatoteke);
			}
		}
	}

	return 0;
}