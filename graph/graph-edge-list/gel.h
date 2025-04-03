/*
 * This code implements graph using edge list.
 */

#ifndef GEL_H
#define GEL_H

typedef int Vertex;

typedef struct Edge {
    Vertex start;
    Vertex end;
} Edge;

typedef struct Graph {
    Edge *edges;
    Vertex *vertices;
} Graph;

#endif /* GEL_H */
