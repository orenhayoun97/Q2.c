//
//  main.c
//  Q2.c
//
//  Created by oren hayoun on 18/03/2022.
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 5

typedef struct Worker {
    unsigned long id;
    char *name;
    unsigned long salery;
    union join_year{
        unsigned long luz_year;
        char heb_year[6];
    }join_year;
}Worker;

typedef struct WorkerList{
    Worker* data;
    struct WorkerList* next;
}WorkerList;



Worker* CrateWorker(int check);
void PrintWorker(Worker* Worker,int check);
void PrintWorkerList(WorkerList *head);
WorkerList* addWorker(WorkerList *head, Worker* w);
int indeX(WorkerList *head, long unsigned id);
int indexR(WorkerList *head, long unsigned id);
WorkerList* deleteWorstWorker(WorkerList *head);
void update_worker(WorkerList* head, float percent);
void freeWorkers(WorkerList * head);
WorkerList* reverse(WorkerList * head);

int main(){
    WorkerList *head = NULL;
    unsigned long search = 0;
    float update = 0;
    
    //for luz year 1
    //for heb year 0
    // we start a 5 workers, we can change it
    
    Worker *W1 = CrateWorker(1);
    Worker *W2 = CrateWorker(1);
    Worker *W3 = CrateWorker(1);
    Worker *W4 = CrateWorker(1);
    Worker *W5 = CrateWorker(1);
    
    head = addWorker(head,W1);
    head = addWorker(head,W2);
    head = addWorker(head,W3);
    head = addWorker(head,W4);
    head = addWorker(head,W5);
    
    PrintWorkerList(head);
    
    // check if the id in the list and print the index
    
    printf("put a id for search\n");
    fseek(stdin,0,SEEK_END);
    scanf("%lu",&search);
    int ind = indeX(head,search);
    if(ind > 0){
        printf("the index in Loop function is : %d\n",ind);
    }
    ind = indexR(head,search);
    if(ind > 0){
        printf("the index in recursion function is : %d\n",ind);
    }
    
    // function that delete the worst worker in the list
    
    head = deleteWorstWorker(head);
    printf("\n//delete worst worker//\n");
    PrintWorkerList(head);
    
    // function that rises the salary according to percent
    // until the percent up to 0
    while(1){
        printf("put a percent number\n");
        fseek(stdin,0,SEEK_END);
        scanf("%f",&update);
        if(update >= 0){
            break;
        }
    }
    update_worker(head,update/100);
    printf("\n//update//\n");
    PrintWorkerList(head);
    
    // function that reverst the list
    
    head = reverse(head);
    printf("\n//reverse//\n");
    PrintWorkerList(head);
    
    //free all the list
    
    freeWorkers(head);
    
    
    
    
    
    return 0;
}

// scanf crate worker function

Worker* CrateWorker(int check){ // check 1 = luz check 0 = heb
    
//    to check this function and the all code we used in const workers list

    char temp_name[40];
    Worker* New_worker = (Worker*)calloc(1,sizeof(Worker));
    if(!New_worker){
        printf("Allocation failed...\n");
        exit(0);
    }
    printf("write a worker id\n");
    fseek(stdin,0,SEEK_END);
    scanf("%lu",&New_worker->id);
    
    
    printf("write a worker name\n");
    fseek(stdin,0,SEEK_END);
    scanf("%s",temp_name);
    
    New_worker->name =(char*)calloc(sizeof(char),strlen(temp_name) + 1);
    if(!New_worker->name){
        printf("Allocation failed...\n");
        exit(1);
    }
    strcpy(New_worker->name,temp_name);
    
    printf("what is salery\n");
    fseek(stdin,0,SEEK_END);
    scanf("%lu",&New_worker->salery);
    
    
    printf("join year\n");
    if(check){ // check=1 -> luz year , check=0 -> heb year
        scanf("%lu",&New_worker->join_year.luz_year);
    }
    else
        scanf("%s",New_worker->join_year.heb_year);
    return New_worker;
}

