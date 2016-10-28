//
// Created by iensen on 10/14/16.
//

#include<plog/input/probability.h>

Probability::Probability(int num, int denum):num(num), denum(denum) {

}

double Probability::getDoubleVal() {
    return double(num)/denum;
}

void Probability::print(std::ostream &out) const {
    throw "not implemented yet";
}
