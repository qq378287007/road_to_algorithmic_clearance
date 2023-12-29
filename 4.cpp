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

// 4.1.1
string countAndSay(int n)
{
    string res = "1";

    for (int i = 1; i < n; i++)
    {
        string tmp = "";
        char current_char = res[0];
        int char_count = 0;

        for (int j = 0; j < res.size(); j++)
        {
            if (res[j] != current_char)
            {
                tmp += to_string(char_count) + current_char;
                current_char = res[j];
                char_count = 1;
            }
            else
            {
                char_count += 1;
            }
        }

        tmp += to_string(char_count) + current_char;
        res = tmp;
    }

    return res;
}

// 4.1.2
namespace ns4_1_2
{
    string countAndSay(int n)
    {
        if (n == 1)
            return "1";

        string pre_str = countAndSay(n - 1);

        int char_index = 0, char_count = 1;
        string cur_str = "";

        for (int i = 0; i < pre_str.length() - 1; i++)
        {
            if (pre_str[char_index] == pre_str[i + 1])
                char_count += 1;
            else
            {
                cur_str += to_string(char_count) + pre_str[char_index];
                char_index = i + 1;
                char_count = 1;
            }
        }

        cur_str += to_string(char_count) + pre_str[char_index];

        return cur_str;
    }
}

// 4.2.1
bool compute(double a)
{
    return fabs(24 - a) < 1e-8;
}
bool compute(double a, double b)
{
    return compute(a + b) || compute(a - b) || compute(a * b) || (b && compute(a / b));
}
bool compute(double a, double b, double c)
{
    return compute(a + b, c) || compute(a - b, c) || compute(a * b, c) || (b && compute(a / b, c)) ||
           compute(a, b + c) || compute(a, b - c) || compute(a, b * c) || (c && compute(a, b / c));
}
bool compute(double a, double b, double c, double d)
{
    return compute(a + b, c, d) || compute(a - b, c, d) || compute(a * b, c, d) || (b && compute(a / b, c, d)) ||
           compute(a, b + c, d) || compute(a, b - c, d) || compute(a, b * c, d) || (c && compute(a, b / c, d)) ||
           compute(a, b, c + d) || compute(a, b, c - d) || compute(a, b, c * d) || (d && compute(a, b, c / d));
}
bool judgePoint24(vector<int> &nums)
{
    sort(nums.begin(), nums.end());

    do
    {
        if (compute(nums[0], nums[1], nums[2], nums[3]))
            return true;
    } while (next_permutation(nums.begin(), nums.end()));

    return false;
}

// 4.2.2
namespace ns4_2_2
{
    bool compute(const vector<double> &nums)
    {
        const int n = nums.size();
        if (n == 1)
            return fabs(nums[0] - 24.0) < 1e-8;

        for (int left = 0; left < n - 1; left++)
        {
            for (int right = left + 1; right < n; right++)
            {
                vector<double> tmp;
                for (int k = 0; k < n; k++)
                    if (k != left && k != right)
                        tmp.push_back(nums[k]);

                tmp.push_back(nums[left] + nums[right]);
                if (compute(tmp))
                    return true;

                tmp.back() = nums[left] * nums[right];
                if (compute(tmp))
                    return true;

                tmp.back() = nums[left] - nums[right];
                if (compute(tmp))
                    return true;

                tmp.back() = nums[left] / nums[right];
                if (compute(tmp))
                    return true;

                tmp.back() = nums[right] - nums[left];
                if (compute(tmp))
                    return true;

                tmp.back() = nums[right] / nums[left];
                if (compute(tmp))
                    return true;
            }
        }

        return false;
    }
    bool judgePoint24(const vector<int> &nums)
    {
        vector<double> tmp(nums.cbegin(), nums.cend());
        return compute(tmp);
    }
}

// 4.3.1
class Solution4_3_1
{
    vector<vector<bool>> row_state;
    vector<vector<bool>> column_state;
    vector<vector<bool>> box_state;

private:
    void placeNumber(vector<vector<char>> &board, int row, int column, char d)
    {
        board[row][column] = d;
        row_state[row][d - '1'] = true;
        column_state[column][d - '1'] = true;
        box_state[((row / 3) * 3) + (column / 3)][d - '1'] = true;
    }

    void undoNumberPlace(vector<vector<char>> &board, int row, int column, char d)
    {
        board[row][column] = '.';
        row_state[row][d - '1'] = false;
        column_state[column][d - '1'] = false;
        box_state[((row / 3) * 3) + (column / 3)][d - '1'] = false;
    }

    void initialState(vector<vector<char>> &board)
    {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                if (board[i][j] != '.')
                    placeNumber(board, i, j, board[i][j]);
    }

