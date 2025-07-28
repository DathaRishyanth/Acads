#include <bits/stdc++.h>
using namespace std;

class Employee
{
private:
    long long int employeeId;
    long long int age;
    long long int experience;
    long long int bossId;
    vector<Employee *> children; // For storing the employee under this particular employee
public:
    Employee(long long int a, long long int b, long long int c, long long int d)
    {
        // Constructor for employee
        employeeId = a;
        age = b;
        experience = c;
        bossId = d;
    }
    // Getter functions for attributes
    long long int getEmployeeId()
    {
        return employeeId;
    }
    long long int getBossId()
    {
        return bossId;
    }

    long long int getExperience()
    {
        return experience;
    }
    long long int getAge()
    {
        return age;
    }
    vector<Employee *> getChildren()
    {
        return children;
    }

    // for adding a child to a employee
    void addChild(Employee *child)
    {
        children.push_back(child);
    }
};

// comparator class for comparing employees for checking dominant employees
class Comparator
{
public:
    long long int i;

    Comparator(long long int k)
    {
        i = k;
    }

    bool operator()(Employee *a, Employee *b, map<long long int, Employee *> &employees)
    {
        if (i == 1)
        {
            if (a->getExperience() > b->getExperience() && depth(a, employees) < depth(b, employees))
                return true;
        }
        else if (i == 2)
        {
            if (a->getAge() > b->getAge() && depth(a, employees) < depth(b, employees))
                return true;
        }
        else if (i == 3)
        {
            if (a->getExperience() > b->getExperience() && a->getAge() < b->getAge())
                return true;
        }
        return false;
    }
};

// Age comparator class for comparing employees based on age and compare employeeId if ages are eqaul.
class AgeComparator
{
public:
    bool operator()(Employee *a, Employee *b)
    {
        if (a->getAge() == b->getAge())
            return a->getEmployeeId() < b->getEmployeeId();
        return a->getAge() < b->getAge();
    }
};

// returns a pair of total experience and number of subordinates
pair<long long int, long long int> totalExperience(Employee *head)
{
    if (head == NULL)
        return {0, 0};
    long long int exp = head->getExperience();
    long long int cnt = 1;
    for (auto &child : head->getChildren())
    {
        if (child != NULL)
        {
            exp += totalExperience(child).first;
            cnt += totalExperience(child).second;
        }
    }
    return {exp, cnt};
}

// prints the avergae experience
void avgExperience(Employee *head)
{
    if (head == NULL)
        return;
    auto ans = totalExperience(head);
    cout << ans.first / ans.second << endl;
}

// returns the depth of the tree
long long int depth(Employee *boss, map<long long int, Employee *> &employees)
{
    if (boss == nullptr)
        return -1;
    long long int bossId = boss->getBossId();
    if (bossId == boss->getEmployeeId())
        return 0;
    return 1 + depth(employees[bossId], employees);
}

// Fills ann array of employees with the subordinates of a employee
void fillWorkers(vector<Employee *> &workers, Employee *head)
{
    if (head == nullptr)
        return;
    workers.push_back(head);
    for (auto &child : head->getChildren())
    {
        fillWorkers(workers, child);
    }
}

// returns the kth youngest in an array of employees
long long int kthYoungest(Employee *head, long long int k, vector<Employee *> &employeeList, map<long long int, Employee *> &employee)
{

    vector<Employee *> Workers;
    fillWorkers(Workers, head);
    sort(Workers.begin(), Workers.end(), AgeComparator());
    if (k > Workers.size())
        return -1;
    return Workers[k - 1]->getEmployeeId();
}

int main()
{
    long long int n;
    cin >> n;
    map<long long int, Employee *> employees; // for getting employee based on employee Id
    vector<Employee *> employeesList;         // for storing list of employees
    for (long long int i = 0; i < n; i++)
    {
        long long int a, b, c, d;
        cin >> a >> b >> c >> d;
        Employee *emp = new Employee(a, b, c, d); // create Employee
        employeesList.push_back(emp);             // storing employee
        employees.insert({a, emp});
    }
    long long int boss = 0; // finding the boss
    for (auto &mem : employees)
    {
        if (mem.first == mem.second->getBossId())
        {
            boss = mem.first;
            break;
        }
    }

    // Building the tree of employees
    for (long long int i = 0; i < n; i++)
    {
        if (employeesList[i]->getBossId() != employeesList[i]->getEmployeeId())
            employees[employeesList[i]->getBossId()]->addChild(employeesList[i]);
    }

    long long int q;
    cin >> q;
    while (q--)
    {
        long long int cmd;
        cin >> cmd;
        if (cmd == 1)
        {
            long long int k;
            cin >> k;
            Comparator cmp(k);
            long long int cnt = 0;
            for (long long int i = 0; i < n; i++)
            {
                bool flag = true;
                for (long long int j = 0; j < n; j++)
                {
                    if (cmp(employeesList[j], employeesList[i], employees))
                    {
                        flag = false; // jth employee is domn=inant than ith employee
                        break;
                    }
                }
                if (flag) // ith employee is non-dominantable
                    cnt++;
            }
            cout << cnt << endl;
        }
        else if (cmd == 2)
        {
            long long int empId;
            cin >> empId;
            avgExperience(employees[empId]); // prints the avg exp
            long long int k;
            cin >> k;
            {
                long long int empId, k;
                cin >> empId >> k;
                // print the kth youngest employee in the subordinates of a employee.
                cout << kthYoungest(employees[empId], k, employeesList, employees) << endl;
            }
        }
    }
}
