gcc -o lab1_par_$1.out -O3 -floop-parallelize-all -ftree-parallelize-loops=$1 main.c -lm $3
./lab1_par_$1.out $2 47