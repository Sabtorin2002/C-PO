#include<iostream>
#include<string>
#include<string.h>
#include<fstream>
#include<map>
#include<vector>

using namespace std;

class InvalidIndex :public exception
{

};
class Produs
{
private:
	string nume;
	char* producator;
	int nrPret;
	int* preturi;
	float cantitate;
	const int id;
	static string distribuitor;

public:

	Produs() :id(0)
	{
		this->nume = "";
		this->producator = new char[strlen("N/A") + 1];
		strcpy(this->producator, "N/A");

		this->nrPret = 0;
		this->preturi = nullptr;
		this->cantitate = 0;
	}
	Produs(int id, string nume, const char* producator, int nrPret, int* preturi, float cantitate) :id(id)
	{
		this->nume = nume;
		this->producator = new char[strlen(producator) + 1];
		strcpy(this->producator, producator);

		if (preturi != nullptr && nrPret > 0)
		{
			this->nrPret = nrPret;
			this->preturi = new int[nrPret];
			for (int i = 0; i < nrPret; i++)
			{
				this->preturi[i] = preturi[i];
			}
		}
		else
		{
			this->preturi = nullptr;
			this->nrPret = 0;
		}

		this->cantitate = cantitate;
	}

	Produs(const Produs& p):id(p.id)
	{
		this->nume = p.nume;
		this->producator = new char[strlen(p.producator) + 1];
		strcpy(this->producator, p.producator);

		if (p.preturi != nullptr && p.nrPret > 0)
		{
			this->nrPret = p.nrPret;
			this->preturi = new int[p.nrPret];
			for (int i = 0; i < p.nrPret; i++)
			{
				this->preturi[i] = p.preturi[i];
			}
		}

		else
		{
			this->preturi = nullptr;
			this->nrPret = 0;
		}

		this->cantitate = p.cantitate;
	}

	~Produs()
	{
		if (this->producator != nullptr)
		{
			delete[]this->producator;
			this->producator = nullptr;
		}
		if (this->preturi != nullptr)
		{
			delete[]this->preturi;
			this->preturi = nullptr;
		}
	}

	Produs& operator=(const Produs& p)
	{
		if (this != &p)
		{
			if (this->producator != nullptr)
			{
				delete[]this->producator;
				this->producator = nullptr;
			}
			if (this->preturi != nullptr)
			{
				delete[]this->preturi;
				this->preturi = nullptr;
			}

			this->nume = p.nume;
			this->producator = new char[strlen(p.producator) + 1];
			strcpy(this->producator, p.producator);

			if (p.preturi != nullptr && p.nrPret > 0)
			{
				this->nrPret = p.nrPret;
				this->preturi = new int[p.nrPret];
				for (int i = 0; i < p.nrPret; i++)
				{
					this->preturi[i] = p.preturi[i];
				}
			}

			else
			{
				this->preturi = nullptr;
				this->nrPret = 0;
			}

			this->cantitate = p.cantitate;

		}

		return*this;
	}

	char* getProducator()
	{
		if (producator != nullptr)
		{
			char* copie = new char[strlen(producator) + 1];
			strcpy(copie, producator);

			return copie;
		}
		else
			return nullptr;
	}

	void setProducator(char* producator)
	{
		if (producator != nullptr)
		{
			if (this->producator != nullptr)
			{
				delete[]this->producator;
			}
			this->producator = new char[strlen(producator) + 1];
			strcpy(this->producator, producator);
		}
	}

	int getNrPret()
	{
		return this->nrPret;
	}

	int getCantiate()
	{
		return this->cantitate;
	}

	void setNrPret(int nrPret)
	{
		this->nrPret = nrPret;
	}

	int* getPreturi()
	{
		if (preturi != nullptr)
		{
			int* copie = new int[nrPret];
			for (int i = 0; i < nrPret; i++)
			{
				copie[i] = preturi[i];
			}

			return copie;
		}

		else
			return nullptr;
	}

	void setPreturi(int* preturi, int nrPreturi)
	{
		if (preturi != nullptr && nrPreturi > 0)
		{
			if (this->preturi != nullptr)
			{
				delete[]this->preturi;
			}

			this->nrPret = nrPreturi;
			this->preturi = new int[nrPreturi];
			for (int i = 0; i < nrPreturi; i++)
			{
				this->preturi[i] = preturi[i];
			}
		}
	}

