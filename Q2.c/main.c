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



Worker* CrateWorker(Worker *w,char *n,int check);
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
    int i = 0;
    WorkerList *head = NULL;
    char name1[20] = "oren";
    char name2[20] = "shahaf";
    char name3[20] = "yossi";
    char name4[20] = "yoni";
    char name5[20] = "poli";
    
    Worker w1 = {209,NULL,1200,2010};
    Worker w2 = {315,NULL,4200,2012};
    Worker w3 = {255,NULL,5000,2014};
    Worker w4 = {441,NULL,600,2022};
    Worker w5 = {762,NULL,1550,2003};
    
    CrateWorker(&w1,name1,1);
    CrateWorker(&w2,name2,1);
    CrateWorker(&w3,name3,1);
    CrateWorker(&w4,name4,1);
    CrateWorker(&w5,name5,1);
    
    PrintWorker(&w5,1);
    
    head = addWorker(head,&w1);
    head = addWorker(head,&w2);
    head = addWorker(head,&w3);
    head = addWorker(head,&w4);
    head = addWorker(head,&w5);
    
    PrintWorkerList(head);
    
    
    printf("the index in Loop function is : %d\n",indeX(head,255));
    
    printf("the index in recursion function is : %d\n",  indexR(head,255));
    
    head = deleteWorstWorker(head);
    printf("\n//delete worst worker//\n");
    PrintWorkerList(head);
    update_worker(head,0.20);
    printf("\n//update//\n");
    PrintWorkerList(head);
    head = reverse(head);
    printf("\n//reverse//\n");
    PrintWorkerList(head);
    freeWorkers(head);
    
    
    
    
    
    return 0;
}

// scanf crate worker function

Worker* CrateWorker(Worker *w,char *n,int check){ // check 1 = luz check 0 = heb
    
//    to check this function and the all code we used in const workers list

    char temp_name[40];
    Worker* New_worker = (Worker*)malloc(sizeof(Worker));
    if(!New_worker){
        printf("Allocation failed...\n");
        exit(0);
    }
//    printf("write a worker id\n");
//    scanf("%lu",&New_worker->id);
    
    New_worker->id = w->id;
    
//    printf("write a worker name\n");
//    scanf("%s",temp_name);
    strcpy(temp_name,n);
    
    char *name1 =(char*)malloc(sizeof(char) * strlen(temp_name) + 1);
    if(!name1){
        printf("Allocation failed...\n");
        exit(1);
    }
    strcpy(name1,temp_name);
    New_worker->name = name1;
    
//    printf("what is salery\n");
//    scanf("%lu",&New_worker->salery);
    
    New_worker->salery = w->salery;
    
//    printf("join year\n");
    if(check){
//        scanf("%lu",&New_worker->join_year.luz_year);
        New_worker->join_year.luz_year = w->join_year.luz_year;
    }
    else
//        scanf("%s",New_worker->join_year.heb_year);
        New_worker->join_year.luz_year = w->join_year.heb_year;
    return New_worker;
}

void PrintWorker(Worker* Worker,int check){ //
    if(check){ // 1-luz year 0-heb year
    printf("id : %lu\nname : %s\nsalery : %lu\njoin year : %lu\n",Worker->id,Worker->name,Worker->salery,Worker->join_year.luz_year);
    }
    else printf("id : %lu\nname : %s\nsalery : %lu\njoin year : %s\n",Worker->id,Worker->name,Worker->salery,Worker->join_year.heb_year);
}
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
        printf("The list is empty...\n");
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
        printf("The list is empty\n");
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
    if(head == NULL) return -1;
    if(head->data->id == id) return 1;
    return 1+indexR(head->next,id);
}

WorkerList* deleteWorstWorker(WorkerList *head){
    // case with empty list
    if(head == NULL){
        printf("The List is empty...");
        return head;
    }
    WorkerList *lowest = head;
    WorkerList *before = NULL;
    WorkerList *curr = head->next;
    WorkerList *prev = head;
    if(curr == NULL){
        printf("there is one worker in list...");
        return head;
    }
    while(curr != NULL){
        if(lowest->data->salery > curr->data->salery){
            lowest = curr;
            before = prev;
        }
        curr=curr->next;
        prev=prev->next;
    }
    before->next = lowest->next;
    free(lowest->data->name);
    free(lowest->next);
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
    //
    while (temp != NULL)
    {
        temp->data->salery = temp->data->salery * percent + temp->data->salery;
        temp = temp->next;
    }
}

    void freeWorkers(WorkerList * head)
    {
        WorkerList* tempSave = head;
        WorkerList* tempFree = head;
        if (head == NULL)
        {
            printf("The list is empty...\n");
            return;
        }

        while (tempSave != NULL)
        {
            tempFree = tempSave;
            tempSave = tempSave->next;
         //   free(tempFree->data->name);
            free(tempFree->data);
        }
    }
WorkerList* reverse(WorkerList * head)
    {
        WorkerList* tmp1 = NULL;
        WorkerList* tmp2 = NULL;
        
        if (head == NULL)
        {
            printf("The list is empty...\n");
            return head;
        }

        while (head != NULL)
        {
            tmp1 = head;
            head = head->next;
            tmp1->next = tmp2;
            tmp2 = tmp1;
        }
        return tmp1;
    }
