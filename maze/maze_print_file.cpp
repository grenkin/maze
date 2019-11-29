/*
    Модуль ввода-вывода лабиринта в файл

    Реализации методов
        Maze
            конструктор (ввод из файла)
            print_data (вывод в файл)

    Вспомогательные функции
        read_bool_matrix
        print_bool_matrix
*/

#include <fstream>
#include "maze.h"

using namespace std;

/************************************************
    объявления
************************************************/

// прочитать из файла fin булеву матрицу из n строк и m столбцов
vector<vector<bool> > read_bool_matrix (ifstream& fin, int n, int m);
// вывести в файл fout булеву матрицу из n строк и m столбцов
void print_bool_matrix (ofstream& fout, vector<vector<bool> > mat);


/************************************************
    реализация методов класса Maze
************************************************/

// конструктор класса Maze
// считывает данные о лабиринте из файла
Maze::Maze (const char *file_name)
/*
    формат входного файла:
    n m
    walls_v : [1..n, 1..m-1]Bool
    walls_h : [1..n-1, 1..m]Bool
*/
{
    // открыть файл для чтения
    ifstream fin(file_name);

    // считать размерность лабиринта
    fin >> n >> m;
    if (! (1 <= n && 1 <= m))
        throw "Incorrect dimension";

    // инициализировать walls_v и walls_h
    init_maze(n, m);

    vector<vector<bool> > mat1 = read_bool_matrix(fin, n, m-1);
    vector<vector<bool> > mat2 = read_bool_matrix(fin, n-1, m);
    // mat1 : [0..n-1,0..m-2]Bool,  mat2 : [0..n-2,0..m-1]Bool

    // TODO : заменить на 2 вызова функции копирования фрагмента
    //   одной матрицы в другую матрицу
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m - 1; ++j)
            walls_v[i][j] = mat1[i - 1][j - 1];
    }
    for (int i = 1; i <= n - 1; ++i) {
        for (int j = 1; j <= m; ++j)
            walls_h[i][j] = mat2[i - 1][j - 1];
    }
}

/***********************************************/

// вывести данные о лабиринте в файл
void Maze::print_data (const char *file_name)
/*
    формат выходного файла:
    n m
    walls_v : [1..n, 1..m-1]Bool
    walls_h : [1..n-1, 1..m]Bool
*/
{
    ofstream fout(file_name);
    fout << n << "  " << m << "\n\n\n";

    /* инициализируем булевы матрицы */
    // mat1[0..n-1, 0..m-2], mat2[0..n-2, 0..m-1]
    // TODO : заменить на два вызова функции инициализации
    vector<vector<bool> > mat1, mat2;
    mat1.resize(n);
    for (int i = 0; i <= n - 1; ++i)
        mat1[i].resize(m - 1);
    mat2.resize(n - 1);
    for (int i = 0; i <= n - 2; ++i)
        mat2[i].resize(m);

    /* заполняем булевы матрицы */
    // TODO : заменить на 2 вызова функции копирования фрагмента
    //   одной матрицы в другую матрицу
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m - 1; ++j)
            mat1[i - 1][j - 1] = walls_v[i][j];
    }
    for (int i = 1; i <= n - 1; ++i) {
        for (int j = 1; j <= m; ++j)
            mat2[i - 1][j - 1] = walls_h[i][j];
    }

    /* выводим булевы матрицы */
    print_bool_matrix(fout, mat1);
    fout << "\n\n";
    print_bool_matrix(fout, mat2);

    fout.close();

    // выводим лабиринт
    FILE *f = fopen(file_name, "a");
    fprintf(f, "\n\n\n");
    print({0, 0}, f);
    fclose(f);
}


/************************************************
    реализация вспомогательных функций
************************************************/

// прочитать из файла fin булеву матрицу из n строк и m столбцов
/*
    вход
        [n*m]{0, 1}
    выход
        mat : [0..n-1,0..m-1]Bool
        mat[i,j], i=0..n-1, j=0..m-1
*/
vector<vector<bool> > read_bool_matrix (ifstream& fin, int n, int m)
{
    vector<vector<bool> > mat;
    mat.resize(n);
    for (int i = 0; i < n; ++i)
        mat[i].resize(m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int x;
            fin >> x;
            mat[i][j] = x;
        }
    }
    return mat;
}

// вывести в файл fout булеву матрицу из n строк и m столбцов
/*
    вход
        mat : [0..n-1,0..m-1]Bool
        mat[i,j], i=0..n-1, j=0..m-1
    вход
        [n*m]{0, 1}
            mat[0,0] mat[0,1] mat[0,2] ... mat[0,m-1]
            mat[1,0] mat[1,1] mat[1,2] ... mat[1,m-1]
            mat[2,0] mat[2,1] mat[2,2] ... mat[2,m-1]
            .........................................
            mat[n-1,0] mat[n-1,1] mat[n-1,2] ... mat[n-1,m-1]
*/
void print_bool_matrix (ofstream& fout, vector<vector<bool> > mat)
{
    int n = mat.size(), m = mat[0].size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            fout << (int)mat[i][j] << " ";
        }
        fout << "\n";
    }
}
