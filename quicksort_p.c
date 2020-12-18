void quicksort_p(int* array, int N);
void quicksort_tasks(int* array, int left, int right, int stop) ;

void quicksort_tasks(int* array, int left, int right, int stop) 
{
	
	int i = left, j = right;
	int tmp;
	int pivot = array[(left + right) / 2];

  //PARTITION
	while (i <= j) {
		while (array[i] < pivot)
			i++;
		while (array[j] > pivot)
			j--;
		if (i <= j) {
			swap(array[i], array[j]);
			i++;
			j--;
		}
	}
 
  //SERIAL PART
	if ( ((right-left)<stop) ){
		if (left < j){ quicksort_tasks(array, left, j, stop); }			
		if (i < right){ quicksort_tasks(array, i, right, stop); }
  
  //PARALLEL PART
	}else{
		#pragma omp task 	
		{ quicksort_tasks(array, left, j, stop); }
		#pragma omp task 	
		{ quicksort_tasks(array, i, right, stop); }		
	}

}

void quicksort_p(int* array, int N){

	int stop = 1000;

	#pragma omp parallel num_threads(8)
	#pragma omp single
	quicksort_tasks(array, 0, N-1, stop);

}