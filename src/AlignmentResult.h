#ifndef ALIGNMENT_RESULT
#define ALIGNMENT_RESULT

#include <string>

class Alignment_Result {
    std::string seq_a;
    std::string seq_b;
    int score;

    public:
        Alignment_Result(std::string,std::string,int);
};

#endif ALIGNMENT_RESULT