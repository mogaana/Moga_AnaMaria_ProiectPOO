#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

//FAZA 8
class AbstractMagazin {
public:
	virtual void clienti() = 0;
};

class AbstractDepozit {
public:
	virtual void disponibilitate() = 0;
};



class ApaDeParfum :public AbstractDepozit {
private:
	const int id;
	int n;										//dimens vector
	float* v;								    //in vector voi stoca preturile parfumurilor
	string marca;
	bool stoc;
	static int rating;

public:
	void disponibilitate() { //FAZA 8
		cout << "In depozitul comun sunt stocuri de parfumuri." << endl;
	}

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
	ApaDeParfum operator=(const ApaDeParfum& p)
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

	ApaDeParfum operator+(const ApaDeParfum& p)
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

	friend ostream& operator<<(ostream& out, const ApaDeParfum& parfum);

	friend istream& operator>>(istream& in, ApaDeParfum& parfum)
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
				cout << "Pret parfum " << i + 1 << ":";
				in >> parfum.v[i];
			}
		}
		else parfum.v = NULL;
		return in;
	}

	static int ratingMin()
	{
		return rating;
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

ostream& operator<<(ostream& out, const ApaDeParfum& parfum)
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



class Machiaj :public AbstractMagazin {
private:
	const int id;
	char* categorie;
	int pret;
	bool crueltyFree;
	static int durataExpirare; //dupa cate luni de la deschidere expira produsul?

public:
	void clienti() { //FAZA 8
		cout << "Clientii recomanda produsele din magazin." << endl;
	}

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
	Machiaj operator=(const Machiaj& p)
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

	bool operator<=(const Machiaj& p) {
		return this->pret <= p.pret;
	}

	friend ostream& operator<<(ostream& out, const Machiaj machiaj)
	{
		out << machiaj.id << ". " << "Categoria produsului de machiaj: " << machiaj.categorie << endl;
		out << "   Pret: " << machiaj.pret << endl;
		out << "   Produsul este Cruelty Free? (0-NU, 1-DA) " << machiaj.crueltyFree << endl;
		//out << "   Durata de expirare a produselor de machiaj este de: " << machiaj.durataExpirare << " luni.";
		return out;
	}

	friend istream& operator>>(istream& in, Machiaj& machiaj)
	{
		cout << "Introduceti CATEGORIA produsului de machiaj: ";
		char buffer[30];
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
	Manichiura operator=(const Manichiura& p)
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

	bool operator!=(const Manichiura& p) const {
		return this->categoria != p.categoria || this->m != p.m || this->produsDefect != p.produsDefect;
	}

	friend ostream& operator<<(ostream& out, Manichiura manichiura)
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

	friend istream& operator>>(istream& in, Manichiura& manichiura)
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



//FAZA 5 = RELATIA HAS-A o noua clasa care detine obiecte de tipul unei clase declarate anterior
class Parfumerie {
private:
	string denumire;
	int nrParf;
	ApaDeParfum* parfum;
	bool areAlcool;

public:
	string getDenumire() {
		return this->denumire;
	}

	void setDenumire(string denumire) {
		if (denumire.length() > 3)
			this->denumire = denumire;
		else this->denumire = "PARFUMERIE ONLINE";
	}

	int getNrParf() {
		return this->nrParf;
	}

	void setNrParf(int nrParf) {
		this->nrParf = nrParf;
	}

	ApaDeParfum* getParfum() {
		return this->parfum;
	}

	void setParfum(int nrParf, ApaDeParfum* parfum) {
		if (this->parfum != NULL)
			delete[]this->parfum;
		if (nrParf > 0 && parfum != NULL)
		{
			this->nrParf = nrParf;
			this->parfum = new ApaDeParfum[nrParf];
			for (int i = 0;i < nrParf;i++)
				this->parfum[i] = parfum[i];
		}
		else {
			this->parfum = NULL;
			this->nrParf = 0;
		}
	}

	bool getAlcool() {
		return this->areAlcool;
	}

	void setAlcool(bool areAlcool) {
		this->areAlcool = areAlcool;
	}

	Parfumerie()
	{
		this->denumire = "PARFUMERIE ONLINE";
		this->nrParf = 0;
		this->parfum = NULL;
		this->areAlcool = false;
	}

	Parfumerie(string denumire, int nrParf, ApaDeParfum* parfum, bool areAlcool)
	{
		if (denumire.length() > 3)
			this->denumire = denumire;
		else
			this->denumire = "PARFUMERIE ONLINE";
		if (nrParf > 0 && parfum != NULL) {
			this->nrParf = nrParf;
			this->parfum = new ApaDeParfum[nrParf];
			for (int i = 0;i < nrParf;i++)
				this->parfum[i] = parfum[i];
		}
		else {
			this->nrParf = 0;
			this->parfum = NULL;
		}
		this->areAlcool = areAlcool;
	}

	Parfumerie(const Parfumerie& p)
	{
		if (p.denumire.length() > 3)
			this->denumire = p.denumire;
		else
			this->denumire = "PARFUMERIE ONLINE";
		if (p.nrParf > 0 && p.parfum != NULL) {
			this->nrParf = p.nrParf;
			this->parfum = new ApaDeParfum[p.nrParf];
			for (int i = 0;i < p.nrParf;i++)
				this->parfum[i] = p.parfum[i];
		}
		else {
			this->nrParf = 0;
			this->parfum = NULL;
		}
		this->areAlcool = p.areAlcool;
	}

	~Parfumerie()
	{
		if (this->parfum != NULL)
			delete[]this->parfum;
	}

	friend ostream& operator<<(ostream& out, const Parfumerie& parf) {
		out << "PARFUMERIE: " << parf.denumire << endl;
		out << "NUMAR PARFUMURI: " << parf.nrParf << endl;
		for (int i = 0;i < parf.nrParf;i++)
			out << "PARFUMUL " << i + 1 << ": " << parf.parfum[i] << " " << endl;
		out << (parf.areAlcool ? "Produsele contin alcool." : "Produsele NU contin alcool.") << endl;
		return out;
	}

	Parfumerie operator=(const Parfumerie& p) {
		if (this != &p)
		{
			if (this->parfum != NULL)
				delete[]this->parfum;
			if (p.denumire.length() > 3)
				this->denumire = p.denumire;
			else
				this->denumire = "PARFUMERIE ONLINE";
			if (p.nrParf > 0 && p.parfum != NULL) {
				this->nrParf = p.nrParf;
				this->parfum = new ApaDeParfum[p.nrParf];
				for (int i = 0;i < p.nrParf;i++)
					this->parfum[i] = p.parfum[i];
			}
			else {
				this->nrParf = 0;
				this->parfum = NULL;
			}
			this->areAlcool = p.areAlcool;
		}
		return *this;
	}

	ApaDeParfum& operator[](int index) {
		if (index >= 0 && index < this->nrParf)
			return this->parfum[index];
	}

	explicit operator string() {
		return this->denumire;
	}
};



//FAZA 7 = RELATIA IS-A clasele vor mosteni atributele claselor declarate anterior
class ParfumuriArabesti :public ApaDeParfum {
private:
	int nrparfvandute;
	int* vector;

public:
	void disponibilitate() { //FAZA 8
		cout << "In depozitul comun sunt stocuri de parfumuri arabesti." << endl;
	}

	int getNrParfVandute() {
		return this->nrparfvandute;
	}

	void setNrParfVandute(int nrparfvandute) {
		if (nrparfvandute > 0)
			this->nrparfvandute = nrparfvandute;
		else this->nrparfvandute = 0;
	}

	int* getComenzi() {
		return this->vector;
	}

	void setComenzi(int nrparfvandute, int* vector) {
		if (nrparfvandute > 0 && vector != NULL)
		{
			this->nrparfvandute = nrparfvandute;
			this->vector = new int[nrparfvandute];
			for (int i = 0;i < nrparfvandute;i++)
				this->vector[i] = vector[i];
		}
		else {
			this->nrparfvandute = 0;
			this->vector = NULL;
		}
	}

	ParfumuriArabesti() :ApaDeParfum() {
		this->nrparfvandute = 0;
		this->vector = NULL;
	}

	ParfumuriArabesti(int id, int n, float* v, string marca, bool stoc, int nrparfvandute, int* vector) :ApaDeParfum(id, n, v, marca, stoc) {
		if (nrparfvandute > 0 && vector != NULL)
		{
			this->nrparfvandute = nrparfvandute;
			this->vector = new int[nrparfvandute];
			for (int i = 0;i < nrparfvandute;i++)
				this->vector[i] = vector[i];
		}
		else {
			this->nrparfvandute = 0;
			this->vector = NULL;
		}
	}

	ParfumuriArabesti(const ParfumuriArabesti& p) :ApaDeParfum(p) {
		if (p.nrparfvandute > 0 && p.vector != NULL)
		{
			this->nrparfvandute = p.nrparfvandute;
			this->vector = new int[p.nrparfvandute];
			for (int i = 0;i < p.nrparfvandute;i++)
				this->vector[i] = p.vector[i];
		}
		else {
			this->nrparfvandute = 0;
			this->vector = NULL;
		}
	}

	~ParfumuriArabesti() {
		if (this->vector != NULL)
			delete[]this->vector;
	}

	friend ostream& operator<<(ostream& out, const ParfumuriArabesti& parf) {
		out << (ApaDeParfum&)parf;
		out << "Numar comenzi: " << parf.nrparfvandute << endl;
		for (int i = 0;i < parf.nrparfvandute;i++)
			out << "Comanda " << i + 1 << ": " << parf.vector[i] << " parfumuri." << endl;
		return out;
	}

	ParfumuriArabesti operator=(const ParfumuriArabesti& p) {
		if (this != &p)
		{
			if (this->vector != NULL)
				delete[]this->vector;
			if (p.nrparfvandute > 0 && p.vector != NULL)
			{
				this->nrparfvandute = p.nrparfvandute;
				this->vector = new int[p.nrparfvandute];
				for (int i = 0;i < p.nrparfvandute;i++)
					this->vector[i] = p.vector[i];
			}
			else {
				this->nrparfvandute = 0;
				this->vector = NULL;
			}
		}
		return *this;
	}
};



class MachiajProduseCrueltyFree :public Machiaj {
private:
	string marca;
	bool etichetaVerde;

public:
	void clienti() { //FAZA 8
		cout << "Clientii recomanda produsele cruelty free din magazin." << endl;
	}

	string getMarca() {
		return this->marca;
	}

	void setMarca() {
		if (marca.length() > 4)
			this->marca = marca;
		else this->marca = "Catrice";
	}

	bool getCrueltyFree() {
		return this->etichetaVerde;
	}

	void setCrueltyFree(bool crueltyFree) {
		this->etichetaVerde = crueltyFree;
	}

	MachiajProduseCrueltyFree() :Machiaj() {
		this->marca = "Catrice";
		this->etichetaVerde = true;
	}

	MachiajProduseCrueltyFree(int id, const char* categorie, float pret, bool crueltyFree, string marca, bool etichetaVerde) :Machiaj(id, categorie, pret, crueltyFree) {
		this->marca = marca;
		this->etichetaVerde = etichetaVerde;
	}

	MachiajProduseCrueltyFree(const MachiajProduseCrueltyFree& p) :Machiaj(p) {
		if (p.marca.length() > 4)
			this->marca = p.marca;
		else this->marca = "Catrice";
		this->etichetaVerde = p.etichetaVerde;
	}

	friend ostream& operator<<(ostream& out, const MachiajProduseCrueltyFree& m)
	{
		out << (Machiaj&)m;
		out << "Marca prodului: " << m.marca << endl;
		out << (m.etichetaVerde ? "Produsele nu sunt testate pe animale." : "Produsele sunt testate pe animale.");
		return out;
	}
};



int main()
{
	float v[10] = { 125, 140, 167, 211, 110, 464, 257, 329, 159, 255 }; //vector cu preturile parfumurilor
	ApaDeParfum parfum1;
	ApaDeParfum parfum2(2, 10, v, "Givenchy", true);

	int vector[3] = { 11,5,20 };
	ParfumuriArabesti pa1;
	ParfumuriArabesti pa2(2, 10, v, "Givenchy", true, 3, vector);



	Machiaj prod2(2, "Fard de pleoape", 80, true);
	Machiaj prod3("Ruj", false);

	MachiajProduseCrueltyFree mcf1;
	MachiajProduseCrueltyFree mcf2(2, "Fard de pleoape", 80, true, "NYX", true);


	//FAZA 8

	cout << "EARLY BINDING CLASA ABSTRACTDEPOZIT + APADEPARFUM + PARFUMURIARABESTI: " << endl;
	parfum2.disponibilitate();
	pa1.disponibilitate();

	cout << endl << endl;

	cout << "LATE BINDING CLASA ABSTRACTDEPOZIT + APADEPARFUM + PARFUMURIARABESTI: " << endl;
	AbstractDepozit* d1, * d2;
	ApaDeParfum* pparfum1, * pparfum2;

	d1 = &parfum2;
	d2 = &pa1;
	d1->disponibilitate();
	d2->disponibilitate();

	pparfum1 = &parfum1;
	pparfum2 = &pa1;
	pparfum1->disponibilitate();
	pparfum2->disponibilitate();

	cout << endl << endl << endl << endl;

	cout << "EARLY BINDING CLASA ABSTRACTMAGAZIN + MACHIAJ + MACHIAJCF: " << endl;
	prod2.clienti();
	mcf1.clienti();

	cout << endl << endl;

	cout << "LATE BINDING CLASA ABSTRACTMAGAZIN + MACHIAJ + MACHIAJCF: " << endl;
	AbstractMagazin* m1, * m2;
	Machiaj* pprod1, * pprod2;

	m1 = &prod2;
	m2 = &mcf1;
	m1->clienti();
	m2->clienti();

	pprod1 = &prod3;
	pprod2 = &mcf1;
	pprod1->clienti();
	pprod2->clienti();
}
