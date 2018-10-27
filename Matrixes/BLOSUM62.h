#include "Scoring_Matrix.h"
#include <map>

class BLOSUM62 : public Scoring_Matrix {
    private:
        std::vector<std::vector<int> > scoring_matrix;
        std::map<char,int> translation;

    public:
        BLOSUM62();
        std::vector<std::vector<int> > getMatrix();
        std::vector<int> translateSequence(std::string seq);
};