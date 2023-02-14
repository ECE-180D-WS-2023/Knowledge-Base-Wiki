# Evaluating Random Number Generators

## Introduction

Uncertainty is a critical facet of human life, but recreating entropy in the digital world requires some extra machinations. Random number generators (RNGs) are the driving force behind system fundamentals from security encryption to rolling virtual dice in online games. Artificially manufacturing randomness is complicated: in this article, we’ll discuss various types of RNG’s and learn about what qualities constitute a “good” random number. 

## tRNGs vs pRNGs

While there are numerous ways to generate random numbers, all RNGs fall into one of two categories: true random number generators (tRNGs), and pseudo random number generators (pRNGs). True RNGs take data from some entropy source (ie. movements of a mouse or date and time) and generate a string of bits based on that source. tRNGs are sometimes viewed as ineffective because the entropy sources can be predictable, and it is often time-consuming to produce a high quality string of random numbers. Two simple examples are rolling dice and flipping a well-balanced coin. Although the exact string of numbers produced would be impossible to predict, the overhead to produce a sequence long enough for cryptographic or other applications is significant. On the other hand, pRNGs take some nonrandom seed and apply a mathematical algorithm to output a high quality string of random numbers. Though the bits generated appear random and pass statistical tests for randomness, a string of pRNG numbers could sometimes be replicated if the seed and the method of generation is known. Deterministic algorithms - algorithms that give the same sequence given the same seed - are therefore less secure for cryptographic purposes. 

## NIST Tests and Quantifying Randomness

I’ve alluded to randomness as a measurable quality, but how can we quantitatively say that one sequence of bits is “more random” than another? A good starting point is to imagine that in a given sequence of bits, a “random” sequence should have the same amount of 0’s and 1’s, the way a coin flip has a 50% chance of landing on heads or tails. Consider the following sequences of bits:

* 1111111100000000
* 1010101010101010
* 1101011001010100

Although all three sequences contain the same amount of 0’s and 1’s, the first two clearly have a more obvious distribution. Using the above example as a basis, we can consider scaling up to bit sequences that are several orders of magnitudes larger. Naturally, patterns will begin to emerge: do the bits begin to repeat themselves? Are the amount of consecutive ones or zeros doubling? Does the Fibonacci pattern start to show up? If I plotted the points, would a discernible image appear? The more recognizable the bits are, the easier it is to predict them. One such framework which can be used to categorize the quality of random numbers is the National Institute of Standards and Technology (NIST) Test Suite for Random and Pseudorandom Number Generators for Cryptographic Applications. The publication is an incredibly detailed technical description of random number generators and fifteen different statistical tests which are considered the industry standard for testing random number generators, and it heavily contributed to this article. If you are curious about the mathematical aspects of the tests, the publication is worth taking a closer look at. We’ll be using the tests as a tool to explore pseudorandom number generators, specifically one you may have used before: Python’s random function. We will write a simple script to generate some random numbers and examine them via the NIST Test Suite. 

## Code and Results

This is the script I used; it’s fairly straightforward, but please see the Python random function documentation page and this tutorial about writing to a file if you want a more detailed explanation. 

    import sys
    import random 

    original_stdout = sys.stdout 

    #open file
    with open('rand1.txt', 'w') as f: 
        sys.stdout = f 
        # generate bit sequence
        for i in range(1000000):
            rnd_num = random.randint(0, 1)
            print(rnd_num)
        sys.stdout = original_stdout 

Essentially, we want to generate around a million random bits and place them in a text file. Once we have generated our bit sequence, we can run the NIST tests on our pRNG data.

When running the NIST tests, follow the instructions listed on page 96 of the publication. Here is a screenshot of the outputs from the text file I generated:

![]()

As seen above in the pass rates in the proportions section, our Python random function generated sequence passed the NIST Test Suite! This is not a go-ahead to use the function for cryptographic purposes, as a robustly tested pRNG would need a much larger sample size including variables we are not covering in this article, but it does tell us that the Python random function is, in fact, pretty random. It’s good enough to tell you that if your code is buggy, the Python random function is probably not the source of your problems.


### References
https://nvlpubs.nist.gov/nistpubs/legacy/sp/nistspecialpublication800-22r1a.pdf
https://www.geeksforgeeks.org/pseudo-random-number-generator-prng/
https://www.sciencedirect.com/topics/computer-science/mersenne-twister 
https://www.synopsys.com/designware-ip/technical-bulletin/true-random-number-generator-security-2019q3.html 