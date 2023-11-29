#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class ApaDeParfum {
private:
	const int id;
	int n;										//dimens vector
	float* v;								    //in vector voi stoca preturile parfumurilor
	string marca;
	bool stoc;
	static int rating;

public:
	const int getId()  const {
		return this->id;
	}

	void setPretParf(int n, float* v) {
		if (this->v != NULL)
			delete[]this->v;
		if (n > 0 && v != NULL)
		{
			this->n = n;
			this->v = new float[n];
			for (int i = 0;i < n;i++)
				this->v[i] = v[i];
		}
		else
		{
			this->v = NULL;
			this->n = 0;
		}
	}

	float* getPretParf() {
		return this->v;
	}

	float getPretulParf(int index) {
		return this->v[index];
	}

	void setMarca(string marca) {
		if (marca.length() > 3)
			this->marca = marca;
	}

	string getMarca() {
		return this->marca;
	}

	void setStoc(bool stoc) {
		this->stoc = stoc;
	}

	bool getStoc() {
		return this->stoc;
	}

	static void setRating(int rating) {
		if (rating >= 2)
			ApaDeParfum::rating = rating;
	}

	static int getRating() {
		return ApaDeParfum::rating;
	}

	ApaDeParfum() :id(1)
	{
		this->n = 0;
		this->v = NULL;
		this->marca = "Mugler";
		this->stoc = false;
	}

	ApaDeParfum(int id, int n, float* v, string marca, bool stoc) :id(id)
	{
		if (n > 0 && v != NULL)
		{
			this->n = n;
			this->v = new float[n];
			for (int i = 0;i < n;i++)
				this->v[i] = v[i];
		}
		else
		{
			this->v = NULL;
			this->n = 0;
		}
		this->marca = marca;
		this->stoc = stoc;
	}

	ApaDeParfum(string marca, bool stoc) :id(3)
	{
		this->n = 0;
		this->v = NULL;
		this->marca = marca;
		this->stoc = stoc;
	}

	ApaDeParfum(const ApaDeParfum& p) :id(p.id)
	{
		if (p.n > 0 && p.v != NULL)
		{
			this->n = p.n;
			this->v = new float[p.n];
			for (int i = 0;i < p.n;i++)
				this->v[i] = p.v[i];
		}
		else
		{
			this->v = NULL;
			this->n = 0;
		}
		this->marca = p.marca;
		this->stoc = p.stoc;
	}

	~ApaDeParfum()
	{
		if (this->v != NULL)
			delete[]this->v;
	}

	friend float pretMaxim(const ApaDeParfum& parfum);
	friend float pretMediu(const ApaDeParfum& parfum);

	//FAZA 3
	ApaDeParfum operator=(const ApaDeParfum& p)								//OPERATOR = (DE ATRIBUIRE)
	{
		if (this != &p)
		{
			if (this->v != NULL)
				delete[]this->v;

			if (p.n > 0 && p.v != NULL)
			{
				this->n = p.n;
				this->v = new float[p.n];
				for (int i = 0;i < p.n;i++)
					this->v[i] = p.v[i];
			}
			else
			{
				this->v = NULL;
				this->n = 0;
			}
			this->marca = p.marca;
			this->stoc = p.stoc;
		}
		return *this;
	}

	ApaDeParfum operator+(const ApaDeParfum& p) // OPERATOR +                  
	{
		ApaDeParfum aux = *this;
		aux.n = this->n + p.n;
		if (aux.v != NULL)
			delete[] aux.v;
		if (aux.n > 0)
		{
			aux.v = new float[aux.n];
			for (int i = 0; i < this->n; i++)
				aux.v[i] = this->v[i];

			for (int i = this->n; i < aux.n; i++)
				aux.v[i] = p.v[i - this->n];

		}
		else aux.v = NULL;
		aux.marca += " " + p.marca; // concatenez marcile
		aux.stoc = aux.stoc && p.stoc; // verific stocul
		return aux;
	}

	friend ostream& operator<<(ostream& out, const ApaDeParfum& parfum); //OPERATOR <<

	friend istream& operator>>(istream& in, ApaDeParfum& parfum)	    //OPERATOR >> inline
	{
		cout << "Introduceti MARCA: ";
		in >> parfum.marca;
		cout << "Sunt in stoc produse cu ac marca? (0-NU, 1-DA) ";
		in >> parfum.stoc;
		cout << "Introducei NR parfumuri: ";
		in >> parfum.n;
		cout << "PRETURI parfumuri: " << endl;

		if (parfum.v != NULL)
		{
			delete[]parfum.v;
		}
		if (parfum.n > 0)
		{
			parfum.v = new float[parfum.n];
			for (int i = 0;i < parfum.n;i++)
			{
				cout << "Pret parfum " << i + 1 << ": ";
				in >> parfum.v[i];
			}
		}
		else parfum.v = NULL;
		return in;
	}

	float operator[](int index) {
		if (index >= 0 && index < this->n)
			return this->v[index];
	}

	static int ratingMin()
	{
		return rating;
	}



	//FAZA 6
	friend ofstream& operator<<(ofstream& out, const ApaDeParfum& parfum)
	{
		out << parfum.marca << " " << parfum.stoc << " " << parfum.rating;
		for (int i = 0; i < parfum.n; i++)
			out << parfum.v[i] << " ";
		return out;
	}

	friend ifstream& operator>>(ifstream& in, ApaDeParfum& parfum)
	{
		in >> parfum.marca >> parfum.stoc >> parfum.n;
		if (parfum.v != NULL)
		{
			for (int i = 0; i < parfum.n; i++)
			{
				delete[] & parfum.v[i];
			}
			delete[] parfum.v;
		}

		if (parfum.n > 0)
		{
			parfum.v = new float[parfum.n];
			for (int i = 0; i < parfum.n; i++)
			{
				parfum.v[i] = parfum.v[i];
			}
		}

		return in;
	}
};

