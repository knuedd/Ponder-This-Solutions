# 2021-07: Primes that are sums of powers

The [June 2021 puzzle](https://www.research.ibm.com/haifa/ponderthis/challenges/June2021.html) asked to find more numbers that are 

  * prime
  * can be represented as a^b+b^a for integers a,b > 1
  * can be represented as x²+y² for integers x,y
  * can be represented as x²+2y² for integers x,y
  * can be represented as x²+7y² for integers x,y

## Generating solutions

The solution idea was to generate numbers of the form a^b+b^a and check if they are prime. That is done pretty quickly. Then one can check if the fullfill the last three conditions by very easy tests according to [[1]](https://de.wikipedia.org/wiki/Zwei-Quadrate-Satz), [[2]](https://de.wikipedia.org/wiki/Zwei-Quadrate-Satz#Verwandte_Resultate), [[3]](https://math.stackexchange.com/questions/3764866/the-diophantine-equation-m-x2-7y2), and
[[4]](https://www.amazon.co.uk/Primes-Form-ny2-Multiplication-Mathematics/dp/1118390180/).


[1] [https://de.wikipedia.org/wiki/Zwei-Quadrate-Satz](https://de.wikipedia.org/wiki/Zwei-Quadrate-Satz)

[2] [https://de.wikipedia.org/wiki/Zwei-Quadrate-Satz#Verwandte_Resultate](https://de.wikipedia.org/wiki/Zwei-Quadrate-Satz#Verwandte_Resultate)

[3] [https://math.stackexchange.com/questions/3764866/the-diophantine-equation-m-x2-7y2](https://math.stackexchange.com/questions/3764866/the-diophantine-equation-m-x2-7y2)

[4] [https://www.amazon.co.uk/Primes-Form-ny2-Multiplication-Mathematics/dp/1118390180/](https://www.amazon.co.uk/Primes-Form-ny2-Multiplication-Mathematics/dp/1118390180/)

This can be done quickly with

    make
    ./gen_candidates 60 | tail -n 1 | tee candidate

## Solving the Diophantine equation

Now, actually solving the last three conditions is harder. Before the month was over I didn't find the idea with [Cornacchia's algorithm](https://en.wikipedia.org/wiki/Cornacchia%27s_algorithm). So I needed to brute force the solutions with the `split_solution_par.cpp` programm using OpenMP for parallelization. 

The commands below will reproduce this with the last arguments of the last three commands being suitable start values for the brute-force attempt. I didn't know those of course and needed to invest a bit more compute power on a somewhat bigger machine to find the solutions. Don't try that at home!

    N=`cat candidate`
    ./split_solution_par $N 0
    ./split_solution_par $N 1 13600000000
    ./split_solution_par $N 2 1522700000000
    ./split_solution_par $N 7 3089900000000
