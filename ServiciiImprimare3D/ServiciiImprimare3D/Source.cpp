#include<iostream>
#include<string>
#include<string.h>
#include<fstream>
#include<map>

using namespace std;

class Imprimare
{
private:
	char* material;
	int nrExemplare;
	string* exemplare;
	int categorii;
	static float pret;
	const int id;

public:

	Imprimare() :id(0)
	{
		this->material = new char[strlen("N/A") + 1];
		strcpy(this->material, "N/A");
		this->nrExemplare = 0;
		this->exemplare = nullptr;
		this->categorii = 0;
	}

	Imprimare(int id, const char* material, int nrExemplare, string* exemplare, int categorii) :id(id)
	{
		this->material = new char[strlen(material) + 1];
		strcpy(this->material, material);
		if (exemplare != nullptr && nrExemplare > 0)
		{
			this->nrExemplare = nrExemplare;
			this->exemplare = new string[nrExemplare];
			for (int i = 0; i < nrExemplare; i++)
			{
				this->exemplare[i] = exemplare[i];
			}
		}
		else
		{
			this->exemplare = nullptr;
			this->nrExemplare = 0;
		}
		this->categorii = categorii;
	}

	Imprimare(const Imprimare& im):id(im.id)
	{
		this->material = new char[strlen(im.material) + 1];
		strcpy(this->material, im.material);

		if (im.exemplare != nullptr && im.nrExemplare > 0)
		{
			this->nrExemplare = im.nrExemplare;
			this->exemplare = new string[im.nrExemplare];
			for (int i = 0; i < im.nrExemplare; i++)
			{
				this->exemplare[i] = im.exemplare[i];
			}
		}
		else
		{
			this->nrExemplare = 0;
			this->exemplare = nullptr;
		}

		this->categorii = im.categorii;
	}

	~Imprimare()
	{
		if (this->material != nullptr)
		{
			delete[]this->material;
			this->material = nullptr;
		}
		if (this->exemplare != nullptr)
		{
			delete[]this->exemplare;
			this->exemplare = nullptr;
		}
	}

	Imprimare& operator=(const Imprimare& im)
	{
		if (this != &im)
		{
			if (this->material != nullptr)
			{
				delete[]this->material;
				this->material = nullptr;
			}
			if (this->exemplare != nullptr)
			{
				delete[]this->exemplare;
				this->exemplare = nullptr;
			}

			this->material = new char[strlen(im.material) + 1];
			strcpy(this->material, im.material);

			if (im.exemplare != nullptr && im.nrExemplare > 0)
			{
				this->nrExemplare = im.nrExemplare;
				this->exemplare = new string[im.nrExemplare];
				for (int i = 0; i < im.nrExemplare; i++)
				{
					this->exemplare[i] = im.exemplare[i];
				}
			}
			else
			{
				this->exemplare = nullptr;
				this->nrExemplare = 0;
			}

			this->categorii = im.categorii;
		}

		return*this;
	}

	int getNrExemplare()
	{
		return this->nrExemplare;
	}

	string* getExemplare()
	{
		if (exemplare != nullptr)
		{
			string* copie = new string[nrExemplare];
			for (int i = 0; i < nrExemplare; i++)
			{
				copie[i] = exemplare[i];
			}
			return copie;
		}
		else
			return nullptr;
	}

	char* getMaterial()
	{
		if (material != nullptr)
		{
			char* copie = new char[strlen(material) + 1];
			strcpy(copie, material);

			return copie;
		}
		else
			return nullptr;
	}

	void setNrExemplare(int nrExemplare)
	{
		this->nrExemplare = nrExemplare;
	}

	void setExemaplare(string* exemplare, int nrExemplare)
	{
		if (exemplare != nullptr && nrExemplare > 0)
		{
			delete[]this->exemplare;
			this->nrExemplare = nrExemplare;
			this->exemplare = new string[nrExemplare];
			for (int i = 0; i < nrExemplare; i++)
			{
				this->exemplare[i] = exemplare[i];
			}
		}
		else
		{
			this->exemplare = nullptr;
			this->nrExemplare=0;
		}
	}

	void setMaterial(const char* material)
	{
		if (material != nullptr)
		{
			delete[]this->material;
			this->material = new char[strlen(material) + 1];
			strcpy(this->material, material);
		}
	}

	friend ostream& operator<<(ostream& out, Imprimare im);
	friend istream& operator>>(istream& in, Imprimare& im);

