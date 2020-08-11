#include <iostream>
#include <vector>

const int MAXN = 20; //the maximum number of cities possible (with such complexity N > 20 would take up too much time to calculate, so N = 20 is max)
const int INF = 1e9; //the infinity - the number much larger than any maximum
int n;//the actual number of cities

int dist[MAXN][MAXN];//the distances between the cities

using namespace std;

void read_the_input(){ //reads the user's input and fills the arrays
    cin >> n; //reads the number of cities
    for(int city1 = 0; city1 < n; city1++){
        for(int city2 = 0; city2 < n; city2++){
            cin >> dist[city1][city2]; //reads the distance matrix and fills the array of distances
        }
    }
}

void get_the_path(vector<vector<int>> &prevCity){
    vector<int> path; //an emppty array where we'll store the path
    int curmask = (1 << n) - 1, curcity = 0; //we start from the end - we finished our way in city 0 and have visited all cities
    while(curmask){
        path.push_back(curcity); //we add the city we visited
        int newcity = prevCity[curmask][curcity]; //we define a city we visited before cursity
        curmask ^= (1 << curcity); //we "undo" this step and erase curcity from the set of visited cities
        curcity = newcity;
    } //we keep undoing unless we reach city 0 again
    path.push_back(0);//we got our path, but in reversed order
    cout << "Minimal distance is acquired by going 0->";
    for (int i = n - 1; i > 0; i--) { //so we iterate through it in reversed order
        cout << path[i] << "->";
    }
    cout << '0';
}

void calculate_the_answer(){
    vector<vector<int>> minimalSum(1 << n, vector<int>(n, INF)); //the dynamic programming, the function is min(mask, c) - a minimal sum of distances for such a subset of cities mask, when every city in the set is visited and the last city we visited is c
    //we use bitmasks to describe a set. We fill all the values with infinity which indicates if there's INF in min(mask, c), then such a combination of cities does not exist yet
    vector<vector<int>> prevCity(1 << n, vector<int>(n)); //for min(mask, c) it is a previous city that we visited before c, we need this to recreate the path after calculating
    minimalSum[0][0] = 0; //we start from the city 0 by default, we haven't visited any city yet, so for an empty set the distance is 0
    for(int mask = 0; mask < (1 << n); mask++){ //we look through masks, 1 << n = 2^n, that's the amount of subsets we have. this order allows to calculate the solution for all subsets before we move to the considered set, thus the dp is correct
        for(int city1 = 0; city1 < n; city1++){ //we choose the city we stop at
            if(minimalSum[mask][city1] == INF ) continue; //if the city1 doesn't belong to the mask or this combination doesn't exist, then we skip it
            for(int city2 = 0; city2 < n; city2++){ //we choose where to go
                if((1 << city2) & mask) continue; //we can't go where we've already been
                int mask2 = mask | (1 << city2); //we include city2 to a new set
                if(minimalSum[mask2][city2] > minimalSum[mask][city1] + dist[city1][city2]) { //we check if this combination is optimal
                    minimalSum[mask2][city2] = minimalSum[mask][city1] + dist[city1][city2]; //if it is, we update the answer
                    prevCity[mask2][city2] = city1; //remember that we came from city1 to city2
                }
            }
        }
    }
    int answer = minimalSum[(1 << n )- 1][0]; //the answer is in the set which contains all elements and we finish in city 0 (right where we started)
    cout << "Minimal distance is " << answer << "\n";
    get_the_path(prevCity); //then we print the path
}



int main() {
    read_the_input();
    calculate_the_answer(); //that's it :)
    return 0;
}
