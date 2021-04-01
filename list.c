#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    const void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(const void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    //creamos la lista e inicializamos con malloc
    List* lista = (List*) malloc(sizeof(List));
    //sus datos queda inicializados en NULL
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
    //retornamos el puntero a la lista
    return lista;
}

void * firstList(List * list) {
  //si el primer dato de la lista es nulo,
  //significa que no hay datos en la lista
  //no hacemos nada
    if(list->head == NULL) return NULL;
  //si no hacemos que el current apunte al primero de 
  //la lista y retornamos el dato
    list->current = list->head;
    return (void*) (list->current->data);
}

void * nextList(List * list) {
  //solo si el current y es siguiente existen
    if(list->current != NULL && list->current->next != NULL){
      //el current apunta al siguiente y retornamos e
      //dato
      list->current = list->current->next;
      return (void*) (list->current->data);
    }
    //si no, no hacemos nada
    else return NULL;
}

void * lastList(List * list) {
  //si el dato del final no existe
  //no hacemos nada
    if(list->tail == NULL) return NULL;
    //si no hacemos que el current apunte al ultimo
    //y retornamos el dato
    list->current = list->tail;
    return (void*) (list->current->data);
}

void * prevList(List * list) {
  //solo si el current y el anterior existen 
    if(list->current != NULL && list->current->prev != NULL){
      //el current apunta al anterior
      //y retornamos el dato
      list->current = list->current->prev;
      return (void*) (list->current->data);
    }
    //si no, no hacemos nada
    return NULL;
}

void pushFront(List * list, const void * data) {
  //creamos un nuevo nodo
    Node * nuevo = createNode(data);
    //siguiente del nuevo nodo es la cabeza
    nuevo->next = list->head;
    //si la cabeza existe
    if(list->head){
      //hacemos que su anterior sea el nuevo nodo
      list->head->prev = nuevo;
    }
    //si la cola no existe
    if(!list->tail){
      //la cola apunta al nuevo nodo
      list->tail = nuevo;
    }
    //el nodo cabeza ahora apunta al nuevo nodo
    list->head = nuevo;
    //el anterior a cabeza apunta a NULL
    nuevo->prev = NULL;
}

void pushBack(List * list, const void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, const void * data) {
  //creamos un nuevo nodo
    Node * nuevo = createNode(data);
    //si no existen nodos en la lista
    if(!list->current){
      //todo apunta al nuevo nodo
      list->head = nuevo;
      list->tail = nuevo;
      list->current = nuevo;
    }
    //si el current es igual a la cola
    else if(list->current == list->tail){
      //el anterior del nuevo apunta al current
      nuevo->prev = list->current;
      //el siguiente del current es el nuevo nodo
      list->current->next = nuevo;
      //la cola y el current van a ser el nuevo nodo
      list->tail = nuevo;
      list->current = nuevo;
    }
    else{
      //el anterior del nuevo apunta al current
      nuevo->prev = list->current;
      //creamos un nodo aux que va a guradar el 
      //siguiente al current
      Node * aux = list->current->next;
      //el siguiente del current va a ser el nuevo nodo
      list->current->next = nuevo;
      //el siguiente del nuevo nodo va a ser el aux
      nuevo->next = aux;
      //el anterior del aux va a ser el nuevo nodo
      aux->prev = nuevo;
      //el current va a ser el nuevo nodo
      list->current = nuevo;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  //almacenamos en dato que hay en el current
    const void * dato = list->current->data;
    //creamos un aux
    Node* aux;
    //si el current esta en el head
    if(list->current == list->head){
      //el aux va a ser el siguiente al current
      aux = list->current->next;
      //el anterior de aux va a apuntar a NULL
      aux->prev = NULL;
      //la head va a apuntar al aux
      list->head = aux;
      //liberamos memoria
      free(list->current);
      //current va a ser el aux
      list->current = aux;
    }
    //si el current esta en la cola
    else if(list->current == list->tail){
      //aux va a ser el anterior al current
      aux = list->current->prev;
      //el siguiente de aux va a apuntar a NULL
      aux->next = NULL;
      //la cola apunta al aux
      list->tail = aux;
      //liberamos memoria
      free(list->current);
      //current va a ser el aux
      list->current =aux;
    }
    //si el current esta en cualquier otro sitio
    else{
      //aux va a ser el anterior del current
      aux = list->current->prev;
      //el siguiente a aux va a ser el siguiente del 
      //current
      aux->next = list->current->next;
      //el aux va a ser el siguiente del current
      aux = list->current->next;
      //el anterior del aux va a ser el siguiente del
      //current
      aux->prev = list->current->prev;
      //liberamos memoria
      free(list->current);
      //current va a ser el aux
      list->current = aux;
    }
    //retornamos el dato
    return (void*) dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}