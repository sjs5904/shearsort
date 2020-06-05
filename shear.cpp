#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <vector>
#include <iostream>
using namespace std; 

/**
* @author Jooseung Sonng
*
* this c file reads 2d array input from text file and sort it using multiple threads
*/

/**
* struct to pass parameter in pthread_create
*/
struct Params{
    int tid;
    int answer;
};

int gather,phase = 0;
int todo = 0;
vector<vector<int> > a;
int n,N = 0;
pthread_mutex_t count_mutex;
pthread_cond_t count_threshold_cv;

/**
* bubble sort right direction
* param i - row index
*/
void rowsort(int i){
    int j, k;
    for(j=0;j<n-1;j++){
        for(k=0;k<n-j-1;k++){
            if(a[i][k]>a[i][k+1]){
                int temp=a[i][k];
                a[i][k]=a[i][k+1];
                a[i][k+1]=temp;
            }
        }
    }
}

/**
* bubble sort left direction
* param i - row index
*/
void rowrevsort(int i){
    int j, k;
    for(j=0;j<n-1;j++){
        for(k=0;k<n-j-1;k++){
            if(a[i][k]<a[i][k+1]){
                int temp=a[i][k];
                a[i][k]=a[i][k+1];
                a[i][k+1]=temp;
            }
        }
    }
}

/**
* bubble sort vertical direction
* param i - column index
*/
void colsort(int i){
    int j, k;
    for(j=0;j<n-1;j++){
        for(k=0;k<n-j-1;k++){
            if(a[k][i]>a[k+1][i]){
                int temp=a[k][i];
                a[k][i]=a[k+1][i];
                a[k+1][i]=temp;
            }
        }
    }
}

/**
* Thread calling sort function
* Using pthread condition variable for mutual exclusion
* prints each phase
* cannot initialize variables in multi thread function
* param arg - holds thread ID
*/
void *shear_sort_thread(void *arg){
    struct Params *arg_struct = (struct Params*) arg;
	int i,j;

	
	for (phase=1;phase<=todo;) {
		// sort row first following the pdf description given
		if (phase%2) { //row
//			cout<<"row=============="<<arg_struct->tid<<"\n";  // check thread execution
			if (arg_struct->tid %2) rowrevsort(arg_struct->tid); // odd
			else rowsort(arg_struct->tid); // even
		}
		else {
//			cout<<"col**************"<<arg_struct->tid<<"\n";  // check thread execution
			colsort(arg_struct->tid); // col
		}
		
		// wait until all n threads finish
		pthread_mutex_lock(&count_mutex);
		if (gather < phase*n - 1) {
			gather++;
			pthread_cond_wait(&count_threshold_cv, &count_mutex);
		}
		else {
			// print each phase
			printf("Phase %d\n",phase);
			printf("--------------------\n");
			for(i=0;i<n;i++){
				for(j=0;j<n;j++) printf("%4d ", a[i][j]);
				printf("\n");
			}
			phase++;
			gather++;
			for (i=0;i<n-1;i++){
				pthread_cond_signal(&count_threshold_cv);
			}
		}
		pthread_mutex_unlock(&count_mutex);	
	}

    pthread_exit(NULL);
}

/**
* call pthread create.
* initiate conditional variable
* terminate thread
*/
void shear_sort(){
    int i = 0;
   
	pthread_mutex_init(&count_mutex, NULL);
	pthread_cond_init(&count_threshold_cv, NULL);
    pthread_t thrd[n];
	struct Params args[n];
	// create n threads;
    for (i=0;i<n;i++){
        args[i].tid = i;
        pthread_create(&thrd[i], NULL, shear_sort_thread, &args[i]);
    }
    
    for (i=0;i<n;i++){
        pthread_join(thrd[i], NULL);
    }
	
	pthread_mutex_destroy(&count_mutex);
	pthread_cond_destroy(&count_threshold_cv);
}


int main(){
    int i, j = 0;
	char c;
	FILE *afile;
    afile = fopen("input.txt", "r");
	// get input array height
	if (afile == NULL) 
    { 
        printf("Could not open file %s", "input.txt"); 
        return 0; 
    } 
	for (c = getc(afile); c != EOF; c = getc(afile)) {
        if (c == '\n') //
            n++; 
	}
	n++;
	rewind(afile);
	// resize array variable
	a.resize(n);
	for(int i=0;i<n;i++)
	{
		a[i].resize(n);
	}
	
	N = n*n;
	todo = ceil(log2(N) + 1);
	
	// print input array
	printf("Input Array\n");
	printf("--------------------\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            fscanf(afile, "%d", &a[i][j]);
            printf("%4d ", a[i][j]);
        }
        printf("\n");
    }
	// run sort
    shear_sort();
	
	fclose(afile);
	
    return 0;
}