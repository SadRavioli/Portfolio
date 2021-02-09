
void bubbleSort(int array[], int list_size) {
	for (int i = 0; i < (list_size - 1); i++) {
		for (int n = 0; n < (list_size - i - 1); n++) {
			if (array[n] > array[n + 1]) {
				swap(&array[n], &array[n + 1]);
			}
		}
	}
}
