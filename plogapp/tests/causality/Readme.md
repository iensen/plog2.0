The programs in this directory, adapted to the syntax of the solver, contain programs from  joint work with Dr.Michael Gelfond on causality. Note that, in several rare cases, the answer may vary, because our solver uses cardinality-based preference for consistency restoring rules.

For detailed instructions on how to install the P-log solver and run the programs (compute possible worlds and probabilities), please refer to https://github.com/iensen/plog2.0/wiki.

For a quick example, given that P-log executable (named plog2.0) is available in the current folder, and plogapp/tests/causality/courorder.plog contains T(S) for scenario S = {dead(0) = false, obs(dead(3)}, this is how to compute the possible worlds of T(S):
```bash
./plog2 --mode=pw plogapp/tests/causality/courtorder.plog 
Plog 2.1
Possible Worlds:
1: {court_order(0), court_order(1) = false, court_order(2) = false, court_order(3) = false, captain_order(1), captain_order(0) = false, captain_order(2) = false, captain_order(3) = false, shoot(a, 2), shoot(b, 2), shoot(a, 0) = false, shoot(a, 1) = false, shoot(a, 3) = false, shoot(b, 0) = false, shoot(b, 1) = false, shoot(b, 3) = false, dead(3), dead(0) = false, dead(1) = false, dead(2) = false}

Probabilities:
1: 1
```
-mode==pw flag is used to indicate that possible worlds should be computed, rather than an answer to certain query.
Note that the solver uses cardinality-based preference for consistency-restoring rules.