	Produs& operator++()
	{
		if (this->preturi != nullptr && this->nrPret > 0)
		{
			preturi[0]++;
		}

		return*this;
	}

	Produs operator++(int i)
	{
		Produs copie = *this;
		if (this->preturi != nullptr && this->nrPret > 0)
		{
			preturi[0]++;
		}

		return copie;
	}

	int& operator[](int index)
	{
		if (index >= 0 && index < nrPret && preturi != nullptr)
		{
			return preturi[index];
		}
		else
			throw new exception("Eroare");
	}

	Produs operator+=(Produs p)
	{
		for (int i = 0; i < p.nrPret; i++)
		{
			this->preturi[i] = this->preturi[i] + p.preturi[i];
		}

		return*this;
	}

	explicit operator string()
	{
		return "Numele este: " + this->nume;
	}

	int operator<(Produs p)
	{
		if (this->cantitate < p.cantitate)
			return 1;
		else return 0;
	}

	Produs& operator+=(int pret)
	{
		Produs copie = *this;

		if (this->preturi != nullptr)
		{
			delete[]this->preturi;
		}

		this->nrPret++;

		this->preturi = new int[this->nrPret];

		for (int i = 0; i < this->nrPret - 1; i++)
		{
			this->preturi[i] = copie.preturi[i];
		}

		this->preturi[this->nrPret - 1] = pret;

		return*this;
	}

	Produs& operator-=(int pozitie)
	{
		Produs copie = *this;

		if (this->preturi != nullptr)
		{
			delete[]this->preturi;
		}

		this->nrPret--;
		
		this->preturi = new int[this->nrPret];

		for (int i = 0; i < pozitie; i++)
		{
			this->preturi[i] = copie.preturi[i];
		}

		for (int i = pozitie + 1; i < this->nrPret; i++)
		{
			this->preturi[i - 1] = copie[i];
		}

		return*this;
	}


	void serialize(fstream& file)
	{
		//string
		int nrLitereNume = this->nume.length();
		file.write((char*)&nrLitereNume, sizeof(int));
		file.write(this->nume.c_str(), nrLitereNume);

		//char*
		int nrLitereProducator = strlen(this->producator);
		file.write((char*)&nrLitereProducator, sizeof(int));
		for (int i = 0; i < nrLitereProducator; i++)
		{
			file.write((char*)&this->producator[i], sizeof(char));
		}

		//int
		file.write((char*)&this->nrPret, sizeof(int));

		//int*
		for (int i = 0; i < this->nrPret; i++)
		{
			file.write((char*)&this->preturi[i], sizeof(int));
		}

		//float
		file.write((char*)&this->cantitate, sizeof(float));

		file.close();
	}

	void deserialize(fstream& file)
	{
		if (this->preturi != nullptr)
		{
			delete[]this->preturi;
		}

		if (this->producator != nullptr)
		{
			delete[]this->producator;
		}
		//string
		int nrLitereNume=0;
		file.read((char*)&nrLitereNume, sizeof(nrLitereNume));
		string aux;
		aux.resize(nrLitereNume);
		file.read((char*)aux.c_str(), nrLitereNume);
		this->nume = aux;

		//char*
		int nrLitereProducator=0;
		file.read((char*)&nrLitereProducator, sizeof(nrLitereProducator));
		this->producator = new char[nrLitereProducator+1];
		for (int i = 0; i < nrLitereProducator; i++)
		{
			file.read((char*)&this->producator[i], sizeof(this->producator[i]));
		}
		this->producator[nrLitereProducator] = '\0';

		//int
		file.read((char*)&this->nrPret, sizeof(this->nrPret));

		//int*
		this->preturi = new int[this->nrPret];
		for (int i = 0; i < this->nrPret; i++)
		{
			file.read((char*)&this->preturi[i], sizeof(this->preturi[i]));
		}

		//float

		file.read((char*)&this->cantitate, sizeof(this->cantitate));

		file.close();
	}
	friend ostream& operator<<(ostream& out, Produs p);
	friend istream& operator>>(istream& in, Produs& p);
	friend ofstream& operator<<(ofstream& out, Produs p);
	friend ifstream& operator>>(ifstream& in, Produs& p);
};
string Produs::distribuitor = "DHL";

