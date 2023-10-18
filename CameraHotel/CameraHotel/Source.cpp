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
	virtual float taxare() = 0;//metoda virtuala pura=>clasa Taxare este abstracta
};
class Camera:public Taxare
{
private:
	int nrCamera;
	char* denumireCamera;
	string tip;
	int nrFacilitati;
	string* facilitati;
	const int id;
	static string patron;

public:
	Camera() :id(0)
	{
		this->nrCamera = 0;
		this->denumireCamera = nullptr;
		this->tip = "N/A";
		this->nrFacilitati = 0;
		this->facilitati = nullptr;
	}

	Camera(int id, int nrCamera, const char* denumireCamera, string tip, int nrFacilitati, string* facilitati) :id(id++)
	{
		this->nrCamera = nrCamera;
		this->denumireCamera = new char[strlen(denumireCamera) + 1];
		strcpy(this->denumireCamera, denumireCamera);
		this->tip = tip;
		if (facilitati != nullptr && nrFacilitati > 0)
		{
			this->nrFacilitati = nrFacilitati;
			this->facilitati = new string[nrFacilitati];
			for (int i = 0; i < nrFacilitati; i++)
			{
				this->facilitati[i] = facilitati[i];
			}
		}
		else
		{
			this->nrFacilitati = 0;
			this->facilitati = nullptr;
		}
	}

	Camera(const Camera& c) :id(c.id)
	{
		this->nrCamera = c.nrCamera;
		this->denumireCamera = new char[strlen(c.denumireCamera) + 1];
		strcpy(this->denumireCamera, c.denumireCamera);

		this->tip = c.tip;
		if (c.facilitati != nullptr && c.nrFacilitati > 0)
		{
			this->nrFacilitati = c.nrFacilitati;
			this->facilitati = new string[c.nrFacilitati];
			for (int i = 0; i < c.nrFacilitati; i++)
			{
				this->facilitati[i] = c.facilitati[i];
			}
		}
		else
		{
			this->nrFacilitati = 0;
			this->facilitati = nullptr;
		}
	}

	~Camera()
	{
		if (this->denumireCamera != nullptr)
		{
			delete[]this->denumireCamera;
			this->denumireCamera = nullptr;
		}

		if (this->facilitati != nullptr)
		{
			delete[]this->facilitati;
			this->facilitati = nullptr;
		}
	}

	Camera& operator=(const Camera& c)
	{
		if (this != &c)
		{
			if (this->denumireCamera != nullptr)
			{
				delete[]this->denumireCamera;
				this->denumireCamera = nullptr;
			}

			if (this->facilitati != nullptr)
			{
				delete[]this->facilitati;
				this->facilitati = nullptr;
			}
			this->nrCamera = c.nrCamera;
			this->denumireCamera = new char[strlen(c.denumireCamera) + 1];
			strcpy(this->denumireCamera, c.denumireCamera);

			this->tip = c.tip;
			if (c.facilitati != nullptr && c.nrFacilitati > 0)
			{
				this->nrFacilitati = c.nrFacilitati;
				this->facilitati = new string[c.nrFacilitati];
				for (int i = 0; i < c.nrFacilitati; i++)
				{
					this->facilitati[i] = c.facilitati[i];
				}
			}
			else
			{
				this->nrFacilitati = 0;
				this->facilitati = nullptr;
			}

		}
		return*this;
	}

	char* getDenumireCamera()
	{
		if (denumireCamera != nullptr)
		{
			char* copie = new char[strlen(denumireCamera) + 1];
			strcpy(copie, denumireCamera);

			return copie;
		}

		else
			return nullptr;
	}

	void setDenumireCamera(const char* denumireCamera)
	{
		if (denumireCamera != nullptr)
		{
			delete[]this->denumireCamera;
			this->denumireCamera = new char[strlen(denumireCamera) + 1];
			strcpy(this->denumireCamera, denumireCamera);
		}
	}

	string* getFacilitati()
	{
		if (facilitati != nullptr)
		{
			string* copie = new string[nrFacilitati];
			for (int i = 0; i < nrFacilitati; i++)
			{
				copie[i] = facilitati[i];
			}

			return copie;
		}
		else
			return nullptr;
	}

