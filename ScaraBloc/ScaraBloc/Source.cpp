#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<map>

using namespace std;

class InvalidIndex :public exception
{

};

class Taxare
{
	virtual float taxare() = 0;
};
class Scara
{
private:
	char* adresa;
	string denumire;
	int nrPersoane;
	int* persoane;
	float intretinere;
	const int id;
	static string cartier;
public:
	Scara() :id(0)
	{
		this->adresa = new char[strlen("N/A") + 1];
		strcpy(this->adresa, "N/A");
		this->denumire = "X";
		this->nrPersoane = 0;
		this->persoane = nullptr;
		this->intretinere = 0;
	}

	Scara(const char* adresa, string denumire) :id(id)
	{
		this->adresa = new char[strlen(adresa) + 1];
		strcpy(this->adresa, adresa);
		this->denumire = denumire;
		this->nrPersoane = 0;
		this->persoane = nullptr;
		this->intretinere = 0;
	}

	Scara(int nrPersoane, int* persoane,float intretinere):id(id)
	{
		this->adresa = new char[strlen("N/A") + 1];
		strcpy(this->adresa, "N/A");
		this->denumire = "X";
		if (nrPersoane > 0 && persoane != nullptr)
		{
			this->nrPersoane = nrPersoane;
			this->persoane = new int[nrPersoane];
			for (int i = 0; i < nrPersoane; i++)
			{
				this->persoane[i] = persoane[i];
			}
		}
		else
		{
			this->nrPersoane = 0;
			this->persoane = nullptr;
		}

		this->intretinere = intretinere;
	}

	Scara(int id, const char* adresa, string denumire, int nrPersoane, int* persoane, float intretinere) :id(id)
	{
		this->adresa = new char[strlen(adresa) + 1];
		strcpy(this->adresa, adresa);
		this->denumire = denumire;
		if (nrPersoane > 0 && persoane != nullptr)
		{
			this->nrPersoane = nrPersoane;
			this->persoane = new int[nrPersoane];
			for (int i = 0; i < nrPersoane; i++)
			{
				this->persoane[i] = persoane[i];
			}
		}
		else
		{
			this->nrPersoane = 0;
			this->persoane = nullptr;
		}

		this->intretinere = intretinere;
	}

	char* getAdresa()
	{
		if (this->adresa != nullptr)
		{
			char* copie = new char[strlen(this->adresa) + 1];
			strcpy(copie, this->adresa);

			return copie;
		}
		else
			return nullptr;
	}

	void setAdresa(const char* adresa)
	{
		if (adresa != nullptr)
		{
			if (this->adresa != nullptr)
			{
				delete[]this->adresa;
			}
			this->adresa = new char[strlen(adresa) + 1];
			strcpy(this->adresa, adresa);
		}
	}

	int getNrPersoane()
	{
		return this->nrPersoane;
	}

	void setnrPersoane(int nrPersoane)
	{
		this->nrPersoane = nrPersoane;
	}

	int* getPersoane()
	{
		if (persoane != nullptr && nrPersoane > 0)
		{
			int* copie = new int[nrPersoane];
			for (int i = 0; i < nrPersoane; i++)
			{
				copie[i] = persoane[i];
			}
			return copie;
		}
		else 
			return nullptr;
	}

	void setPersoane(int* persoane, int nrPersoane)
	{
		if (persoane != nullptr && nrPersoane > 0)
		{
			if (this->persoane != nullptr)
			{
				delete[]this->persoane;
			}
			this->nrPersoane = nrPersoane;
			this->persoane = new int[nrPersoane];
			for (int i = 0; i < nrPersoane; i++)
			{
				this->persoane[i] = persoane[i];
			}
		}
	}

	Scara(const Scara& s):id(s.id)
	{
		this->adresa = new char[strlen(s.adresa) + 1];
		strcpy(this->adresa, s.adresa);

		this->denumire = s.denumire;
		if (s.persoane != nullptr && s.nrPersoane > 0)
		{
			this->nrPersoane = s.nrPersoane;
			this->persoane = new int[s.nrPersoane];
			for (int i = 0; i < s.nrPersoane; i++)
			{
				this->persoane[i] = s.persoane[i];
			}
		}
		else
		{
			this->nrPersoane = 0;
			this->persoane = nullptr;
		}

		this->intretinere = s.intretinere;

	}

	~Scara()
	{
		if (this->adresa != nullptr)
		{
			delete[]this->adresa;
			this->adresa = nullptr;
		}

		if (this->persoane != nullptr)
		{
			delete[]this->persoane;
			this->persoane = nullptr;
		}
	}

