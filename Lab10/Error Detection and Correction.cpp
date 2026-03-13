#include <vector>
#include <stdexcept>
using namespace std;

int hammingDistance(vector<int>& a, vector<int>& b) {
    if (a.size() != b.size())
        throw invalid_argument("Vectors must be same length");
    int dist = 0;
    for (int i = 0; i < a.size(); i++)
        if (a[i] != b[i]) dist++;
    return dist;
}

// Example: a={1,0,1,1}, b={1,0,0,1} → distance = 1
