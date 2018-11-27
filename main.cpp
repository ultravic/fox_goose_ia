// Victor Picussa - GRR20163068
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <string.h>
#include <graphviz/cgraph.h>
// #include "board.h"

using namespace std;

//=============================Constantes=====================================//
// Estrutura para armazenar a cor e peso dos nodos.                           //
//============================================================================//

#define MAXSTR 512
#define MAXINT 16
#define DEPTH  4
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


int evaluateMovement(data_t *data)
{
    return 1;
}

int treeCreate(Agraph_t *graph_map, Agnode_t *node_i, char board[MAXSTR],
				char player, int line_fox, int column_fox, int depth_h)
{
	Agnode_t *node;
	data_t   *data;
	char move_test[MAXSTR];
	char *name_node = (char*)malloc(sizeof(char)*10);

	if (depth_h < DEPTH) {
		if (board[line_fox*10+column_fox+1] == '-' || board[line_fox*10+column_fox+1] == 'r') {
	        sprintf(name_node, "%s%d%d", agnameof(node_i), line_fox, column_fox+1);
	        node = agnode(graph_map, name_node, TRUE);

	        data = (data_t*)agbindrec(node, name_node, sizeof(data_t), TRUE);
	        sprintf(move_test, "%c m %d %d %d %d", player, line_fox, column_fox, line_fox, column_fox+1);
	        strcpy(data->move, move_test);
	        data->score = 0;
			data->depth = depth_h;

			strcpy(data->board, board);

			data->board[line_fox*10+column_fox+1] = 'r';
			data->board[line_fox*10+column_fox] = '-';

			strcat(name_node, agnameof(node_i));
			agedge(graph_map, node_i, node, name_node, TRUE);

	        treeCreate(graph_map, node, data->board, player, line_fox, column_fox+1, depth_h+1);
	    }
	    if (board[line_fox*10+column_fox-1] == '-' || board[line_fox*10+column_fox-1] == 'r') {
	        sprintf(name_node, "%s%d%d", agnameof(node_i), line_fox, column_fox-1);
	        node = agnode(graph_map, name_node, TRUE);

	        data = (data_t*)agbindrec(node, name_node, sizeof(data_t), TRUE);
	        sprintf(move_test, "%c m %d %d %d %d", player, line_fox, column_fox, line_fox, column_fox-1);
	        strcpy(data->move, move_test);
	        data->score = 0;
			data->depth = depth_h;

			strcpy(data->board, board);

			data->board[line_fox*10+column_fox-1] = 'r';
			data->board[line_fox*10+column_fox] = '-';

			strcat(name_node, agnameof(node_i));
			agedge(graph_map, node_i, node, name_node, TRUE);

			treeCreate(graph_map, node, data->board, player, line_fox, column_fox-1, depth_h+1);
	    }
	    if (board[(line_fox+1)*10+column_fox] == '-' || board[(line_fox+1)*10+column_fox] == 'r') {
	        sprintf(name_node, "%s%d%d", agnameof(node_i), line_fox+1, column_fox);
	        node = agnode(graph_map, name_node, TRUE);

	        data = (data_t*)agbindrec(node, name_node, sizeof(data_t), TRUE);
	        sprintf(move_test, "%c m %d %d %d %d", player, line_fox, column_fox, line_fox+1, column_fox);
	        strcpy(data->move, move_test);
	        data->score = 0;
			data->depth = depth_h;

			strcpy(data->board, board);

			data->board[(line_fox+1)*10+column_fox] = 'r';
			data->board[line_fox*10+column_fox] = '-';

			strcat(name_node, agnameof(node_i));
			agedge(graph_map, node_i, node, name_node, TRUE);

			treeCreate(graph_map, node, data->board, player, line_fox+1, column_fox, depth_h+1);
	    }
	    if (board[(line_fox-1)*10+column_fox] == '-' || board[(line_fox-1)*10+column_fox] == 'r') {
	        sprintf(name_node, "%s%d%d", agnameof(node_i), line_fox-1, column_fox);
	        node = agnode(graph_map, name_node, TRUE);

	        data = (data_t*)agbindrec(node, name_node, sizeof(data_t), TRUE);
	        sprintf(move_test, "%c m %d %d %d %d", player, line_fox, column_fox, line_fox-1, column_fox);
	        strcpy(data->move, move_test);
	        data->score = 0;
			data->depth = depth_h;

			strcpy(data->board, board);

			data->board[(line_fox-1)*10+column_fox] = 'r';
			data->board[line_fox*10+column_fox] = '-';

			strcat(name_node, agnameof(node_i));
			agedge(graph_map, node_i, node, name_node, TRUE);

			treeCreate(graph_map, node, data->board, player, line_fox-1, column_fox, depth_h+1);
	    }
	}

    return 1;
}

