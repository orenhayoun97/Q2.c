//
//  main.c
//  Q2.c
//
//  Created by oren hayoun on 18/03/2022.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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



Worker* CrateWorker(unsigned long id,char *name,unsigned long salery,void *p2year,int check);
void PrintWorker(Worker* Worker);
WorkerList* addWorker(WorkerList *head, Worker* w);
int index(WorkerList *head, long unsigned id);
int indexR(WorkerList *head, long unsigned id);
WorkerList* deleteWorstWorker(WorkerList *head);

int main(){
    
}
Worker* CrateWorker(unsigned long id,char *name,unsigned long salery,void *p2year,int check){
    Worker* New_worker = (Worker*)malloc(sizeof(Worker));
    if(!New_worker){
        printf("Allocation failed...\n");
        exit(0);
    }
    New_worker->name = (New_worker->name)malloc(sizeof(strlen(name)+1));
    if(!New_worker->name){
        printf("Allocation failed...\n");
        exit(0);
    }
    strcpy(New_worker->name,name);
    New_worker->id = (unsigned long)id;
    New_worker->salery = salery;
    if(check){
        New_worker->join_year.luz_year = (int) *p2year;
    }
    else
        New_worker->join_year.heb_year = (char) *p2year;
    return New_worker ;
}
void PrintWorker(Worker* Worker,int check){ //
    if(check){ // 1-luz year 0-heb year
    printf("id : %llu\name : %s\nsalery : %llu\njoin year : %llu\n",Worker->id,Worker->name,Worker->salery,Worker->join_year.luz_year);
    }
    else printf("id : %llu\name : %s\nsalery : %llu\njoin year : %s\n",Worker->id,Worker->name,Worker->salery,Worker->join_year.heb_year);
}
WorkerList* addWorker(WorkerList *head, Worker* w){
    WorkerList* New = (WorkerList*) malloc(sizeof(WorkerList));
    New->data->name = w->name;
    New->data->salery = w->salery;
    New->data->join_year = w->join_year;
    New->data->id = w->id;
    New->next = NULL;
    
    WorkerList* prev = NULL;
    WorkerList* curr = head;
    
    // empty list
    if(head == NULL){
        printf("The list is empty...\n");
        head = New;
        return head;
    }
    if(New->data->salery > prev->data->salery){
        New->next = head;
        head = New;
        return head;
    }
    while(curr != NULL && curr->data->salery > New->data->salery){
        prev=curr;
        curr=curr->next;
    }
    prev->next = New;
    New->next = curr;
    return head;
}
// Loop
int index(WorkerList *head, long unsigned id){
    if(!head){
        printf("The list is empty\n");
        return -1;
    }
    WorkerList* temp = head;
    int i = 0,found = 0;
    do{
        i++;
        if(temp->data->id == id){
            found++;
        }
        temp=temp->next;
    }while(!found || temp == NULL);
    if(found) return i;
    else return -1;
}
// Recursion
int indexR(WorkerList *head, long unsigned id){
    if(head == NULL) return -1;
    if(head->next == id) return 1;
    return indexR(head->next,id);
}
WorkerList* deleteWorstWorker(WorkerList *head){
    if(head == NULL){
        printf("The List is empty...");
        return head;
    }
    WorkerList *lowest = NULL;
    WorkerList *before = NULL;
    WorkerList *curr = head->next;
    WorkerList *prev = head;
    if(curr == NULL){
        printf("there is one worker in list...");
        return head;
    }
    while(curr != NULL){
        if(curr->data->salery > lowest->data->salery){
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
