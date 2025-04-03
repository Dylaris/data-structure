/*
 * This code implements graph using adjacency matrix.
 */

#ifndef GAM_H
#define GAM_H

typedef int Vertex;

typedef struct Graph {
    int v_num;
    Vertex **matrix;
} Graph;

#endif /* GAM_H */
