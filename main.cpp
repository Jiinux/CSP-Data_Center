
#include <iostream>
#include <string>
using namespace std;

// Class 1: Variable
class Variable
{
public:
    string name;

    Variable()
    {
        name = "";
    }
};

// Class 2: Constraint
class Constraint
{
public:
    int experiment;

    Constraint()
    {
        experiment = 1;
    }

    bool check(int a[])
    {
        // VM1 and VM2 must be different
        if (a[0] != -1 && a[1] != -1)
        {
            if (a[0] == a[1])
                return false;
        }

        // VM3 and VM4 cannot both use Rack C
        if (a[2] == 2 && a[3] == 2)
            return false;

        // VM4 cannot use Rack C
        if (experiment != 2 && a[3] == 2)
            return false;

        // Extra conflicting rule in experiment 3
        if (experiment == 3)
        {
            if (a[0] != -1 && a[1] != -1)
            {
                if (a[0] != a[1])
                    return false;
            }
        }

        return true;
    }
};

// Class 3: CSP
class CSP
{
public:
    Variable VM[4];
    string Rack[3];
    Constraint rules;

    CSP()
    {
        VM[0].name = "VM1";
        VM[1].name = "VM2";
        VM[2].name = "VM3";
        VM[3].name = "VM4";

        Rack[0] = "Rack A";
        Rack[1] = "Rack B";
        Rack[2] = "Rack C";
    }
};

// Class 4: Solver
class Solver
{
public:
    int nodes;
    int backtracks;

    Solver()
    {
        nodes = 0;
        backtracks = 0;
    }

    // Naive Backtracking
    bool backtracking(CSP &c, int a[], int level)
    {
        if (level == 4)
            return true;

        for (int r = 0; r < 3; r++)
        {
            nodes++;

            a[level] = r;

            if (c.rules.check(a))
            {
                if (backtracking(c, a, level + 1))
                    return true;
            }

            a[level] = -1;
            backtracks++;
        }

        return false;
    }

    // Count legal values for MRV
    int countValues(CSP &c, int a[], bool d[][3], int v)
    {
        int count = 0;

        for (int r = 0; r < 3; r++)
        {
            if (d[v][r])
            {
                a[v] = r;

                if (c.rules.check(a))
                    count++;

                a[v] = -1;
            }
        }

        return count;
    }

    // MRV: choose the VM with the fewest choices
    int chooseVM(CSP &c, int a[], bool d[][3])
    {
        int chosen = -1;
        int smallest = 4;

        for (int i = 0; i < 4; i++)
        {
            if (a[i] == -1)
            {
                int number = countValues(c, a, d, i);

                if (number < smallest)
                {
                    smallest = number;
                    chosen = i;
                }
            }
        }

        return chosen;
    }

    // MRV + Forward Checking
    bool smartSearch(CSP &c, int a[], bool d[][3], int level)
    {
        if (level == 4)
            return true;

        int v = chooseVM(c, a, d);

        if (v == -1)
            return false;

        for (int r = 0; r < 3; r++)
        {
            if (d[v][r])
            {
                nodes++;
                a[v] = r;

                if (c.rules.check(a))
                {
                    bool old[4][3];

                    // Save old domains
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 3; j++)
                            old[i][j] = d[i][j];
                    }

                    // Forward Checking
                    bool failed = false;

                    for (int i = 0; i < 4; i++)
                    {
                        if (a[i] == -1)
                        {
                            for (int j = 0; j < 3; j++)
                            {
                                if (d[i][j])
                                {
                                    a[i] = j;

                                    if (!c.rules.check(a))
                                        d[i][j] = false;

                                    a[i] = -1;
                                }
                            }

                            if (!d[i][0] && !d[i][1] && !d[i][2])
                                failed = true;
                        }
                    }

                    if (!failed)
                    {
                        if (smartSearch(c, a, d, level + 1))
                            return true;
                    }

                    // Restore domains
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 3; j++)
                            d[i][j] = old[i][j];
                    }
                }

                a[v] = -1;
                backtracks++;
            }
        }

        return false;
    }

    void printSolution(CSP &c, int a[])
    {
        for (int i = 0; i < 4; i++)
        {
            cout << c.VM[i].name << " -> "
                 << c.Rack[a[i]] << endl;
        }
    }

    void run(CSP &c, int mode)
    {
        c.rules.experiment = mode;

        int a[4] = {-1, -1, -1, -1};

        nodes = 0;
        backtracks = 0;

        cout << "\nNaive Backtracking\n";

        if (backtracking(c, a, 0))
            printSolution(c, a);
        else
            cout << "No solution\n";

        cout << "Nodes: " << nodes << endl;
        cout << "Backtracks: " << backtracks << endl;

        // Prepare for the second algorithm
        for (int i = 0; i < 4; i++)
            a[i] = -1;

        bool d[4][3];

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 3; j++)
                d[i][j] = true;
        }

        nodes = 0;
        backtracks = 0;

        cout << "\nMRV + Forward Checking\n";

        if (smartSearch(c, a, d, 0))
            printSolution(c, a);
        else
            cout << "No solution\n";

        cout << "Nodes: " << nodes << endl;
        cout << "Backtracks: " << backtracks << endl;
    }
};

// Main
int main()
{
    CSP problem;
    Solver s;

    cout << "EXPERIMENT 1: Original Rules\n";
    s.run(problem, 1);

    cout << "\nEXPERIMENT 2: Network Rule Removed\n";
    s.run(problem, 2);

    cout << "\nEXPERIMENT 3: Conflicting Rule Added\n";
    s.run(problem, 3);

    return 0;
}
