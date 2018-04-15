gcc -o lab1_par_$1.out -O3 -floop-parallelize-all -ftree-parallelize-loops=$1 main.c -lm

delta=`expr $3 - $2`
delta=`expr $delta / 10`

current=$2
while [ $current -le $3 ]
do
	current_time=$(./lab1_par_$1.out $current 47)
	echo "$current $current_time"
	current=`expr $current + $delta`
done
