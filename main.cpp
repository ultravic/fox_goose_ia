// Victor Picussa - GRR20163068

#include "movements.h"

//===========================evaluateMovement=================================//
// Retorna uma valoração para um determinado tabuleiro.                       //
//============================================================================//
int evaluateMovement(Agraph_t *graph_map, data_t *data, char player)
{
	Agnode_t *node;
	data_t   *data_fst;
	int result, gooses_fst, gooses, line, column, fox_l, fox_c;

	node = agfstnode(graph_map);
	data_fst = (data_t*)agbindrec(node, agnameof(node), sizeof(data_t), TRUE);

	result = 1;
	gooses = 0;
	gooses_fst = 0;

	if (player == 'r') {
		for (line = 0; line < 9; line++) {
			for (column = 0; column < 9; column++) {
				if (data_fst->board[line*10+column] == 'g')
					gooses_fst++;
				if (data->board[line*10+column] == 'g')
					gooses++;
				if (data->board[line*10+column] == 'r') {
					fox_l = line;
					fox_c = column;
				}
			}
		}

		if (data->board[fox_l*10+fox_c+1] == 'g') {
			if (data->board[fox_l*10+fox_c+2] == '-')
				result++;
			else
				result--;
		}
		if (data->board[fox_l*10+fox_c-1] == 'g') {
			if (data->board[fox_l*10+fox_c-2] == '-')
				result++;
			else
				result--;
		}
		if (data->board[(fox_l+1)*10+fox_c] == 'g') {
			if (data->board[(fox_l+2)*10+fox_c] == '-')
				result++;
			else
				result--;
		}
		if (data->board[(fox_l-1)*10+fox_c] == 'g') {
			if (data->board[(fox_l-2)*10+fox_c] == '-')
				result++;
			else
				result--;
		}

		if (gooses < gooses_fst) result+=(1+(gooses_fst-gooses));
	} else {
		// Goose evaluation
	}

	return result;
}
//============================================================================//

//===============================minimax======================================//
// Função para executar o algoritmo minimax sobre a árvore de movimentos.     //
//============================================================================//
char* minimax(Agraph_t *graph_map, Agnode_t *node_i, char player, int depth_h)
{
	Agedge_t *edge;
	data_t   *data, *data_i;
	char *move_result = (char*)malloc(sizeof(char)*MAXSTR);

	// Faz uma busca em profundidade utilizando recursão
	for (edge = agfstedge(graph_map, node_i); edge; edge = agnxtedge(graph_map, edge, node_i))
		if (agnameof(agtail(edge)) == agnameof(node_i))
			minimax(graph_map, aghead(edge), player, depth_h+1);

	data = (data_t*)aggetrec(node_i, agnameof(node_i), TRUE);

	if (data->depth == DEPTH-1) {
		data->score = evaluateMovement(graph_map, data, player);
		return data->move;
	}

	// printf("> %d\n", data->depth);

	int scores, set;
	scores = set = 0;

	edge = agfstedge(graph_map, node_i);
	do {
		if (agnameof(agtail(edge)) == agnameof(node_i)) {
			data_i = (data_t*)aggetrec(aghead(edge), agnameof(aghead(edge)), TRUE);
			// printf("%d ", data_i->score);
			scores = data_i->score;
			strcpy(move_result, data_i->move);
			set++;
		}
		edge = agnxtedge(graph_map, edge, node_i);
	} while (!set);
	if (!(data->depth % 2)) {
		for (; edge; edge = agnxtedge(graph_map, edge, node_i)) {
			if (agnameof(agtail(edge)) == agnameof(node_i)) {
				data_i = (data_t*)aggetrec(aghead(edge), agnameof(aghead(edge)), TRUE);
				// printf("%d ", data_i->score);
				if (data_i->score > scores) {
					scores = data_i->score;
					strcpy(move_result, data_i->move);
				}
			}
		}
	} else {
		for (; edge; edge = agnxtedge(graph_map, edge, node_i)) {
			if (agnameof(agtail(edge)) == agnameof(node_i)) {
				data_i = (data_t*)aggetrec(aghead(edge), agnameof(aghead(edge)), TRUE);
				// printf("%d ", data_i->score);
				if (data_i->score < scores) {
					scores = data_i->score;
					strcpy(move_result, data_i->move);
				}
			}
		}
	}

	data->score = scores;

	return move_result;
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
	printf("\n");

	return 1;
}
//============================================================================//

//==============================treeSearch====================================//
// Função para buscar o melhor movimento a ser reproduzido.                   //
//============================================================================//
char* treeSearch(char board[MAXSTR], int line_fox, int column_fox, char players[2])
{
	Agraph_t *graph_map;
	Agnode_t *node_root, *node;
	data_t   *data;
	char move_test[MAXSTR];
	char *name_node = (char*)malloc(sizeof(char)*10);

	sprintf(name_node, "tree_chance");
	graph_map = agopen(name_node, Agundirected, NULL);
	sprintf(name_node, "0%d%d", line_fox, column_fox);
	node_root = agnode(graph_map, name_node, TRUE);

	data = (data_t*)agbindrec(node_root, name_node, sizeof(data_t), TRUE);
	strcpy(data->board, board);
	sprintf(move_test, "%c m %d %d %d %d", players[0], line_fox, column_fox, line_fox, column_fox);
	strcpy(data->move, move_test);
	data->score = 0;
	data->depth = 0;

	treeCreate(graph_map, node_root, players, 0);

	// printGraph(graph_map);
	printf("> %d\n", agnnodes(graph_map));
	return (minimax(graph_map, agfstnode(graph_map), players[0], 0));
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

	sprintf(move, "g m 3 4 4 4");

	line_fox = '5' - '0';
	column_fox = '4' - '0';

	players[0] = *argv[1];
	if (*argv[1] == 'r')
		players[1] = 'g';
	else
		players[1] = 'r';

	printf("> %s\n", treeSearch(board, line_fox, column_fox, players));

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
