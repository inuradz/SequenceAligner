#ifndef ALIGNMENT_H
#define ALIGNMENT_H
#include <vector>
#include <string>
#include "../Matrixes/Scoring_Matrix.h"
#include "AlignmentResult.h"

class Alignment {
    public:
        virtual int                 alignSequence_score(std::string& a, std::string& b)             = 0 ;
        virtual int                 alignSequence_score(std::vector<int>& a, std::vector<int>& b)   = 0 ;
        virtual Alignment_Result    alignSequence(std::string& a, std::string& b)                   = 0 ;
};

#endif ALIGNMENT_H
