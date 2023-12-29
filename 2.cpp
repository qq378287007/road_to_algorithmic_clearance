#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <string>
#include <sstream>
#include <iterator>
#include <map>
using namespace std;

// 2.1.1
vector<int> twoSum(vector<int> &nums, int target)
{
    sort(nums.begin(), nums.end());
    int l = 0;
    int r = nums.size() - 1;
    while (l < r)
    {
        if (nums[l] + nums[r] < target)
            l += 1;
        else if (nums[l] + nums[r] > target)
            r -= 1;
        else
            return {l, r};
    }
    return {};
}

// 2.1.2
vector<int> twoSum(const vector<int> &nums, int target)
{
    unordered_map<int, int> mapper;
    for (int i = 0; i < nums.size(); i++)
    {
        if (mapper.find(target - nums[i]) != mapper.end())
            return {mapper[target - nums[i]], i};
        mapper[nums[i]] = i;
    }
    return {};
}

// 2.2.1
vector<vector<int>> threeSum(vector<int> &nums)
{
    sort(nums.begin(), nums.end());

    const int n = nums.size();
    vector<vector<int>> res;

    for (int i = 0; i < n - 2; i++)
    {
        if (i > 0 && nums[i] == nums[i - 1])
            continue;
        int l = i + 1;
        int r = n - 1;
        while (l < r)
        {
            if (nums[i] + nums[l] + nums[r] < 0)
            {
                l += 1;
            }
            else if (nums[i] + nums[l] + nums[r] > 0)
            {
                r -= 1;
            }
            else
            {
                res.emplace_back(vector<int>{nums[i], nums.at(l), nums.at(r)});
                while (l < r && nums[l] == nums[l + 1])
                    l += 1;
                while (l < r && nums[r] == nums[r - 1])
                    r -= 1;
                l += 1;
                r -= 1;
            }
        }
    }
    return res;
}

// 2.3.1
vector<vector<int>> res;
set<string> set_str;
void backtrack(vector<int> &nums, int n, vector<int> &tempList, int remain, int start)
{
    const int tmpList_size = tempList.size();
    if (tmpList_size > 4)
        return;

    if (remain == 0 && tmpList_size == 4)
    {
        stringstream ss;
        copy(tempList.cbegin(), tempList.cend(), ostream_iterator<int>(ss, ""));
        string s = ss.str();
        if (set_str.count(s) == 0)
        {
            set_str.insert(s);
            vector<int> copy;
            copy.assign(tempList.cbegin(), tempList.cend());
            res.emplace_back(copy);
            return;
        }
        return;
    }

    for (int i = start; i < n; i++)
    {
        tempList.push_back(nums[i]);
        backtrack(nums, n, tempList, remain - nums[i], i + 1);
        tempList.pop_back();
    }
}
vector<vector<int>> fourSum(vector<int> &nums, int target)
{
    sort(nums.begin(), nums.end());
    vector<int> tempList;
    backtrack(nums, nums.size(), tempList, target, 0);
    return res;
}

// 2.3.2
namespace ns2_3_2
{
    void findNsum(const vector<int> &nums, int target, int N, vector<int> tempList, vector<vector<int>> &results)
    {
        if (nums.size() < N || N < 2)
            return;

        if (N == 2)
        {
            int l = 0, r = nums.size() - 1;
            while (l < r)
            {
                if (nums[l] + nums[r] == target)
                {
                    vector<int> bufList = tempList;
                    bufList.push_back(nums[l]);
                    bufList.push_back(nums[r]);
                    results.push_back(bufList);
                    l += 1;
                    r -= 1;
                    while (l < r && nums[l] == nums[l - 1])
                        l += 1;
                    while (r > l && nums[r] == nums[r + 1])
                        r -= 1;
                }
                else if (nums[l] + nums[r] < target)
                    l += 1;
                else
                    r -= 1;
            }
        }
        else
        {
            for (int i = 0; i < nums.size(); i++)
            {
                if (i == 0 || i > 0 && nums[i - 1] != nums[i])
                {
                    vector<int> buf_nums;
                    for (int j = i + 1; j < nums.size(); j++)
                        buf_nums.push_back(nums[j]);
                    vector<int> bufList = tempList;
                    bufList.push_back(nums[i]);
                    findNsum(buf_nums, target - nums[i], N - 1, bufList, results);
                }
            }
        }
    }
    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());
        vector<int> tempList;
        vector<vector<int>> results;
        findNsum(nums, target, 4, tempList, results);
        return results;
    }
}