	Scara& operator=(const Scara& s)
	{
		if (this != &s)
		{
			if (this->adresa != nullptr)
			{
				delete[]this->adresa;
				this->adresa = nullptr;
			}

			if (this->persoane != nullptr)
			{
				delete[]this->persoane;
				this->persoane = nullptr;
			}
			this->adresa = new char[strlen(s.adresa) + 1];
			strcpy(this->adresa, s.adresa);

			this->denumire = s.denumire;
			if (s.persoane != nullptr && s.nrPersoane > 0)
			{
				this->nrPersoane = s.nrPersoane;
				this->persoane = new int[s.nrPersoane];
				for (int i = 0; i < s.nrPersoane; i++)
				{
					this->persoane[i] = s.persoane[i];
				}
			}
			else
			{
				this->nrPersoane = 0;
				this->persoane = nullptr;
			}

			this->intretinere = s.intretinere;

		}

		return*this;
	}

	Scara& operator++()
	{
		if (persoane != nullptr && nrPersoane > 0)
		{
			this->persoane[0]++;
		}
		return*this;
	}

	Scara operator++(int i)
	{
		Scara copie = *this;
		if (persoane != nullptr && nrPersoane > 0)
		{
			this->persoane[0]++;
		}

		return*this;
	}

	Scara& operator+=(Scara s)
	{
		this->persoane[0] = this->persoane[0] + s.persoane[0];
		return*this;
	}

	Scara& operator+=(int valoare)
	{
		this->persoane[0] = this->persoane[0] + valoare;
		return*this;
	}

	int& operator[](int index)
	{
		if (index >= 0 && index < nrPersoane && persoane != nullptr)
		{
			return persoane[index];
		}
		else
			throw new InvalidIndex();
	}

	friend ostream& operator<<(ostream& out, Scara s);
	friend istream& operator>>(istream& in, Scara& s);
	friend ofstream& operator<<(ofstream& out, Scara s);
	friend ifstream& operator>>(ifstream& in, Scara& s);

	float getIntretinere()
	{
		return this->intretinere;
	}

	void serialize(fstream& file)
	{
		//char*
		int nrLitereAdresa = strlen(this->adresa);
		file.write((char*)&nrLitereAdresa, sizeof(int));
		for (int i = 0; i < nrLitereAdresa; i++)
		{
			file.write((char*)&this->adresa[i], sizeof(this->adresa[i]));
		}

		//string
		int nrLitereDenumire = this->denumire.length();
		file.write((char*)&nrLitereDenumire, sizeof(int));
		file.write(this->denumire.c_str(), nrLitereDenumire);

		//int
		file.write((char*)&this->nrPersoane, sizeof(int));

		//int*
		for (int i = 0; i < this->nrPersoane; i++)
		{
			file.write((char*)&this->persoane[i], sizeof(this->persoane[i]));
		}

		//float

		file.write((char*)&this->intretinere, sizeof(float));

		file.close();
	}

	void deserialize(fstream& file)
	{
		if (this->adresa != nullptr)
		{
			delete[]this->adresa;
		}
		if (this->persoane != nullptr)
		{
			delete[]this->persoane;
		}
		//char*
		int nrLitereAdresa = 0;
		file.read((char*)&nrLitereAdresa, sizeof(int));
		this->adresa = new char[nrLitereAdresa + 1];
		for (int i = 0; i < nrLitereAdresa; i++)
		{
			file.read((char*)&this->adresa[i], sizeof(this->adresa[i]));
		}
		this->adresa[nrLitereAdresa] = '\0';

		//string
		int nrLitereDenumire = 0;
		file.read((char*)&nrLitereDenumire, sizeof(nrLitereDenumire));
		string aux;
		aux.resize(nrLitereDenumire);
		file.read((char*)aux.c_str(), nrLitereDenumire);
		this->denumire = aux;

		//int 
		file.read((char*)&this->nrPersoane, sizeof(int));

		//int*
		this->persoane = new int[this->nrPersoane];
		for (int i = 0; i < this->nrPersoane; i++)
		{
			file.read((char*)&this->persoane[i], sizeof(this->persoane[i]));
		}

		//float
		file.read((char*)&this->intretinere, sizeof(float));

		file.close();

	}
};
string Scara::cartier = "Micro_17";

