#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define N_TESTS 20
#define USEC_IN_SEC 1000000
#define MAX_TIME 100000000L

#define A 49.0 // |Komarov| * |Dmitryi|

double do_work(int);
double conform(int, double, double);
void sort(double[], int);
void print_array(double[], int);

int main(int argc, char* argv[]) {
	int i;
	int n;
	int seed;
	unsigned long best_time;

	n = atoi(argv[1]);
	seed = atoi(argv[2]);

	best_time = MAX_TIME;

	for (i = 0; i < N_TESTS; ++i) {
		struct timeval start, end;
		unsigned long elapsed_time;
		double work_result;

		srand(seed);
		gettimeofday(&start, NULL);

		work_result = do_work(n);

		gettimeofday(&end, NULL);

		#ifdef DEBUG
		printf("Work result = %lf\n", work_result);
		#endif

		elapsed_time = (end.tv_sec - start.tv_sec) * USEC_IN_SEC;
		elapsed_time += (end.tv_usec - start.tv_usec);
		if (elapsed_time < best_time) {
			#ifdef DEBUG
			printf("Best time will be updated: step=%d old=%ldus new=%ldus\n", 
				i, best_time, elapsed_time);
			#endif
			best_time = elapsed_time;
		}
	}

	#ifdef DEBUG
	printf("Best time (us): ");
	#endif
	printf("%ld\n", best_time);
    return 0;
}

double do_work(int n) {
	double *m1;
	double *m2;
	unsigned int next;
	int i;
	double last_element;
	double min;
	double sum;

	m1 = malloc(sizeof(double) * n);
	m2 = malloc(sizeof(double) * (n / 2));

	next = 1;

	// generate M1
	for (i = 0; i < n; ++i) {
		m1[i] = conform(rand_r(&next), 1.0, A);
	}

	#ifdef DEBUG
	printf("Generated M1: ");
	print_array(m1, n);
	#endif
	
	// generate M2
	for (i = 0; i < n / 2; ++i) {
		m2[i] = conform(rand_r(&next), A, 10 * A);
	}

	#ifdef DEBUG
	printf("Generated M2: ");
	print_array(m2, n / 2);
	#endif
	
	// map M1
	for (i = 0; i < n; ++i) {
		m1[i] = sqrt(m1[i] / M_E);
	}

	#ifdef DEBUG
	printf("Mapped M1: ");
	print_array(m1, n);
	#endif

	// map M2
	for (i = 1; i < n / 2; ++i) {
		m2[i] += m2[i - 1];
	}

	#ifdef DEBUG
	printf("Mapped M2 (sum elements): ");
	print_array(m2, n / 2);
	#endif

	for (i = 0; i < n / 2; ++i) {
		m2[i] = abs(tan(m2[i]));
	}

	#ifdef DEBUG
	printf("Mapped M2: ");
	print_array(m2, n / 2);
	#endif

	// merging
	for (i = 0; i < n / 2; ++i) {
		m2[i] *= m1[i];
	}

	#ifdef DEBUG
	printf("Merged M2: ");
	print_array(m2, n / 2);
	#endif

	// sorting
	sort(m2, n / 2);

	#ifdef DEBUG
	printf("Sorted M2: ");
	print_array(m2, n / 2);
	#endif

	// min value of sorted
	i = 0;
	while (m2[i++] == 0.0);

	if (i >= n / 2) {
		printf("Cannot find min val.\n");
		return -1.0;
	}

	min = m2[i];

	// reduce
	sum = 0.0;
	for (i = 0; i < n / 2; ++i) {
		int result;
		double div;

		div = m2[i] / min;
		result = (int) div;
		if (result % 2 == 0) {
			sum += sin(div);
		}

	}

	return sum;
}

double conform(int rand_val, double low, double high) {
	double a;

	a = (double) rand_val;  // [0.0; RAND_MAX]
	a /= (double) RAND_MAX; // [0.0; 1.0]
	a *= (high - low);      // [0.0; HIGH - LOW]
	a += low;               // [LOW; HIGH]

	return a;
}

void sort(double array[], int n) {
	int i, j;
	double key;

	for (i = 1; i < n; ++i) {
		key = array[i];
		j = i - 1;

		while (j >= 0 && array[j] > key) {
			array[j + 1] = array[j];
			--j;
		}
		array[j + 1] = key;
	}
}

void print_array(double array[], int n) {
	int i;

	printf("[");
	for (i = 0; i < (n - 1); ++i) {
		printf("%.4lf, ", array[i]);
	}
	printf("%.4lf]\n", array[n - 1]);
}