// 2.4.1
int fourSumCount(const vector<int> &A, const vector<int> &B, const vector<int> &C, const vector<int> &D)
{
    map<int, int> mapper;
    int res = 0;
    for (int i = 0; i < A.size(); i++)
        for (int j = 0; j < B.size(); j++)
            if (mapper.count(A[i] + B[j]))
                mapper[A[i] + B[j]] = mapper[A[i] + B[j]] + 1;
            else
                mapper[A[i] + B[j]] = 1;

    for (int i = 0; i < C.size(); i++)
        for (int j = 0; j < D.size(); j++)
            if (mapper.count(-1 * (C[i] + D[j])))
                res += mapper[-1 * (C[i] + D[j])];
    return res;
}

// 2.5.1
int threeSumClosest(vector<int> &nums, int target)
{
    int n = nums.size();
    // if (n < 3) return;
    sort(nums.begin(), nums.end());
    int res = nums[0] + nums[1] + nums[2];
    for (int i = 0; i < n - 2; i++)
    {
        if (i && nums[i] == nums[i - 1])
            continue;
        int l = i + 1, r = n - 1;
        while (l < r)
        {
            int s = nums[i] + nums[l] + nums[r];
            if (s == target)
                return s;
            if (abs(s - target) < abs(res - target))
                res = s;
            if (s < target)
                l += 1;
            else if (s > target)
                r -= 1;
        }
    }
    return res;
}

// 2.6.1
int maxSubArray(const vector<int> &nums)
{
    int n = nums.size();
    int maxSum = -0x7fffffff, total = 0;
    for (int i = 0; i < n; i++)
    {
        total = 0;
        for (int j = i; j < n; j++)
        {
            total += nums[j];
            maxSum = max(maxSum, total);
        }
    }
    return maxSum;
}

// 2.6.2
namespace ns2_6_2
{
    int helper(const vector<int> &nums, int l, int r)
    {
        if (l > r)
            return -0x7fffffff;
        int mid = (l + r) / 2;
        int left = helper(nums, l, mid - 1);
        int right = helper(nums, mid + 1, r);
        int left_suffix_max_sum = 0;
        int right_prefix_max_sum = 0;
        int total = 0;
        for (int i = mid - 1; i >= l; i--)
        {
            total += nums[i];
            left_suffix_max_sum = max(left_suffix_max_sum, total);
        }
        total = 0;
        for (int i = mid + 1; i < r + 1; i++)
        {
            total += nums[i];
            right_prefix_max_sum = max(right_prefix_max_sum, total);
        }
        int cross_max_sum = left_suffix_max_sum + right_prefix_max_sum + nums[mid];
        return max(cross_max_sum, max(left, right));
    }
    int maxSubArray(const vector<int> &nums)
    {
        return helper(nums, 0, nums.size() - 1);
    }
}

// 2.6.3
namespace ns2_6_3
{
    int maxSubArray(const vector<int> &nums)
    {
        int n = nums.size();
        int max_sum_ending_curr_idx = nums[0];
        int max_sum = nums[0];
        for (int i = 1; i < n; i++)
        {
            max_sum_ending_curr_idx = max(max_sum_ending_curr_idx + nums[i], nums[i]);
            max_sum = max(max_sum_ending_curr_idx, max_sum);
        }
        return max_sum;
    }
}

// 2.6.4
namespace ns2_6_4
{
    int maxSubArray(const vector<int> &nums)
    {
        int n = nums.size();
        int maxSum = nums[0], minSum = 0, sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum += nums[i];
            maxSum = max(maxSum, sum - minSum);
            minSum = min(minSum, sum);
        }
        return maxSum;
    }
}

