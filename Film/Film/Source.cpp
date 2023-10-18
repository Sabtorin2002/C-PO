#include<iostream>
#include<string>
#include<string.h>
#include<fstream>
#include<vector>
#include<map>

using namespace std;

class InvalidIndex :public exception
{

};

class Film
{
private:
	float pret;
	char* nume;
	int* vizualiziari;
	int nrVizualizari;
	string colectie;
	
	const int id=0;
	static string regizor;
public:

	Film():id(1)
	{
		this->pret = 0;
		this->nume = new char[strlen("N/A") + 1];
		strcpy(this->nume, "N/A");
		this->vizualiziari = nullptr;
		this->nrVizualizari = 0;
		this->colectie = "";
	}

	Film(int id, float pret, const char* nume, int* vizualizari,int nrVizualizari, string colectie) :id(id)
	{
		this->pret = pret;
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		
		if (vizualizari != nullptr && nrVizualizari > 0)
		{
			this->vizualiziari = new int[nrVizualizari];
			for (int i = 0; i < nrVizualizari; i++)
			{
				this->vizualiziari[i] = vizualizari[i];
			}
			this->nrVizualizari = nrVizualizari;
		}

		else
		{
			this->vizualiziari = nullptr;
			this->nrVizualizari = 0;
		}
		this->colectie = colectie;
	}

	char* getNume()
	{
		if (nume != nullptr)
		{
			char* copie = new char[strlen(nume) + 1];
			strcpy(copie, nume);

			return copie;
		}
		else
			return nullptr;
	}

	int getNrVizualiari()
	{
		return this->nrVizualizari;
	}

	int* getVizualizari()
	{
		if (vizualiziari != nullptr)
		{
			int* copie = new int[nrVizualizari];
			for (int i = 0; i < nrVizualizari; i++)
			{
				copie[i] = vizualiziari[i];
			}

			return copie;
		}
		else
			return nullptr;
	}

