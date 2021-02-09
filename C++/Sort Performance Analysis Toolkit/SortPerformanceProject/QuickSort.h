

int partition(int array[], int a, int b) {
	int pivot = array[a];
	int n = (b + 1);
	for (int i = b; i > a; i--) {
		if (array[i] >= pivot) {
			n--;
			swap(&array[n], &array[i]);
		}
	}
	swap(&array[n - 1], &array[a]);
	return (n - 1);
}

void quickSort(int array[], int a, int b) { 
	if (a < b) {
		int pi = partition(array, a, b);
		quickSort(array, a, pi - 1);
		quickSort(array, pi + 1, b);
	}
}