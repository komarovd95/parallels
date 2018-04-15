gcc -o lab1_seq.out -O3 main.c -lm

delta=`expr $2 - $1`
delta=`expr $delta / 10`

current=$1
while [ $current -le $2 ]
do
	current_time=$(./lab1_seq.out $current 47)
	echo "$current $current_time"
	current=`expr $current + $delta`
done
