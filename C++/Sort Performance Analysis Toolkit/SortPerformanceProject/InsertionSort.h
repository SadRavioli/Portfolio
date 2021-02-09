void insertionSort(int array[], int list_size) {
	for (int i = 1; i < list_size; i++) {
		int temp = array[i];
		int n = i - 1;

		while ((n >= 0) && (array[n] > temp)) {
			array[n + 1] = array[n];
			n = n - 1;
		}
		array[n + 1] = temp;
	}
}
