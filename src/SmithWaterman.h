#ifndef SmithWaterman_H
#define SmithWaterman_H
#include <vector>
#include <map>
#include <string>



class SmithWaterman {
    int capacity;
    std::vector<std::vector<int> > scoringMatrix;
    std::map<char,int> letterMap;

    public:
        SmithWaterman();
        int alignSequence(std::string a, std::string b);
};

#endif SmithWaterman_H