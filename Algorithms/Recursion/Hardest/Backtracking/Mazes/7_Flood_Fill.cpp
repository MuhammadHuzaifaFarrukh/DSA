#include <iostream>
#include <vector>

using namespace std;

/*
You are given an image represented by an m x n grid of integers image, where image[i][j] represents the pixel value of the image. You are also given three integers sr, sc, and color. Your task is to perform a flood fill on the image starting from the pixel image[sr][sc].

To perform a flood fill:

Begin with the starting pixel and change its color to color.
Perform the same process for each pixel that is directly adjacent (pixels that share a side with the original pixel, either horizontally or vertically) and shares the same color as the starting pixel.
Keep repeating this process by checking neighboring pixels of the updated pixels and modifying their color if it matches the original color of the starting pixel.
The process stops when there are no more adjacent pixels of the original color to update.
Return the modified image after performing the flood fill.

Input: image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, color = 2
Output: [[2,2,2],[2,2,0],[2,0,1]]
*/

// Forward Declarations :

void dfs(vector<vector<int>> &image, int sr, int sc, int color, int original, int m, int n);
bool isValid(int i, int j, int m, int n);

// This is in fact a graph problem.
// Its like finding the Connected Component of all nodes that share the same starting color
// We can solve it using BFS as well.
// We use just once and that DFS will find each same valued color if there is.
// Time : O(mn)
// Space : O(mn) due to recursion.
vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color)
{
    // Must check , because if image[sr][sc] is the same as the color then it will cause infinite recursion in our dfs.
    // If this happens , then we don't need to do anything , because its neighbours will also have same valued color.
    if (image[sr][sc] == color)
    {
        return image;
    }

    dfs(image, sr, sc, color, image[sr][sc], image.size(), image[0].size());
    return image;
}

void dfs(vector<vector<int>> &image, int sr, int sc, int color, int original, int m, int n)
{

    image[sr][sc] = color;
    if (isValid(sr - 1, sc, m, n) && image[sr - 1][sc] == original)
    {
        dfs(image, sr - 1, sc, color, original, m, n);
    }

    if (isValid(sr + 1, sc, m, n) && image[sr + 1][sc] == original)
    {
        dfs(image, sr + 1, sc, color, original, m, n);
    }

    if (isValid(sr, sc + 1, m, n) && image[sr][sc + 1] == original)
    {
        dfs(image, sr, sc + 1, color, original, m, n);
    }

    if (isValid(sr, sc - 1, m, n) && image[sr][sc - 1] == original)
    {
        dfs(image, sr, sc - 1, color, original, m, n);
    }
}

bool isValid(int i, int j, int m, int n)
{
    if (i >= 0 && i < m && j < n && j >= 0)
    {
        return 1;
    }
    return 0;
}

int main()
{
    vector<vector<int>> v = {{2, 80, 2},
                             {2, 1, 2},
                             {2, 2, 2}};
    floodFill(v, 1, 1, 1);
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[i].size(); j++)
        {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}