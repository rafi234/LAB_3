#include <iostream>
#include <fstream>

using namespace std;

class Matrix
{
private:
    double **mat = nullptr;
    int x, y;

public:
    Matrix(int n, int m);
    Matrix(int n);
    Matrix(string filenam, string path);
    void CreateMatrix();
    Matrix substract(Matrix m2);
    Matrix add(Matrix m2);
    Matrix multiply(Matrix m2);
    int cols();
    int rows();
    void set(int n, int m, double val);
    double get(int n, int m);
    void print();
    void store(string filename, string path);
};

int main()
{
    cout << "\nTworzymy macierz A o wymiarach 4x4\n\n";
    Matrix A(4, 4);
    cout << " Przed zainicjowaniem wartosci: \n";
    A.print();
    A.CreateMatrix();
    cout << " Po zainicjowaniu wartosci wedlug przypadkowego wzoru: \n";
    A.print();
    cout << "\n\nTworzymy macierz B o wymiarach 4x4\n\n";
    Matrix B(4);
    cout << " Przed zainicjowaniem wartosci: \n";
    B.print();
    B.CreateMatrix();
    cout << " Po zainicjowaniu wartosci wedlug przypadkowego wzoru: \n";
    B.print();

    cout << "\n\nW macierzy A znajduja sie " << A.cols() << " kolumny i " << A.rows() << " wiersze" << endl
         << endl;

    cout << "Teraz sprawdzimy jaka wartosc znajduje sie w komurce o wspolrzednych (1, 3) w macierzy A\n";
    cout << "Wartosc w tej komurce jest rowna: " << A.get(1, 3) << endl
         << endl;
    double x = B.get(2, 3);
    cout << "Nastepnie  zmienimy warosc komurki (2, 3) w macierzy B na 10\n";
    B.set(2, 3, 10);
    cout << "Przed zamiana: " << x << "\nPo zamianie: " << B.get(2, 3) << endl
         << endl;

    cout << "Teraz dodajmy do siebie te macierze.\n\nPrzed dodaniem A wyglada nastepujaco:\n";
    A.print();
    cout << "\n\nNatomiast B wyglada tak:\n";
    B.print();
    cout << "\n\nPo dodaniu:\n";
    Matrix C = A.add(B);
    C.print();

    cout << "\n\nTeraz odejmiemy  macierz B od macierzy powstalej w wyniku dodania A i B\n\n";
    Matrix D = C.substract(B);
    D.print();

    cout << "\n\nNa koncu pomnozmy macierz uzyskana po odejmowaniu z macierza uzyskana po dodawaniu  \n\n";
    Matrix E = D.multiply(C);
    E.print();

    string filename = "plik.txt", path;
    cout << "\n\nTeraz zapiszymy macierz A do pliku\n\n";
    cout << "Podaj sciezke do zapisu\n";
    cin >> path;
    A.store(filename, path);

    cout << "Nastepnie wczytamy macierz A z pliku do innego obiektu\n\n";
    Matrix f(filename, path);
    cout << "Powstala macierz wyglada nastepujaco:\n\n";
    f.print();

    return 0;
}

Matrix::Matrix(int n, int m)
{
    if (n > 1 || m > 1)
    {
        x = n;
        y = m;
        mat = new double *[n];
        for (int i = 0; i < n; ++i)
            mat[i] = new double[m];
    }
    else
        cout << "blad\n";

    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
            mat[i][j] = 0;
    }
}

Matrix::Matrix(int n)
{
    if (n > 1)
    {
        y = n;
        x = n;
        mat = new double *[n];
        for (int i = 0; i < n; ++i)
            mat[i] = new double[n];
    }
    else
        cout << "blad\n";
    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
            mat[i][j] = 0;
    }
}

Matrix::Matrix(string filename, string path)
{
    ifstream plik(path);
    plik.open(filename);

    plik >> x >> y;

    mat = new double *[x];
    for (int i = 0; i < x; ++i)
        mat[i] = new double[y];

    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
            plik >> mat[i][j];
    }
    plik.close();
}

int Matrix::cols()
{
    return x;
}

int Matrix::rows()
{
    return y;
}

double Matrix::get(int n, int m)
{
    if (n < x && m < y)
        return mat[n][m];
    else
    {
        cout << "Podana komurka nie istnieje w podanej macierzy\n";
        return 0.0;
    }
}

void Matrix::set(int n, int m, double val)
{
    if (n < x && m < y)
        mat[n][m] = val;
    else
        cout << "Podana komurka nie istnieje w podanej macierzy\n";
}

void Matrix::print()
{
    for (int i = 0; i < x; ++i)
    {
        cout << endl;
        for (int j = 0; j < y; ++j)
        {
            cout.width(8);
            cout << mat[i][j] << "  ";
        }
    }
}

Matrix Matrix::substract(Matrix m2)
{
    if (x != m2.x && y != m2.y)
    {
        cout << "Nie da sie odjac macierzy, poniewaz nie sa one tej samej wielkosci!" << endl;
        return NULL;
    }
    else
    {
        Matrix temp(m2.x, m2.y);

        for (int i = 0; i < m2.x; ++i)
        {
            for (int j = 0; j < m2.y; ++j)
            {
                temp.mat[i][j] = m2.mat[i][j] - mat[i][j];
            }
        }

        return temp;
    }
}

Matrix Matrix::add(Matrix m2)
{
    if (x != m2.x && y != m2.y)
    {
        cout << "Nie da sie dodac macierzy, poniewaz nie sa one tej samej wielkosci!" << endl;
        return NULL;
    }
    else
    {
        Matrix temp(m2.x, m2.y);

        for (int i = 0; i < m2.x; ++i)
        {
            for (int j = 0; j < m2.y; ++j)
            {
                temp.mat[i][j] = m2.mat[i][j] + mat[i][j];
            }
        }

        return temp;
    }
}

Matrix Matrix::multiply(Matrix m2)
{
    if (x != m2.y)
    {
        cout << "Nie mozna pomnozyc macierzy, poniewaz liczba kolumn pierwszej nie jest rowna liczbie wierszy drugiej!" << endl;
        return NULL;
    }
    else
    {
        Matrix temp(y, m2.x);

        for (int i = 0; i < y; ++i)
        {
            for (int j = 0; j < m2.x; ++j)
            {
                temp.mat[i][j] = 0.0;

                for (int k = 0; k < x; ++k)
                    temp.mat[i][j] += mat[i][k] * m2.mat[k][j];
            }
        }
        return temp;
    }
}

void Matrix::CreateMatrix()
{
    for (int i = 0; i < x; ++i)
    {
        cout << endl;
        double temp_i = i;
        for (int j = 0; j < y; ++j)
        {
            double temp_j = j;
            mat[i][j] = ((temp_i + 1) * (temp_j + 4)) / 3;
        }
    }
}

void Matrix::store(string filename, string path)
{
    ofstream plik(path);
    plik.open(filename);

    if (plik.good() == false)
        cout << "Dostep do pliku zostal zabroniony!" << endl;

    plik << x << " " << y << endl;

    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
        {
            plik << get(i, j) << " ";
        }
        plik << endl;
    }
    plik.close();
}