int ApaDeParfum::rating = 3;

float pretMaxim(const ApaDeParfum& parfum)
{
	int max = 0;
	for (int i = 0;i < parfum.n;i++)
		if (parfum.v[i] > max)
			max = parfum.v[i];
	return max;
}

float pretMediu(const ApaDeParfum& parfum)
{
	float suma = 0;
	for (int i = 0;i < parfum.n;i++)
		suma = suma + parfum.v[i];
	int media = suma / parfum.n;
	return media;
}

ostream& operator<<(ostream& out, const ApaDeParfum& parfum)                        //FUNCTIE OPERATOR <<
{
	out << parfum.getId() << ". " << "Parfum: " << parfum.marca << endl;
	out << "   Sunt in stoc produse cu ac marca? (0-NU, 1-DA) " << parfum.stoc << endl;

	out << "   Preturile parfumurilor: ";
	if (parfum.v != NULL)
	{
		for (int i = 0;i < parfum.n;i++)
			out << parfum.v[i] << " ";
		out << endl;
	}
	else
		out << "nu avem parfumuri." << endl;
	//out << "   Rating-ul minim pentru selectia de parfumuri este de: " << parfum.rating << " stele.";
	return out;
}



class Machiaj {
private:
	const int id;
	char* categorie;
	int pret;
	bool crueltyFree;
	static int durataExpirare; //dupa cate luni de la deschidere expira produsul?

public:
	const int getId() {
		return this->id;
	}

	void setCategorie(char* categorie) {
		this->categorie = new char[strlen(categorie) + 1];
		strcpy_s(this->categorie, strlen(categorie) + 1, categorie);
	}

	char* getCategorie() {
		return this->categorie;
	}

	void setPret(int pret) {
		if (this->pret > 0)
			this->pret = pret;
	}

	int getPret() {
		return this->pret;
	}