ostream& operator<<(ostream& out, Scara s)
{
	if (s.adresa != nullptr)
	{
		out << "Adresa: " << s.adresa << endl;
	}
	out << "Denumire: " << s.denumire<<endl;
	out << "Numar persoane: " << s.nrPersoane << endl;
	out << "Persoane: " << endl;
	for (int i = 0; i < s.nrPersoane; i++)
	{
		out << s.persoane[i] << " ";
	}

	out <<endl<< "Intretinere: " << s.intretinere << endl;

	return out;
}
istream& operator>>(istream& in, Scara& s)
{
	if (s.adresa != nullptr)
	{
		delete[]s.adresa;
	}
	if (s.persoane != nullptr)
	{
		delete[]s.persoane;
	}

	char aux[50];
	cout << "Adresa: ";
	in >> aux;
	s.adresa = new char[strlen(aux) + 1];
	strcpy(s.adresa, aux);

	cout << "Denumire: ";
	in >> s.denumire;

	cout << "Numar persoane: ";
	in >> s.nrPersoane;

	cout << "Persoane: ";
	s.persoane = new int[s.nrPersoane];
	for (int i = 0; i < s.nrPersoane; i++)
	{
		in >> s.persoane[i];
	}

	cout << "Intretinere: ";
	in >> s.intretinere;

	return in;
}
ofstream& operator<<(ofstream& out, Scara s)
{
	if (s.adresa != nullptr)
	{
		out << "Adresa: " << s.adresa << endl;
	}
	out << "Denumire: " << s.denumire << endl;
	out << "Numar persoane: " << s.nrPersoane << endl;
	out << "Persoane: " << endl;
	for (int i = 0; i < s.nrPersoane; i++)
	{
		out << s.persoane[i] << " ";
	}

	out << endl << "Intretinere: " << s.intretinere << endl;

	return out;
}

ifstream& operator>>(ifstream& in, Scara& s)
{
	if (s.adresa != nullptr)
	{
		delete[]s.adresa;
	}
	if (s.persoane != nullptr)
	{
		delete[]s.persoane;
	}

	char aux[50];
	cout << "Adresa: ";
	in >> aux;
	s.adresa = new char[strlen(aux) + 1];
	strcpy(s.adresa, aux);

	cout << "Denumire: ";
	in >> s.denumire;

	cout << "Numar persoane: ";
	in >> s.nrPersoane;

	cout << "Persoane: ";
	s.persoane = new int[s.nrPersoane];
	for (int i = 0; i < s.nrPersoane; i++)
	{
		in >> s.persoane[i];
	}

	cout << "Intretinere: ";
	in >> s.intretinere;

	return in;
}

class Bloc :public Taxare
{
private:
	Scara* scari;
	int nrScari;
public:
	Bloc()
	{
		this->scari = nullptr;
		this->nrScari = 0;
	}

	Bloc(int nrScari, Scara* scari)
	{
		if (nrScari > 0 && scari != nullptr)
		{
			this->nrScari = nrScari;
			this->scari = new Scara[nrScari];
			for (int i = 0; i < nrScari; i++)
			{
				this->scari[i] = scari[i];
			}
		}
		else
		{
			this->nrScari = 0;
			this->scari = nullptr;
		}
	}
	Bloc(const Bloc& b)
	{
		if (b.nrScari > 0 && b.scari != nullptr)
		{
			this->nrScari = b.nrScari;
			this->scari = new Scara[b.nrScari];
			for (int i = 0; i < b.nrScari; i++)
			{
				this->scari[i] = b.scari[i];
			}
		}
		else
		{
			this->nrScari = 0;
			this->scari = nullptr;
		}
	}
	~Bloc()
	{
		if (this->scari != nullptr)
		{
			delete[]this->scari;
			this->scari = nullptr;
		}
	}

	Bloc& operator=(const Bloc& b)
	{
		if (this != &b)
		{
			if (this->scari != nullptr)
			{
				delete[]this->scari;
				this->scari = nullptr;
			}
			if (b.nrScari > 0 && b.scari != nullptr)
			{
				this->nrScari = b.nrScari;
				this->scari = new Scara[b.nrScari];
				for (int i = 0; i < b.nrScari; i++)
				{
					this->scari[i] = b.scari[i];
				}
			}
			else
			{
				this->nrScari = 0;
				this->scari = nullptr;
			}
		}
		return*this;
	}
	friend ostream& operator<<(ostream& out, Bloc b);

	Bloc& operator+=(Scara scara)
	{
		Bloc copie = *this;

		if (this->scari != nullptr)
		{
			delete[]this->scari;
		}

		this->nrScari++;

		this->scari = new Scara[this->nrScari];

		for (int i = 0; i < this->nrScari - 1; i++)
		{
			this->scari[i] = copie.scari[i];
		}
		this->scari[this->nrScari-1] = scara;
		
		return *this;
	}