	void setFacilitati(int nrFacilitati, string* facilitati)
	{
		if (facilitati != nullptr && nrFacilitati > 0)
		{
			delete[]this->facilitati;
			this->nrFacilitati = nrFacilitati;
			this->facilitati = new string[nrFacilitati];
			for (int i = 0; i < nrFacilitati; i++)
			{
				this->facilitati[i] = facilitati[i];
			}
		}
	}

	int getNrCamera()
	{
		return this->nrCamera;
	}

	void setNrCamera(int nrCamera)
	{
		this->nrCamera = nrCamera;
	}

	Camera& operator++()
	{
		if(nrCamera>0)
		nrCamera++;
		return*this;
	}

	Camera operator++(int i)
	{
		Camera copie = *this;
		if (nrCamera > 0)
		{
			nrCamera++;
		}
		return copie;
	}

	Camera operator+=(Camera c)
	{
		this->nrCamera += c.nrCamera;
		return *this;
	}

	Camera operator+=(int valoare)
	{
		this->nrCamera += valoare;
		return *this;
	}
	string& operator[](int index)
	{
		if (index >= 0 && index <= nrFacilitati && facilitati != nullptr)
		{
			return facilitati[0];
		}
		else
			throw new InvalidIndex();
	}

	friend ostream& operator<<(ostream& out, Camera c);
	friend istream& operator>>(istream& in, Camera& c);
	friend ofstream& operator<<(ofstream& out, Camera c);
	friend ifstream& operator>>(ifstream& in, Camera& c);

	Camera& operator+=(string facilitate)
	{
		Camera copie = *this;
		if (this->facilitati != nullptr)
		{
			delete[]this->facilitati;
		}

		this->nrFacilitati++;

		this->facilitati = new string[this->nrFacilitati];

		for (int i = 0; i < this->nrFacilitati-1; i++)
		{
			this->facilitati[i] = copie.facilitati[i];
		}

		this->facilitati[this->nrFacilitati-1] = facilitate;

		return*this;
	}

	Camera& operator-=(int pozitie)
	{
		Camera copie = *this;
		if (this->facilitati != nullptr)
		{
			delete[]this->facilitati;
		}

		this->nrFacilitati--;
		this->facilitati = new string[this->nrFacilitati];

		for (int i = 0; i < pozitie; i++)
		{
			this->facilitati[i] = copie.facilitati[i];
		}

		for (int i = pozitie + 1; i < this->nrFacilitati+1; i++)
		{
			this->facilitati[i - 1] = copie.facilitati[i];
		}

		return*this;
	}

	void serialize(fstream& file)
	{
		//int
		file.write((char*)&this->nrCamera, sizeof(int));
		//char*
		int nrLitereDenumire = strlen(this->denumireCamera);
		file.write((char*)&nrLitereDenumire, sizeof(int));
		for (int i = 0; i < nrLitereDenumire; i++)
		{
			file.write((char*)&this->denumireCamera[i], sizeof(denumireCamera[i]));
		}

		//string

		int nrLitereTip = this->tip.size();
		file.write((char*)&nrLitereTip, sizeof(int));
		file.write(this->tip.c_str(), nrLitereTip);

		//int
		file.write((char*)&this->nrFacilitati, sizeof(int));

		//string*

		for (int i = 0; i < this->nrFacilitati; i++)
		{
			file.write((char*)&this->facilitati[i], sizeof(this->facilitati[i]));
		}

		file.close();
	}