	void setNume(const char* nume)
	{
		if (nume != nullptr)
		{
			delete[]this->nume;
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
	}

	void setNrVizualizari(int nrVizualizari)
	{
		this->nrVizualizari = nrVizualizari;
	}

	void setVizualizari(int* vizualizari, int nrVizualizari)
	{
		if (vizualizari != nullptr && nrVizualizari > 0)
		{
			delete[]this->vizualiziari;
			this->vizualiziari = new int[nrVizualizari];
			for (int i = 0; i < nrVizualizari; i++)
			{
				this->vizualiziari[i] = vizualizari[i];
			}

			this->nrVizualizari = nrVizualizari;
		}
	}

	Film(const Film& f):id(f.id)
	{
		this->pret = f.pret;
		this->nume = new char[strlen(f.nume) + 1];
		strcpy(this->nume, f.nume);
		if (f.vizualiziari != nullptr && f.nrVizualizari > 0)
		{
			this->vizualiziari = new int[f.nrVizualizari];
			for (int i = 0; i < f.nrVizualizari; i++)
			{
				this->vizualiziari[i] = f.vizualiziari[i];
			}
			this->nrVizualizari = f.nrVizualizari;
		}
		else
		{
			this->vizualiziari = nullptr;
			this->nrVizualizari = 0;
		}

		this->colectie = f.colectie;
	}

	~Film()
	{
		if (this->nume != nullptr)
		{
			delete[]this->nume;
			this->nume = nullptr;
		}

		if (this->vizualiziari != nullptr)
		{
			delete[]this->vizualiziari;
			this->vizualiziari = nullptr;
		}
	}


	Film& operator=(const Film& f)
	{
		if (this != &f)
		{
			if (this->nume != nullptr)
			{
				delete[]this->nume;
				this->nume = nullptr;
			}

			if (this->vizualiziari != nullptr)
			{
				delete[]this->vizualiziari;
				this->vizualiziari = nullptr;
			}

			this->pret = f.pret;
			this->nume = new char[strlen(f.nume) + 1];
			strcpy(this->nume, f.nume);
			if (f.vizualiziari != nullptr && f.nrVizualizari > 0)
			{
				this->vizualiziari = new int[f.nrVizualizari];
				for (int i = 0; i < f.nrVizualizari; i++)
				{
					this->vizualiziari[i] = f.vizualiziari[i];
				}
				this->nrVizualizari = f.nrVizualizari;
			}
			else
			{
				this->vizualiziari = nullptr;
				this->nrVizualizari = 0;
			}

			this->colectie = f.colectie;
		}
		return*this;
	}

	int& operator[](int index)
	{
		if (index >= 0 && index < nrVizualizari && vizualiziari != nullptr)
		{
			return vizualiziari[index];
		}
		else
			throw new InvalidIndex;
	}


	//pre-incrementare
	Film& operator++()
	{
		if (vizualiziari != nullptr && nrVizualizari > 0)
		{
			vizualiziari[0]++;
		}

		return *this;
	}

	//post-incrementare

	Film operator++(int i)
	{
		Film copie = *this;
		if (vizualiziari != nullptr && nrVizualizari > 0)
		{
			vizualiziari[0]++;
		}

		return copie;
	}

	friend ostream& operator<<(ostream& out, Film f);
	friend istream& operator>>(istream& in, Film& f);

	explicit operator double()
	{
		double max = vizualiziari[0];
		for (int i = 1; i < nrVizualizari; i++)
		{
			if (max < vizualiziari[i])
			{
				max = vizualiziari[i];
			}
		}

		return max;
	}

	Film& operator+=(int vizualizare)
	{
		Film copie = *this;

		if (this->vizualiziari != nullptr)
		{
			delete[]this->vizualiziari;
		}

		this->nrVizualizari++;

		this->vizualiziari = new int[this->nrVizualizari];

		for (int i = 0; i < nrVizualizari - 1; i++)
		{
			this->vizualiziari[i] = copie.vizualiziari[i];
		}
		this->vizualiziari[this->nrVizualizari - 1] = vizualizare;

		return*this;
	}

	Film& operator-=(int pozitie)
	{
		Film copie = *this;

		if (this->vizualiziari != nullptr)
		{
			delete[]this->vizualiziari;
		}

		this->nrVizualizari--;

		this->vizualiziari = new int[nrVizualizari];

		for (int i = 0; i < pozitie;i++)
		{
			this->vizualiziari[i] = copie.vizualiziari[i];
		}

		for (int i = pozitie+1; i <nrVizualizari; i++)
		{
			this->vizualiziari[i-1] = copie.vizualiziari[i];
		}

		return *this;
	}

	 static string* celeMaiVizionate(Film* filme, int nrFilme)
	{
		string* filmeString = new string[5];
		for (int i = 0; i < nrFilme;i++)
			for (int j = i + 1; j <= nrFilme; j++)
			{
				if (filme[i].nrVizualizari < filme[j].nrVizualizari)
				{
					int aux = filme[i].nrVizualizari;
					filme[i].nrVizualizari = filme[j].nrVizualizari;
					filme[j].nrVizualizari = aux;

					filmeString[i] = filme[i].colectie;
				}
			}

		return filmeString;
	}

	 void serialize(fstream& file)
	 {
		 //pret
		 file.write((char*)&this->pret, sizeof(pret));
		 //char*
		 int nrLitereNume = strlen(this->nume);
		 file.write((char*)&nrLitereNume, sizeof(nrLitereNume));
		 for (int i = 0; i < nrLitereNume; i++)
		 {
			 file.write((char*)&nume[i], sizeof(nume[i]));
		 }

		 //int
		 file.write((char*)&this->nrVizualizari, sizeof(nrVizualizari));

		 //int*

		 for (int i = 0; i < this->nrVizualizari; i++)
		 {
			 file.write((char*)&this->vizualiziari[i], sizeof(vizualiziari[i]));
		 }

		 //string

		 int nrLitereColectie = this->colectie.length();
		 file.write((char*)&nrLitereColectie, sizeof(nrLitereColectie));
		 file.write(this->colectie.c_str(), nrLitereColectie);

		 file.close();
	 }

	 void deserialize(fstream& file)
	 {

		 if (this->nume != nullptr)
		 {
			 delete[]this->nume;
		 }

		 if (this->vizualiziari != nullptr)
		 {
			 delete[]this->vizualiziari;
		 }
		 //float
		 file.read((char*)&this->pret, sizeof(this->pret));

		 //char*
		 int nrLitereNume = 0;
		 file.read((char*)&nrLitereNume, sizeof(nrLitereNume));
		 this->nume = new char[nrLitereNume+1];
		 for (int i = 0; i < nrLitereNume; i++)
		 {
			 file.read((char*)&this->nume[i], sizeof(this->nume[i]));
		 }
		 this->nume[nrLitereNume] = '\0';

		 //int
		 file.read((char*)&this->nrVizualizari, sizeof(this->nrVizualizari));

		 //int*
		 this->vizualiziari = new int[this->nrVizualizari];
		 for (int i = 0; i < this->nrVizualizari; i++)
		 {
			 file.read((char*)&this->vizualiziari[i], sizeof(this->vizualiziari[i]));
		 }


		 //string
		 int nrLitereColectie = 0;
		 file.read((char*)&nrLitereColectie, sizeof(nrLitereColectie));
		 string aux;
		 aux.resize(nrLitereColectie);
		 file.read((char*)aux.c_str(), nrLitereColectie);
		 this->colectie = aux;

		 file.close();
	 }
	 friend ofstream& operator<<(ofstream& out, Film f);
	 friend ifstream& operator>>(ifstream& in, Film& f);
};
string Film::regizor = "Tarantino";

ostream& operator<<(ostream& out, Film f)
{
	out << "Pret: " << f.pret<<endl;
	if (f.nume != nullptr)
	{
		out << "Nume: " << f.nume << endl;
	}

	out << "Numar vizualizari: " << f.nrVizualizari << endl;
	out << "Vizualizari: ";
	for (int i = 0; i < f.nrVizualizari; i++)
	{
		out << f.vizualiziari[i] << " ";
	}

	out <<endl<< "Colectie: " << f.colectie << endl;

	return out;
}

istream& operator>>(istream& in, Film& f)
{
	if (f.nume != nullptr)
	{
		delete[]f.nume;
	}
	if (f.vizualiziari != nullptr)
	{
		delete[]f.vizualiziari;
	}

	cout << "Pret: ";
	in >> f.pret;

	char aux[50];
	cout << "Nume: ";
	in >> aux;
	f.nume = new char[strlen(aux) + 1];
	strcpy(f.nume, aux);

	cout << "Numar vizualizari: ";
	in >> f.nrVizualizari;

	cout << "Vizualizari: ";
	f.vizualiziari = new int[f.nrVizualizari];
	for (int i = 0; i < f.nrVizualizari; i++)
	{
		in >> f.vizualiziari[i];
	}

	cout << "Colectie: ";
	in >> f.colectie;

	return in;
}

ofstream& operator<<(ofstream& out, Film f)
{
	out << "Pret: " << f.pret << endl;
	if (f.nume != nullptr)
	{
		out << "Nume: " << f.nume << endl;
	}

	out << "Numar vizualizari: " << f.nrVizualizari << endl;
	out << "Vizualizari: ";
	for (int i = 0; i < f.nrVizualizari; i++)
	{
		out << f.vizualiziari[i] << " ";
	}

	out << endl << "Colectie: " << f.colectie << endl;

	return out;
}

ifstream& operator>>(ifstream& file, Film& f)
{
	if (f.nume != nullptr)
	{
		delete[]f.nume;
	}
	if (f.vizualiziari != nullptr)
	{
		delete[]f.vizualiziari;
	}

	cout << "Pret: ";
	file >> f.pret;

	char aux[50];
	cout << "Nume: ";
	file >> aux;
	f.nume = new char[strlen(aux) + 1];
	strcpy(f.nume, aux);

	cout << "Numar vizualizari: ";
	file >> f.nrVizualizari;

	cout << "Vizualizari: ";
	f.vizualiziari = new int[f.nrVizualizari];
	for (int i = 0; i < f.nrVizualizari; i++)
	{
		file >> f.vizualiziari[i];
	}

	cout << "Colectie: ";
	file >> f.colectie;

	return file;
}

template<class Film, int size>

class Vector
{
private:
	Film filme[size];
public:
	Film& operator[](int index)
	{
		if (index >= 0 && index < size)
		{
			return filme[size];
		}
		throw new InvalidIndex();
	}
};

class Film3D : public Film
{
private:
	int pretOchlari;
	char* ochelari;
public:

