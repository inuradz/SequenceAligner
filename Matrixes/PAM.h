#ifndef PAM_H
#define PAM_H
#include <vector>
#include <string>

class PAM {
    public:
        PAM(int num);
        std::vector<int> translateSequence(std::string seq);
        std::vector<std::vector<int> > getMatrix();
};

#endif PAM_H