	void setCrueltyFree(bool crueltyFree) {
		this->crueltyFree = crueltyFree;
	}

	bool getCrueltyFree() {
		return this->crueltyFree;
	}

	static void setDurataExpirare(int durataExpirare) {
		if (durataExpirare >= 12)
			Machiaj::durataExpirare = durataExpirare;
	}

	static int getDurataExpirare() {
		return Machiaj::durataExpirare;
	}

	Machiaj() :id(1)
	{
		this->categorie = new char[strlen("Paleta") + 1];
		strcpy_s(this->categorie, strlen("Paleta") + 1, "Paleta");
		this->pret = 100;
		this->crueltyFree = false;
	}

	Machiaj(int id, const char* categorie, float pret, bool crueltyFree) :id(id)
	{
		this->categorie = new char[strlen(categorie) + 1];
		strcpy_s(this->categorie, strlen(categorie) + 1, categorie);
		this->pret = pret;
		this->crueltyFree = crueltyFree;
	}

	Machiaj(const char* categorie, bool crueltyFree) :id(3)
	{
		this->categorie = new char[strlen(categorie) + 1];
		strcpy_s(this->categorie, strlen(categorie) + 1, categorie);
		this->crueltyFree = crueltyFree;
	}

	Machiaj(const Machiaj& p) :id(p.id)
	{
		this->categorie = new char[strlen(p.categorie) + 1];
		strcpy_s(this->categorie, strlen(p.categorie) + 1, p.categorie);
		this->pret = p.pret;
		this->crueltyFree = p.crueltyFree;
	}

	~Machiaj()
	{
		if (this->categorie != NULL)
			delete[]this->categorie;
	}

	//FAZA 3
	Machiaj operator=(const Machiaj& p)	 //OPERATOR = (DE ATRIBUIRE)
	{
		if (this != &p)
		{

			if (this->categorie != NULL)
				delete[]this->categorie;
			this->categorie = new char[strlen(p.categorie) + 1];
			strcpy_s(this->categorie, strlen(p.categorie) + 1, p.categorie);

			this->pret = p.pret;
			this->crueltyFree = p.crueltyFree;
		}
		return *this;
	}

	bool operator<=(const Machiaj& p) {  //OPERATOR <=
		return this->pret <= p.pret;
	}

	friend ostream& operator<<(ostream& out, const Machiaj machiaj) //OPERATOR <<
	{
		out << machiaj.id << ". " << "Categoria produsului de machiaj: " << machiaj.categorie << endl;
		out << "   Pret: " << machiaj.pret << endl;
		out << "   Produsul este Cruelty Free? (0-NU, 1-DA) " << machiaj.crueltyFree << endl;
		//out << "   Durata de expirare a produselor de machiaj este de: " << machiaj.durataExpirare << " luni.";
		return out;
	}

	friend istream& operator>>(istream& in, Machiaj& machiaj) //OPERATOR >>
	{
		cout << "Introduceti CATEGORIA produsului de machiaj: ";
		char buffer[256];
		in >> buffer;
		machiaj.setCategorie(buffer);
		if (machiaj.categorie != NULL)
			delete[]machiaj.categorie;
		machiaj.categorie = new char[strlen(buffer) + 1];
		strcpy_s(machiaj.categorie, strlen(buffer) + 1, buffer);

		cout << "Introduceti PRET: ";
		in >> machiaj.pret;
		cout << "Produsul este CRUELTY FREE? (0-NU, 1-DA) ";
		in >> machiaj.crueltyFree;
		cout << endl;
		return in;
	}

	static int durataExp()
	{
		return durataExpirare;
	}
};

int Machiaj::durataExpirare = 12;


class Manichiura {
private:
	const int id;
	string categoria;
	int m;
	int* w;								//aici voi stoca cate produse din categoria respectiva avem
	bool produsDefect;					//exista produse din categoria respectiva care au defecte? (ex. defecte fizice, data de expirare depasita)
	static int rating;

public:
	const int getId() {
		return this->id;
	}

