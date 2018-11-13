#ifndef NeedlemanWunsch_H
#define NeedlemanWunsch_H
#include <vector>
#include <map>
#include <string>
#include "../Matrixes/Scoring_Matrix.h"
#include "Alignment.h"
#include <tuple>

class NeedlemanWunsch : Alignment {
    int capacity;
    int gap_penalty;
    std::vector<std::vector<int> > scoringMatrix;
    std::vector<std::vector<int> > matrix;
    Scoring_Matrix& score;

    private:
        int run_algo(std::vector<int>& a, std::vector<int>& b);
        std::pair<std::string,std::string> backtrace(std::string a,std::string b);
    public:
        NeedlemanWunsch(int max_seq_size, int gap_penalty, Scoring_Matrix& s);
        int alignSequence_score(std::string& a, std::string& b);
        int alignSequence_score(std::vector<int>& a, std::vector<int>& b);
        Alignment_Result alignSequence(std::string& a, std::string& b);
};

#endif NeedlemanWunsch_H