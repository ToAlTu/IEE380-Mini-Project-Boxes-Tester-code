#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct ll{
    int num;
    ll *next;
}ll;
typedef ll *pll;

void shuffle(int *arr, size_t n, int r)
{
    if (n > 1) 
    {
        size_t i;
        srand(r*time(NULL));
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = arr[j];
          arr[j] = arr[i];
          arr[i] = t;
        }
    }
}

void searchBoxesMethod1(bool* lop, int* boxes, int n){
    int tag = -1;
    int counter = 0;
    for (int i = 0; i < n; i++){
        counter = 0;
        tag = boxes[i];
        while((counter < n/2) && !lop[i]){
            if(tag == i){
                lop[i] = true;
                //printf("SUCCESS\n");
            }else{
                tag = boxes[tag];
            }
            counter++;
            //printf("counter: %d\n", counter);
        }
    }
}

void searchBoxesMethod2(bool* lop, int* boxes, int n, int* number){
    int tag = -1;
    int counter = 0;
    int* rList;
    for (int i = 0; i < n; i++){
        counter = 0;
        rList = number;
        shuffle(rList, n, n-i);
        int numbers = 0;
        tag = boxes[rList[numbers]];
        //printf("%d\n", tag);
        numbers++;
        while((counter < n/2) && !lop[i]){
            if(tag == i){
                lop[i] = true;
                //printf("SUCCESS\n");
            }else{
                tag = boxes[rList[numbers]];
                //printf("%d\n", tag);
                numbers++;
            }
            counter++;
            //printf("counter: %d\n", counter);
        }
    }
}

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Usage: ./BoxProb amountOfPeople testRuns\n   amountOfPeople should be greater than 1\n   testRuns should be >= 1\n");
        exit(1);
    }
    int capacity = atoi(argv[1]);
    int testRuns = atoi(argv[2]);
    if(capacity <= 1 || testRuns < 1){
        printf("Usage: ./BoxProb amountOfPeople testRuns\n   amountOfPeople should be greater than 1\n   testRuns should be >= 1\n");
        exit(1);
    }
    bool lop[capacity];
    int boxes[capacity];
    int correct = 0;
    int success = 0;
    for (int j = 0; j < testRuns; j++){
        success = 0;
        for (int i = 0; i < capacity; i++){
            boxes[i] = i;
            lop[i] = false;
        }
        int* number = boxes;
        shuffle(boxes, capacity, j);
        // for (int i = 0; i < capacity; i++){
        //     printf("box%d: %d\n", i, boxes[i]);
        // }
        //searchBoxesMethod1(lop, boxes, capacity);
        searchBoxesMethod2(lop, boxes, capacity, number);
        for (int i = 0; i < capacity; i++){
            if(lop[i]){
                //printf("box%d: %d\n", i, boxes[i]);
                success++;
            }
        }
        if(success == capacity){
            correct++;
        }
        printf("%d\n", success);
        //printf("Total people who found their number %d/%d\n", success, capacity);
    }
    //printf("For %d people the total successes is %d/%d\n", capacity, correct, testRuns);
}