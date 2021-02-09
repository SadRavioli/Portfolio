

void selectionSort(int array[], int list_size) {
	for (int i = 0; i <= list_size - 2; i++) {
		int smallest = i;
		for (int n = i + 1; n < list_size; n++) {
			if (array[n] < array[smallest]) {
				smallest = n;
			}
		}
		swap(&array[smallest], &array[i]);
	}
}