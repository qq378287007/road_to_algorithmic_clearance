#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <queue>
using namespace std;

// 5.1.1
// 5.1.2
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
bool hasPathSum(TreeNode *root, int sum)
{
    if (root == NULL)
        return false;

    if (root->left == NULL && root->right == NULL)
        return root->val == sum;

    return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
}

// 5.1.3
namespace ns5_1_3
{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) { val = x; }
    };

    /*
        List<List<Integer>> pathSum(TreeNode root, int sum)
        {
            List<List<Integer>> res = new ArrayList<>();

            if (root == null)
                return res;

            Deque<Integer> path = new ArrayDeque<>();
            pathSum(root, sum, path, res);

            return res;
        }

        void pathSum(TreeNode node, int sum, Deque<Integer> path, List<List<Integer>> res)
        {
            if (node == null)
                return;

            // 沿途结点必须选择，这个时候要做两件事：1、sum 减去这个结点的值；2、添加到 path 里
            sum -= node.val;
            path.addLast(node.val);

            if (sum == 0 && node.left == null && node.right == null)
            {
                // path 全局只有一份，必须做拷贝
                res.add(new ArrayList<>(path));
                // 注意：这里 return 之前必须重置
                path.removeLast();
                return;
            }

            pathSum(node.left, sum, path, res);
            pathSum(node.right, sum, path, res);
            // 递归完成以后，必须重置变量
            path.removeLast();
        }*/
}

// 5.1.4
namespace ns5_1_4
{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) { val = x; }
    };
    /*
        List<List<Integer>> pathSum(TreeNode root, int sum)
        {
            List<List<Integer>> res = new ArrayList<>();

            if (root == null)
                return res;

            Deque<Integer> path = new ArrayDeque<>();
            Deque<Pair<TreeNode, Integer>> stack = new ArrayDeque<>();

            stack.addLast(new Pair<TreeNode, Integer>(root, root.val));
            path.addLast(root.val)

                while (!stack.isEmpty())
            {
                Pair<TreeNode, Integer> top = stack.removeLast();
                TreeNode node = top.getKey();
                int total = top.getValue();

                if ((node.right == null) && (node.left == null) && (total == sum))
                {
                    res.add(new ArrayList<>(path));
                }
                if (node.right != null)
                {
                    stack.addLast(new Pair<TreeNode, Integer>(node.right, total + node.right.val));
                    path.addLast(node.right.val);
                }
                if (node.left != null)
                {
                    stack.addLast(new Pair<TreeNode, Integer>(node.left, total + node.left.val));
                    path.addLast(node.left.val);
                }
            }
        }*/
}

// 5.1.5
int helper(TreeNode *node, int &maxSum)
{
    if (node == nullptr)
        return 0;

    // 递归计算左右子节点的最大贡献值
    // 只有在最大贡献值大于 0 时，才会选取对应子节点
    int leftGain = max(helper(node->left, maxSum), 0);
    int rightGain = max(helper(node->right, maxSum), 0);

    // 节点的最大路径和取决于该节点的值与该节点的左右子节点的最大贡献值
    int priceNewpath = node->val + leftGain + rightGain;

    // 更新答案
    maxSum = max(maxSum, priceNewpath);

    // 返回节点的最大贡献值
    return node->val + max(leftGain, rightGain);
}
int maxPathSum(TreeNode *root)
{
    int maxSum = INT_MIN;
    helper(root, maxSum);
    return maxSum;
}

// 5.2.1
void dfs(vector<vector<char>> &grid, int r, int c)
{
    int nr = grid.size();
    int nc = grid[0].size();

    grid[r][c] = '0';
    if (r - 1 >= 0 && grid[r - 1][c] == '1')
        dfs(grid, r - 1, c);
    if (r + 1 < nr && grid[r + 1][c] == '1')
        dfs(grid, r + 1, c);
    if (c - 1 >= 0 && grid[r][c - 1] == '1')
        dfs(grid, r, c - 1);
    if (c + 1 < nc && grid[r][c + 1] == '1')
        dfs(grid, r, c + 1);
}
int numIslands(vector<vector<char>> &grid)
{
    int nr = grid.size();
    if (!nr)
        return 0;
    int nc = grid[0].size();

    int num_islands = 0;
    for (int r = 0; r < nr; ++r)
    {
        for (int c = 0; c < nc; ++c)
        {
            if (grid[r][c] == '1')
            {
                ++num_islands;
                dfs(grid, r, c);
            }
        }
    }

    return num_islands;
}

// 5.2.2
/*
from typing import List


class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        if not grid or not grid[0]:
            return 0

        m = len(grid)
        n = len(grid[0])
        ans = 0

        def dfs(row, col):
            grid[row][col] = "0"
            stack = [[row, col]]
            while stack:
                r, c = stack[-1]
                if r - 1 >= 0 and grid[r - 1][c] == "1":
                    stack.append([r - 1, c])
                    grid[r - 1][c] = "0"
                    continue
                if r + 1 < m and grid[r + 1][c] == "1":
                    stack.append([r + 1, c])
                    grid[r + 1][c] = "0"
                    continue
                if c - 1 >= 0 and grid[r][c - 1] == "1":
                    stack.append([r, c - 1])
                    grid[r][c - 1] = "0"
                    continue
                if c + 1 < n and grid[r][c + 1] == "1":
                    stack.append([r, c + 1])
                    grid[r][c + 1] = "0"
                    continue
                stack.pop()

        for i in range(m):
            for j in range(n):
                if grid[i][j] == "1":
                    ans += 1
                    dfs(i, j)

        return ans
*/

