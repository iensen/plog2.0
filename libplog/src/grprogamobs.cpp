//
// Created by iensen on 11/18/16.
//

#include<plog/grprogramobs.h>

void PlogGroundProgramBuilder::rule(bool choice, AtomSpan headats, LiteralSpan bodyLits) {
  printf("RULE\n");
}
// question: why is it i need to include the namespace here? Is it C++ bug?
void PlogGroundProgramBuilder::output_atom(Clingo::Symbol symbol, atom_t atom) {
   printf("ATOM\n");
}

PlogGroundProgramBuilder::PlogGroundProgramBuilder(GroundPlogBackend &out):out(out) {

}