	bool operator<(Imprimare im)
	{
		if (this->categorii < im.categorii)
			return 1;
		return 0;
	}

	bool operator>(Imprimare im)
	{
		if (this->categorii > im.categorii)
			return true;
		return false;
	}

	/*static void sortare(Imprimare* imprimari, int nrImprimari)
	{
		for(int i=0;i<nrImprimari;i++)
			for (int j = i + 1; i < j <= nrImprimari; j++)
				if (imprimari[i].categorii < imprimari[j].categorii)
				{
					Imprimare aux = imprimari[i];
					imprimari[i] = imprimari[j];
					imprimari[j] = aux;
				}
	}*/

	int getCategorii()
	{
		return this->categorii;
	}

	Imprimare& operator+=(string exemplar)
	{
		Imprimare copie = *this;
		if (this->exemplare != nullptr)
		{
			delete[]this->exemplare;
		}
		this->nrExemplare++;
		this->exemplare = new string[this->nrExemplare];
		for (int i = 0; i < this->nrExemplare-1; i++)
		{
			this->exemplare[i] = copie.exemplare[i];
		}

		this->exemplare[this->nrExemplare - 1] = exemplar;

		return*this;
	}

	Imprimare& operator+(Imprimare im)
	{
		this->categorii = this->categorii + im.categorii;
		return *this;
	}

	Imprimare& operator+(int valoare)
	{
		this->categorii = this->categorii + valoare;
		return*this;
	}

	void serializare(fstream& file)
	{
		//char*
		int nrLitereMateriale = strlen(this->material);
		file.write((char*)&nrLitereMateriale, sizeof(nrLitereMateriale));
		for (int i = 0; i < nrLitereMateriale; i++)
		{
			file.write((char*)&this->material[i], sizeof(this->material[i]));
		}

		//int
		file.write((char*)&this->nrExemplare, sizeof(this->nrExemplare));

		//string*

		for (int i = 0; i < this->nrExemplare; i++)
		{
			file.write((char*)&this->exemplare[i], sizeof(this->exemplare[i]));
		}

		//int
		file.write((char*)&this->categorii, sizeof(this->categorii));

		file.close();
	}

	void deserializare(fstream& file)
	{
		if (this->exemplare != nullptr)
		{
			delete[]this->exemplare;
		}
		if (this->material != nullptr)
		{
			delete[]this->material;
		}

		//char*

		int nrLitereMateriale=0;
		file.read((char*)&nrLitereMateriale, sizeof(nrLitereMateriale));
		this->material = new char[nrLitereMateriale + 1];
		for (int i = 0; i < nrLitereMateriale; i++)
		{
			file.read((char*)&this->material[i], sizeof(this->material[i]));
		}
		this->material[nrLitereMateriale] = '\0';

		//int
		file.read((char*)&this->nrExemplare, sizeof(this->nrExemplare));

		//string*
		this->exemplare = new string[nrExemplare];
		for (int i = 0; i < nrExemplare; i++)
		{
			file.read((char*)&this->exemplare[i], sizeof(this->exemplare[i]));
		}

		//int
		file.read((char*)&this->categorii, sizeof(this->categorii));

		file.close();
	}

};
float Imprimare::pret = 100.0;

ostream& operator<<(ostream& out, Imprimare im)
{
	//out << "ID: " << im.id << endl;
	out << "Material: " << im.material << endl;
	out << "Numar exemplare: " << im.nrExemplare << endl;
	out << "Exemplare: ";
	for (int i = 0; i < im.nrExemplare; i++)
	{
		out << im.exemplare[i] << " ";
	}

	out <<endl<< "Categorii: " << im.categorii;

	return out;
}
istream& operator>>(istream& in, Imprimare& im)
{
	if (im.material != nullptr)
	{
		delete[]im.material;
	}
	if (im.exemplare != nullptr)
	{
		delete[]im.exemplare;
	}

	cout << "Material: ";
	char aux[50];
	in >> aux;
	im.material = new char[strlen(aux) + 1];
	strcpy(im.material, aux);

	cout << "Numar exemplare: ";
	in >> im.nrExemplare;

	cout << "Exemplare: ";
	im.exemplare = new string[im.nrExemplare];
	for (int i = 0; i < im.nrExemplare; i++)
	{
		in >> im.exemplare[i];
	}

	cout << "Categorii: ";
	in >> im.categorii;
	
	return in;
}