	void setCategorie(string categoria) {
		if (categoria.length() > 3)
			this->categoria = categoria;
	}

	string getCategorie() {
		return this->categoria;
	}

	void setCateProd(int m, int* w) {
		if (this->w != NULL)
			delete[]this->w;
		if (m > 0 && w != NULL)
		{
			this->m = m;
			this->w = new int[m];
			for (int i = 0;i < m;i++)
				this->w[i] = w[i];
		}
		else
		{
			this->w = NULL;
			this->m = 0;
		}
	}

	int* getCateProd() {
		return this->w;
	}

	int getCateProd(int index) {
		return this->w[index];
	}

	void setProdusDefect(bool produsDefect) {
		this->produsDefect = produsDefect;
	}

	bool getProdusDefect() {
		return this->produsDefect;
	}

	static void setrating(int rating) {
		if (rating >= 2)
			Manichiura::rating = rating;
	}

	static int getRating() {
		return Manichiura::rating;
	}

	Manichiura() :id(1)
	{
		this->categoria = "Ingrijirea unghiilor";
		this->w = NULL;
		this->m = 0;
		this->produsDefect = false;
	}

	Manichiura(int id, string categoria, int m, int* w, bool produsDefect) :id(id)
	{
		this->categoria = categoria;
		if (m > 0 && w != NULL)
		{
			this->m = m;
			this->w = new int[m];
			for (int i = 0;i < m;i++)
				this->w[i] = w[i];
		}
		else
		{
			this->w = NULL;
			this->m = 0;
		}
		this->produsDefect = produsDefect;
	}

	Manichiura(string categoria, bool produsDefect) :id(3)
	{
		if (categoria.length() > 3)
			this->categoria = categoria;
		this->produsDefect = produsDefect;
	}

	Manichiura(const Manichiura& p) :id(p.id)
	{
		this->categoria = p.categoria;
		if (p.m > 0 && p.w != NULL)
		{
			this->m = p.m;
			this->w = new int[p.m];
			for (int i = 0;i < p.m;i++)
				this->w[i] = p.w[i];
		}
		else
		{
			this->w = NULL;
			this->m = 0;
		}
		this->produsDefect = p.produsDefect;
	}

	~Manichiura()
	{
		if (this->w != NULL)
		{
			delete[]this->w;
		}
	}

	//FAZA 3
	Manichiura operator=(const Manichiura& p) //OPERATOR = (DE ATRIBUIRE)
	{
		if (this != &p)
		{
			if (this->w != NULL)
			{
				delete[]this->w;
			}

			this->categoria = p.categoria;
			if (p.m > 0 && p.w != NULL)
			{
				this->m = p.m;
				this->w = new int[p.m];
				for (int i = 0;i < p.m;i++)
					this->w[i] = p.w[i];
			}
			else
			{
				this->w = NULL;
				this->m = 0;
			}
			this->produsDefect = p.produsDefect;
		}
		return *this;
	}

	bool operator!=(const Manichiura& p) const {  //OPERATOR !=
		return this->categoria != p.categoria || this->m != p.m || this->produsDefect != p.produsDefect;
	}

	friend ostream& operator<<(ostream& out, Manichiura manichiura) //OPERATOR <<
	{
		out << manichiura.getId() << ". ";
		out << "Categoria: " << manichiura.getCategorie() << endl;
		out << "   Sunt in stoc produse din ac categorie care au un defect? (0-NU, 1-DA) " << manichiura.getProdusDefect() << endl;
		out << "   Din aceasta categorie avem: ";
		if (manichiura.w != NULL) {
			for (int i = 0;i < manichiura.m;i++)
			{
				out << manichiura.w[i] << ", ";

			}
			out << "tipuri de produse (marci diferite).";
		}
		else cout << "0 tipuri de produse (marci diferite).";
		//out << "   Rating-ul acestor produse porneste de la: " << manichiura.Rating() << " stele.";
		return out;
	}

