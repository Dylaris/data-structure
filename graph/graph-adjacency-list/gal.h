/*
 * This code implement graph using adjacency list.
 */

 #ifndef GAL_H
 #define GAL_H

typedef struct Vertex {
    int id;
    struct Vertex *next;    /* Link to adjacency vertex (edge) */
} Vertex;


typedef struct Graph {
    Vertex *vertices;
} Graph;

 #endif /* GAL_H */
