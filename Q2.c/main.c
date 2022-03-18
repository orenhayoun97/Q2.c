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

Worker* CrateWorker(unsigned long id,char *name,unsigned long salery,int join_year);
void PrintWorker(Worker* Worker);

int main(){
    
}
Worker* CrateWorker(unsigned long id,char *name,unsigned long salery,int join_year){
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
    New_worker->join_year. = join_year;
    return New_worker ;
}
void PrintWorker(Worker* Worker,int check){ //
    if(check){ // 1-luz year 0-heb year
    printf("id : %llu\name : %s\nsalery : %llu\njoin year : %llu\n",Worker->id,Worker->name,Worker->salery,Worker->join_year.luz_year);
    }
    else printf("id : %llu\name : %s\nsalery : %llu\njoin year : %s\n",Worker->id,Worker->name,Worker->salery,Worker->join_year.heb_year);
        
}
