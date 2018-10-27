#include "NeedlemanWunsch.h"
#include <vector>
#include <iostream>
#include <string>
//#include "../Matrix/BLOSUM62.cpp"

NeedlemanWunsch::NeedlemanWunsch(int max_seq_size, int gap_penalty,Scoring_Matrix& s) : score(s){
    std::vector<std::vector<int> > m;
    m.reserve(max_seq_size+1);
    int i;
    for( i = 0; i < max_seq_size+1; i++){
        std::vector<int> temp(max_seq_size+1,0);
        m.push_back(temp);
    }
    m[0][0] = 0;
    for ( i = 1; i < max_seq_size+1; i++){
        m[0][i] = i * gap_penalty;
        m[i][0] = i * gap_penalty;
    }
    this->matrix = m;
    this->gap_penalty = gap_penalty;
    this->scoringMatrix = this->score.getMatrix();
}

int NeedlemanWunsch::alignSequence(std::string a, std::string b){
    int i;
    int j;
    int size_a = a.length();
    int size_b = b.length();
    std::vector<int> a_translate = this->score.translateSequence(a);
    std::vector<int> b_translate = this->score.translateSequence(b);
    for (i = 0; i < size_a;i++){
        for (j = 0;j < size_b;j++){
            int a = this->matrix[i][j+1] + this->gap_penalty;
            int b = this->matrix[i+1][j] + this->gap_penalty;
            int c = this->matrix[i][j] + this->scoringMatrix[a_translate[i]][b_translate[j]];
            this->matrix[i+1][j+1] = std::max(std::max(a,b),c);
        }
    }
    for (i = 0; i < size_a;i++){
        std::cout << '|';
        for (j = 0;j < size_b;j++){
            std::cout << this->matrix[i][j] << '|';
        }
        std::cout << std::endl;
    }

    return this->matrix[size_a][size_b];
}