void PrintWorker(Worker* Worker,int check){ //
    if(check){ // 1-luz year 0-heb year
    printf("id : %lu\nname : %s\nsalery : %lu\njoin year : %lu\n",Worker->id,Worker->name,Worker->salery,Worker->join_year.luz_year);
    }
    else printf("id : %lu\nname : %s\nsalery : %lu\njoin year : %s\n",Worker->id,Worker->name,Worker->salery,Worker->join_year.heb_year);
}

// not part from the Question
// print all the list

void PrintWorkerList(WorkerList *head){
    WorkerList *temp = head;
    while(temp != NULL){
        PrintWorker(temp->data,1);
        printf("\n");
        temp=temp->next;
    }
}

WorkerList* addWorker(WorkerList *head, Worker* w){
    WorkerList* New = (WorkerList*) malloc(sizeof(WorkerList));
    if(!New){
        printf("Allocation failed...\n");
        exit(2);
    }
    New->data = w;
    New->next = NULL;
    
    WorkerList* prev = NULL;
    WorkerList* curr = head;
    
    // case with empty list
    if(head == NULL){
        head = New;
        return head;
    }
    // case with the new worker have a bigger salary from the head worker
    if(New->data->salery > curr->data->salery){
        New->next = head;
        head = New;
        return head;
    }
    // case with somewhere in the middle of list
    while(curr != NULL && curr->data->salery > New->data->salery){
        prev=curr;
        curr=curr->next;
    }
    prev->next = New;
    New->next = curr;
    return head;
}

// Loop
int indeX(WorkerList *head, long unsigned id){
    // case empty list
    if(!head){
        printf("The id not found because the list is empty...\n");
        return -1;
    }
    WorkerList* temp = head;
    int i = 0,found = 0;
    while(!found && temp != NULL){
        i++;
        if(temp->data->id == id){
            found = 1;
        }
        temp=temp->next;
    }
    if(found) return i;
    else return -1;
}


// Recursion
int indexR(WorkerList *head, long unsigned id){
    int ind = 0;
    if(head == NULL) return -1;
    if(head->data->id == id) return 1;
    ind = indexR(head->next,id);
    if(ind == -1) return -1;
    else return ++ind;
}


WorkerList* deleteWorstWorker(WorkerList *head){
    WorkerList *lowest = head;
    WorkerList *before = NULL;
    WorkerList *curr = head->next;
    WorkerList *prev = head;
    
    // case with empty list
    if(head == NULL){
        printf("The List is empty...");
        return head;
    }
    // case with one worker in the list
    if(curr == NULL){
        printf("there is one worker in the list...");
        return head;
    }
    // case with more than one worker in the list
    while(curr != NULL){
        if(lowest->data->salery > curr->data->salery){
            lowest = curr;
            before = prev;
        }
        curr=curr->next;
        prev=prev->next;
    }
    before->next = lowest->next;
    
    // free the worst worker
    free(lowest->data->name);
    free(lowest->data);
    free(lowest);
    return head;
}
void update_worker(WorkerList* head, float percent){

    WorkerList* temp = head;
    // case list is empty
    if (head == NULL)
    {
        printf("The list is empty...\n");
        return;
    }
    while (temp != NULL)
    {
        temp->data->salery = temp->data->salery * percent + temp->data->salery;
        temp = temp->next;
    }
}
WorkerList* reverse(WorkerList * head)
    {
        // crate 2 pointeres
        WorkerList* new_head = NULL;
        WorkerList* temp = NULL;
        
        if (head == NULL)
        {
            printf("The list is empty...\n");
            return head;
        }
        
        while (head != NULL)
        {
            new_head = head;
            head = head->next;
            new_head->next = temp;
            temp = new_head;
        }
        return new_head;
    }

    void freeWorkers(WorkerList* head)
    {
        // crate 2 pointers
        WorkerList* tempSave = head;
        WorkerList* tempFree = head;
        // deal with empty list
        if (head == NULL)
        {
            printf("The list is empty...\n");
            return;
        }
        // free all the list
        while (tempSave != NULL)
        {
            tempFree = tempSave;
            tempSave = tempSave->next;
            free(tempFree->data->name);
            free(tempFree->data);
        }
    }