	friend istream& operator>>(istream& in, Manichiura& manichiura) //OPERATOR >>
	{
		cout << "Introduceti CATEGORIA produsului: ";
		in >> manichiura.categoria;
		cout << "Sunt in STOC produse din ac categorie care au un defect? (0-NU, 1-DA) ";
		in >> manichiura.produsDefect;
		cout << "Cate TIPURI DE PRODUSE (de marci diferite) avem? ";
		in >> manichiura.m;
		if (manichiura.w != NULL)
		{
			delete[]manichiura.w;
		}
		if (manichiura.m > 0)
		{
			manichiura.w = new int[manichiura.m];
			for (int i = 0;i < manichiura.m;i++)
			{
				cout << "Tip produs " << i + 1 << ":";
				in >> manichiura.w[i];
			}
		}
		else manichiura.w = NULL;
		return in;
	}

	static int Rating()
	{
		return Manichiura::rating;
	}
};

int Manichiura::rating = 2;


//FAZA 5
class MagazinOnline {
private:
	int nrparf;
	ApaDeParfum* parfum; //vector de obiecte
	bool areAlcool;

public:
	MagazinOnline()
	{
		this->nrparf = 2;
		this->parfum = new ApaDeParfum[2]; //apelez constructorul default din clasa ApaDeParfum
		this->areAlcool = false;
	}

	~MagazinOnline()
	{
		if (this->parfum != NULL)
			delete[]this->parfum;
	}

	int getNrParf() {
		return this->nrparf;
	}

	void setNrParf(int nrparf) {
		this->nrparf = nrparf;
	}

	ApaDeParfum* getParfum() {
		return this->parfum;
	}

	void setParfum(int nrparf, ApaDeParfum* parfum) {
		if (this->parfum != NULL)
			delete[]this->parfum;
		if (nrparf > 0 && parfum != NULL)
		{
			this->nrparf = nrparf;
			this->parfum = new ApaDeParfum[nrparf];
			for (int i = 0;i < nrparf;i++)
				this->parfum[i] = parfum[i];
		}
		else
		{
			this->parfum = NULL;
			this->nrparf = 0;
		}
	}

	bool getAlcool() {
		return this->areAlcool;
	}

	void setAlcool(bool areAlcool) {
		this->areAlcool = areAlcool;
	}

	friend ostream& operator<<(ostream& out, const MagazinOnline& magazin) { //????????????????
		out << "NUMAR PARFUMURI: " << endl;
		if (magazin.parfum != NULL)
		{
			for (int i = 0;i < magazin.nrparf;i++)
				out << magazin.parfum[i] << " " << endl;
		}
		out << (magazin.areAlcool ? "Produsele contin alcool." : "Produsele NU contin alcool.");
		return out;
	}

	ApaDeParfum operator[](int index) {
		if (index >= 0 && index < this->nrparf)
			return this->parfum[index];
	}

	explicit operator bool() {
		return this->areAlcool;
	}
};


