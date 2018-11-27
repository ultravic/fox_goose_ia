// Victor Picussa - GRR20163068
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <string.h>
#include <graphviz/cgraph.h>
// #include "board.h"
#include "movements.h"

using namespace std;

//===========================evaluateMovement=================================//
// Retorna uma valoração para um determinado tabuleiro.                       //
//============================================================================//
int evaluateMovement(Agraph_t *graph_map, data_t *data)
{
	Agnode_t *node;
	data_t   *data_ch;
	int result;

	node = agfstnode(graph_map);
	data_ch = (data_t*)agbindrec(node, agnameof(node), sizeof(data_t), TRUE);

	result = 1;
	if (!strcmp(data->board, data_ch->board))
		return -1;
	if (data->board[data->move[8]*10+data->move[10]+1] == 'g') {
		if (data->board[data->move[8]*10+data->move[10]+2] == '-')
			result++;
		else
			result--;
	}
	if (data->board[data->move[8]*10+data->move[10]-1] == 'g') {
		if (data->board[data->move[8]*10+data->move[10]-2] == '-')
			result++;
		else
			result--;
	}
	if (data->board[(data->move[8]+1)*10+data->move[10]] == 'g') {
		if (data->board[(data->move[8]+2)*10+data->move[10]] == '-')
			result++;
		else
			result--;
	}
	if (data->board[(data->move[8]-1)*10+data->move[10]] == 'g') {
		if (data->board[(data->move[8]-2)*10+data->move[10]] == '-')
			result++;
		else
			result--;
	}

	return result;
}
//============================================================================//

//===============================minimax======================================//
// Função para executar o algoritmo minimax sobre a árvore de movimentos.     //
//============================================================================//
int minimax(Agraph_t *graph_map, Agnode_t *node_i, int depth_h)
{
	Agedge_t *edge;
	data_t   *data;

	// Faz uma busca em profundidade utilizando recursão
	for (edge = agfstedge(graph_map, node_i); edge; edge = agnxtedge(graph_map, edge, node_i))
		if (agnameof(agtail(edge)) == agnameof(node_i))
			minimax(graph_map, aghead(edge), depth_h+1);

	data = (data_t*)aggetrec(node_i, agnameof(node_i), TRUE);

	if (!data->score) data->score = evaluateMovement(graph_map, data);

	int scores = 0;
	for (edge = agfstedge(graph_map, node_i); edge; edge = agnxtedge(graph_map, edge, node_i)) {
		if (agnameof(agtail(edge)) == agnameof(node_i)) {
			data = (data_t*)aggetrec(aghead(edge), agnameof(aghead(edge)), TRUE);
			if (!depth_h % 2)
				if (data->score > scores) scores = data->score;
			else
				if (data->score < scores) scores = data->score;
		}
	}

	return scores;
}
//============================================================================//

//==============================printGraph====================================//
// Função utilitária para verificar os nodos da criação da árvore.            //
//============================================================================//
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
//============================================================================//

//==============================treeSearch====================================//
// Função para buscar o melhor movimento a ser reproduzido.                   //
//============================================================================//
int treeSearch(char board[MAXSTR], int line_fox, int column_fox, char players[2])
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
	strcpy(data->board, board);
	sprintf(move_test, "%c m %d %d %d %d", players[0], line_fox, column_fox, line_fox, column_fox);
	strcpy(data->move, move_test);
	data->score = 0;
	data->depth = 0;

	treeCreate(graph_map, node_root, players, 1);

	printGraph(graph_map);
	printf("> %d\n", agnnodes(graph_map));
	minimax(graph_map, agfstnode(graph_map), 0);

	return 1;
}
//============================================================================//

//============================================================================//
int main(int argc, char const *argv[])
{
	char move[MAXSTR];
	char players[2];
	int line_fox, column_fox;
	int qtd_moves;

	// board inicial
	char board[MAXSTR] =
	"#########\n"
	"#  ggg  #\n"
	"#  ggg  #\n"
	"#ggggggg#\n"
	"#-------#\n"
	"#---r---#\n"
	"#  ---  #\n"
	"#  ---  #\n"
	"#########\n";

	sprintf(move, "r m 5 4 5 3");

	line_fox = '5' - '0';
	column_fox = '4' - '0';

	players[0] = *argv[1];
	if (*argv[1] == 'r')
		players[1] = 'g';
	else
		players[1] = 'r';

	treeSearch(board, line_fox, column_fox, players);

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
