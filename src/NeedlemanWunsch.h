#ifndef NeedlemanWunsch_H
#define NeedlemanWunsch_H
#include <vector>
#include <map>
#include <string>
#include "../matrixes/Scoring_Matrix.h"


class NeedlemanWunsch {
    int capacity;
    int gap_penalty;
    std::vector<std::vector<int> > scoringMatrix;
    std::vector<std::vector<int> > matrix;
    Scoring_Matrix& score;

    private:
        int run_algo(std::vector<int>& a, std::vector<int>& b);

    public:
        NeedlemanWunsch(int max_seq_size, int gap_penalty, Scoring_Matrix& s);
        int alignSequence(std::string& a, std::string& b);
        int alignSequence(std::vector<int>& a, std::vector<int>& b);
};

#endif NeedlemanWunsch_H