int main()
{
	float v[10] = { 125, 140, 167, 211, 110, 464, 257, 329, 159, 255 }; //vector cu preturile parfumurilor

	ApaDeParfum parfum1;
	cout << parfum1;

	cout << endl;
	ApaDeParfum parfum2(2, 10, v, "Givenchy", true);
	cout << parfum2;
	cout << endl << "   Pretul maxim al unui parfum din ac marca este: " << pretMaxim(parfum2);
	cout << endl << "   Pretul mediu al parfumurilor din ac marca este: " << pretMediu(parfum2);

	cout << endl << endl;
	ApaDeParfum parfum3("Armani", false);
	cout << parfum3;

	cout << endl << endl;
	cout << "OPERATOR = (DE ATRIBUIRE): " << endl;
	ApaDeParfum parfum4;
	cout << parfum4;
	parfum4 = parfum3;
	cout << parfum4;

	cout << endl << endl;
	cout << "OPERATOR >>: " << endl;
	ApaDeParfum parfum5;
	cin >> parfum5;
	cout << endl;
	cout << parfum5;

	cout << endl << endl;
	cout << "OPERATOR +: " << endl;
	ApaDeParfum parfum6;
	parfum6 = parfum2 + parfum5;
	cout << parfum6;

	cout << endl << endl << "   Rating-ul minim pentru selectia de parfumuri este de: " << ApaDeParfum::ratingMin() << " stele.";

	cout << endl << endl << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;

	Machiaj prod1;
	cout << prod1;

	cout << endl << endl;
	Machiaj prod2(2, "Fard de pleoape", 80, true);
	cout << prod2;

	cout << endl << endl;
	Machiaj prod3("Ruj", false);
	cout << prod3;

	cout << endl << endl;
	cout << "OPERATOR >>: " << endl;
	Machiaj prod4;
	cin >> prod4;
	cout << endl << prod4;

	cout << endl << endl;
	cout << "OPERATOR = (DE ATRIBUIRE): " << endl;
	Machiaj prod5;
	cout << prod5;
	prod5 = prod4;
	cout << prod5;

	cout << endl << endl;
	cout << "OPERATOR <=: " << endl;
	Machiaj prod6(6, "Fond de ten", 150, true);
	cout << prod2 << endl << prod6 << endl;
	if (prod2 <= prod6)
		cout << "   Produsul cu id 2 are un pret mai mic sau egal cu produsul id 6." << endl;
	else
		cout << "   Produsul cu id 2 are un pret mai mare decat produsul id 6." << endl;

	cout << endl << endl << "   Durata de expirare a produselor de machiaj este de: " << Machiaj::durataExp() << " luni.";

	cout << endl << endl << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;

	int w[5] = { 10, 158, 52, 4, 0 }; //vector care retine cate tipuri de produse din categoria selectata avem

	Manichiura man1;
	cout << man1;

	cout << endl << endl;
	Manichiura man2(2, "Lac de unghii", 5, w, true);
	cout << man2;

	cout << endl << endl;
	Manichiura man3("Acetona", false);
	cout << man3;

	cout << endl << endl;
	cout << "OPERATOR >>: " << endl;
	Manichiura man4;
	cin >> man4;
	cout << man4;

	cout << endl << endl;
	cout << "OPERATORUL =: " << endl;
	Manichiura man5;
	cout << man5;
	man5 = man2;
	cout << endl << man5;

	cout << endl << endl;
	cout << "OPERATORUL !=: " << endl;
	Manichiura man6(2, "Lac de unghii", 5, w, true);
	cout << man2 << endl;
	cout << man6;
	cout << endl << endl;
	if (man2 != man6)
		cout << "   Cele doua obiecte sunt diferite." << endl;
	else
		cout << "   Cele doua obiecte sunt identice." << endl;

	cout << endl << endl << "   Rating-ul acestor produse porneste de la: " << Manichiura::Rating() << " stele.";

	cout << endl << endl << endl << endl;

	////FAZA 5
	//cout << "Relatia de HAS A: " << endl;
	//MagazinOnline magazin;
	//cout << magazin << endl; //?????????????
	//magazin[1] = parfum1;
	//cout << magazin[1].getMarca() << endl; //se va afisa Marca din constructorul default
	//bool alcool = (bool)magazin;
	//cout << magazin;

	//cout << endl << endl << endl << endl;

	//FAZA 6

	ApaDeParfum parfum11;
	ofstream file1;
	file1.open("parfum.txt", ios::out);
	file1 << parfum11;
	file1.close();

	ApaDeParfum parfum12;
	ifstream file2;
	file2.open("parfum.txt", ios::in);
	file2 >> parfum12;
	cout << parfum12;
	file2.close();

	cout << endl << endl;




}
