#include <iostream>
#include "matrixes/BLOSUM62.h"
#include "src/NeedlemanWunsch.h"
#include <vector>
#include <string>
#include <algorithm>
#include <future>

void printCSV(std::vector<std::vector<float> > v){
    int i;
    int j;
    bool first = true;
    std::cout << "[";
    for (i = 0; i < v.size();i++){
        if (!first){
            std::cout << ',';
        }
        first =  false;
        std::cout << "[ ";
        std::cout << v[i][0];
        for(j = 1;j < v[i].size();j++){
            std::cout << ',' << v[i][j];
        }
        std::cout << " ]";
    }
    std::cout << "]";
}

float identity(std::string a, std::string b,NeedlemanWunsch n){
    int match = 0;
    int k;
    Alignment_Result temp = n.alignSequence(a,b);
    for (k = 0; k < temp.seq_a.length();k++){
        if (temp.seq_a[k] == temp.seq_b[k]){
            match++;
        }
    }
    return ((float)match)/std::min(temp.seq_a.length(),temp.seq_b.length());
}

std::vector<float> getRow(int a, std::vector<std::string> inputs,NeedlemanWunsch n){
    std::vector<float> ans;
    int i;
    for(i=a;i < inputs.size();i++){
        ans.push_back(identity(inputs[a],inputs[i],n));
    }
    return ans;
}

int main(){
    int max_size = 0;
    std::vector<std::string> inputs;
    for (std::string line; std::getline(std::cin, line);) {
        max_size = std::max(max_size,(int) line.length());
        inputs.push_back(line);
    }
    BLOSUM62 b;
    const int max_thread = 8;
    int i;
    int j;
    int k;
    int l;
    std::vector<std::vector<float> > scores;
    for(i=0;i<inputs.size();i++){
        std::vector<float> t(inputs.size(),0);
        scores.push_back(t);
    }
    NeedlemanWunsch n(max_size, -10, b);
    
    
    for (i=0;i<inputs.size();){
        std::vector<std::future<std::vector<float> > > futures;
        for (k = 0; k < max_thread && (i+k) < inputs.size();k++){
            futures.push_back(std::async(getRow,i+k,inputs,n));
        }
        for (k = 0; k < max_thread && (i+k) < inputs.size();k++){
			std::cout << i + k << std::endl;
            std::vector<float> f = futures[k].get();
            for (j = 0; j < f.size();j++){
                
                int index_a = i+k;
                int index_b = index_a + j;
                scores[index_a][index_b] = f[j];
                scores[index_b][index_a] = f[j];
            }
        }
        i += max_thread;
    }
    printCSV(scores);
    
    return 0;
}