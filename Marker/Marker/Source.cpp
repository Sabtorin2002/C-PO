#include<iostream>
#include<string>
#include<fstream>
#include<map>
#include<vector>
using namespace std;

class InvalidIndexException :public exception
{

};
class Marker
{
private:
	char* culoare;
	string producator;
	int nrDimensiuni;
	int* dimensiuni;
	float pret;
	const int id=0;
	static string numeMagazain;

public:
	Marker() :id(0)
	{
		this->culoare = nullptr;
		this->producator = "X";
		this->nrDimensiuni = 0;
		this->dimensiuni = nullptr;
		this->pret = 0;
	}

	Marker(const char* culoare, string producaotor, int nrDimensiuni):id(id)
	{
		this->culoare = new char[strlen(culoare) + 1];
		strcpy(this->culoare, culoare);

		this->producator = producaotor;
		
		this->nrDimensiuni = nrDimensiuni;
		this->dimensiuni = new int[nrDimensiuni];
	}

	Marker(int id, const char* culoare, string producator, int nrDimenisuni, int* dimensiuni, float pret):id(id)
	{
		this->culoare = new char[strlen(culoare) + 1];
		strcpy(this->culoare, culoare);

		this->producator = producator;
		
		if (nrDimenisuni > 0 && dimensiuni != nullptr)
		{
			this->nrDimensiuni = nrDimenisuni;
			this->dimensiuni = new int[nrDimenisuni];
			for (int i = 0; i < nrDimenisuni; i++)
			{
				this->dimensiuni[i] = dimensiuni[i];
			}
		}
		else
		{
			this->nrDimensiuni = 0;
			this->dimensiuni = nullptr;
		}

		this->pret = pret;
	}

	int getNrDimenisiuni()
	{
		return this->nrDimensiuni;
	}

	void setNrDimenisuni(int nrDimensiuni)
	{
		this->nrDimensiuni = nrDimensiuni;
	}

	char* getCuloare()
	{
		if (culoare != nullptr)
		{
			char* copie = new char[strlen(culoare) + 1];
			strcpy(copie, culoare);

			return copie;
		}

		else
			return nullptr;
	}

	void setCuloare(const char* culoare)
	{
		if (culoare != nullptr)
		{
			if (this->culoare != nullptr)
			{
				delete[]this->culoare;
			}
			this->culoare = new char[strlen(culoare) + 1];
			strcpy(this->culoare, culoare);
		}
	}

	int* getDimeniuni()
	{
		if (dimensiuni != nullptr)
		{
			int* copie = new int[nrDimensiuni];
			for (int i = 0; i < nrDimensiuni; i++)
			{
				copie[i] = dimensiuni[i];
			}
			return copie;
		}
		else
			return nullptr;
	}

	void setDimenisuni(int nrDimensiuni, int* dimensiuni)
	{
		if (dimensiuni != nullptr && nrDimensiuni > 0)
		{
			if (this->dimensiuni != nullptr)
			{
				delete[]this->dimensiuni;
			}

			this->dimensiuni = new int[nrDimensiuni];
			for (int i = 0; i < nrDimensiuni; i++)
			{
				this->dimensiuni[i] = dimensiuni[i];
			}

			this->nrDimensiuni = nrDimensiuni;
		}
	}

	Marker(const Marker& m) :id(m.id)
	{
		this->culoare = new char[strlen(m.culoare) + 1];
		strcpy(this->culoare, m.culoare);

		this->producator = m.producator;

		if (m.dimensiuni != nullptr && m.nrDimensiuni > 0)
		{
			this->nrDimensiuni = m.nrDimensiuni;
			this->dimensiuni = new int[m.nrDimensiuni];
			for (int i = 0; i < m.nrDimensiuni; i++)
			{
				this->dimensiuni[i] = m.dimensiuni[i];
			}
		}
		else
		{
			this->nrDimensiuni = 0;
			this->dimensiuni = nullptr;
		}

		this->pret = m.pret;
	}

	~Marker()
	{
		if (this->dimensiuni != nullptr)
		{
			delete[]this->dimensiuni;
			this->dimensiuni = nullptr;
		}

		if (this->culoare != nullptr)
		{
			delete[]this->culoare;
			this->culoare = nullptr;
		}
	}

