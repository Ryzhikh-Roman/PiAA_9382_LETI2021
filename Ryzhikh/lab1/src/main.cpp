#include <iostream>
#include <vector>

int N;
int minCounter;
std::vector<std::pair<int, std::pair<int, int>>> resArr;

void printAnswer(int scale = 1)
{
    std::cout << minCounter << '\n';
    for (int i = 0; i < minCounter; i++)
    {
        std::cout << resArr[i].second.first * scale + 1 << ' ' << resArr[i].second.second * scale + 1 << ' ' << resArr[i].first * scale << '\n';
    }
}

void insertBlock(std::vector<std::vector<bool>>& mainArr, int m, int x, int y) //Вставка квадрата размером m * m с левым верхним углов в точке (x, y)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            mainArr[x + i][y + j] = true;
        }
    }
}

void removeBlock(std::vector<std::vector<bool>>& mainArr, int m, int x, int y) //Вставка квадрата размером m * m с левым верхним углов в точке (x, y)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            mainArr[x + i][y + j] = false;
        }
    }
}

std::pair<int, int> findEmpty(std::vector<std::vector<bool>>& mainArr) //Поиск первой свободной ячейки для вставки
{
    for (int i = N / 2; i < N; i++)
    {
        for (int j = N / 2; j < N; j++)
        {
            if (!mainArr[i][j])
                return std::make_pair(i, j);
        }
    }
    return std::make_pair(-1, -1);
}

std::pair<int, bool> findMaxSize(std::vector<std::vector<bool>>& mainArr, int x, int y)
{
    for (int i = y + 1; i < N; i++)
    {
        if (mainArr[x][i])
        {
            if (N - x == i - y)
                return std::make_pair(N - x, true);
            return std::make_pair((N - x > i - y) ? i - y : N - x, false);
        }
    }
    if (N - x == N - y)
        return std::make_pair(N - x, true);
    return std::make_pair((N - x > N - y) ? N - y : N - x, false);
}

void chooseBlock(std::vector<std::vector<bool>>& mainArr, std::vector<std::pair<int, std::pair<int, int>>>& tmpArr, int counter, int x, int y)
{
    std::pair<int, int> coord = findEmpty(mainArr);
    if (coord.first == -1)
    {
        if (tmpArr.size() < minCounter)
        {
            resArr = tmpArr;
            minCounter = tmpArr.size();
        }
        return;
    }
    if (counter + 1 >= minCounter)
    {
        return;
    }
    int tmpBestCounter = minCounter;
    //поиск места для вставки блока
    std::pair<int, bool> maxSize = findMaxSize(mainArr, coord.first, coord.second); //поиск максимального размера блока для вставки на найденное пустое место
    if (maxSize.second)                                                        //Если можно вставить сразу блок максимального размера
    {
        tmpArr.push_back(make_pair(maxSize.first, coord));
        insertBlock(mainArr, maxSize.first, coord.first, coord.second);
        chooseBlock(mainArr, tmpArr, counter + 1, x, y); //вставляем очередной блок
        removeBlock(mainArr, maxSize.first, coord.first, coord.second);
        tmpArr.pop_back();
    }
    else
    {
        for (int i = maxSize.first; i >= 1; i--)
        {
            if (tmpBestCounter > minCounter && i == 1)
                continue;
            tmpArr.push_back(make_pair(i, coord));
            insertBlock(mainArr, i, coord.first, coord.second);
            chooseBlock(mainArr, tmpArr, counter + 1, x, y); //вставляем очередной блок
            removeBlock(mainArr, i, coord.first, coord.second);
            tmpArr.pop_back();
        }
    }
}

void primeNumber(std::vector<std::vector<bool>>& mainArr) //вставка начальных блоков и начало работы бэктрекинга
{
    insertBlock(mainArr, N / 2 + 1, 0, 0);
    insertBlock(mainArr, N / 2, N / 2 + 1, 0);
    insertBlock(mainArr, N / 2, 0, N / 2 + 1);
    int counter = 3;
    int minCounter = N * N;
    std::vector<std::pair<int, std::pair<int, int>>> tmpArr;
    tmpArr.push_back(std::make_pair(N / 2 + 1, std::make_pair(0, 0)));
    tmpArr.push_back(std::make_pair(N / 2, std::make_pair(N / 2 + 1, 0)));
    tmpArr.push_back(std::make_pair(N / 2, std::make_pair(0, N / 2 + 1)));
    chooseBlock(mainArr, tmpArr, counter, N / 2, N / 2);
}

void division2()
{
    if (N % 2 == 0)
    {
        int N_div = N / 2;
        std::cout << 4 << '\n';
        std::cout << 1 << ' ' << 1 << ' ' << N_div << '\n';
        std::cout << N_div + 1 << ' ' << 1 << ' ' << N_div << '\n';
        std::cout << 1 << ' ' << N_div + 1 << ' ' << N_div << '\n';
        std::cout << N_div + 1 << ' ' << N_div + 1 << ' ' << N_div << '\n';
    }
}

void division3(std::vector<std::vector<bool>>& mainArr)
{
    int realN = N;
    int scale = N / 3;
    N = 3;
    primeNumber(mainArr);
    printAnswer(scale);
}

void division5(std::vector<std::vector<bool>>& mainArr)
{
    int realN = N;
    int scale = N / 5;
    N = 5;
    primeNumber(mainArr);
    printAnswer(scale);
}

int main()
{
    std::cin >> N;
    minCounter = N * N;
    if (N % 2 == 0)
    {
        division2();
        return 0;
    }
    //создание "карты" столешницы
    std::vector<std::vector<bool>> mainArr(N);
    for (int i = 0; i < N; i++)
        mainArr[i].resize(N);

    if (N % 3 == 0)
    {
        division3(mainArr);
    }
    else if (N % 5 == 0)
    {
        division5(mainArr);
    }
    else
    {
        primeNumber(mainArr);
        printAnswer();
    }

    return 0;
}