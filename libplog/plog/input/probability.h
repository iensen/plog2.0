//
// Created by iensen on 9/16/16.
//

#ifndef PLOG_PROBABILITY_H
#define PLOG_PROBABILITY_H
struct Probability {
    Probability(int num, int denum);
    double getDoubleVal();
    int num, denum;

};
#endif //PLOG_PROBABILITY_H
