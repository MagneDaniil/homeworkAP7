#include <iostream>

void del_matrix(size_t k, int **&hs)
{
    for (size_t i = 0; i < k; i++)
    {
        delete[] hs[i];
    }
    delete[] hs;
}

int **concat_rows(const int *const *lhs, size_t n1, size_t m1, const int *const *rhs, size_t n2, size_t m2)
{
    size_t n_max = 0, m_max = 0, n_min = 0;
    if (n1 > n2)
    {
        n_max = n1;
        n_min = n2;
        m_max = m1;
    }
    else
    {
        n_max = n2;
        n_min = n1;
        m_max = m2;
    }

    size_t k = 0;
    int **comb_matrix = nullptr;
    try
    {
        // выделение памяти для комбинированной матрицы
        comb_matrix = new int *[n_max];
        for (k = 0; k < n_min; k++)
        {
            comb_matrix[k] = new int[m1 + m2];
        }
        for (k = n_min; k < n_max; k++)
        {
            comb_matrix[k] = new int[m_max];
        }

        for (int i = 0; i < n_min; i++)
        {
            for (int j = 0; j < m1; j++)
            {
                comb_matrix[i][j] = lhs[i][j];
            }
            for (int j = 0; j < m2; j++)
            {
                comb_matrix[i][m1 + j] = rhs[i][j];
            }
        }
        if (n1 > n2)
        {
            for (int i = n_min; i < n_max; i++)
            {
                for (int j = 0; j < m_max; j++)
                {
                    comb_matrix[i][j] = lhs[i][j];
                }
            }
        }
        if (n1 < n2)
        {
            for (int i = n_min; i < n_max; i++)
            {
                for (int j = 0; j < m_max; j++)
                {
                    comb_matrix[i][j] = rhs[i][j];
                }
            }
        }
    }
    catch (const std::bad_alloc &e)
    {
        del_matrix(k, comb_matrix);
        return nullptr;
    }
    return comb_matrix;
}

int **input_matrix(size_t n, size_t m, int **hs)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            std::cin >> hs[i][j];
            if (std::cin.fail())
            {
                del_matrix(n, hs);
                return nullptr;
            }
        }
    }
    return hs;
}

int **new_matrix(size_t n, size_t m)
{
    size_t k = 0;
    int **hs = nullptr;
    try
    {
        hs = new int *[n];
        for (k = 0; k < n; k++)
        {
            hs[k] = new int[m];
        }
    }
    catch (const std::bad_alloc &e)
    {
        del_matrix(k, hs);
        return nullptr;
    }
    return hs;
}

int main()
{
    const int input_error = 1;
    const int memory_error = 2;

    // ввод размерности
    int n1_int = 0, m1_int = 0, n2_int = 0, m2_int = 0;
    std::cin >> n1_int >> m1_int >> n2_int >> m2_int;
    if (std::cin.fail() || n1_int <= 0 || m1_int <= 0 || n2_int <= 0 || m2_int <= 0)
    {
        std::cerr << "Bad matrix dimensions.\n";
        return input_error;
    }
    size_t n1 = static_cast<size_t>(n1_int), m1 = static_cast<size_t>(m1_int), n2 = static_cast<size_t>(n2_int), m2 = static_cast<size_t>(m2_int);

    // ввод матриц
    int **lhs = new_matrix(n1, m1);
    if (lhs == nullptr)
    {
        std::cerr << "Memory error.\n";
        return memory_error;
    }
    lhs = input_matrix(n1, m1, lhs);
    if (lhs == nullptr)
    {
        std::cerr << "Input error.\n";
        return input_error;
    }
    int **rhs = new_matrix(n2, m2);
    if (rhs == nullptr)
    {
        del_matrix(n1, lhs);
        std::cerr << "Memory error.\n";
        return memory_error;
    }
    rhs = input_matrix(n2, m2, rhs);
    if (rhs == nullptr)
    {
        del_matrix(n1, lhs);
        std::cerr << "Input error.\n";
        return input_error;
    }

    // создание комбинированной матрицы
    int **comb_matrix = concat_rows(lhs, n1, m1, rhs, n2, m2);
    if (comb_matrix == nullptr)
    {
        del_matrix(n1, lhs);
        del_matrix(n2, rhs);
        return memory_error;
    }

    // вывод матрицы
    size_t n_min = 0, n_max = 0, m_max = 0;
    if (n1 > n2)
    {
        n_max = n1;
        n_min = n2;
        m_max = m1;
    }
    else
    {
        n_max = n2;
        n_min = n1;
        m_max = m2;
    }
    for (int i = 0; i < n_min; i++)
    {
        for (int j = 0; j < m1 + m2; j++)
        {
            std::cout << comb_matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    for (int i = n_min; i < n_max; i++)
    {
        for (int j = 0; j < m_max; j++)
        {
            std::cout << comb_matrix[i][j] << " ";
        }
        std::cout << "\n";
    }

    // удаление матриц
    del_matrix(n1, lhs);
    del_matrix(n2, rhs);
    del_matrix(n_max, comb_matrix);
    return 0;
}