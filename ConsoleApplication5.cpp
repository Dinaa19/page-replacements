// ConsoleApplication5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include<queue>
#include<unordered_set>
#include<unordered_map>
using namespace std;
const int numbers = 100005;
int n;
int frame;
int pageArray[numbers];
int pointer[numbers];

void fifoalgo(void)
{
    queue<int> que;
    int pagefaults = 0;
    for (int i = 0; i < n; i++)
    {
        if (pointer[pageArray[i]] == true)
        {
            cout << " " << pageArray[i] << " No page faults \n";
        }
        else
        {
            que.push(pageArray[i]);
            pointer[pageArray[i]] = true;
            if (que.size() > frame)
            {
                int p = que.front();
                pointer[p] = false;
                que.pop();
            }
            pagefaults++;
            cout << " " << pageArray[i] << " page fault occured \n";
        }
    }
    cout << " Page Faults = " << pagefaults;
    return;
}
void lrualgo()
{
    vector<int> vec;
    int pagefaults = 0;
    for (int i = 0; i < n; i++)
    {
        int m;
        for (m = 0; m < vec.size(); m++)
            if (vec[m] == pageArray[i])
                break;
        if (m == vec.size())
        {
            if (vec.size() < frame)
                vec.push_back(pageArray[i]);

            else
            {
                int index = i + 1;
                int empty = -1, temp = index;
                for (int l = 0; l < vec.size(); l++)
                {
                    int j;
                    for (j = index; j < n; j++)
                    {
                        if (vec[l] == pageArray[j])
                        {
                            if (j > temp)
                            {
                                temp = j;
                                empty = l;
                            }
                            break;
                        }
                    }
                    if (j == n)
                    {
                        empty = l;
                        break;
                    }
                }
                vec[empty] = pageArray[i];
            }
            pagefaults++;
            cout << " " << pageArray[i] << " page fault occured \n";
        }
        else
        {
            cout << " " << pageArray[i] << "  No page faults \n ";
        }
    }
    cout << endl << " Total Page Faults = " << pagefaults << "\n";
}
void optimalalgo()
{
    unordered_set<int> set;
    unordered_map<int, int> index;

    int pagefaults = 0;
    for (int i = 0; i < n; i++)
    {

        if (set.find(pageArray[i]) != set.end())
        {
            cout << " " << pageArray[i] << " No page faults \n ";
        }
        else
        {
            if (set.size() < frame)
            {
                set.insert(pageArray[i]);
                pagefaults++;
            }
            else
            {
                int lru = INT_MAX, val;
                for (auto it : set)
                {
                    if (index[it] < lru)
                    {
                        lru = index[it];
                        val = it;
                    }
                }
                set.erase(val);
                set.insert(pageArray[i]);
                pagefaults++;
            }
            cout << " " << pageArray[i] << "   page fault occured  \n";

        }
        index[pageArray[i]] = i;
    }
    cout << "  Page Faults = " << pagefaults;
}
int main()
{
    cout << " how many frames ? \n";
    cin >> frame;

    cout << " Enter number of pages \n ";
    cin >> n;

    cout << " Enter the pages values \n";
    for (int i = 0; i < n; i++)
        cin >> pageArray[i];
    while (true)
    {
        cout << endl << " Choose your page algorithsm  \n ";
        cout << "1) First in first out page replacment \n";
        cout << "2) Least recently used page replacment \n";
        cout << "3) Optimal page replacment \n";
        int algo;
        cin >> algo;
        switch (algo)
        {
        case 1:
            fifoalgo();
            break;
        case 2:
            lrualgo();
            break;
        case 3:
            optimalalgo();
            break;
        }
    }
    return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
