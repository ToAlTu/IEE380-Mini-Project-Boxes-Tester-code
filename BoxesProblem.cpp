#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Randomize an int array
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

//Randomly finds a box based on what boxes are left
void searchBoxesMethod1(bool* lop, int* boxes, int n, int* number){
    int tag = -1;
    int counter = 0;
    int* rList;
    for (int i = 0; i < n; i++){
        counter = 0;
        rList = number;
        shuffle(rList, n, n-i);
        int numbers = 0;
        tag = boxes[rList[numbers]];
        numbers++;
        while((counter < n/2) && !lop[i]){
            if(tag == i){
                lop[i] = true;
            }else{
                tag = boxes[rList[numbers]];
                numbers++;
            }
            counter++;
        }
    }
}

//Find boxes based on what tag was found from the previous box
void searchBoxesMethod2(bool* lop, int* boxes, int n){
    int tag = -1;
    int counter = 0;
    for (int i = 0; i < n; i++){
        counter = 0;
        tag = boxes[i];
        while((counter < n/2) && !lop[i]){
            if(tag == i){
                lop[i] = true;
            }else{
                tag = boxes[tag];
            }
            counter++;
        }
    }
}

int main(int argc, char *argv[]){
    if(argc != 5){
        printf("Usage: ./BoxProb amountOfPeople testRuns type info\n   amountOfPeople should be greater than 1\n   testRuns should be >= 1\n   type should be 1 or 2\n   info should be 1 to 4\n");
        exit(1);
    }
    int capacity = atoi(argv[1]);
    int testRuns = atoi(argv[2]);
    int type = atoi(argv[3]);
    int info = atoi(argv[4]);
    if(capacity <= 1 || testRuns < 1 || !(type == 1 || type == 2) || !(info == 1 || info == 2 || info == 3 || info == 4)){
        printf("Usage: ./BoxProb amountOfPeople testRuns type info\n   amountOfPeople should be greater than 1\n   testRuns should be >= 1\n   type should be 1 or 2\n   info should be 1 to 4\n");
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
        if(type == 1){
            searchBoxesMethod1(lop, boxes, capacity, number);
        }else if(type == 2){
            searchBoxesMethod2(lop, boxes, capacity);
        }
        for (int i = 0; i < capacity; i++){
            if(lop[i])
                success++;
        }
        if(success == capacity)
            correct++;
        if(info == 1)
            printf("%d\n", success);
        if(info == 2 || info == 4)
            printf("Total people who found their number %d/%d\n", success, capacity);
    }
    if(info == 3 || info == 4)
        printf("For %d people the total successes is %d/%d\n", capacity, correct, testRuns);
}