    bool recursivePlaceNumber(vector<vector<char>> &board, int row, int column)
    {
        if (row == 9)
            return true;
        if (column == 9)
            return recursivePlaceNumber(board, row + 1, 0);
        if (board[row][column] != '.')
            return recursivePlaceNumber(board, row, column + 1);

        for (int i = '1'; i <= '9'; i++)
        {
            if (!(row_state[row][i - '1'] || column_state[column][i - '1'] || box_state[((row / 3) * 3) + (column / 3)][i - '1']))
            {
                placeNumber(board, row, column, i);
                if (recursivePlaceNumber(board, row, column + 1) == true)
                    return true;
                undoNumberPlace(board, row, column, i);
            }
        }

        return false;
    }

public:
    void solveSudoku(vector<vector<char>> &board)
    {
        row_state = vector<vector<bool>>(9, vector<bool>(9, false));
        column_state = vector<vector<bool>>(9, vector<bool>(9, false));
        box_state = vector<vector<bool>>(9, vector<bool>(9, false));

        initialState(board);

        recursivePlaceNumber(board, 0, 0);
    }
};

// 4.3.2
class Solution4_3_2
{
    vector<vector<bool>> row_state;
    vector<vector<bool>> column_state;
    vector<vector<bool>> box_state;

private:
    pair<int, int> getMaxPossibleCoordinate(vector<vector<char>> &board)
    {
        int x = -1, y = -1, min_count = 9;
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] != '.')
                    continue;
                int tmp_count = 9;
                for (int k = 0; k < 9; k++)
                {
                    if (row_state[i][k] || column_state[j][k] || box_state[(i / 3) * 3 + j / 3][k])
                        tmp_count -= 1;
                }

                if (tmp_count == 1)
                    return make_pair(i, j);
                if (min_count > tmp_count)
                {
                    min_count = tmp_count;
                    x = i;
                    y = j;
                }
            }

        return make_pair(x, y);
    }

    void placeNumber(vector<vector<char>> &board, int row, int column, int i)
    {
        board[row][column] = i + '0';
        row_state[row][i] = true;
        column_state[column][i] = true;
        box_state[((row / 3) * 3) + (column / 3)][i] = true;
    }

    void undoNumberPlace(vector<vector<char>> &board, int row, int column, int i)
    {
        board[row][column] = '.';
        row_state[row][i] = false;
        column_state[column][i] = false;
        box_state[((row / 3) * 3) + (column / 3)][i] = false;
    }

    void initialState(vector<vector<char>> &board)
    {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                if (board[i][j] != '.')
                {
                    row_state[i][board[i][j] - '0'] = true;
                    column_state[j][board[i][j] - '0'] = true;
                    box_state[(i / 3) * 3 + j / 3][board[i][j] - '0'] = true;
                }
    }

    bool recursivePlaceNumber(vector<vector<char>> &board, int row, int column)
    {
        if (row == -1 && column == -1)
            return true;
        if (board[row][column] != '.')
            return false;

        for (int i = 1; i < 10; i++)
        {
            if (row_state[row][i] ||
                column_state[column][i] ||
                box_state[(row / 3) * 3 + column / 3][i])
            {
                continue;
            }
            else
            {
                placeNumber(board, row, column, i);
                pair<int, int> coordinate = getMaxPossibleCoordinate(board);
                if (recursivePlaceNumber(board, coordinate.first, coordinate.second))
                    return true;
                undoNumberPlace(board, row, column, i);
            }
        }

        return false;
    }

public:
    void solveSudoku(vector<vector<char>> &board)
    {
        row_state = vector<vector<bool>>(9, vector<bool>(10, false));
        column_state = vector<vector<bool>>(9, vector<bool>(10, false));
        box_state = vector<vector<bool>>(9, vector<bool>(10, false));

        initialState(board);

        pair<int, int> coor = getMaxPossibleCoordinate(board);

        recursivePlaceNumber(board, coor.first, coor.second);
    }
};

// 4.4.1
int get_neighbor_count(int i, int j, vector<vector<int>> &board)
{
    int top = max(0, i - 1);
    int bottom = min<int>(board.size() - 1, i + 1);
    int left = max(0, j - 1);
    int right = min<int>(board[0].size() - 1, j + 1);

    int count = 0;
    for (int x = top; x < bottom + 1; x++)
        for (int y = left; y < right + 1; y++)
            if (board[x][y] == 1 || board[x][y] == -1)
                count += 1;

    return count;
}
void gameOfLife(vector<vector<int>> &board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            int res = get_neighbor_count(i, j, board);
            if (board[i][j] == 1 && (res == 3 || res == 4))
                board[i][j] = 1;
            else if (board[i][j] == 1)
                board[i][j] = -1;
            else if (board[i][j] == 0 && res == 3)
                board[i][j] = -2;
        }
    }

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] == -2)
                board[i][j] = 1;
            else if (board[i][j] == -1)
                board[i][j] = 0;
        }
    }
}

int main()
{
    cout << "Over!\n";
    return 0;
}
