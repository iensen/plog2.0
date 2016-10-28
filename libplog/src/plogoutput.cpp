//
// Created by iensen on 9/16/16.
//

#include<plog/plogoutput.h>

void PlogOutput::output(DomainData &data, GringoStatement &stm) {
    // implement text output for now:

    stm.print({data, std::cout},"");


}