	Marker& operator=(const Marker& m)
	{
		if (this != &m)
		{
			if (this->dimensiuni != nullptr)
			{
				delete[]this->dimensiuni;
				this->dimensiuni = nullptr;
			}

			if (this->culoare != nullptr)
			{
				delete[]this->culoare;
				this->culoare = nullptr;
			}

			this->culoare = new char[strlen(m.culoare) + 1];
			strcpy(this->culoare, m.culoare);

			this->producator = m.producator;

			if (m.dimensiuni != nullptr && m.nrDimensiuni > 0)
			{
				this->nrDimensiuni = m.nrDimensiuni;
				this->dimensiuni = new int[m.nrDimensiuni];
				for (int i = 0; i < m.nrDimensiuni; i++)
				{
					this->dimensiuni[i] = m.dimensiuni[i];
				}
			}
			else
			{
				this->nrDimensiuni = 0;
				this->dimensiuni = nullptr;
			}

			this->pret = m.pret;
		}

		return*this;
	}

	Marker& operator++()
	{
		if (this->dimensiuni != nullptr && this->nrDimensiuni > 0)
		{
			this->dimensiuni[0]++;
		}

		return *this;
	}

	Marker operator++(int i)
	{
		Marker copie = *this;
		if (this->dimensiuni != nullptr && this->nrDimensiuni > 0)
		{
			this->dimensiuni[0]++;;
		}

		return copie;
	}

	bool operator==(Marker m)
	{
		if (this->nrDimensiuni == m.nrDimensiuni && this->pret == m.pret)
		{
			return 1;
		}
		else
			return 0;
	}

	int& operator[](int index)
	{
		if (index >= 0 && index < nrDimensiuni && dimensiuni != nullptr)
		{
			return dimensiuni[0];
		}
		else
			throw new InvalidIndexException;
			
	}

	virtual float marirePret()
	{
		return this->pret * 1.5;
	}

	float getPret()
	{
		return this->pret;
	}

	friend ostream& operator<<(ostream& out, Marker m);
	friend istream& operator>>(istream& in, Marker& m);

	void serialize(fstream& file)
	{
		//char*
		int nrLitereCuloare = strlen(this->culoare);
		file.write((char*)&nrLitereCuloare, sizeof(int));
		for (int i = 0; i < nrLitereCuloare; i++)
		{
			file.write((char*)&this->culoare[i], sizeof(char));
		}

		//string

		int nrLitereProducator = this->producator.length();
		file.write((char*)&nrLitereProducator, sizeof(int));
		file.write(this->producator.c_str(), nrLitereProducator);

		//int
		file.write((char*)&this->nrDimensiuni, sizeof(int));

		//int*
		for (int i = 0; i < this->nrDimensiuni; i++)
		{
			file.write((char*)&this->dimensiuni[i], sizeof(this->dimensiuni[i]));
		}

		//float

		file.write((char*)&this->pret, sizeof(this->pret));

		file.close();
	}

	void deserialize(fstream& file)
	{
		if (this->culoare != nullptr)
		{
			delete[]this->culoare;
		}
		if (this->dimensiuni != nullptr)
		{
			delete[]this->dimensiuni;
		}
		//char*
		int nrLitereCuloare = 0;
		file.read((char*)&nrLitereCuloare, sizeof(int));
		this->culoare = new char[nrLitereCuloare + 1];
		for (int i = 0; i < nrLitereCuloare; i++)
		{
			file.read((char*)&this->culoare[i], sizeof(this->culoare[i]));
		}
		this->culoare[nrLitereCuloare] = '\0';

		//string
		int nrLitereProducator = 0;
		file.read((char*)&nrLitereProducator, sizeof(int));
		string aux;
		aux.resize(nrLitereProducator);
		file.read((char*)aux.c_str(), nrLitereProducator);
		this->producator = aux;

		//int
		file.read((char*)&this->nrDimensiuni, sizeof(int));

		//int*
		this->dimensiuni = new int[this->nrDimensiuni];
		for (int i = 0; i < this->nrDimensiuni; i++)
		{
			file.read((char*)&this->dimensiuni[i], sizeof(this->dimensiuni[i]));
		}

		//float
		file.read((char*)&this->pret, sizeof(float));

		file.close();
	}