	Bloc& operator-=(int pozitie)
	{
		Bloc copie = *this;
		if (this->scari != nullptr)
		{
			delete[]this->scari;
		}

		this->nrScari--;
		this->scari = new Scara[this->nrScari];

		for (int i = 0; i < pozitie; i++)
		{
			this->scari[i] = copie.scari[i];
		}

		for (int i = pozitie + 1; i < this->nrScari+1; i++)
		{
			this->scari[i - 1] = copie.scari[i];
		}

		return*this;
	}
	float taxare()
	{
		return nrScari*50;
	}


	void MinSiMax(Scara minim, Scara maxim)
	{
		 minim = this->scari[0];;
		 maxim=this->scari[0];
		for (int i = 0; i < nrScari; i++)
		{	
			float suma = 0;
			suma += this->scari[i].getIntretinere();
			if (maxim.getIntretinere() < suma)
			{
				maxim = this->scari[i];
			}
			if (minim.getIntretinere() > suma)
			{
				minim = this->scari[i];
			}
		}

		cout << "Valoare minima este :" << minim << ". Si valoarea maxima este: " << maxim;
	}

	float calculTotal()
	{
		float suma = 0;
		for (int i = 0; i < this->nrScari; i++)
		{
			suma += this->scari[i].getIntretinere();
		}

		return suma;
	}

};
ostream& operator<<(ostream& out, Bloc b)
{
	out << "Numar scari: " << b.nrScari<<endl;
	out << "Scari: " << endl;
	for (int i = 0; i < b.nrScari; i++)
	{
		cout << b.scari[i] << endl;
	}

	return out;
}

int main()
{
	Scara s1;
	int w[]{ 2,4,3 };
	Scara s2(1, "Fizicienilor", "4Elements", 3, w, 950);
	cout << s2;
	Scara s3 = s1;
	s3 = s2;
	cout << endl << s3<<endl;

	int* familie = s2.getPersoane();
	int nr = s2.getNrPersoane();
	for (int i = 0; i < nr; i++)
	{
		cout << familie[i] << " ";
	}

	cout << endl;
	int n[]{ 2,4,3,2 };
	s3.setPersoane(n, 4);
	for (int i = 0; i < s3.getNrPersoane(); i++)
	{
		cout << s3[i] << " ";
	}

	cout << endl;
	/*Scara s4;
	cin >> s4;
	cout << endl << s4 << endl;*/

	Bloc b1;
	Scara scari[]{ s2,s3 };
	Bloc b2(2, scari);
	cout << b2<<endl;

	Scara s4(4, "Platinia", "Serban_Voda", 4, n, 1750);
	b2 += s4;
	cout << endl << b2 << endl;

	b2 -= 1;
	cout << endl << b2 << endl;

	Scara minima;
	Scara maxima;
	b2.MinSiMax(minima, maxima);

	cout << endl;
	cout << b2.calculTotal();

	vector<Scara>vectSTLScara;
	vectSTLScara.push_back(s2);
	vectSTLScara.push_back(s3);
	vectSTLScara.push_back(s4);

	float sumaLocatari = 0;
	for (int i = 0; i < vectSTLScara.size(); i++)
	{
		sumaLocatari += vectSTLScara[i].getIntretinere();
	}

	cout << endl << "Suma totala care trebuie platita de locatari este: " << sumaLocatari;

	map<int, Scara>m;
	m.insert(make_pair(1, s2));
	m.insert(make_pair(2, s3));
	m.insert(make_pair(3, s4));

	cout <<endl<< m[1];

	cout<<"S-a marit intretinerea cu: "<<b2.taxare()<<endl;

	ofstream fisier1("Scara.txt", ios::out);
	fisier1 << s4;
	fisier1.close();

	cout << endl << "----------CITIRE TEXT---------------" << endl;
	Scara s5;
	ifstream fisier2("Scara.txt", ios::in);
	fisier2 >> s5;
	fisier2.close();

	cout <<s5<<endl << endl;

	fstream fisier3("Scara.bin", ios::binary | ios::out);
	s2.serialize(fisier3);
	fisier3.close();

	cout << endl << "--------CITIRE BINAR--------------" << endl;
	fstream fisier4("Scara.bin", ios::binary | ios::in);
	s2.deserialize(fisier4);
	fisier4.close();

	cout << s2 << endl << endl;
}