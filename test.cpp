#include <iostream>
#include "matrixes/BLOSUM62.h"
#include "src/NeedlemanWunsch.h"
#include <vector>
#include <string>
#include <algorithm>

#define NUM_OF_SEQ 183

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

int main(){
    int max_size = 0;
    std::vector<std::string> inputs;
    for (std::string line; std::getline(std::cin, line);) {
        max_size = std::max(max_size,(int) line.length());
        inputs.push_back(line);
    }
    BLOSUM62 b;
    NeedlemanWunsch n(max_size, -10, b);
    
    int i;
    int j;
    int k;
    int match;
    std::vector<std::vector<float> > scores;
    for(i=0;i<inputs.size();i++){
        std::vector<float> t(inputs.size(),0);
        scores.push_back(t);
    }
    for (i=0;i<inputs.size();i++){
        for(j=i;j<inputs.size();j++){
            match = 0;
            Alignment_Result temp = n.alignSequence(inputs[i],inputs[j]);
            for (k = 0; k < temp.seq_a.length();k++){
                if (temp.seq_a[k] == temp.seq_b[k]){
                    match++;
                }
            }
            scores[i][j] = ((float)match)/std::min(temp.seq_a.length(),temp.seq_b.length());
            scores[j][i] = ((float)match)/std::min(temp.seq_a.length(),temp.seq_b.length());
            //std::cout << temp.score << std::endl;
            //std::cout << temp.seq_a << std::endl;
            //std::cout << temp.seq_b << std::endl;
        }
    }
    printCSV(scores);
    
    return 0;
}