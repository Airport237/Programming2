//
// Created by Justin Galin on 11/30/22.
//

#ifndef PROJECT3_MINESWEEPER_RANDOM_H
#define PROJECT3_MINESWEEPER_RANDOM_H
#include <random>

class Random {
static std::mt19937 random;
public:
    static int Int(int min, int max);
    static float Float(float min, float max);
};


#endif //PROJECT3_MINESWEEPER_RANDOM_H
