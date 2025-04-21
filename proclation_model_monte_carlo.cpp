#include <bits/stdc++.h>
using namespace std;
class Proclate
{

private:
    int n;
    vector<vector<int>> x;
    vector<int> id;
    vector<int> sz;

    void unionOf(int i, int j)
    {
        int x = root(i);
        int y = root(j);
        // id[x] = y;
        if (x == y)
            return;
        if (sz[x] < sz[y])
            id[x] = y, sz[j] += sz[i];
        else
            id[y] = x, sz[i] += sz[j];
    }

    bool connected(int i, int j)
    {
        return root(i) == root(j);
    }

    int root(int i)
    {
        while (i != id[i])
        {
            id[i] = id[id[i]];
            i = id[i];
        }
        return i;
    }

    bool isOpen(int i, int j)
    {
        return x[i][j];
    }

public:
    Proclate(int _n) : n(_n), x(_n, vector<int>(_n, 0)), id(_n * _n + 2), sz(_n * _n + 2, 1)
    {
        for (size_t i = 0; i < n * n + 2; i++)
        {
            id[i] = i;
        }
    }

    void open(int i, int j)
    {
        if (!isOpen(i, j))
        {
            x[i][j] = 1;

            if (i == 0)
            {
                unionOf(j, n * n);
                if (j == 0)
                {
                    if (isOpen(i, j + 1))
                        unionOf(n * i + j, n * i + (j + 1));
                    if (isOpen(i + 1, j))
                        unionOf(n * i + j, n * (i + 1) + j);
                }
                else if (j == n - 1)
                {
                    if (isOpen(i, j - 1))
                        unionOf(n * i + j, n * i + (j - 1));
                    if (isOpen(i + 1, j))
                        unionOf(n * i + j, n * (i + 1) + j);
                }
                else
                {
                    if (isOpen(i, j - 1))
                        unionOf(n * i + j, n * i + (j - 1));
                    if (isOpen(i + 1, j))
                        unionOf(n * i + j, n * (i + 1) + j);
                    if (isOpen(i, j + 1))
                        unionOf(n * i + j, n * i + (j + 1));
                }
            }
            else if (i == n - 1)
            {
                unionOf(n * i + j, n * n + 1);
                if (j == 0)
                {
                    if (isOpen(i - 1, j))
                        unionOf(n * i + j, n * (i - 1) + j);
                    if (isOpen(i, j + 1))
                        unionOf(n * i + j, n * i + (j + 1));
                }
                else if (j == n - 1)
                {
                    if (isOpen(i - 1, j))
                        unionOf(n * i + j, n * (i - 1) + j);
                    if (isOpen(i, j - 1))
                        unionOf(n * i + j, n * i + (j - 1));
                }
                else
                {
                    if (isOpen(i, j - 1))
                        unionOf(n * i + j, n * i + (j - 1));

                    if (isOpen(i - 1, j))
                        unionOf(n * i + j, n * (i - 1) + j);
                    if (isOpen(i, j + 1))
                        unionOf(n * i + j, n * i + (j + 1));
                }
            }
            else if (j == 0)
            {
                if (isOpen(i - 1, j))
                    unionOf(n * i + j, n * (i - 1) + j);
                if (isOpen(i, j + 1))
                    unionOf(n * i + j, n * i + (j + 1));
                if (isOpen(i + 1, j))
                    unionOf(n * i + j, n * (i + 1) + j);
            }
            else if (j == n - 1)
            {
                if (isOpen(i - 1, j))
                    unionOf(n * i + j, n * (i - 1) + j);
                if (isOpen(i, j - 1))
                    unionOf(n * i + j, n * i + (j - 1));
                if (isOpen(i + 1, j))
                    unionOf(n * i + j, n * (i + 1) + j);
            }
            else
            {
                if (isOpen(i, j + 1))
                    unionOf(n * i + j, n * i + (j + 1));
                if (isOpen(i, j - 1))
                    unionOf(n * i + j, n * i + (j - 1));
                if (isOpen(i + 1, j))
                    unionOf(n * i + j, n * (i + 1) + j);
                if (isOpen(i - 1, j))
                    unionOf(n * i + j, n * (i - 1) + j);
            }
        }
    }

    bool proclates()
    {
        return connected(n * n, n * n + 1);
    }

    int count()
    {
        int c = 0;
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                if (isOpen(i, j))
                    c++;
            }
        }
        return c;
    }

    void reset()
    {
        for (size_t i = 0; i < n * n + 2; i++)
        {
            id[i] = i;
            sz[i] = 1;
        }
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                x[i][j] = 0;
            }
        }
    }
};

int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, t;
    cin >> n >> t;
    int x = t;
    auto start = chrono::high_resolution_clock::now();
    random_device rd;
    mt19937 gen(rd());
    vector<double> o;
    uniform_int_distribution<int> uid(0, n - 1);

    Proclate p(n);
    int c = 0;
    double sum = 0;
    double mean = 0, std = 0;

    while (t > 0)
    {
        cout << "Starting simulation " << x - t + 1 << endl;
        c = 0;
        while (!p.proclates())
        {
            int x = uid(gen);
            int y = uid(gen);
            p.open(x, y);
        }
        double result = static_cast<double>(p.count()) / (n * n);
        sum += result;
        o.push_back(result);
        cout << "Simulation " << x - t + 1 << " completed. Count: " << p.count() << endl;
        p.reset();
        t--;
    }
    mean = sum / x;
    cout << "\n\n";
    cout << "MEAN : " << mean << endl;

    double var = 0.0;
    for (auto i : o)
    {
        var += (i - mean) * (i - mean);
    }
    var = var / (x - 1);

    std = pow(var, 0.5);
    cout << "STD : " << std << "\n";

    double confLo99 = mean - ((2.54 * var) / sqrt(x));
    double confHi99 = mean + ((2.54 * var) / sqrt(x));

    double confLo95 = mean - ((1.96 * var) / sqrt(x));
    double confHi95 = mean + ((1.96 * var) / sqrt(x));

    cout << "95% confidence levels : (" << confLo95 << ", " << confHi95 << ")\n";
    cout << "99% confidence levels : (" << confLo99 << ", " << confHi99 << ")\n";

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Time taken: " << duration.count() << " microseconds" << endl;

    return 0;
}