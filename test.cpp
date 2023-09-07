	/***********************************************************/
	/*                       Multithreading Test               */
	/***********************************************************/

	#include <iostream>
	#include <thread>
	#include <functional>
	#include <ctime>
	using namespace std;

	/***********************************************************/

	void fill_Array(int* arr, int size)
	{
		for (int i = 0; i < size; i++)arr[i] = 1;
	};

	void sum_Array(int* arr, int size, int*sum)
	{
		int s = 0;
		for (int i = 0; i < size; i++)s += arr[i];
		*sum = s;
	};

	/***********************************************************/

	void single_Thread(int* arr, int size)
	{
		int sum = 0;
		sum_Array(arr, size, &sum);
		// cout << sum << endl;
	};

	/***********************************************************/
	
	// arr - source array, size - array size, numb - number of threads 

	void multi_Thread(int* arr, int size, int numb) 
	{
		int sum = 0;
		int part_size = size / numb;			// part size
		int reminder  = size % numb;			// reminder
		int part = 0;
		int init = 0;

		thread* threads = new thread[numb];		// thread array
		int* part_sum = new int[numb];			// array of parial sum

		for (int i = 0; i < numb; i++)			// start threads
		{
			part = part_size;
			if (i == 0) part += reminder;   
			std::thread t(sum_Array, &arr[init], part, &part_sum[i]);
			threads[i] = std::move(t);
			init += part_size;
		};

		for (int i = 0; i < numb; i++)			// wait for completion
		{
			threads[i].join();
			sum += part_sum[i];
		};
		delete[] threads;
		delete[] part_sum;

		// cout << sum << endl;
	};

	/***********************************************************/

	void show_Bar()
	{
		for (unsigned i = 0; i < 40; i++)cout << "-";
		cout << endl;
	};

	/***********************************************************/

	// size - array size, numb - number of threads

	void start_Test(int size, int numb) 
	{
		unsigned init;
		unsigned last;

		cout << " array size = " << size << endl;

		int* arr = new int[size];			// source array
		fill_Array(arr, size);				// fill the source array with values

		init = clock();						// single thread test
		single_Thread(arr, size);
		last = clock();
		cout << " single thread time : " << last - init << endl;

		init = clock();
		multi_Thread(arr, size, numb);		// multi thread test
		last = clock();
		cout << " multi thread  time : " << last - init << endl;

		show_Bar();

		delete[] arr;
		
	};

	/***********************************************************/

	void numb_Test(int numb) 
	{
		// cout << " number of threads = " << numb << endl;	  
		show_Bar();
		start_Test(100000, numb);
		start_Test(1000000, numb);
		start_Test(10000000, numb);
		cout << endl;
	};

	/***********************************************************/

	int main()
	{
		int numb = 1;
		cout << " number of threads : ";
		cin >> numb;
		numb_Test(2);

		return 0;
	}
	
	/***********************************************************/



	


