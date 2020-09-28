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

//This function works correctly. +10
void insertMap(HashMap * map, char * key, void * value) {
    long auxHash= hash(key, map->capacity);
    long i;
    for (i=auxHash; i< map->capacity; i++ )
    {
      if ((map->buckets[i]==NULL)||(map->buckets[i]->key==NULL)||(map->buckets[i]->value==NULL)){
        map->buckets[i] = createPair (key,value);
        break;
      }
      if (i == map->capacity-1)
      {
        i= -1;  
      }
    }
    map->current=i;
    map->size++;
    if ( (double)map->size/(double)map->capacity > 0.7){
        enlarge(map);
    } 
}//TIRAMISU estuvo aqui, muy buena ayudante. :D #antifunable yeey nwn

//30/70 vamo chile. This function works correctly. +10 y favorito 1link megaupload +crack
void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
  Pair** auxMap= map->buckets;
  map->buckets= (Pair**) malloc(map->capacity*2 *sizeof(Pair*));
  map->size=0;
  map->capacity*= 2; 
  for (long i=0; i<map->capacity/2; i++){
    if ( (auxMap[i]!=NULL) && (auxMap[i]->key!=NULL) )
    insertMap(map, auxMap[i]->key, auxMap[i]->value);
  }
} 

//This function works correctly. +10 
HashMap * createMap(long capacity) {
    HashMap* auxMap= (HashMap*) malloc(sizeof(HashMap));
    auxMap->buckets= (Pair**) malloc(sizeof(Pair*) * capacity);

    auxMap->size= 0;
    auxMap->capacity= capacity;
    auxMap->current= -1;
  
    return auxMap;
}

void eraseMap(HashMap * map,  char * key) {    
  if(searchMap(map, key)){
  map->buckets[map->current]->key =NULL;
  map->size--;
  }
}
//TIRAMISU estuvo aqui.
void * searchMap(HashMap * map,  char * key) {   
    long auxHash= hash(key, map-> capacity);
    long i;
    char* auxKey;
    for (i=auxHash; i< map->capacity; i++ )
    {
      if( (map->buckets[i]==NULL)||(map->buckets[i]->key==NULL) ) return NULL; //Key not found.
      auxKey= map->buckets[i]->key;
      
      if (is_equal(key, auxKey))
      {
        map->current=i;
        return map->buckets[i]->value;
      }
      if (i == map->capacity-1)
      {
        i= -1;  
      }

    }

    return NULL;
}
// 
void * firstMap(HashMap * map) {

    return NULL;
}

void * nextMap(HashMap * map) {

    return NULL;
}