	Film3D() :Film()
	{
		this->pretOchlari = 0;
		this->ochelari = nullptr;
	}

	Film3D(int id, float pret, const char* nume, int* vizualizari, int nrVizualizari, string colectie,
		int pretOchelari, const char* ochelari) :Film(id, pret, nume, vizualizari, nrVizualizari, colectie)
	{
		this->pretOchlari = pretOchelari;
		this->ochelari = new char[strlen(ochelari) + 1];
		strcpy(this->ochelari, ochelari);
	}

	Film3D(const Film3D& fd) :Film(fd)
	{
		this->pretOchlari = fd.pretOchlari;
		this->ochelari = new char[strlen(fd.ochelari) + 1];
		strcpy(this->ochelari, fd.ochelari);
	}

	~Film3D()
	{
		if (this->ochelari != nullptr)
		{
			delete[]this->ochelari;
			this->ochelari != nullptr;
		}
	}

	Film3D& operator=(const Film3D& fd)
	{
		if (this != &fd)
		{
			Film::operator=(fd);
			if (this->ochelari != nullptr)
			{
				delete[]this->ochelari;
				this->ochelari = nullptr;
			}
			this->pretOchlari = fd.pretOchlari;
			this->ochelari = new char[strlen(fd.ochelari) + 1];
			strcpy(this->ochelari, fd.ochelari);
		}

		return*this;
	}