	void deserialize(fstream& file)
	{
		if (this->denumireCamera != nullptr)
		{
			delete[]this->denumireCamera;
		}
		if (this->facilitati != nullptr)
		{
			delete[]this->facilitati;
		}
		//int
		file.read((char*)&this->nrCamera, sizeof(int));

		//char*
		int nrLitereDenumire = 0;
		file.read((char*)&nrLitereDenumire, sizeof(int));
		this->denumireCamera = new char[nrLitereDenumire + 1];
		for (int i = 0; i < nrLitereDenumire+1; i++)
		{
			file.read((char*)&this->denumireCamera[i], sizeof(this->denumireCamera[i]));
		}
		this->denumireCamera[nrLitereDenumire] = '\0';

		//string

		int nrLitereTip = 0;
		file.read((char*)&nrLitereTip, sizeof(int));
		string aux;
		aux.resize(nrLitereTip);
		file.read((char*)aux.c_str(), nrLitereTip);
		this->tip = aux;

		//int

		file.read((char*)&this->nrFacilitati, sizeof(int));

		//string*
		this->facilitati = new string[this->nrFacilitati];
		for (int i = 0; i < this->nrFacilitati; i++)
		{
			file.read((char*)&this->facilitati[i], sizeof(this->facilitati[i]));
		}

		file.close();
	}

	float taxare()
	{
		if (strcmp(this->denumireCamera, "President") == 0)
			return 500;
		if (strcmp(this->denumireCamera, "Standard") == 0)
			return 200;
	}
};
string Camera::patron = "Popescu";

ostream& operator<<(ostream& out, Camera c)
{
	out << "Numar camera: " << c.nrCamera << endl;
	if (c.denumireCamera != nullptr)
	{
		out << "Denumire camera: " << c.denumireCamera << endl;
	}

	out << "Tip camera: " << c.tip << endl;
	out << "Numar facilitati: " << c.nrFacilitati << endl;
	out << "Facilitati: ";
	for (int i = 0; i < c.nrFacilitati; i++)
	{
		out << c.facilitati[i] << " ";
	}

	return out;
}
istream& operator>>(istream& in, Camera& c)
{
	if (c.denumireCamera != nullptr)
	{
		delete[]c.denumireCamera;
	}
	if (c.facilitati != nullptr)
	{
		delete[]c.facilitati;
	}

	cout << "Numar camera: ";
	in >> c.nrCamera;

	char aux[50];
	cout << "Denumire camera: ";
	in >> aux;
	c.denumireCamera = new char[strlen(aux) + 1];
	strcpy(c.denumireCamera, aux);

	cout << "Tipul camerei: ";
	in >> c.tip;

	cout << "Numar facilitati: ";
	in >> c.nrFacilitati;

	c.facilitati = new string[c.nrFacilitati];
	cout << "Facilitati: ";
	for (int i = 0; i < c.nrFacilitati; i++)
	{
		in >> c.facilitati[i];
	}

	return in;
}
ofstream& operator<<(ofstream& out, Camera c)
{
	out << "Numar camera: " << c.nrCamera << endl;
	if (c.denumireCamera != nullptr)
	{
		out << "Denumire camera: " << c.denumireCamera << endl;
	}

	out << "Tip camera: " << c.tip << endl;
	out << "Numar facilitati: " << c.nrFacilitati << endl;
	out << "Facilitati: ";
	for (int i = 0; i < c.nrFacilitati; i++)
	{
		out << c.facilitati[i] << " ";
	}

	return out;
}
ifstream& operator>>(ifstream& in, Camera& c)
{
	if (c.denumireCamera != nullptr)
	{
		delete[]c.denumireCamera;
	}
	if (c.facilitati != nullptr)
	{
		delete[]c.facilitati;
	}

	cout << "Numar camera: ";
	in >> c.nrCamera;

	char aux[50];
	cout << "Denumire camera: ";
	in >> aux;
	c.denumireCamera = new char[strlen(aux) + 1];
	strcpy(c.denumireCamera, aux);

	cout << "Tipul camerei: ";
	in >> c.tip;

	cout << "Numar facilitati: ";
	in >> c.nrFacilitati;

	c.facilitati = new string[c.nrFacilitati];
	cout << "Facilitati: ";
	for (int i = 0; i < c.nrFacilitati; i++)
	{
		in >> c.facilitati[i];
	}

	return in;
}

class cameraVIP :public Camera
{
private:
	bool menajera;
public:
	cameraVIP() :Camera()
	{
		this->menajera = false;
	}

