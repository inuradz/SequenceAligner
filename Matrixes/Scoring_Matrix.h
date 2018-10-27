#ifndef SCORING_MATRIX_H
#define SCORING_MATRIX_H
#include <vector>
#include <string>

class Scoring_Matrix {
    public:
        virtual std::vector<int> translateSequence(std::string seq) = 0;
        virtual std::vector<std::vector<int> > getMatrix() = 0;
};

#endif SCORING_MATRIX_H