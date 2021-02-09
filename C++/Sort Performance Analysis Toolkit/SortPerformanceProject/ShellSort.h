void shellSort(int array[], int list_size) { 
	for (int gap = list_size / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < list_size; i += 1) {
			int temp = array[i];
			int n;
			for (n = i; n >= gap && array[n - gap] > temp; n -= gap) {
				array[n] = array[n - gap];
			}
			array[n] = temp;
		}

	}
}