	cameraVIP(int id, int nrCamera, const char* denumireCamera, string tip, int nrFacilitati, string* facilitati, bool menajera)
		:Camera(id, nrCamera, denumireCamera, tip, nrFacilitati, facilitati)
	{
		this->menajera = menajera;
	}

	cameraVIP(const cameraVIP& cv) :Camera(cv)
	{
		this->menajera = cv.menajera;
	}

	~cameraVIP()
	{

	}

	cameraVIP& operator=(const cameraVIP& cv)
	{
		if (this != &cv)
		{
			Camera::operator=(cv);
			this->menajera = cv.menajera;
		}

		return *this;
	}
	friend ostream& operator<<(ostream& out, cameraVIP cv);

	float taxare() override
	{
		return 1000;
	}
};

ostream& operator<<(ostream& out, cameraVIP cv)
{
	out << (Camera)cv;

	out << "Menajera: " << cv.menajera;

	return out;
}

class Hotel
{
private:
	Camera* camere;
	int nrCamere;
	string nume;
public:

	Hotel()
	{
		this->camere = nullptr;
		this->nrCamere = 0;
		this->nume = "X";
	}

	Hotel(string nume, int nrCamere)
	{
		this->nume = nume;
		this->nrCamere = nrCamere;
		this->camere = new Camera[this->nrCamere];
	}

	Hotel(string nume, Camera camera)
	{
		this->nume = nume;
		this->nrCamere = 1;
		this->camere = new Camera[this->nrCamere];
		for (int i = 0; i < this->nrCamere; i++)
		{
			this->camere[i] = camera;
		}
	}

	Hotel(string nume, int nrCamere, Camera* camere)
	{
		this->nume = nume;
		this->nrCamere = nrCamere;
		this->camere = new Camera[this->nrCamere];
		for (int i = 0; i < this->nrCamere; i++)
		{
			this->camere[i] = camere[i];
		}
	}

	Hotel(const Hotel& h)
	{
		this->nume = h.nume;
		this->nrCamere = h.nrCamere;
		this->camere = new Camera[this->nrCamere];
		for (int i = 0; i < this->nrCamere; i++)
		{
			this->camere[i] = h.camere[i];
		}
	}

	~Hotel()
	{
		if (this->camere != nullptr)
		{
			delete[]this->camere;
			this->camere = nullptr;
		}
	}

	Hotel& operator=(const Hotel& h)
	{
		if (this != &h)
		{
			if (this->camere != nullptr)
			{
				delete[]this->camere;
				this->camere = nullptr;
			}

			this->nume = h.nume;
			this->nrCamere = h.nrCamere;
			this->camere = new Camera[this->nrCamere];
			for (int i = 0; i < this->nrCamere; i++)
			{
				this->camere[i] = h.camere[i];
			}
		}

		return*this;
	}

	static void determinareMinSiMax(Camera* camere, int nrCamere, int min, int max)
	{
		for (int i = 0; i < nrCamere; i++)
		{
			if (min > camere[i].getNrCamera())
			{
				min = camere[i].getNrCamera();
			}
			if (max < camere[i].getNrCamera())
			{
				max = camere[i].getNrCamera();
			}
		}

		cout << "Minimul este: " << min << ", iar maximul este: " << max;
	}
	friend ostream& operator<<(ostream& out, Hotel h);
	friend istream& operator>>(istream& in, Hotel& h);

	Hotel& operator+=(Camera c)
	{
		Hotel copie = *this;
		if (this->camere != nullptr)
		{
			delete[]this->camere;
		}

		this->nrCamere++;

		this->camere = new Camera[this->nrCamere];

		for (int i = 0; i < this->nrCamere - 1; i++)
		{
			this->camere[i] = copie.camere[i];
		}

		this->camere[this->nrCamere - 1] = c;

		return*this;
	}

};

