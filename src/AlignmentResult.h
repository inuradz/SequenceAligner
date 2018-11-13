#ifndef ALIGNMENT_RESULT
#define ALIGNMENT_RESULT

#include <string>

class Alignment_Result {

    public:
        std::string seq_a;
        std::string seq_b;
        int score;
        Alignment_Result(std::string a,std::string b,int s):seq_a{a},seq_b{b},score(s){};
};

#endif ALIGNMENT_RESULT