#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"

typedef struct Pair Pair;
typedef struct HashMap HashMap;
int enlarge_called=0;

struct Pair {
     char * key;
     void * value;
};

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};



Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    long auxHash= hash(key, map->capacity);
    long i;
    for (i=auxHash; i< map->capacity; i++ )
    {
      if ((map->buckets[i]==NULL)||(map->buckets[i]->key==NULL)){
        map->buckets[i] = createPair (key,value);
        break;
      }
      if ( (i == map->capacity-1) && (map->buckets[i]==NULL) )
      {
        i= -1;  
      }
      if ( (double)map->size/(double)map->capacity > 0.7){
        enlarge(map);
      }
    }
    
    map->current=i;
    map->size++;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
    


}


HashMap * createMap(long capacity) {
    HashMap* auxMap= (HashMap*) malloc(sizeof(HashMap));
    auxMap->buckets= (Pair**) malloc(sizeof(Pair*) * capacity);

    auxMap->size= 0;
    auxMap->capacity= capacity;
    auxMap->current= -1;
  
    return auxMap;
}

void eraseMap(HashMap * map,  char * key) {    


}

void * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

void * firstMap(HashMap * map) {

    return NULL;
}

void * nextMap(HashMap * map) {

    return NULL;
}
