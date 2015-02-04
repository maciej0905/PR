#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <Windows.h>
#include <stdlib.h>

long long num_steps = 1000000000;
double step;

void bindThreadsToCores(int numOfCores){
	HANDLE thread_uchwyt=GetCurrentThread();
	int th_id=omp_get_thread_num();
	DWORD_PTR mask = (1 << (th_id % numOfCores ));
	DWORD_PTR result = SetThreadAffinityMask(thread_uchwyt,mask);
}

int main(int argc, char* argv[])
{
	/* // Punkt 1
	clock_t start, stop;
	double x, pi, sum=0.0;
	int i;
	step = 1./(double)num_steps;
	start = clock();
	for (i=0; i<num_steps; i++)
	{
	x = (i + .5)*step;
	sum = sum + 4.0/(1.+ x*x);
	}

	pi = sum*step;
	stop = clock();

	printf("Wartosc liczby PI wynosi %15.12f\n",pi);
	printf("Czas przetwarzania wynosi %f sekund\n",((double)(stop - start)/1000.0));
	return 0; */


	//Wersja pierwsza kodu 
	omp_set_num_threads(4); 
	clock_t start, stop;
	double x, pi, sum=0.0;
	int i;
	step = 1./(double)num_steps;
	start = clock();

#pragma omp parallel for 
	for (i=0; i<num_steps; i++)
	{

		x = (i + .5)*step;
		#pragma omp atomic
		sum += 4.0/(1.+ x*x);
		printf("Suma %d \n", i); 
	} 

	pi = sum*step;
	stop = clock();

	printf("Wartosc liczby PI wynosi %15.12f\n",pi);
	printf("Czas przetwarzania wynosi %f sekund\n",((double)(stop - start)/1000.0));
	return 0;


	//	//Wersja druga kodu 
	//	omp_set_num_threads(4); 
	//	clock_t start, stop;
	//	double x, pi, sum=0.0;
	//	int i;
	//	step = 1./(double)num_steps;
	//	start = clock();
	//#pragma omp parallel for reduction (+:sum)
	//	for (i=0; i<num_steps; i++)
	//	{
	//		x = (i + .5)*step;
	//		sum += 4.0/(1.+ x*x);
	//	} 
	//	pi = sum*step;
	//	stop = clock();
	//	printf("Wartosc liczby PI wynosi %15.12f\n",pi);
	//	printf("Czas przetwarzania wynosi %f sekund\n",((double)(stop - start)/1000.0));
	//	return 0;


	//	// Zadanie 6 i 7 
	//	omp_set_num_threads(2); 
	//	clock_t start, stop;
	//	double x, pi, sum=0.0, suml[30];
	//	memset(suml,0,sizeof(suml)); 
	//	int i;
	//	step = 1./(double)num_steps;
	//	//start = clock();
	//
	//	// Zadanie 7 
	//	for(int j=0;j<20;j++)
	//	{
	//		// Wersja 3 kodu 
	//		start = clock();
	//		sum=0; 
	//#pragma omp parallel reduction (+:sum)
	//		{
	//			bindThreadsToCores(2);
	//			int id = omp_get_thread_num();
	//#pragma omp for private(x)
	//			for (i=0; i<num_steps; i++)
	//			{
	//				x = (i + .5)*step;
	//				suml[j+id] += 4.0/(1.+ x*x);
	//			} 
	//			sum+=suml[j+id]; 
	//			suml[j+id]=0; 
	//		}
	//		pi = sum*step;
	//		stop = clock();
	//		printf("Wartosc liczby PI wynosi %15.12f\n",pi);
	//		printf("Czas przetwarzania wynosi %f sekund\n",((double)(stop - start)/1000.0)); 
	//	} 
	//	return 0;

	//	//Dedykowanie wątków 
	//	omp_set_num_threads(4); 
	//	clock_t start, stop;
	//	double x, pi, sum=0.0;
	//	int i;
	//	step = 1./(double)num_steps;
	//	start = clock();
	//
	//#pragma omp parallel reduction (+:sum)
	//	{
	//		//bindThreadsToCores(2);
	//#pragma omp for private(x)
	//		for (i=0; i<num_steps; i++)
	//		{
	//			x = (i + .5)*step;
	//			sum += 4.0/(1.+ x*x);
	//		} 
	//	} 
	//	pi = sum*step;
	//	stop = clock();
	//
	//	printf("Wartosc liczby PI wynosi %15.12f\n",pi);
	//	printf("Czas przetwarzania wynosi %f sekund\n",((double)(stop - start)/1000.0)); 
	//	return 0;

	//False Sharing, dlaczego bindThreadToCores, dlaczego występuje FalseSharing
	// Pomiar czasu z taktowaniem, turboBoost
	// Jak działa atomic - dba o to, żeby globalna zmienna często używana nie była zapisywana do rejestrów 
}
