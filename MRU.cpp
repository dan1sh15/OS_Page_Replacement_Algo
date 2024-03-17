/* --------------------------- MRU Page Replacement Algorithm --------------------------- */

#include <bits/stdc++.h>
using namespace std;

queue<pair<vector<int>, string>> processChart;

int calculatePageFault(vector<int>& refString, int frames, int n){
    // set to check which process is visited;
    unordered_set<int> s;
    int pageFaults = 0;

    vector<int> v;
    unordered_map<int,int> indexes; // map to track indexes of the recently used process

    // traverse the string
    for(int i=0; i<n; i++){
        bool hit = true;
        if(s.size() < frames){
            if(s.find(refString[i]) == s.end()){
                hit = false;
                pageFaults++;
                v.push_back(refString[i]);
                s.insert(refString[i]);
            }
            // store the recently used page index
            indexes[refString[i]] = i;
        }
        else{
            if(s.find(refString[i]) == s.end()){
                hit = false;
                pageFaults++;

                int mru = INT_MIN, val;
                for(auto process: s){
                    if(indexes[process] > mru){
                        mru = indexes[process];
                        val = process;
                    }
                }
                s.erase(val);
                s.insert(refString[i]);
                // change the fram values
                for(auto& process: v){
                    if(process == val){
                        process = refString[i];
                    }
                }
            }
            indexes[refString[i]] = i;
        }
        hit ? processChart.push({v, "Hit"}) : processChart.push({v, "Fault"});
    }
    return pageFaults;
}

int main() {

    int n;
    cout << "\n\nEnter the size of the Reference String: ";
    cin >> n;

    vector<int> refString(n);

    cout << "Enter the Reference String: ";
    for(int i=0; i<n; i++) cin >> refString[i];

    int frames;
    cout << "Enter the number of frames: ";
    cin >> frames;

    int pageFaults = calculatePageFault(refString, frames, n);
    int hits = n - pageFaults;

    cout << "\nThe process Chart is\n";
    while(!processChart.empty()){
        auto v = processChart.front().first;
        string s = processChart.front().second;

        for(auto& i: v){
            cout << i << " ";
        }
        cout << " - " << s;
        cout << "\n";
        processChart.pop();
    }
    cout << "\n\n";

    cout << "The number of Page Faults are: " << pageFaults << endl;
    cout << "The number of Page Hits are: " << hits << endl;

    double hitRatio = (double) (hits * 100) / (double) n;
    cout << "The Hit Ratio is: " << hitRatio << "%" << endl;
    cout << "\n\n";

    return 0;
}