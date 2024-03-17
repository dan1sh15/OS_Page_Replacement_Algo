/* --------------------------- Optimum Page Replacement Algorithm --------------------------- */

#include <bits/stdc++.h>
using namespace std;

queue<pair<vector<int>, string>> processChart;

int findOptimalPage(vector<int> &v, vector<int> &refString, int currIdx){
    int farthest = v[0], farthestIdx = currIdx;
    for(int i=0; i<v.size(); i++){
        int j;
        for(j=currIdx+1; j<refString.size(); j++){
            if(v[i] == refString[j]){
                if(j > farthestIdx){
                    farthest = refString[j];
                    farthestIdx = j;
                }
                break;
            }
        }
        if(j == refString.size()){
            return v[i];
        }
    }
    return farthest;
}

int calculatePageFault(vector<int>& refString, int frames, int n){
    // set to check which process is visited;
    unordered_set<int> s;
    int pageFaults = 0;

    vector<int> v;
    int idx = 0;

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
        }
        else{
            if(s.find(refString[i]) == s.end()){
                hit = false;
                pageFaults++;

                int processToRemove = findOptimalPage(v, refString, i);
                // change the frame value
                for(auto& process: v){
                    if(process == processToRemove){
                        process = refString[i];
                    }
                }
                s.erase(processToRemove);
                s.insert(refString[i]);
            }
        }
        hit ? processChart.push({v, "Hit"}) : processChart.push({v, "Fault"});
    }
    return pageFaults;
}

int main() {

    int n;
    std::cout << "\n\nEnter the size of the Reference String: ";
    cin >> n;

    vector<int> refString(n);

    std::cout << "Enter the Reference String: ";
    for(int i=0; i<n; i++) cin >> refString[i];

    int frames;
    std::cout << "Enter the number of frames: ";
    cin >> frames;

    int pageFaults = calculatePageFault(refString, frames, n);
    int hits = n - pageFaults;

    std::cout << "\nThe process Chart is\n";
    while(!processChart.empty()){
        auto v = processChart.front().first;
        string s = processChart.front().second;

        for(auto& i: v){
            std::cout << i << " ";
        }
        std::cout << " - " << s;
        std::cout << "\n";
        processChart.pop();
    }
    std::cout << "\n\n";

    std::cout << "The number of Page Faults are: " << pageFaults << endl;
    std::cout << "The number of Page Hits are: " << hits << endl;

    double hitRatio = (double) (hits * 100) / (double) n;
    std::cout << "The Hit Ratio is: " << hitRatio << "%" << endl;
    std::cout << "\n\n";

    return 0;
}