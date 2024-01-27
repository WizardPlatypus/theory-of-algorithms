This is a simple interpreter for a [Turing (tape) Machine]().
It takes a TM program and simulates its execution from start to finish.

You can find example programs in the `samples/` directory.

To build the project, use can use the `build.sh` script:

```bash
./build.sh
```

To run the project, supply the executable with a path to a file containing TM program, and a list of numbers - arguments to that program:

```bash
./main samples/01\ x\ +\ y.txt 2 3
```

You should then see a simulation of given TM:

```bash
||#|||
^
q0|->q0|R ||#|||
           ^
q0|->q0|R ||#|||
            ^
q0#->q0|R ||||||
             ^
q0|->q0|R ||||||
              ^
q0|->q0|R ||||||
               ^
q0|->q0|R ||||||A
                ^
q0A->q1AL ||||||A
               ^
q1|->q*A |||||AA
              ^
Reached final state
```
