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
    }
    if ( (double)map->size/(double)map->capacity > 0.7){
        enlarge(map);
    }
    map->current=i;
    map->size++;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
  Pair** auxMap= map->buckets;
  map->buckets= (Pair**) realloc(map->buckets, map->capacity*2 *sizeof(Pair*));
  map->size=0;
  map->capacity*= 2; 
  for (long i=0; i<map->capacity/2; i++){
    if ( (auxMap[i]!=NULL) && (auxMap[i]->key!=NULL) )
    insertMap(map, auxMap[i]->key, auxMap[i]->value); //soi buenisimo mish ahora si lo puedes hacer solito tay listo <3 suerte :3 graciaaaas suerte para ti tambien <3 arigatou asdasd F la manquie de pana asdasdas falto algo muy importante, que cosas tienes que insertar? si las puse po :c pero me falto ver si la key es null
    //a eso iba :x insertaras los nulos? NO POOO ahi si:v ya estas dentro del for lo se pero cuando se tope con algo invalido, habia puesto que si alguno de esos 2 era NULL que pasara al siguiente indice :v y si hay dos nulos seguios?sigue saltandolos po, nuu trataria de insertar el siguienteaaaaah que loca mi tiaasdasds
    
     
  }
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
