#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <string>
#include <sstream>
#include <iterator>
#include <map>
#include <cmath>
using namespace std;

// 3.1.1
bool isPalindrome(const string &s, int n)
{
    for (int l = 0, r = n - 1; l < r; l++, r--)
        if (s[l] != s[r])
            return false;
    return true;
}

// 3.1.2
bool isPalindrome(const string &s, int i, int n)
{
    for (int l = 0, r = n - 1; l < r; l++, r--)
    {
        if (l == i)
            l += 1;
        else if (r == i)
            r -= 1;

        if (s[l] != s[r])
            return false;
    }
    return true;
}
bool validPalindrome(string s)
{
    int n = s.length();
    for (int l = 0, r = n - 1; l < r; l++, r--)
        if (s[l] != s[r])
            return isPalindrome(s, l, n) || isPalindrome(s, r, n);
    return true;
}

// 3.2.1
struct ListNode
{
    int val;
    ListNode *next;
};
ListNode *reverseList(ListNode *head)
{
    ListNode *prev = head;
    for (ListNode *cur = head; cur; cur = cur->next)
    {
        cur->next = prev;
        prev = cur;
    }
    return prev;
}

// 3.2.2
bool isPalindrome(ListNode *head)
{
    ListNode *pre = NULL;
    ListNode *slow = head, *fast = head;
    while (fast && fast->next)
    {
        fast = fast->next->next;
        ListNode *next = slow->next;
        slow->next = pre;
        pre = slow;
        slow = next;
    }
    if (fast)
        slow = slow->next;
    while (slow)
    {
        if (slow->val != pre->val)
            return false;
        pre = pre->next;
        slow = slow->next;
    }
    return true;
}

// 3.3.1
bool isPalindrome(int x)
{
    if (x < 0)
        return false;
    if (x == 0)
        return true;
    if (x % 10 == 0)
        return false;

    int res = 0, copy = x;
    while (x > 0)
    {
        res = res * 10 + (x % 10);
        x /= 10;
    }
    return copy == res;
}

// 3.4.1
string extend(int i, int j, string s)
{
    while (i >= 0 && j < s.length() && s[i] == s[j])
    {
        i -= 1;
        j += 1;
    }
    return s.substr(i + 1, j - i - 1);
}
string longestPalindrome(string s)
{
    int n = s.length();
    if (n == 0)
        return "";
    string res = s.substr(0, 1);
    for (int i = 0; i < n - 1; i++)
    {
        string e1 = extend(i, i, s);
        string e2 = extend(i, i + 1, s);
        if (max(e1.length(), e2.length()) > res.length())
            res = ((e1.length() > e2.length()) ? e1 : e2);
    }
    return res;
}

// 3.5.1
int longestPalindromeSubseq(string s)
{
    int n = s.length();
    int **dp = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        dp[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            dp[i][j] = 0;
    }
    for (int i = n - 1; i >= 0; i--)
        for (int j = i; j < n; j++)
        {
            if (i == j)
                dp[i][j] = 1;
            else if (s[i] == s[j])
                dp[i][j] = dp[i + 1][j - 1] + 2;
            else
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
        }
    int ans = dp[0][n - 1];
    for (int i = 0; i < n; i++)
        free(dp[i]);
    free(dp);
    return ans;
}

// 3.5.2
namespace ns3_5_2
{
    int longestPalindromeSubseq(string s)
    {
        int n = s.length();
        int *pre = (int *)malloc(n * sizeof(int));
        int *cur = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            pre[i] = cur[i] = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = i; j < n; j++)
            {
                if (i == j)
                    cur[j] = 1;
                else if (s[i] == s[j])
                    cur[j] = pre[j - 1] + 2;
                else
                    cur[j] = max(pre[j], cur[j - 1]);
            }
            for (int j = 0; j < n; j++)
                pre[j] = cur[j];
        }
        int ans = pre[n - 1];
        free(pre);
        free(cur);
        return ans;
    }
}

// 3.6.1
namespace ns3_6_1
{
    typedef long long ll;
    bool validPalindrome(string s)
    {
        int l = 0, r = s.length() - 1;
        while (l < r)
        {
            if (s[l] != s[r])
                return false;
            l += 1;
            r -= 1;
        }
        return true;
    }
    int superpalindromesInRange(string L, string R)
    {
        int cnt = 0;
        ll l_num = 0LL, r_num = 0LL;
        for (int i = 0; i < L.length(); i++)
            l_num = (l_num * 10LL) + ll(L[i] - '0');
        for (int i = 0; i < R.length(); i++)
            r_num = (r_num * 10LL) + ll(R[i] - '0');
        for (ll i = ll(floor(sqrt(double(l_num))));
             i < ll(ceil(sqrt(double(r_num)))); i += 1LL)
            if (validPalindrome(to_string(i)) &&
                validPalindrome(to_string(i * i)))
                cnt += 1;
        return cnt;
    }
}

// 3.6.2
namespace ns3_6_2
{
    typedef long long ll;
    bool validPalindrome(string s)
    {
        int l = 0, r = s.length() - 1;
        while (l < r)
        {
            if (s[l] != s[r])
                return false;
            l += 1;
            r -= 1;
        }
        return true;
    }
    int superpalindromesInRange(string L, string R)
    {
        int cnt = 0;
        ll i = 1;
        map<ll, bool> seen;
        seen.clear();
        while (i < 100000LL)
        {
            ll power = ll(floor(log(i) / log(10.0) + 0.5));
            ll x = i, r = 0;
            while (x > 0LL)
            {
                r = r * 10LL + (x % 10LL);
                x /= 10LL;
            }
            ll Q = ll(i * pow(10, power) +
                      r % ll(pow(10, power)));
            if (LLONG_MAX / Q < Q)
                return cnt;
            Q = Q * Q;
            ll l_num = 0LL, r_num = 0LL;
            for (int ww = 0; ww < L.size(); ww++)
                l_num = (l_num * 10LL) + ll(L[ww] - '0');
            for (int ww = 0; ww < R.size(); ww++)
                r_num = (r_num * 10LL) + ll(R[ww] - '0');
            if (Q > r_num)
                return cnt;
            if (Q >= l_num && validPalindrome(to_string(Q)))
                if (!seen.count(Q))
                {
                    cnt += 1;
                    seen[Q] = true;
                }
            Q = i * pow(10, power + 1LL) + r;
            if (LLONG_MAX / Q < Q)
                return cnt;
            Q = Q * Q;
            if (Q >= l_num && Q <= r_num && validPalindrome(to_string(Q)))
                if (!seen.count(Q))
                {
                    cnt += 1;
                    seen[Q] = true;
                }
            i += 1LL;
        }
        return cnt;
    }
}

int main()
{
    cout << "Over!\n";
    return 0;
}
