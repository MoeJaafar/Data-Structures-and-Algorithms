// Mohammad Jaafar
#include <iostream>
#include <string>
using namespace std;

struct Player
{
    string name;
    int score;
};

int main()
{
    int n, k;
    cin >> n >> k;
    Player players[n];
    for (int i = 0; i < n; i++)
    {
        cin >> players[i].name >> players[i].score;
    }

    if (k > n)
        k = n; // check the value of K before running the loop

    for (int i = 0; i < k; i++)
    {
        int maxScore = -1;
        int maxScoreIndex = -1;
        for (int j = 0; j < n; j++)
        {
            if (players[j].score > maxScore)
            {
                maxScore = players[j].score;
                maxScoreIndex = j;
            }
        }
        cout << players[maxScoreIndex].name << " " << players[maxScoreIndex].score << endl;
        players[maxScoreIndex].score = -1;
    }
    return 0;
}
