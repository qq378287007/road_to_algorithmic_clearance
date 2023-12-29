#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <queue>
using namespace std;

// 7.1.1
int hammingWeight(uint32_t n)
{
    int num = 0;
    for (int i = 0; i < 32; i++)
        if (n & (1 << i))
            num++;
    return num;
}

// 7.1.2
int hammingWeight_712(uint32_t n)
{
    int ret;
    for (ret = 0; n; ret++)
        n &= (n - 1);
    return ret;
}

// 7.2.1
int getSum(int a, int b)
{
    int ans = a ^ b;
    int c = a & b;
    while (c != 0)
    {
        c = (c & 0xffffffff) << 1;
        int ans_prim = ans ^ c;
        c = ans & c;
        ans = ans_prim;
    }
    return ans;
}

// 7.3.1
class Solution
{
    unordered_map<int, int> visited;

public:
    int integerReplacement(int n)
    {
        if (n == 1)
            return 0;

        if (visited.count(n) == 0)
            if (n & 1 == 1)
                visited[n] = 2 + min(integerReplacement(n >> 1), integerReplacement((n >> 1) + 1));
            else
                visited[n] = 1 + integerReplacement(n >> 1);

        return visited[n];
    }
};

// 7.3.2
int integerReplacement(int n)
{
    long int tmp_num = n;
    int count;
    for (count = 0; tmp_num > 1; count++)
        if (tmp_num % 2 == 0)
            tmp_num >>= 1;
        else if (((tmp_num + 1) % 4 == 0) && (tmp_num != 3))
            tmp_num += 1;
        else
            tmp_num -= 1;
    return count;
}

// 7.3.3
int integerReplacement_733(int n)
{
    long int tmp_num = n;
    int count;
    for (count = 0; tmp_num != 1; count++)
        if (tmp_num % 2 == 0)
        {
            tmp_num >>= 1;
        }
        else
        {
            if (((tmp_num & 2) == 0) || (tmp_num == 3))
                tmp_num -= 1;
            else
                tmp_num += 1;
        }
    return count;
}

// 7.4.1
int singleNumber(const vector<int> &nums)
{
    unordered_map<int, int> m;

    for (int i = 0; i < nums.size(); i++)
        m[nums[i]]++;

    for (auto it = m.cbegin(); it != m.cend(); it++)
        if (it->second == 1)
            return it->first;

    return 0;
}

// 7.4.2
int singleNumber_742(const vector<int> &nums)
{
    int result = 0;
    for (int i = 0; i < nums.size(); i++)
        result ^= nums[i];
    return result;
}

// 7.4.3
/*
int singleNumber(int[] nums)
{
    int distinctSum = Arrays.stream(nums).distinct().sum();
    int sum = Arrays.stream(nums).sum();
    return distinctSum * 2 - sum;
}
*/
// 7.4.4
int singleNumber_744(const vector<int> &nums)
{
    vector<int> t(32);

    for (int i = 0; i < nums.size(); i++)
    {
        int num = nums[i];
        for (int j = 31; j >= 0; j--)
        {
            t[j] += num & 1;
            num >>= 1;
            if (!num)
                break;
        }
    }

    int res = 0;
    for (int j = 31; j >= 0; j--)
    {
        int num = t[j] % 3;
        if (num)
            res += 1 << (31 - j);
    }

    return res;
}

// 7.4.5
/*
int singleNumber(int[] nums)
{
    int[] counts = new int[32];
    for (int num : nums)
    {
        for (int i = 0; i < 32; i++)
        {
            counts[i] += num & 1;
            num >>= 1;
        }
    }
    int res = 0;
    for (int i = 0; i < 32; i++)
    {
        res <<= 1;
        res |= counts[31 - i] % 3;
    }
    return res;
}
*/

int main()
{
    cout << "Over!\n";
    return 0;
}