int minimax(Agraph_t *graph_map, Agnode_t *node_i, int depth_h)
{
    Agedge_t *edge;
    data_t   *data;

    // Faz uma busca em profundidade utilizando recursão
    for (edge = agfstedge(graph_map, node_i); edge; edge = agnxtedge(graph_map, edge, node_i))
        if (agnameof(agtail(edge)) == agnameof(node_i))
            minimax(graph_map, aghead(edge), depth_h+1);

	data = (data_t*)aggetrec(node_i, agnameof(node_i), TRUE);

	if (!data->score) evaluateMovement(data);

	int scores = 0;
	for (edge = agfstedge(graph_map, node_i); edge; edge = agnxtedge(graph_map, edge, node_i)) {
		if (agnameof(agtail(edge)) == agnameof(node_i)) {
			data = (data_t*)aggetrec(aghead(edge), agnameof(aghead(edge)), TRUE);
			if (!depth_h % 2)
				if (data->score > scores)
					scores = data->score;
			else
				if (data->score < scores)
					scores = data->score;
		}
	}

    return 1;
}

int printGraph(Agraph_t *graph_map)
{
	Agnode_t *node_it;
	data_t   *data;

	for (node_it = agfstnode(graph_map); node_it; node_it = agnxtnode(graph_map, node_it)) {
		data = (data_t*)aggetrec(node_it, agnameof(node_it), TRUE);
		//printf("> %s - %d - %s\n", data->move, data->depth, agnameof(node_it));
		printf("%s\n", data->board);
	}

	return 1;
}

int treeSearch(char board[MAXSTR], int line_fox, int column_fox, char player)
{
    Agraph_t *graph_map;
    Agnode_t *node_root, *node;
    data_t   *data;
    char move_test[MAXSTR];
    char *name_node = (char*)malloc(sizeof(char)*10);

    sprintf(name_node, "tree_chance");
    graph_map = agopen(name_node, Agundirected, NULL);
    sprintf(name_node, "%d%d", line_fox, column_fox);
    node_root = agnode(graph_map, name_node, TRUE);

    data = (data_t*)agbindrec(node_root, name_node, sizeof(data_t), TRUE);
    data->score = 0;
	data->depth = 0;

    treeCreate(graph_map, node_root, board, player, line_fox, column_fox, 1);

	//printGraph(graph_map);
	printf("> %d\n", agnnodes(graph_map));
    // minimax(graph_map, agfstnode(graph_map), 0);

    return 1;
}

int main(int argc, char const *argv[])
{
    char move[MAXSTR];
    char player;
	int line_fox, column_fox;
    int qtd_moves;

    // board inicial
    char board[MAXSTR] = "#########\n"
                         "#  ggg  #\n"
                         "#  ggg  #\n"
                         "#ggggggg#\n"
                         "#-------#\n"
                         "#---r---#\n"
                         "#  ---  #\n"
                         "#  ---  #\n"
                         "#########\n";

    sprintf(move, "r m 5 4 5 3");

	player = 'r';
    line_fox = '5' - '0';
    column_fox = '4' - '0';

    treeSearch(board, line_fox, column_fox, player);

    // while(true) {
    //     // Recebe movimento e atualiza tabuleiro
    //     // tabuleiro_recebe(move);
    //     if (move[0] == 'r') {
    //         // Raposa
    //         if (move[2] == 'm') {
    //             // Mover
    //             if (board[((move[4] - '0')*10)+(move[6] - '0')] = 'r') {
    //                 board[((move[4] - '0')*10)+(move[6] - '0')] = '-';
    //                 board[((move[8] - '0')*10)+(move[10] - '0')] = 'r';
    //             }
    //         } else {
    //             // Salto
    //         }
    //     } else {
    //         // Ganso
    //         if (move[2] == 'm') {
    //             // Mover
    //             if (board[((move[4] - '0')*10)+(move[6] - '0')] == 'g') {
    //                 board[((move[4] - '0')*10)+(move[6] - '0')] = '-';
    //                 board[((move[8] - '0')*10)+(move[10] - '0')] = 'g';
    //             }
    //         } else {
    //             // Salto
    //         }
    //     }
    //     treeSearch(board, line_fox, column_fox);
    // }

    // // Conecta com controlador
    // tabuleiro_conecta(argc, argv);
    //
    // // Recebe o movimento
    // tabuleiro_recebe(move);
    //
    // // Envia movimento
    // tabuleiro_envia(move);

    return 0;
}