ostream& operator<<(ostream& out, Produs p)
{
	out << "Nume: " << p.nume << endl;
	if (p.producator != nullptr)
	{
		out << "Producator: " << p.producator << endl;
	}

	out << "Numar pret: " << p.nrPret << endl;
	out << "Preturi: ";
	for (int i = 0; i < p.nrPret; i++)
	{
		out << p.preturi[i] << " ";
	}

	out <<endl<< "Cantitate: " << p.cantitate << endl;
	return out;


}
istream& operator>>(istream& in, Produs& p)
{
	if (p.producator != nullptr)
	{
		delete[]p.producator;
	}
	if (p.preturi != nullptr)
	{
		delete[]p.preturi;
	}

	cout << "Nume: ";
	in >> p.nume;

	char aux[50];
	cout << "Producator: ";
	in >> aux;
	p.producator = new char[strlen(aux) + 1];
	strcpy(p.producator, aux);

	cout << "Numar preturi: ";
	in >> p.nrPret;

	cout << "Preturi: ";
	p.preturi = new int[p.nrPret];
	for (int i = 0; i < p.nrPret; i++)
	{
		in >> p.preturi[i];
	}

	cout << "Cantitate: ";
	in >> p.cantitate;

	return in;
}

ofstream& operator<<(ofstream& file, Produs p)
{
	file << "Nume: " << p.nume << endl;
	if (p.producator != nullptr)
	{
		file << "Producator: " << p.producator << endl;
	}

	file << "Numar pret: " << p.nrPret << endl;
	file << "Preturi: ";
	for (int i = 0; i < p.nrPret; i++)
	{
		file << p.preturi[i] << " ";
	}

	file << endl << "Cantitate: " << p.cantitate << endl;
	return file;


}
ifstream& operator>>(ifstream& file, Produs& p)
{
	if (p.producator != nullptr)
	{
		delete[]p.producator;
	}
	if (p.preturi != nullptr)
	{
		delete[]p.preturi;
	}

	cout << "Nume: ";
	file >> p.nume;

	char aux[50];
	cout << "Producator: ";
	file >> aux;
	p.producator = new char[strlen(aux) + 1];
	strcpy(p.producator, aux);

	cout << "Numar preturi: ";
	file >> p.nrPret;

	cout << "Preturi: ";
	p.preturi = new int[p.nrPret];
	for (int i = 0; i < p.nrPret; i++)
	{
		file >> p.preturi[i];
	}

	cout << "Cantitate: ";
	file >> p.cantitate;

	return file;
}

class Cos
{
private:
	Produs* produsCos;
	int nrProduse;

public:

	Cos()
	{
		this->produsCos = nullptr;
		this->nrProduse = 0;
	}

	Cos(Produs* produsCos, int nrProduse)
	{
		this->nrProduse = nrProduse;
		if (produsCos != nullptr && nrProduse > 0)
		{
			this->produsCos = new Produs[nrProduse];
			for (int i = 0; i < nrProduse; i++)
			{
				this->produsCos[i] = produsCos[i];
			}
		}
		else
		{
			this->produsCos = nullptr;
			this->nrProduse = 0;
		}
	}

	Produs& operator[](int index)
	{
		if (index >= 0 && index <= nrProduse && produsCos != nullptr)
		{
			return produsCos[index];
		}
		else
			throw new exception("Eroare produs");
	}

	Cos& operator+=(Produs prod)
	{
		Cos copie = *this;

		if (this->produsCos != nullptr)
		{
			delete[]this->produsCos;
		}

		this->nrProduse++;
		this->produsCos = new Produs[this->nrProduse];

		for (int i = 0; i < this->nrProduse-1; i++)
		{
			this->produsCos[i] = copie.produsCos[i];
		}

		this->produsCos[this->nrProduse-1] = prod;

		return*this;
	}

	Cos& operator-=(int pozitie)
	{
		Cos copie = *this;

		if (this->produsCos != nullptr)
		{
			delete[]this->produsCos;
		}

		this->nrProduse--;
		this->produsCos = new Produs[this->nrProduse];

		for (int i = 0; i < pozitie; i++)
		{
			this->produsCos[i] = copie.produsCos[i];
		}

		for (int i = pozitie + 1; i < this->nrProduse; i++)
		{
			this->produsCos[i - 1] = copie.produsCos[i];
		}

		return*this;
	}

