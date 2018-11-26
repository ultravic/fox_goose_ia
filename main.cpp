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
#define DEPTH  3
#define RADIUS 4

//============================================================================//

//=============================Estruturas=====================================//
// Estrutura para armazenar a cor e peso dos nodos.                           //
//============================================================================//

typedef struct {
	Agrec_t header;
	char move[MAXSTR];
    int score;
} data_t;

//============================================================================//


int evaluateMovement()
{
    return 1;
}

int childNodes(Agnode_t *actual_node)
{
    return 1;
}

int minimax(Agraph_t *graph_map, Agnode_t *node_i, int depth)
{
    Agedge_t *edge;
    data_t   *data;

    // Faz uma busca em profundidade utilizando recursão
    for (edge = agfstedge(graph_map, node_i); edge; edge = agnxtedge(graph_map, edge, node_i))
        if (agnameof(agtail(edge)) == agnameof(node_i))
            if (minimax(graph_map, aghead(edge), depth+1))
                return 0;

    return 1;
}

int treeSearch(char board[MAXSTR], char line_fox, char column_fox)
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
    strcpy(data->move, move_test);
    data->score = 0;

    if (board[line_fox*10+column_fox+1] == '-') {
        sprintf(name_node, "%d%d", line_fox, column_fox+1);
        node = agnode(graph_map, name_node, TRUE);

        data = (data_t*)agbindrec(node, name_node, sizeof(data_t), TRUE);
        sprintf(move_test, "r m %d %d %d %d", line_fox, column_fox, line_fox, column_fox+1);
        strcpy(data->move, move_test);
        data->score = 0;
        // childNodes(node);
    }
    if (board[line_fox*10+column_fox-1] == '-') {
        sprintf(name_node, "%d%d", line_fox, column_fox-1);
        node = agnode(graph_map, name_node, TRUE);

        data = (data_t*)agbindrec(node, name_node, sizeof(data_t), TRUE);
        sprintf(move_test, "r m %d %d %d %d", line_fox, column_fox, line_fox, column_fox-1);
        strcpy(data->move, move_test);
        data->score = 0;
        // childNodes(node);
    }
    if (board[(line_fox+1)*10+column_fox] == '-') {
        sprintf(name_node, "%d%d", line_fox+1, column_fox);
        node = agnode(graph_map, name_node, TRUE);

        data = (data_t*)agbindrec(node, name_node, sizeof(data_t), TRUE);
        sprintf(move_test, "r m %d %d %d %d", line_fox, column_fox, line_fox+1, column_fox);
        strcpy(data->move, move_test);
        data->score = 0;
        // childNodes(node);
    }
    if (board[(line_fox-1)*10+column_fox-1] == '-') {
        sprintf(name_node, "%d%d", line_fox-1, column_fox+1);
        node = agnode(graph_map, name_node, TRUE);

        data = (data_t*)agbindrec(node, name_node, sizeof(data_t), TRUE);
        sprintf(move_test, "r m %d %d %d %d", line_fox, column_fox, line_fox-1, column_fox);
        strcpy(data->move, move_test);
        data->score = 0;
        // childNodes(node);
    }

    // minimax(graph_map, agfstnode(graph_map), 0);

    return 1;
}

int main(int argc, char const *argv[])
{
    char move[MAXSTR];
    char line_fox, column_fox;
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

    line_fox = '5';
    column_fox = '4';

    treeSearch(board, line_fox, column_fox);

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