ostream& operator<<(ostream& out, Hotel h)
{
	out << "Nume hotel: " << h.nume<<endl;
	out << "Numar camere: " << h.nrCamere<<endl;
	out << "Camere: "<<endl;
	for (int i = 0; i < h.nrCamere; i++)
	{
		out << h.camere[i] << endl;
	}

	return out;
}
istream& operator>>(istream& in, Hotel& h)
{
	if (h.camere != nullptr)
	{
		delete[]h.camere;
	}
	cout << "Nume hotel: ";
	in >> h.nume;

	cout << "Numar camere: ";
	in >> h.nrCamere;

	h.camere = new Camera[h.nrCamere];
	cout << "Camere: "<<endl;
	for (int i = 0; i < h.nrCamere; i++)
	{
		in >> h.camere[i];
	}

	return in;
}

int main()
{
	Camera c1;
	string v[]{ "AC","Room-service" };
	Camera c2(1, 1, "Standard", "Dubla", 2, v);
	cout << c2<<endl;
	Camera c3(c2);
	cout << c3 << endl;
	Camera c4;
	c4 = c3;
	cout << c4;

	c4 = ++c2;
	cout << endl;
	cout << c4.getNrCamera() << " " << c2.getNrCamera();

	c3 = c4++;
	cout << endl;
	cout << c4.getNrCamera() << " " << c3.getNrCamera();

	cout <<endl<< c2[0];
	c2[0] = "Mini-Frigider";
	cout <<" " <<c2[0]<<endl;

	/*cin >> c1;
	cout << endl;
	cout << c1;
	cout << endl;*/

	c2 += 15;
	//cout << c2;
	c2 += c4;
	//cout << c2;

	c2 += "Jacuzzi";
	cout << c2<<endl;

	c2 -= 1;
	cout << c2 << endl;

	ofstream fisier1("CameraHotel.txt", ios::out);
	fisier1 << c2;
	fisier1.close();

	ifstream fisier2("CameraHotel.txt", ios::in);
	Camera c6;
	fisier2 >> c6;
	fisier2.close();

	cout << c2 << endl << endl;

	string w[]{ "AC","Room-Service","Masaj" };
	Camera c5(2, 5, "President", "Tripla", 3, w);

	cout << endl << c5 << endl;

	Camera camere[]{ c4,c5 };
	Hotel h1("Provenza", 2, camere);

	cout <<endl<< h1<<endl;

	int min=999;
	int max=0;
	Hotel::determinareMinSiMax(camere,2, min, max);
	cout << endl;

	Hotel h2;
	/*cin >> h2;
	cout << endl;
	cout << h2 << endl;*/

	h1 += c2;
	cout << endl << "--------------------------" << endl;
	cout << h1;

	fstream fisier3("Camera.bin", ios::binary | ios::out);
	c5.serialize(fisier3);
	fisier3.close();

	/*cout << endl << "-------------CITIRE BINAR---------------" << endl;
	fstream fisier4("Camera.bin", ios::binary | ios::in);
	c5.deserialize(fisier4);
	fisier4.close();*/

	cout << c5 << endl << endl;
	cout << "Pretul camerei c5 este:" << c5.taxare()<<endl;
	cout << "Pretul camerei c2 este: " << c2.taxare();

	cout << endl << "----------MAP-----------" << endl;
	map<int, Camera>m;
	m.insert(make_pair(1, c2));
	m.insert(make_pair(2, c4));
	m.insert(make_pair(3, c5));
	cout << m[1];

	vector<Camera>vectSTLCamere;
	vectSTLCamere.push_back(c2);
	vectSTLCamere.push_back(c4);
	vectSTLCamere.push_back(c5);
	int total = 0;
	for (int i = 0; i < vectSTLCamere.size(); i++)
	{
		total += vectSTLCamere[i].taxare();
	}

	cout << endl << "Totalul rezervarii este: " << total;

	//cameraVIP cv1(11,24,"VIP","Dubla",3,v,0);
	//cout << endl << cv1 << endl;
	cameraVIP cv2(10, 23, "VIP", "Family", 2, w,true);
	cout << endl << cv2 << endl;

	cameraVIP cv3 = cv2;
	cameraVIP cv4;
	cv4 = cv3;

	cout << endl << cv4 << endl;
	cout << cv4.taxare();
}