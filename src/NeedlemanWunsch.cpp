#include "NeedlemanWunsch.h"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
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

int NeedlemanWunsch::run_algo(std::vector<int>& a, std::vector<int>& b){
    int i;
    int j;
    int size_a = a.size();
    int size_b = b.size();
    for (i = 0; i < size_a;i++){
        for (j = 0;j < size_b;j++){
            this->matrix[i+1][j+1] = std::max(std::max(this->matrix[i][j+1] + this->gap_penalty,this->matrix[i+1][j] + this->gap_penalty),this->matrix[i][j] + this->scoringMatrix[a[i]][b[j]]);
        }
    }
    return this->matrix[size_a][size_b];
}

std::pair<std::string,std::string> NeedlemanWunsch::backtrace(std::string a,std::string b){
    int i = a.length()-1;
    int j = b.length()-1;
    std::stringstream a_alignment;
    std::stringstream b_alignment;
    int match;
    int gap_a;
    int gap_b;
    while(i >= 1 && j >= 1){
        match = this->matrix[i-1][j-1];
        gap_a = this->matrix[i-1][j];
        gap_b = this->matrix[i][j-1];
        if(match >= gap_a){
            //This means the match is better than a gap
            if(match >= gap_b){
                //This match is the best
                a_alignment << a[i];
                b_alignment << b[j];
                i--;
                j--;
            } else {
                // gap_a < match < gap_b
                //This means that the gap in string b is needed
                a_alignment << '-';
                b_alignment << b[j];
                j--;
            }
        } else {
            //match < gap_a
            if(gap_a > gap_b){
                //match < gap_a && gap_b < gap_a
                //Pick a gap for string a
                a_alignment << a[i];
                b_alignment << '-';
                i--;
            } else {
                //Pick a gap for string b
                //match < gap_a && gap_a < gap_b

                a_alignment << '-';
                b_alignment << b[j];
                j--;
            }
        }
    }
    //This means that j = 1 or i = 1
    if ( i == 0 && j == 0 ){
        a_alignment << a[i];
        b_alignment << b[j];
        i--;
        j--;
    }

    if (i == 0){
        //This means we need to fill the rest of seq b
        while(j >= 0){
            if(i >= 0 && this->matrix[i][j] > this->matrix[0][j-1]){
                //We do the last match
                a_alignment << a[i];
                b_alignment << b[j];
                i--;
                j--;
            } else {
                a_alignment << '-';
                b_alignment << b[j];
                j--;
            }
        }
    } else {
        //This means we need to fill the rest of seq a
        while(i >= 0){
            if(j >= 0 && this->matrix[i][j] > this->matrix[i-1][j]){
                //We do the last match
                a_alignment << a[i];
                b_alignment << b[j];
                i--;
                j--;
            } else {
                a_alignment << a[i];
                b_alignment << '-';
                i--;
            } 
        }
    }
    
    std::string align_a = a_alignment.str();
    std::string align_b = b_alignment.str();
    std::reverse(align_a.begin(), align_a.end());
    std::reverse(align_b.begin(), align_b.end());
    std::pair<std::string,std::string> res (align_a,align_b);
    return res;
}

int NeedlemanWunsch::alignSequence_score(std::string& a, std::string& b){
    std::vector<int> a_translate = this->score.translateSequence(a);
    std::vector<int> b_translate = this->score.translateSequence(b);
    return this->run_algo(a_translate,b_translate);
}

int NeedlemanWunsch::alignSequence_score(std::vector<int>& a,std::vector<int>& b){
    return this->run_algo(a,b);
}

Alignment_Result NeedlemanWunsch::alignSequence(std::string& a, std::string& b){
    std::vector<int> a_translate = this->score.translateSequence(a);
    std::vector<int> b_translate = this->score.translateSequence(b);
    int score = this->run_algo(a_translate,b_translate);
    std::pair<std::string,std::string> res = this->backtrace(a,b);
    Alignment_Result r(res.first,res.second,score);
    return r;
}
