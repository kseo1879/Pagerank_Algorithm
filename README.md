# PAGERANK

This is the submittion for PAGERANK-Algorithm Simulation for SOFT3410 Assignment2 Part 2

By: Calvin Seo

SID: 480347192

## How to use

### 1. To run and test the program 

To compile: You can simply type this in your command line
```bash
make
```
OR
```bash
make pagerank
```

- Now, You can test by simply typing

```bash
make test
```

This will output the result from running the program and the output you need to get. It sill look something like this:

```bash
PASSED THE TEST: tests/sample.in, AGAINST: tests/sample.out
PASSED THE TEST: tests/test01.in, AGAINST: tests/test01.out
PASSED THE TEST: tests/test02.in, AGAINST: tests/test02.out
PASSED THE TEST: tests/test03.in, AGAINST: tests/test03.out
PASSED THE TEST: tests/test04.in, AGAINST: tests/test04.out
PASSED THE TEST: tests/test05.in, AGAINST: tests/test05.out
PASSED THE TEST: tests/test06.in, AGAINST: tests/test06.out
PASSED THE TEST: tests/test07.in, AGAINST: tests/test07.out
PASSED THE TEST: tests/test08.in, AGAINST: tests/test08.out
PASSED THE TEST: tests/test09.in, AGAINST: tests/test09.out
PASSED THE TEST: tests/test10.in, AGAINST: tests/test10.out
PASSED THE TEST: tests/test11.in, AGAINST: tests/test11.out
PASSED THE TEST: tests/test12.in, AGAINST: tests/test12.out
```
The first line is saying that the running sample.in to the program produced the same output as sample.out.

### 2. To clean the directory

To clean the directory simply type
```bash
make clean
```

### 3. Changing the number of threads

If you look at the pagerank.c line 18,
```bash
    omp_set_num_threads(ncores);
```

It will set the thread numbers to the same number of the cores.

However you can manually change this number to test with different number of threads for testing the performance. 

### 4. What is pagerank_old.c file?
It is the old version of the pagerank.c where I missed some of the optimization
