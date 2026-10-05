#include <iostream>

// освобождение памяти
void delmat(int **matr, size_t m)
{
    for (size_t i = 0; i < m; i++)
    {
        delete[] matr[i];
    }
    delete[] matr;
}

// транспанирование
void transp(int **matr, int **matr_t, size_t m, size_t n)
{
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            matr_t[j][i] = matr[i][j];
        }
    }
}

// заполнение матрицы
int **input_matr(int **matr, size_t m, size_t n)
{
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (!(std::cin >> matr[i][j]))
            {
                std::cerr << "Matrix input failed.\n";
                delmat(matr, m);
                return nullptr;
            }
        }
    }
    return matr;
}

// создание новой матрицы с обработкой ошибки выделения памяти
int **new_matrix(size_t m, size_t n)
{
    int **matr = nullptr;
    size_t k = 0;
    try
    {
        matr = new int *[m];
        for (k = 0; k < m; k++)
        {
            matr[k] = new int[n];
        }
        return matr;
    }
    catch (const std::bad_alloc &e)
    {
        delmat(matr, k);
        return nullptr;
    }
}

int main()
{
    // размерность матрицы
    size_t m = 1;
    size_t n = 1;
    if (!(std::cin >> m >> n) || m == 0 || n == 0)
    {
        std::cerr << "Matrix input failed.\n";
        return 1;
    }

    // создание и заполнение основной матрицы
    int **matr = new_matrix(m, n);
    if (matr == nullptr)
    {
        std::cerr << "Memory error.\n";
        return 2;
    }
    matr = input_matr(matr, m, n);
    if (matr == nullptr)
    {
        std::cerr << "Matrix input failed.\n";
        return 1;
    }

    // создание и заполнение транспонированной матрицы
    int **matr_t = new_matrix(n, m);
    if (matr_t == nullptr)
    {
        std::cerr << "Memory error.\n";
        delmat(matr, m);
        return 2;
    }
    transp(matr, matr_t, m, n);

    // переприсваивание и вывод основной матрицы
    delmat(matr, m);
    matr = matr_t;
    int m_0 = m;
    m = n;
    n = m_0;
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            std::cout << matr[i][j] << " ";
        }
        std::cout << "\n";
    }
    delmat(matr, n);
    return 0;
}