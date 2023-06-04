// Mohammad Jaafar
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int dp[100005];
vector<string> words;

int main()
{
    int N, K;
    cin >> N >> K;

    for (int i = 0; i < N; i++)
    {
        string word;
        cin >> word;
        words.push_back(word);
    }

    string text;
    cin >> text;

    memset(dp, -1, sizeof(dp));
    dp[0] = 0;

    for (int i = 0; i < K; i++)
    {
        if (dp[i] != -1)
        {
            for (string word : words)
            {
                int len = word.length();
                if (i + len <= K && text.substr(i, len) == word)
                {
                    if (dp[i + len] == -1)
                    {
                        dp[i + len] = i;
                    }
                }
            }
        }
    }

    if (dp[K] == -1)
    {
        cout << "Impossible\n";
    }
    else
    {
        string result = "";
        int idx = K;
        while (idx > 0)
        {
            int prev = dp[idx];
            result = " " + text.substr(prev, idx - prev) + result;
            idx = prev;
        }
        cout << result.substr(1) << "\n";
    }

    return 0;
}
