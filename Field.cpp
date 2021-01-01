#include<vector>
#include<algorithm>
#include<stdexcept>
#include"Field.hpp"

using namespace std;

//parameterized constructor
Field::Field(const vector<vector<int>>& matrix) {
    //filling two utility matrices
    weights.clear();
    leastPathCost.clear();
    for (int i { 0 }; i < matrix.size(); i++) {
        weights.push_back({});
        leastPathCost.push_back({});
        for (int j { 0 }; j < matrix[i].size(); j++) {
            //case for the first element
            if (i == 0 && j == 0) {
                weights[i].push_back(matrix[i][j]);
                leastPathCost[i].push_back(matrix[i][j]);
            //case for the left most elements
            } else if (i == 0) {
                weights[i].push_back(matrix[i][j] + weights[i][j-1]);
                leastPathCost[i].push_back(matrix[i][j] + leastPathCost[i][j-1]);
            //case for the upper elements
            } else if (j == 0) {
                weights[i].push_back(matrix[i][j] + weights[i-1][j]);
                leastPathCost[i].push_back(matrix[i][j] + leastPathCost[i-1][j]);
            //general case
            } else {
                weights[i].push_back(matrix[i][j] + weights[i][j-1] + weights[i-1][j] 
                - weights[i-1][j-1]);
                leastPathCost[i].push_back(min(leastPathCost[i-1][j], leastPathCost[i][j-1]) 
                + matrix[i][j]);
            }
        }
    }
}

//move constructor
Field::Field(vector<vector<int>>&& matrix) {
    //filling two utility matrices
    weights.clear();
    leastPathCost.clear();
    for (int i { 0 }; i < matrix.size(); i++) {
        weights.push_back({});
        leastPathCost.push_back({});
        for (int j { 0 }; j < matrix[i].size(); j++) {
            //case for the first element
            if (i == 0 && j == 0) {
                weights[i].push_back(matrix[i][j]);
                leastPathCost[i].push_back(matrix[i][j]);
            //case for the left most elements
            } else if (i == 0) {
                weights[i].push_back(matrix[i][j] + weights[i][j-1]);
                leastPathCost[i].push_back(matrix[i][j] + leastPathCost[i][j-1]);
            //case for the upper elements
            } else if (j == 0) {
                weights[i].push_back(matrix[i][j] + weights[i-1][j]);
                leastPathCost[i].push_back(matrix[i][j] + leastPathCost[i-1][j]);
            //general case
            } else {
                weights[i].push_back(matrix[i][j] + weights[i][j-1] + weights[i-1][j] 
                - weights[i-1][j-1]);
                leastPathCost[i].push_back(min(leastPathCost[i-1][j], leastPathCost[i][j-1]) 
                + matrix[i][j]);
            }
        }
    }
}

//returns the sum of all elements in the rectangle defined by given coordinates
int Field::Weight(const int& x1, const int& y1, const int& x2, const int& y2) const {
    //calculate the row and column bounds of the rectangle
    int rowLowerBound = min(y1, y2);
    int rowUpperBound = max(y1, y2);
    int columnUpperBound = max(x1, x2);
    int columnLowerBound = min(x1, x2);
    //check for out of range
    if (weights.empty() || weights[0].empty() || rowLowerBound < 0 || columnLowerBound < 0 || rowUpperBound > weights.size()-1 
    || columnUpperBound > weights[0].size()-1) {
        throw out_of_range("The given coordinates are out of range");
        return 0;
    }
    //start with the weight at the lower right position of the rectangle
    int res = weights[rowUpperBound][columnUpperBound];
    //subtract weight at upper right position if the rectangle is not attached to the upper bound of the matrix
    if (rowLowerBound > 0) {
        res -= weights[rowLowerBound-1][columnUpperBound];
    }
    //subtract weight at lower left position if the rectangle is not attached to the left bound of the matrix
    if (columnLowerBound > 0) {
        res -= weights[rowUpperBound][columnLowerBound-1];
    }
    //add weight at upper left position if both previous conditions are true, because upper left weight is being subtracted twice
    if (rowLowerBound > 0 && columnLowerBound > 0) {
        res += weights[rowLowerBound-1][columnLowerBound-1];
    }
    return res;
}

//returns the shortest path cost from the upper left corner to the lower right corner
int Field::PathCost() const {
    if (leastPathCost.empty() || leastPathCost[0].empty()) {
        throw out_of_range("The matrix is empty");
        return 0;
    }
    return leastPathCost[leastPathCost.size()-1][leastPathCost[leastPathCost.size()-1].size()-1];
}