	friend ostream& operator<<(ostream& out, Film3D fd);

	char* getOchelari()
	{
		if (ochelari != nullptr)
		{
			char* copie = new char[strlen(ochelari) + 1];
			strcpy(copie, ochelari);

			return copie;
		}

		else
			return nullptr;
	}
};

ostream& operator<<(ostream& out, Film3D fd)
{
	out << (Film)fd<<endl;
	out << "Pret ochelari: " << fd.pretOchlari<<endl;
	if (fd.ochelari != nullptr)
	{
		out << "Ochelari: " << fd.ochelari << endl;
	}

	return out;
}

int main()
{
	Film f1;
	int v[]{ 120, 130, 165 };
	Film f2(1, 30, "Inglorious_Bastards", v, 3, "The_Specials-Inglorious_Bastards");
	
	cout << f2;
	Film f3(f2);
	Film f4 = f1;
	f4 = f3 = f2;
	cout << endl << "--------------------------------" << endl;
	cout << f4;

	Film f5 = f4++;
	cout << f4[0] << " " << f5[0]<<endl;
	Film f6 = ++f4;
	cout << f4[0] << " " << f6[0] << endl;

	int* vizualizari = f2.getVizualizari();
	int nr = f2.getNrVizualiari();
	for (int i = 0; i < nr; i++)
	{
		cout << vizualizari[i] << " ";
	}
	delete[] vizualizari;

	cout << endl;
	int n[]{ 130,200 };
	f6.setVizualizari(n, 2);
	for (int i = 0; i < 2; i++)
	{
		cout << f6[i] << " ";
	}
	f6[0] = 131;
	cout << ""<< f6[0];

	/*cout << endl;
	cin >> f1;
	cout << endl;
	cout << f1;*/

	cout << endl;
	double max = (double)f2;
	cout << max;

	cout << endl << "--------------------------" << endl;
	f5 += 120;
	cout << f5;
	
	cout << endl << "--------------------------" << endl;
	f5 -= 3;
	cout << f5;
	Film f7(2, 40, "Django_Unchained", n, 2, "The_Specials-Django_Unchained");
	int w[]{ 120, 250, 300 };
	int z[]{ 320, 150 };
	int u[]{ 225, 150, 240, 285 };
	int q[]{ 400,350 };

	Film f8(3, 50, "Interstellar", w, 3, "The_Classics-Interstellar");
	Film f9(4, 45, "The Revenant", z, 2, "The_Classics-The_Revenanat");
	Film f10(6, 30, "The Hateful 8", u, 4, "Some_of_the_best-The_Hateful8");
	Film f11(7, 30, "The Matrix", q, 2, "Some_of_the_best-The Matrix");

	Film filme[]{ f2,f7,f8,f9,f10};
	cout << endl << "--------------------------" << endl;
	
	string* filmeString = Film::celeMaiVizionate(filme, 5);
	for (int i = 0; i < 5; i++)
	{
		cout << filmeString[i] << " ";
	}

	cout << endl << "--------Map---------" << endl;
	map<int, Film> m;
	m.insert(make_pair(1, f2));
	m.insert(make_pair(2, f7));
	m.insert(make_pair(3, f8));
	cout << m[2];

	fstream fisier1("film.bin", ios::binary | ios::out);
	f2.serialize(fisier1);
	fisier1.close();

	fstream fisier2("film.bin", ios::binary | ios::in);
	f2.deserialize(fisier2);
	fisier2.close();
	cout <<endl <<"---------Citire binar---------------"<<endl;

	cout << f2 << endl;

	ofstream fisier3("film.txt", ios::out);
	fisier3 << f2;
	fisier3.close();

	ifstream fisier4("test.txt", ios::in);
	fisier4 >> f2;
	fisier4.close();
	cout << endl << "--------Citire txt---------------" << endl;
	cout << f2 << endl;

	cout << endl << "-------------Mosternire---------------" << endl;
	Film3D fd1;
	Film3D fd2(2, 30, "Avengers:Infinity_War", w, 3, "Marvel", 4, "3D");
	cout << fd2;
	Film3D fd3 = fd2;
	cout << endl << fd3;
	fd1 = fd3;
	cout << endl << fd1;
	char* ochelari3D = fd2.getOchelari();
	cout << endl<<ochelari3D;
}