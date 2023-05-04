#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
 int i, j, k, p;
    int fila[10] = {0};  
    int columna[10] = {0};  
    int matrices[10] = {0}; 
    

    for (i = 0; i < 9; i++) {
        memset(fila, 0, sizeof(fila));  
        for (j = 0; j < 9; j++) {
            if (n->sudo[i][j] == 0) continue;  
            if (fila[n->sudo[i][j]]) return 0; 
            fila[n->sudo[i][j]] = 1;  
        }
    }
    
    for (j = 0; j < 9; j++) {
        memset(columna, 0, sizeof(columna));  
        for (i = 0; i < 9; i++) {
            if (n->sudo[i][j] == 0) continue;  
            if (columna[n->sudo[i][j]]) return 0;  
            columna[n->sudo[i][j]] = 1; 
        }
    }
    
    for (k = 0; k < 9; k++) {
        memset(matrices, 0, sizeof(matrices));  
        for (p = 0; p < 9; p++) {
            int i = 3*(k/3) + (p/3);
            int j = 3*(k%3) + (p%3);
            if (n->sudo[i][j] == 0) continue;  
            if (matrices[n->sudo[i][j]]) return 0; 
            matrices[n->sudo[i][j]] = 1;  
        }
    }
    
    return 1;  
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    
    for(int i=0; i<9; i++){
      
    for(int j=0; j<9; j++){
      
        if(n->sudo[i][j] == 0){  
          
            for(int k=1; k<=9; k++){
              
              Node* new_node = copy(n);
              new_node->sudo[i][j] = k;
              if(is_valid(new_node)){
              pushBack(list, new_node);
             }else{
              free(new_node);
            }
              
            }
          
        return list;
          
            }
        }
    }
    
    return list;
}


int is_final(Node* n){
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            if(n->sudo[i][j] == 0){
                return 0;
            }
        }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){

2 / 2

Para implementar la búsqueda en profundidad, necesitamos una función que explore el grafo a partir del nodo inicial y que vaya generando los nodos adyacentes para explorarlos en profundidad. La idea es ir explorando cada rama del grafo hasta encontrar un nodo final o hasta agotar todas las posibilidades.

Aquí está la implementación de la función DFS (Depth-First Search):

c
Copy code
Node* DFS(Node* initial, int* cont){
    Stack* stack = createStack(); // Creamos una pila para guardar los nodos a explorar
    push(stack, initial); // Insertamos el nodo inicial en la pila
    while (!isEmpty(stack)) { // Mientras la pila no esté vacía
        Node* current = pop(stack); // Sacamos el nodo de la cima de la pila
        if (is_final(current)) { // Si es un nodo final, lo retornamos
            return current;
        }
        List* adj_nodes = get_adj_nodes(current); // Obtenemos los nodos adyacentes
        Node* adj_node = first(adj_nodes); // Obtenemos el primer nodo adyacente
        while (adj_node != NULL) { // Mientras haya nodos adyacentes por explorar
            if (is_valid(adj_node)) { // Si el nodo adyacente es válido
                push(stack, adj_node); // Lo insertamos en la pila
            }
            else { // Si el nodo adyacente no es válido, lo eliminamos
                free(adj_node);
            }
            adj_node = next(adj_nodes); // Obtenemos el siguiente nodo adyacente
        }
        destroyList(adj_nodes); // Liberamos la memoria de la lista de nodos adyacentes
        (*cont)++; // Incrementamos el contador de iteraciones
    }
    return NULL; // Si no se encontró un nodo final, retornamos NULL
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/