#include <iostream>

// освобождение памяти
void delmat(int **matr, size_t m)
{
    if (matr != nullptr)
    {
        for (size_t i = 0; i < m; i++)
        {
            delete[] matr[i];
        }
        delete[] matr;
    }
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
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (!(std::cin >> matr[i][j]))
            {
                std::cerr << "Matrix input failed.\n";
                delmat(matr, m);
                return 1;
            }
        }
    }
    // создание и заполнение транспонированной матрицы
    int **matr_t = new_matrix(n, m);
    if (matr_t == nullptr)
    {
        std::cerr << "Memory error.\n";
        delmat(matr, m);
        return 2;
    }
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            matr_t[i][j] = matr[j][i];
        }
    }
    // удаление и переприсваивание оссновной матрицы
    delmat(matr, m);
    matr = matr_t;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            std::cout << matr[i][j] << " ";
        }
        std::cout << "\n";
    }

    delmat(matr, n);
    return 0;
}
