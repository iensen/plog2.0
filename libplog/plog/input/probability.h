//
// Created by iensen on 9/16/16.
//

#ifndef PLOG_PROBABILITY_H
#define PLOG_PROBABILITY_H

#include <gringo/printable.hh>
#include <gringo/locatable.hh>

class Probability: Gringo::Printable, Gringo::Locatable {
    int num, denum;
public:
    Probability(int num, int denum);
    double getDoubleVal();
    virtual void print(std::ostream &out) const;
    int getNum();
    int getDenum();

};
#endif //PLOG_PROBABILITY_H
