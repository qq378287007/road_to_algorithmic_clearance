#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <queue>
using namespace std;

// 6.1.1
int search(const vector<int> &nums, int target)
{
    int l = 0;
    int h = nums.size() - 1;
    while (l <= h)
    {
        int mid = l + (h - l) / 2;
        if (nums[mid] == target)
            return mid;
        else if (nums[mid] < target)
            l = mid + 1;
        else
            h = mid - 1;
    }
    return -1;
}

// 6.2.1
int findMin(const vector<int> &nums)
{
    int l = 0;
    int h = nums.size() - 1;
    while (l <= h)
    {
        int mid = l + (h - l) / 2;
        if (l == h)
            return nums[l];
        else if (nums[mid] > nums[h])
            l = mid + 1;
        else
            h = mid;
    }
    return -1;
}

// 6.3.1
bool help(const vector<int> &piles, int k, int H) // 判断速度 k 是否满足条件
{
    int cnt = 0;
    for (int pile : piles)
        cnt += (pile - 1) / k + 1;
    return cnt <= H;
}
int minEatingSpeed(const vector<int> &piles, int H)
{
    int maxPile = piles[0];
    for (int pile : piles)
        if (pile > maxPile)
            maxPile = pile;

    int l = 1;
    int h = maxPile;
    while (l <= h)
    {
        int mid = l + (h - l) / 2;
        if (l == h)
            return l;
        else if (help(piles, mid, H))
            h = mid;
        else
            l = mid + 1;
    }
    return -1;
}

// 6.4.1
int mySqrt(int x)
{
    long l = 0;
    long h = x;
    while (l <= h)
    {
        long mid = l + (h - l) / 2;
        if (l == h || l + 1 == h)
            break;
        else if (mid * mid > x)
            h = mid - 1;
        else
            l = mid;
    }

    if (h * h <= x)
        return (int)h;
    else
        return (int)l;
}

// 6.4.2
int bs(const vector<int> &nums, int x)
{
    int l = 0;
    int h = nums.size() - 1;
    while (l <= h)
    {
        int mid = l + (h - l) / 2;
        if (l == h)
            break;
        else if (nums[mid] >= x)
            h = mid;
        else
            l = mid + 1;
    }
    return nums[l];
}

// 6.4.3
int bs_643(const vector<int> &nums, int x)
{
    int l = 0;
    int h = nums.size() - 1;
    while (l <= h)
    {
        int mid = l + (h - l) / 2;
        if (l == h || l + 1 == h)
            break;
        else if (nums[mid] <= x)
            l = mid;
        else
            h = mid - 1;
    }

    if (nums[h] <= x)
        return nums[h];
    else
        return nums[l];
}

// 6.5.1
int findPeakElement(const vector<int> &nums)
{
    const int n = nums.size();
    int l = 0;
    int h = n - 1;
    while (l <= h)
    {
        int mid = l + (h - l) / 2;
        if (mid + 1 < n && nums[mid] < nums[mid + 1])
            l = mid + 1;
        else if (mid - 1 >= 0 && nums[mid] < nums[mid - 1])
            h = mid - 1;
        else
            return mid;
    }
    return -1;
}

// 6.6.1
bool help(const vector<int> &nums, long ans, int m)
{
    long cnt = 1, cur = 0;
    for (int num : nums)
    {
        if (cur + num > ans)
        {
            cur = num;
            cnt += 1;
        }
        else
        {
            cur += num;
        }
    }
    return cnt <= m;
}
int splitArray(const vector<int> &nums, int m)
{
    long maxNum = nums[0], sumNum = 0;
    for (int num : nums)
    {
        if (num > maxNum)
            maxNum = num;
        sumNum += num;
    }
    long l = maxNum, h = sumNum;
    while (l <= h)
    {
        long mid = l + (h - l) / 2;
        if (l == h)
            return (int)l;
        else if (help(nums, mid, m))
            h = mid;
        else
            l = mid + 1;
    }
    return -1;
}

int main()
{
    cout << "Over!\n";
    return 0;
}