	Marker& operator+=(int dimensiune)
	{
		Marker copie = *this;

		if (this->dimensiuni != nullptr)
		{
			delete[]this->dimensiuni;
		}

		this->nrDimensiuni++;

		this->dimensiuni = new int[this->nrDimensiuni];

		for (int i = 0;i<this->nrDimensiuni-1; i++)
		{
			this->dimensiuni[i] = copie.dimensiuni[i];
		}

		this->dimensiuni[this->nrDimensiuni-1] = dimensiune;

		return*this;
	}

	Marker& operator-=(int pozitie)
	{
		Marker copie = *this;

		if (dimensiuni != nullptr)
		{
			delete[]this->dimensiuni;
		}

		this->nrDimensiuni--;

		this->dimensiuni = new int[this->nrDimensiuni];

		for (int i = 0; i < pozitie; i++)
		{
			this->dimensiuni[i] = copie.dimensiuni[i];
		}

		for (int i = pozitie + 1; i < this->nrDimensiuni+1; i++)
		{
			this->dimensiuni[i - 1] = copie.dimensiuni[i];
		}

		return*this;
	}
};
string Marker::numeMagazain = "Penita";
ostream& operator<<(ostream& out, Marker m)
{
	if (m.culoare != nullptr)
	{
		out << "Culoare: " << m.culoare << endl;
	}

	out << "Producator: " << m.producator << endl;
	out << "Numar dimensiuni: " << m.nrDimensiuni << endl;
	out << "Dimensiuni: " << endl;
	for (int i = 0; i < m.nrDimensiuni; i++)
	{
		out << m.dimensiuni[i] << " ";
	}

	out <<endl<< "Pret: " << m.pret << endl;

	return out;
}

istream& operator>>(istream& in, Marker& m)
{
	if (m.culoare != nullptr)
	{
		delete[]m.culoare;
	}

	if (m.dimensiuni != nullptr)
	{
		delete[]m.dimensiuni;
	}

	char aux[50];
	cout << "Culoare: ";
	in >> aux;
	m.culoare = new char[strlen(aux) + 1];
	strcpy(m.culoare, aux);

	cout << "Producator: ";
	in >> m.producator;

	cout << "Numar dimensiuni: ";
	in >> m.nrDimensiuni;

	cout << "Dimensiuni: ";
	m.dimensiuni = new int[m.nrDimensiuni];
	for (int i = 0; i < m.nrDimensiuni; i++)
	{
		in >> m.dimensiuni[i];
	}

	cout << "Pret: ";
	in >> m.pret;

	return in;
}

class MarkerElectronic :public Marker
{
private:
	int baterie;
	float razaDeActiune;
	char* unitateDeMasura;
public:
	MarkerElectronic() :Marker()
	{
		this->baterie = 0;
		this->razaDeActiune = 0;
		this->unitateDeMasura = nullptr;
	}

	MarkerElectronic(int id, const char* culoare, string producator, int nrDimenisuni, int* dimensiuni, float pret,
		int baterie, float razaDeActiune,const char* unitateDeMasura) :Marker(id, culoare, producator, nrDimenisuni, dimensiuni, pret)
	{
		this->baterie = baterie;
		this->razaDeActiune = razaDeActiune;
		this->unitateDeMasura = new char[strlen(unitateDeMasura) + 1];
		strcpy(this->unitateDeMasura, unitateDeMasura);
	}

	MarkerElectronic(const MarkerElectronic& me) :Marker(me)
	{
		this->baterie = me.baterie;
		this->razaDeActiune = me.razaDeActiune;
		this->unitateDeMasura = new char[strlen(me.unitateDeMasura)+1];
		strcpy(this->unitateDeMasura, me.unitateDeMasura);
	}

	~MarkerElectronic()
	{
		if (this->unitateDeMasura != nullptr)
		{
			delete[]this->unitateDeMasura;
			this->unitateDeMasura = nullptr;
		}
	}

	MarkerElectronic& operator=(const MarkerElectronic& me)
	{
		if (this != &me)
		{
			Marker::operator=(me);
			if (this->unitateDeMasura != nullptr)
			{
				delete[]this->unitateDeMasura;
				this->unitateDeMasura = nullptr;
			}

			this->baterie = me.baterie;
			this->razaDeActiune = me.razaDeActiune;
			
			this->unitateDeMasura = new char[strlen(me.unitateDeMasura) + 1];
			strcpy(this->unitateDeMasura, me.unitateDeMasura);
		}

		return*this;
	}