// 5.2.3
int numIslands_523(vector<vector<char>> &grid)
{
    int nr = grid.size();
    if (!nr)
        return 0;
    int nc = grid[0].size();

    int num_islands = 0;
    for (int r = 0; r < nr; ++r)
    {
        for (int c = 0; c < nc; ++c)
        {
            if (grid[r][c] == '1')
            {
                ++num_islands;
                grid[r][c] = '0';
                queue<pair<int, int>> neighbors;
                neighbors.push({r, c});
                while (!neighbors.empty())
                {
                    auto rc = neighbors.front();
                    neighbors.pop();
                    int row = rc.first, col = rc.second;
                    if (row - 1 >= 0 && grid[row - 1][col] == '1')
                    {
                        neighbors.push({row - 1, col});
                        grid[row - 1][col] = '0';
                    }
                    if (row + 1 < nr && grid[row + 1][col] == '1')
                    {
                        neighbors.push({row + 1, col});
                        grid[row + 1][col] = '0';
                    }
                    if (col - 1 >= 0 && grid[row][col - 1] == '1')
                    {
                        neighbors.push({row, col - 1});
                        grid[row][col - 1] = '0';
                    }
                    if (col + 1 < nc && grid[row][col + 1] == '1')
                    {
                        neighbors.push({row, col + 1});
                        grid[row][col + 1] = '0';
                    }
                }
            }
        }
    }

    return num_islands;
}

// 5.2.4
class UnionFind
{
    vector<int> parent;
    vector<int> rank;
    int count;

public:
    inline int getCount() const { return count; }

    UnionFind(vector<vector<char>> &grid)
    {
        count = 0;
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == '1')
                {
                    parent.push_back(i * n + j);
                    ++count;
                }
                else
                {
                    parent.push_back(-1);
                }
                rank.push_back(0);
            }
        }
    }

    int find(int i)
    {
        if (parent[i] != i)
            parent[i] = find(parent[i]);
        return parent[i];
    }

    void unionData(int x, int y)
    {
        int rootx = find(x);
        int rooty = find(y);
        if (rootx != rooty)
        {
            if (rank[rootx] < rank[rooty])
            {
                swap(rootx, rooty);
            }
            parent[rooty] = rootx;
            if (rank[rootx] == rank[rooty])
                rank[rootx] += 1;
            --count;
        }
    }
};
class Solution
{
public:
    int numIslands(vector<vector<char>> &grid)
    {
        int nr = grid.size();
        if (!nr)
            return 0;
        int nc = grid[0].size();

        UnionFind uf(grid);
        int num_islands = 0;
        for (int r = 0; r < nr; ++r)
        {
            for (int c = 0; c < nc; ++c)
            {
                if (grid[r][c] == '1')
                {
                    grid[r][c] = '0';
                    if (r - 1 >= 0 && grid[r - 1][c] == '1')
                        uf.unionData(r * nc + c, (r - 1) * nc + c);
                    if (r + 1 < nr && grid[r + 1][c] == '1')
                        uf.unionData(r * nc + c, (r + 1) * nc + c);
                    if (c - 1 >= 0 && grid[r][c - 1] == '1')
                        uf.unionData(r * nc + c, r * nc + c - 1);
                    if (c + 1 < nc && grid[r][c + 1] == '1')
                        uf.unionData(r * nc + c, r * nc + c + 1);
                }
            }
        }

        return uf.getCount();
    }
};

// 5.2.5
/*
class Solution:
    class UnionFind:
        def __init__(self, grid):
            self.count = 0
            m = len(grid)
            n = len(grid[0])
            self.parent = [0 for _ in range(m * n)]
            self.rank = [0 for _ in range(m * n)]
            for i in range(m):
                for j in range(n):
                    if grid[i][j] == "1":
                        self.parent[i * n + j] = i * n + j
                        self.count += 1

        def find(self, i):
            if self.parent[i] != i:
                self.parent[i] = self.find(self.parent[i])
            return self.parent[i]

        def union(self, x, y):
            rootx = self.find(x)
            rooty = self.find(y)
            if rootx != rooty:
                if self.rank[rootx] > self.rank[rooty]:
                    self.parent[rooty] = rootx
                elif self.rank[rootx] < self.rank[rooty]:
                    self.parent[rootx] = rooty
                else:
                    self.parent[rooty] = rootx
                    self.rank[rootx] += 1

                self.count -= 1

        def getCount(self):
            return self.count

        def setCount(self, count):
            self.count = count

        def setParent(self, i, val):
            self.parent[i] = val

    def numIslands(self, m, n, positions):
        if m <= 0 or n <= 0:
            return []

        ans = []
        grid = [[0 for _ in range(n)] for _ in range(m)]

        uf = self.UnionFind(grid)

        for i in range(len(positions)):
            position = positions[i]
            uf.setCount(uf.getCount() + 1)
            uf.setParent(position[0] * n + position[1], position[0] * n + position[1])
            grid[position[0]][position[1]] = "1"
            if position[0] - 1 >= 0 and grid[position[0] - 1][position[1]] == "1":
                uf.union(
                    position[0] * n + position[1], (position[0] - 1) * n + position[1]
                )
            if position[0] + 1 < m and grid[position[0] + 1][position[1]] == "1":
                uf.union(
                    position[0] * n + position[1], (position[0] + 1) * n + position[1]
                )
            if position[1] - 1 >= 0 and grid[position[0]][position[1] - 1] == "1":
                uf.union(
                    position[0] * n + position[1], position[0] * n + position[1] - 1
                )
            if position[1] + 1 < n and grid[position[0]][position[1] + 1] == "1":
                uf.union(
                    position[0] * n + position[1], position[0] * n + position[1] + 1
                )
            ans.append(uf.getCount())

        return ans
*/

int main()
{
    cout << "Over!\n";
    return 0;
}