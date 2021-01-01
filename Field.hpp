#pragma once
#include<vector>

using namespace std;

class Field {
private:
    //weights at each position
    vector<vector<int>> weights;
    //least path cost from upper left corner to every position
    vector<vector<int>> leastPathCost;
public:
    //parameterized constructor
    Field(const vector<vector<int>>& matrix);
    //move constructor
    Field(vector<vector<int>>&& matrix);
    //returns the sum of all elements in the rectangle defined by given coordinates
    int Weight(const int& x1, const int& y1, const int& x2, const int& y2) const;
    //returns the shortest path cost from the upper left corner to the lower right corner
    int PathCost() const;
};