	float marirePret()override
	{
		return this->getPret() * 2;
	}

	friend ostream& operator<<(ostream& out, MarkerElectronic me);
	friend istream& operator>>(istream& in, MarkerElectronic& me);

	
};
ostream& operator<<(ostream& out, MarkerElectronic me)
{
	out << (Marker)me << endl;

	out << "Baterie: " << me.baterie << endl;
	out << "Raza de actiune: " << me.razaDeActiune << endl;
	out << "Unitate de masura: " << me.unitateDeMasura;

	return out;
}
istream& operator>>(istream& in, MarkerElectronic& me)
{
	if (me.unitateDeMasura != nullptr)
	{
		delete[]me.unitateDeMasura;
	}
	in >> (Marker&)me;

	cout << "Baterie: ";
	in >> me.baterie;

	cout << "Raza de actiune: ";
	in >> me.razaDeActiune;

	char aux[50];
	cout << "Unitate de masura: ";
	in >> aux;
	me.unitateDeMasura = new char[strlen(aux) + 1];
	strcpy(me.unitateDeMasura, aux);

	return in;

}

int main()
{
	Marker m1;
	int v[]{1,3};
	Marker m2(1, "Albastru", "Milan", 2, v, 7.5);
	Marker m3(m2);
	m1 = m3;
	cout << m1;
	/*Marker m4("Gri", "Bic", 2);
	cout << m4<< endl;*/
	/*Marker m5;
	cin >> m5;
	cout << endl;
	cout << m5 << endl << endl;*/

	cout << endl << "---------Mostenire--------" << endl;
	MarkerElectronic me1;
	int w[]{ 1,4,5 };
	MarkerElectronic me2(4, "Negru", "Milan", 3, w, 10.5, 100,2,"milimetri");
	cout << me2 << endl;

	/*cin >> me1;
	cout << endl;
	cout << me1 << endl;*/

	if (m2 == m3)
	{
		cout << "Sunt la fel";
	}
	else cout << "Nu sunt la fel";

	Marker m4 = m2++;
	cout << endl;
	cout << m2[0] << " " << m4[0];

	Marker m5 = ++m2;
	cout << endl;
	cout << m2[0] <<" "<< m5[0];

	cout << endl<<m2.marirePret()<<" "<<me2.marirePret();
	int z[]{ 7,2,4,1 };

	Marker m6(7, "Rosu", "Milan", 3, w, 6);
	Marker m7(8, "Verde", "Bic", 2, v, 5.5);
	Marker m8(10, "Negru", "BMW", 4, z, 10.2);

	cout << endl << "------------MAP-------------" << endl;
	map<int, Marker>m;
	m.insert(make_pair(1, m2));
	m.insert(make_pair(2, m6));
	m.insert(make_pair(3, m7));
	m.insert(make_pair(4, m8));
	cout << m[4];

	cout << endl << "------------VECTOR-------------" << endl;
	vector<Marker>vectorSTL;
	vectorSTL.push_back(m2);
	vectorSTL.push_back(m6);
	vectorSTL.push_back(m7);
	vectorSTL.push_back(m8);

	float sumaMarkere = 0;
	for (int i = 0; i < vectorSTL.size(); i++)
	{
		sumaMarkere += vectorSTL[i].getPret();
	}

	cout << "Nota markere: " << sumaMarkere << endl;

	ofstream fisier1("Marker.txt", ios::out);
	fisier1 << m8;
	fisier1.close();

	ifstream fisier2("Marker.txt", ios::in);
	Marker m9;
	fisier2 >> m9;
	fisier2.close();

	cout << endl << m9 << endl;

	fstream fisier3("Marker.bin", ios::binary | ios::out);
	m7.serialize(fisier3);
	fisier3.close();

	fstream fisier4("Marker.bin", ios::binary | ios::in);
	m7.deserialize(fisier4);
	fisier4.close();

	cout << endl << "----------CITIRE BINAR-------------" << endl;
	cout << m7 << endl << endl;

	m6 += 10;
	cout << m6 << endl;

	m6 -= 2;
	cout << m6 << endl;
}