// 2.7.1
struct my_str
{
    string str;
    my_str(int num) : str(to_string(num)) {}
    bool operator<(const my_str &rhs) const
    {
        return str + rhs.str > rhs.str + str;
    }
};
string largestNumber(const vector<int> &nums)
{
    vector<my_str> s;
    for (int i = 0; i < nums.size(); i++)
        s.push_back(my_str(nums[i]));
    sort(s.begin(), s.end());
    string ans("");
    for (int i = 0; i < nums.size(); i++)
        ans += s[i].str;
    string real_ans("");
    bool flag = false;
    for (int i = 0; i < ans.length(); i++)
    {
        if (!flag)
            flag = !(ans[i] == '0');
        if (flag)
            real_ans.push_back(ans[i]);
    }
    if (!flag)
        return string("0");
    else
        return real_ans;
}

// 2.7.2
namespace ns2_7_2
{
    string largestNumber(const vector<int> &nums)
    {
        vector<string> s;
        for (int i = 0; i < nums.size(); i++)
            s.push_back(to_string(nums[i]));

        sort(s.begin(), s.end(), [](string a, string b) -> bool
             { return a + b > b + a; });
        string ans("");
        for (int i = 0; i < nums.size(); i++)
            ans += s[i];
        string real_ans("");
        bool flag = false;
        for (int i = 0; i < ans.length(); i++)
        {
            if (!flag)
                flag = !(ans[i] == '0');
            if (flag)
                real_ans.push_back(ans[i]);
        }
        if (!flag)
            return string("0");
        else
            return real_ans;
    }
}

// 2.8.1
typedef long long ll;
string fractionToDecimal(ll numerator, ll denominator)
{
    string res("");
    if (double(numerator) / double(denominator) < 0.0)
        res += "-";
    numerator = llabs(numerator);
    denominator = llabs(denominator);
    ll n = numerator / denominator;
    ll remainder = numerator % denominator;
    res += to_string(n);
    if (!remainder)
        return res;
    res += ".";
    int idx = res.size();
    map<ll, int> seen;
    while (remainder && !seen.count(remainder))
    {
        seen[remainder] = idx++;
        n = (remainder * 10LL) / denominator;
        remainder = (remainder * 10LL) % denominator;
        res += to_string(n);
    }
    if (remainder)
    {
        res.insert(seen[remainder], 1, '(');
        res += ")";
    }
    return res;
}

// 2.9.1
struct node
{
    set<int> s;
    node()
    {
        s.clear();
    }
    bool operator<(const node &rhs) const
    {
        return s.size() > rhs.s.size();
    }
    void operator=(const node &rhs)
    {
        s = rhs.s;
    }
};
vector<int> largestDivisibleSubset(vector<int> &nums)
{
    map<int, node> S;
    S[-1] = node();
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); i++)
    {
        int x = nums[i];
        vector<node> temp;
        for (map<int, node>::iterator it = S.begin(); it != S.end(); it++)
        {
            int d = it->first;
            if (x % d == 0)
            {
                S[d].s.insert(x);
                temp.push_back(S[d]);
                S[d].s.erase(x);
            }
        }
        node buf = node();
        for (int j = 0; j < temp.size(); j++)
            if (temp[j] < buf)
                buf = temp[j];
        if (!buf.s.count(x))
            buf.s.insert(x);
        S[x] = buf;
    }
    vector<int> ans;
    node buf = node();
    for (map<int, node>::iterator it = S.begin(); it != S.end(); it++)
        if (it->second < buf)
            buf = it->second;
    for (set<int>::iterator it = buf.s.begin(); it != buf.s.end(); it++)
        ans.push_back(*it);
    return ans;
}

// 2.10.1
typedef long long ll;
const ll magic = 1000000007LL;
ll factorial(ll n)
{
    return (n <= 1LL) ? 1LL : n % magic * (factorial(n - 1) % magic) % magic;
}
ll numPrimeArrangements(ll n)
{
    ll primes[] = {2,
                   3,
                   5,
                   7,
                   11,
                   13,
                   17,
                   19,
                   23,
                   29,
                   31,
                   37,
                   41,
                   43,
                   47,
                   53,
                   59,
                   61,
                   67,
                   71,
                   73,
                   79,
                   83,
                   89,
                   97,
                   101};
    int primeCount = 0;
    while (primes[primeCount] <= n)
        primeCount += 1;
    return factorial(primeCount) % magic * (factorial(n - primeCount) % magic) % magic;
}

int main()
{
    cout << "Over!\n";
    return 0;
}