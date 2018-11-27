
#include "movements.h"

void foxMove(Agraph_t *graph_map, Agnode_t *node_i, char players[2], int depth_h)
{
  Agnode_t *node;
  data_t   *data, *data_i;
  char move_test[MAXSTR];
  char *name_node = (char*)malloc(sizeof(char)*10);

  data_i = (data_t*)agbindrec(node_i, agnameof(node_i), sizeof(data_t), TRUE);

	if (data_i->board[(data_i->move[8]-'0')*10+(data_i->move[10]-'0')+1] == '-') {
		sprintf(name_node, "%s%d%d", agnameof(node_i), data_i->move[8]-'0', (data_i->move[10]-'0')+1);
		node = agnode(graph_map, name_node, TRUE);

		data = (data_t*)agbindrec(node, name_node, sizeof(data_t), TRUE);
		sprintf(move_test, "%c m %d %d %d %d", players[0], data_i->move[8]-'0', data_i->move[10]-'0', data_i->move[8]-'0', (data_i->move[10]-'0')+1);
		strcpy(data->move, move_test);
		data->score = 0;
		data->depth = depth_h;

		strcpy(data->board, data_i->board);

		data->board[(data->move[8]-'0')*10+data->move[10]-'0'] = 'r';
		data->board[(data_i->move[8]-'0')*10+data_i->move[10]-'0'] = '-';

		strcat(name_node, agnameof(node_i));
		agedge(graph_map, node_i, node, name_node, TRUE);

		treeCreate(graph_map, node, players, depth_h+1);
	}
	if (data_i->board[(data_i->move[8]-'0')*10+(data_i->move[10]-'0')-1] == '-') {
		sprintf(name_node, "%s%d%d", agnameof(node_i), data_i->move[8]-'0', (data_i->move[10]-'0')-1);
		node = agnode(graph_map, name_node, TRUE);

		data = (data_t*)agbindrec(node, name_node, sizeof(data_t), TRUE);
		sprintf(move_test, "%c m %d %d %d %d", players[0], data_i->move[8]-'0', data_i->move[10]-'0', data_i->move[8]-'0', (data_i->move[10]-'0')-1);
		strcpy(data->move, move_test);
		data->score = 0;
		data->depth = depth_h;

		strcpy(data->board, data_i->board);

		data->board[(data->move[8]-'0')*10+data->move[10]-'0'] = 'r';
		data->board[(data_i->move[8]-'0')*10+data_i->move[10]-'0'] = '-';

		strcat(name_node, agnameof(node_i));
		agedge(graph_map, node_i, node, name_node, TRUE);

		treeCreate(graph_map, node, players, depth_h+1);
	}
	if (data_i->board[((data_i->move[8]-'0')+1)*10+(data_i->move[10]-'0')] == '-') {
		sprintf(name_node, "%s%d%d", agnameof(node_i), (data_i->move[8]-'0')+1, data_i->move[10]-'0');
		node = agnode(graph_map, name_node, TRUE);

		data = (data_t*)agbindrec(node, name_node, sizeof(data_t), TRUE);
		sprintf(move_test, "%c m %d %d %d %d", players[0], data_i->move[8]-'0', data_i->move[10]-'0', (data_i->move[8]-'0')+1, data_i->move[10]-'0');
		strcpy(data->move, move_test);
		data->score = 0;
		data->depth = depth_h;

		strcpy(data->board, data_i->board);

		data->board[((data->move[8]-'0'))*10+data->move[10]-'0'] = 'r';
		data->board[(data_i->move[8]-'0')*10+data_i->move[10]-'0'] = '-';

		strcat(name_node, agnameof(node_i));
		agedge(graph_map, node_i, node, name_node, TRUE);

		treeCreate(graph_map, node, players, depth_h+1);
	}
	if (data_i->board[((data_i->move[8]-'0')-1)*10+(data_i->move[10]-'0')] == '-') {
		sprintf(name_node, "%s%d%d", agnameof(node_i), (data_i->move[8]-'0')-1, data_i->move[10]-'0');
		node = agnode(graph_map, name_node, TRUE);

		data = (data_t*)agbindrec(node, name_node, sizeof(data_t), TRUE);
		sprintf(move_test, "%c m %d %d %d %d", players[0], data_i->move[8]-'0', data_i->move[10]-'0', (data_i->move[8]-'0')-1, data_i->move[10]-'0');
		strcpy(data->move, move_test);
		data->score = 0;
		data->depth = depth_h;

    strcpy(data->board, data_i->board);

		data->board[((data->move[8]-'0'))*10+data->move[10]-'0'] = 'r';
		data->board[(data_i->move[8]-'0')*10+data_i->move[10]-'0'] = '-';

		strcat(name_node, agnameof(node_i));
		agedge(graph_map, node_i, node, name_node, TRUE);

		treeCreate(graph_map, node, players, depth_h+1);
	}
}

// void gooseMove()
// {
//
// }

//=============================treeCreate=====================================//
// Cria a árvore de jogadas utilizando recursão.                              //
//============================================================================//
int treeCreate(Agraph_t *graph_map, Agnode_t *node_i,	char players[2], int depth_h)
{
	if (depth_h < DEPTH) {
		// if (!((depth_h-1) % 2))
			foxMove(graph_map, node_i, players, depth_h);
		// else
			// gooseMove(graph_map, node_i, board, depth_h);
	}

	return 1;
}
//============================================================================//
