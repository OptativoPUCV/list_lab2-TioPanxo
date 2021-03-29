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
    List* lista = (List*) malloc(sizeof(List));
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
    return lista;
}

void * firstList(List * list) {
    if(list->head == NULL) return NULL;
    list->current = list->head;
    return (void*) (list->current->data);
}

void * nextList(List * list) {
    if(list->current && list->current->next != NULL){
      list->current = list->current->next;
      return (void*) (list->current->data);
    }
    return NULL;
}

void * lastList(List * list) {
    if(list->tail == NULL) return NULL;
    list->current = list->tail;
    return (void*) (list->current->data);
}

void * prevList(List * list) {
    if(list->current && list->current->prev != NULL){
      list->current = list->current->prev;
      return (void*) (list->current->data);
    }
    return NULL;
}

void pushFront(List * list, const void * data) {
    Node * n = createNode(data);
    n->next = list->head;
    if(list->head){
      list->head->prev = n;
    }
    if(!list->tail){
      list->tail = n;
    }
    list->head = n;
    n->prev = NULL;
}

void pushBack(List * list, const void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, const void * data) {
    Node * n = createNode(data);
    n->prev = list->current;
    if(!n->prev){
      list->head = n;
    }
    if(list->current->next){
      n->next = list->current->next;
      list->current->next->prev = n;
    }
    else{
      n->next = NULL;
      list->tail = n;
    }
    list->current->next = n;
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
    const void * p = list->current->data;
    Node* aux;
    if(list->current == list->head){
      aux = list->current->next;
      aux->prev = NULL;
      list->head = aux;
      free(list->current);
      list->current = aux;
    }else if(list->current == list->tail){
      aux = list->current->prev;
      aux->next = NULL;
      list->tail = aux;
      free(list->current);
      list->current =aux;
    }
    else{
      aux = list->current->prev;
      aux->next = list->current->next;
      aux = list->current->next;
      aux->prev = list->current->prev;
      free(list->current);
      list->current = aux;
    }
    return (void*) p;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}