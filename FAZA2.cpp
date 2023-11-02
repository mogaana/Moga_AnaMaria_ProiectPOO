#include <iostream>
using namespace std;

class ApaDeParfum {
private:
	const int id;
	int n;										//dimens vector
	float* v;									//in vector voi stoca preturile parfumurilor
	string marca;
	bool stoc;
	static int rating;

public:
	const int getId() {
		return this->id;
	}

	void setPretParf(int n, float* v) {  //SETTER COMPUS PT VECTOR
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

	ApaDeParfum() :id(1)					   //CONSTRUCTOR DEFAULT
	{
		this->n = 0;
		this->v = NULL;
		this->marca = "Mugler";
		this->stoc = true;
	}

	ApaDeParfum(int id, int n, float* v, string marca, bool stoc) :id(id) //CONSTRUCTOR CU PARAMETRI (TOTI) + ATRIBUT CONSTANT id
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

	ApaDeParfum(string marca, bool stoc) :id(3)							   //CONSTRUCTOR CU 2 PARAMETRI + ATRIBUT CONSTANT id
	{
		this->n = 0;
		this->v = NULL;
		this->marca = marca;
		this->stoc = stoc;
	}

	ApaDeParfum(const ApaDeParfum& p) :id(p.id)							   //CONSTRUCTOR DE COPIERE
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

	~ApaDeParfum()														   //DESTRUCTOR = dezaloc spatiul folosit de v
	{
		if (this->v != NULL)
			delete[]this->v;
	}

	friend float pretMaxim(const ApaDeParfum& parfum);
	friend float pretMediu(const ApaDeParfum& parfum);

	static int ratingMin()        //FUNCTIE STATICA
	{
		return rating;
	}
};

int ApaDeParfum::rating = 3;  //ATRIBUT STATIC

//CELE 2 FUNCTII GLOBALE (PRIETENE) PENTRU FAZA 2
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

	char* getCategorie() { //idk daca e bine
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

	static int durataExp()  //FUNCTIE STATICA
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
	bool produsDefect;					//exista produse din categoria respectiva care au defecte (ex. defecte fizice, data de expirare depasita) ?
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

	void setCateProd(int m, int* w) {  //SETTER COMPUS PT VECTOR
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

	static int Rating()  //FUNCTIE STATICA
	{
		return Manichiura::rating;
	}
};

int Manichiura::rating = 2;


int main() 
{
	float v[10] = { 125, 140, 167, 211, 110, 464, 257, 329, 159, 255 }; //vector cu preturile parfumurilor

	ApaDeParfum parfum1;
	cout << parfum1.getId() << ". ";
	cout << "Parfum: " << parfum1.getMarca() << endl;
	cout << "   Sunt in stoc produse cu aceasta marca? (0-NU, 1-DA) " << parfum1.getStoc();

	cout << endl << endl;
	ApaDeParfum parfum2(2, 10, v, "Givenchy", false);
	cout << parfum2.getId() << ". ";
	cout << "Parfum: " << parfum2.getMarca() << endl;
	cout << "   Sunt in stoc produse cu aceasta marca? (0-NU, 1-DA) " << parfum2.getStoc() << endl;
	cout << "   Preturile parfumurilor: " << parfum2.getPretulParf(0) << " " << parfum2.getPretulParf(1) << " " << parfum2.getPretulParf(2) << " " << parfum2.getPretulParf(3) << " " << parfum2.getPretulParf(4) << " " << parfum2.getPretulParf(5) << " " << parfum2.getPretulParf(6) << " " << parfum2.getPretulParf(7) << " " << parfum2.getPretulParf(8) << " " << parfum2.getPretulParf(9);
	//FAZA 2
	cout << endl << "   Pretul maxim al unui parfum din ac marca este: " << pretMaxim(parfum2); 
	cout << endl << "   Pretul mediu al parfumurilor din ac marca este: " << pretMediu(parfum2);

	cout << endl << endl;
	ApaDeParfum parfum3("Armani", true);
	cout << parfum3.getId() << ". ";
	cout << "Parfum: " << parfum3.getMarca() << endl;
	cout << "   Sunt in stoc produse cu aceasta marca? (0-NU, 1-DA) " << parfum3.getStoc();

	cout << endl << endl << "   Rating-ul minim pentru selectia de parfumuri este de: " << ApaDeParfum::ratingMin() << " stele.";

	cout << endl << endl << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;


	Machiaj prod1;
	cout << prod1.getId() << ". ";
	cout << "Categoria prodului de machiaj: " << prod1.getCategorie() << endl;
	cout << "   Pret: " << prod1.getPret() << endl;
	cout << "   Produsul este Cruelty Free? (0-NU, 1-DA) " << prod1.getCrueltyFree();

	cout << endl << endl;
	Machiaj prod2(2, "Fard de pleoape", 80, true);
	cout << prod2.getId() << ". ";
	cout << "Categoria prodului de machiaj: " << prod2.getCategorie() << endl;
	cout << "   Pret: " << prod2.getPret() << endl;
	cout << "   Produsul este Cruelty Free? (0-NU, 1-DA) " << prod2.getCrueltyFree();

	cout << endl << endl;
	Machiaj prod3("Ruj", false);
	cout << prod3.getId() << ". ";
	cout << "Categoria prodului de machiaj: " << prod3.getCategorie() << endl;
	cout << "   Pret: " << prod3.getPret() << endl;
	cout << "   Produsul este Cruelty Free? (0-NU, 1-DA) " << prod3.getCrueltyFree();

	cout << endl << endl << "   Durata de expirare a produselor de machiaj este de: " << Machiaj::durataExp() << " luni.";

	cout << endl << endl << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;


	int w[5] = { 10, 158, 52, 4, 0 }; //vector care retine cate produse din categoria selectata avem

	Manichiura man1;
	cout << man1.getId() << ". ";
	cout << "Categoria: " << man1.getCategorie() << endl;
	cout << "   Sunt in stoc produse din ac categorie care au un defect? (0-NU, 1-DA) " << man1.getProdusDefect();

	cout << endl << endl;
	Manichiura man2(2, "Lac de unghii", 5, w, true);
	cout << man2.getId() << ". ";
	cout << "Categoria: " << man2.getCategorie() << endl;
	cout << "   Sunt in stoc produse din ac categorie care au un defect? (0-NU, 1-DA) " << man2.getProdusDefect();

	cout << endl << endl;
	Manichiura man3("Acetona", false);
	cout << man3.getId() << ". ";
	cout << "Categoria: " << man3.getCategorie() << endl;
	cout << "   Sunt in stoc produse din ac categorie care au un defect? (0-NU, 1-DA) " << man3.getProdusDefect();

	cout << endl << endl << "   Rating-ul acestor produse porneste de la: " << Manichiura::Rating() << " stele.";

	cout << endl << endl;
}