class Imprimare3D :public Imprimare
{
private:
	int cantitate;
	char* tip;
public:

	Imprimare3D() :Imprimare()
	{
		this->cantitate = 0;
		this->tip = nullptr;
	}

	Imprimare3D(int id, const char* material, int nrExemplare, string* exemplare, int categorii, int cantitate, const char* tip)
		:Imprimare(id, material, nrExemplare, exemplare, categorii)
	{
		this->cantitate = cantitate;
		if (tip != nullptr)
		{
			this->tip = new char[strlen(tip) + 1];
			strcpy(this->tip, tip);
		}
		else
		{
			this->tip = nullptr;
		}
	}

	Imprimare3D(const Imprimare3D& imd) :Imprimare(imd)
	{
		this->cantitate = imd.cantitate;
		if (imd.tip != nullptr)
		{
			this->tip = new char[strlen(imd.tip) + 1];
			strcpy(this->tip, imd.tip);
		}
		else
		{
			this->tip = nullptr;
		}
	}
	
	~Imprimare3D()
	{
		if (this->tip != nullptr)
		{
			delete[]this->tip;
			this->tip = nullptr;
		}
	}

	Imprimare3D& operator=(const Imprimare3D& imd)
	{
		if (this != &imd)
		{
			Imprimare::operator=(imd);
			if (this->tip != nullptr)
			{
				delete[]this->tip;
				this->tip = nullptr;
			}
			this->cantitate = imd.cantitate;
			if (imd.tip != nullptr)
			{
				this->tip = new char[strlen(imd.tip) + 1];
				strcpy(this->tip, imd.tip);
			}
		}

		return*this;
	}

	friend ostream& operator<<(ostream& out, Imprimare3D imd);

};

ostream& operator<<(ostream& out, Imprimare3D imd)
{
	out << (Imprimare)imd<<endl;//upcasting

	if (imd.tip != nullptr)
	{
		out << "Tip: " << imd.tip << endl;
	}
	out << "Cantitate: " << imd.cantitate << endl;

	return out;
}

class Vector
{
private:

};

int main()
{
	Imprimare im1;
	string v[]{ "gri","bej","alb" };
	Imprimare im2(1, "fag", 3, v, 2);
	Imprimare im3 = im2;
	Imprimare im4(im2);
	Imprimare im5;
	im5 = im4 = im2;

	cout << im5<<endl;

	cout << "------------------------"<<endl;
	/*cin >> im1;
	cout << endl;
	cout << im1 << endl;*/

	Imprimare im6(2, "lemn", 3, v, 5);
	Imprimare im7(3, "stejar", 3, v, 10);

	Imprimare imprimari[]{ im2, im6, im7 };
	for(int i=0;i<3;i++)
		for(int j=i+1;j<=3;j++)
			if (imprimari[i].getCategorii() < imprimari[j].getCategorii())
			{
				Imprimare aux = imprimari[i];
				imprimari[i] = imprimari[j];
				imprimari[j] = aux;
			}
	for (int i = 0; i < 3; i++)
	{
		cout << imprimari[i] << endl;
	}

	im2 += "mesteacan";
	cout << endl << "-------------------------------" << endl;
	cout << im2;

	cout << endl << "-------------------------------" << endl;
	Imprimare im8 = im2 + im5;
	cout << im8;
	
	cout << endl << "-------------------------------" << endl;
	Imprimare im9 = im8 + 15;
	cout << im9;
	cout << endl;

	Imprimare3D imd1;
	Imprimare3D imd2(5, "tei", 3, v, 2, 15,"Roman");
	cout << endl << "------------------IMPRIMARE 3D--------------------" << endl;
	cout << imd1 << endl;
	cout << endl << "--------------IMPRIMARE3D 2------------------"<<endl;
	cout << imd2<< endl;

	fstream fisier1("fisier.bin", ios::binary | ios::out);
	im2.serializare(fisier1);
	fisier1.close();

	cout << endl << "------------------CITIRE BINAR--------------------" << endl;
	fstream fisier2("fisier.bin", ios::binary | ios::in);
	//im2.deserializare(fisier2);
	fisier2.close();

	//cout << im2 << endl;

	cout << endl<<"---------Map-----------"<<endl;
	map<int, Imprimare> m;
	m.insert(make_pair(1, im2));
	m.insert(make_pair(2,im4));
	cout << m[2] << endl;
}