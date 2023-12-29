#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stack>
using namespace std;

// 1.3.1
int sum(int n)
{
    int res = 0;
    for (int i = 0; i < n; i++)
        res += i;
    return res;
}

// 1.3.2
vector<int> twoSum(const vector<int> &nums, int target)
{
    unordered_map<int, int> mapper;
    for (int i = 0; i < nums.size(); i++)
    {
        if (mapper.find(target - nums[i]) != mapper.cend())
            return {mapper[target - nums[i]], i};
        mapper[nums[i]] = i;
    }
    return {};
}

// 1.3.3
vector<int> dailyTemperatures(const vector<int> &T)
{
    const int n = T.size();
    stack<int> st;
    vector<int> ans(n, 0);
    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && T[i] > T[st.top()])
        {
            int top = st.top();
            st.pop();
            ans[top] = i - top;
        }
        st.push(i);
    }
    return ans;
}

// 1.3.4
int binarySearch(const vector<int> &nums, int target)
{
    const int n = nums.size();
    if (n == 0)
        return -1;

    int left = 0;
    int right = n - 1;
    while (left <= right)
    {
        int mid = left + ((right - left) >> 1);
        if (nums[mid] == target)
            return mid;
        else if (nums[mid] < target) // 搜索区间变为 [mid+1, right]
            left = mid + 1;
        else // 搜索区间变为 [left, mid - 1]
            right = mid - 1;
    }
    return -1;
}

// 1.3.5
int fibonacci(int n)
{
    if (n < 2)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// 1.3.6
void dfs(int idx, const vector<int> &nums, vector<bool> &visited, vector<int> &path, vector<vector<int>> &ans)
{
    const int n = nums.size();

    // 结束条件
    if (path.size() == n) // 1. 找到解
    {
        vector<int> temp(n);
        copy(path.cbegin(), path.cend(), temp.begin());
        ans.emplace_back(temp);
        return;
    }

    if (idx == n) // 2. 搜索完毕
        return;

    for (int i = 0; i < n; ++i) // 考虑可能的解，进入下一层递归
    {
        if (visited[i]) // 非法解忽略
            continue;

        // 更新状态
        visited[i] = true;
        path.push_back(nums[i]);

        dfs(idx + 1, nums, visited, path, ans);

        // 恢复状态
        path.pop_back();
        visited[i] = false;
    }
}
vector<vector<int>> permute(const vector<int> &nums)
{
    vector<bool> visited(nums.size(), false);
    vector<int> path;
    vector<vector<int>> ans;
    dfs(0, nums, visited, path, ans);
    return ans;
}

int main()
{
    cout << "Over!\n";
    return 0;
}