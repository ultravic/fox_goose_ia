#ifndef __MOVEMENTS__
#define __MOVEMENTS__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphviz/cgraph.h>

//=============================Constantes=====================================//
// Estrutura para armazenar a cor e peso dos nodos.                           //
//============================================================================//

#define MAXSTR 512
#define MAXINT 16
#define DEPTH  6
#define RADIUS 4

//============================================================================//

//=============================Estruturas=====================================//
// Estrutura para armazenar a cor e peso dos nodos.                           //
//============================================================================//

typedef struct {
	Agrec_t header;
	char move[MAXSTR];
	char board[MAXSTR];
	int score, depth;
} data_t;

//============================================================================//

int treeCreate(Agraph_t *graph_map, Agnode_t *node_i, char players[2], int depth_h);

#endif