	static float valoareTotala(Cos cos, int nrCosuri)
	{
		float suma = 0;
		for (int i = 0; i < nrCosuri; i++)
		{
			float valoare = 0;
			for (int j = 0; j < cos.nrProduse; j++)
			{
				valoare = valoare + cos[j].getNrPret() * cos[j].getCantiate();
			}
			suma = suma + valoare;
		}

		return suma;
	}
	friend ostream& operator<<(ostream& out, Cos c);
};

ostream& operator<<(ostream& out, Cos c)
{
	out << "Numar produse: " << c.nrProduse << endl;
	out << "Produse: ";
	for (int i = 0; i < c.nrProduse; i++)
	{
		out << c.produsCos[i] << endl;
	}

	return out;
}

int main()
{
	Produs p1;
	int v[]{ 12, 13 };
	Produs p2(1, "Lapte", "Napolact", 2, v, 3);
	Produs p3;
	p3 = p2;

	cout << p3;

	Produs p4 = p2++;
	cout << p2[0] << " " << p4[0];

	Produs p5 = ++p2;
	cout << endl << p2[0] << " " << p5[0];

	p3 += p2;

	cout << endl << p3;
	cout << endl <<(string)p3;
	cout << endl;

	int w[]{ 8 };
	Produs p6(2, "Cascaval", "Delaco", 1, w, 2);
	if (p2 < p6)
	{
		cout << "Lapte e in cantitate mai mica.";
	}
	else
		cout << "Cascaval e in cantiate mai mica.";

	cout << endl << "----------Cos_1------------------" << endl;
	Produs produse[]{ p2,p6 };
	Cos c1(produse, 2);
	cout << c1;

	cout << endl;
	cout << c1[0];

	/*cout << endl << "----Citire_si_afisare_______" << endl;
	cin >> p1;
	cout << endl;
	cout << p1;
	cout << endl;*/

	cout << endl;
	p2 += 11;
	cout << p2;

	cout << endl;
	p2 -= 2;
	cout << p2;

	cout << endl;
	p5[0] = 1000;
	cout << p5;
	
	cout << endl;
	try {
		p5[18] = 2;
		cout << p5;
	}
	catch (InvalidIndex& e)
	{
		cout << "Eroare";
	}
	catch (exception& e)
	{
		e.what();
	}
	catch (...)
	{
		cout << "Eroare totala";
	}
	
	/*c1 += p3;
	cout << endl << "------------Cos_1_modificat-----------" << endl;
	cout << c1;*/

	/*c1 -= 1;
	cout << endl << "---------------Cos_1_modificat_v2--------------" << endl;
	cout << c1;*/

	fstream fisier1("produs.bin", ios::binary | ios::out);
	p2.serialize(fisier1);
	fisier1.close();


	cout << endl << "--------------Citire_binar-------------" << endl;
	fstream fisier2("produs.bin", ios::binary | ios::in);
	p2.deserialize(fisier2);
	fisier2.close();

	cout << p2 << endl;

	cout << endl<< "-------MAP----------"<<endl;
	map<int, Cos>m;
	m.insert(make_pair(1, c1));
	cout << m[1];
	int x[]{ 7 };
	Produs p7(3, "Apa", "Azuga", 1, x, 2);
	Produs produse2[]{p7};
	Cos c2(produse2, 1);

	cout << Cos::valoareTotala(c1, 1);
	cout << endl;

	vector<Produs> vectProdusSTL;
	vectProdusSTL.push_back(p2);
	vectProdusSTL.push_back(p6);
	vectProdusSTL.push_back(p7);

	float valoare = 0;
	for (int i = 0; i < vectProdusSTL.size(); i++)
	{
		valoare = valoare + vectProdusSTL[i].getCantiate() * vectProdusSTL[i].getNrPret();
	}

	cout << "Valoare totala a produselor este: "<<valoare;

	ofstream fisier3("produs.txt", ios::out);
	fisier3 << p7;
	fisier3.close();


	cout <<endl<<"--------Citire_fisier_txt--------"<<endl;
	ifstream fisier4("Test.txt", ios::in);
	fisier4 >> p7;
	fisier4.close();

	cout << p7 <<endl<< endl;




}