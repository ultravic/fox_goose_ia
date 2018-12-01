
#include "movements.h"

Agnode_t* createNodeEdge(Agraph_t *graph_map, Agnode_t *node_i, data_t *data_i, char player,
                            char *move_test, char *name_node, int line, int column, int depth_h)
{
    Agnode_t *node;
    data_t   *data;

    node = agnode(graph_map, name_node, TRUE);

    data = (data_t*)agbindrec(node, name_node, sizeof(data_t), TRUE);
    strcpy(data->move, move_test);
    data->score = 0;
    data->depth = depth_h;

    strcpy(data->board, data_i->board);

    if (data->move[2] == 'm') {
        data->board[(data->move[8]-'0')*10+data->move[10]-'0'] = player;
        data->board[(line)*10+column] = '-';
    } else {
        data->board[(data->move[8]-'0')*10+data->move[10]-'0'] = player;
        data->board[(line)*10+column] = '-';
        if ((line - (data->move[8]-'0')) < 0) data->board[(line+1)*10+column] = '-';
        else if ((line - (data->move[8]-'0')) > 0) data->board[(line-1)*10+column] = '-';
        else if ((column - (data->move[10]-'0')) < 0) data->board[line*10+column+1] = '-';
        else if ((column - (data->move[10]-'0')) > 0) data->board[line*10+column-1] = '-';
    }

    strcat(name_node, agnameof(node_i));
    agedge(graph_map, node_i, node, name_node, TRUE);

    return node;
}

void childCreate(Agraph_t *graph_map, Agnode_t *node_i, char players[2], int depth_h)
{
    Agnode_t *node;
    data_t   *data, *data_i;
    char move_test[MAXSTR], player;
    int pos, line, column;
    char *name_node = (char*)malloc(sizeof(char)*50);

    data_i = (data_t*)agbindrec(node_i, agnameof(node_i), sizeof(data_t), TRUE);

    pos = 0;
    for (line = 0; line < 9; line++) {
        for (column = 0; column < 9; column++) {
            if (data_i->board[line*10+column] == 'r') {
                pos = 1;
                break;
            }
        }
        if (pos) break;
    }

    if (((depth_h % 2) && players[0] == 'r') || (!(depth_h % 2) && players[1] == 'r')) {
        if (data_i->board[(line)*10+(column)+1] == '-') {
            sprintf(name_node, "%d%s%d%d", depth_h, agnameof(node_i), line, (column)+1);
            sprintf(move_test, "%c m %d %d %d %d", 'r', line, column, line, (column)+1);
            node = createNodeEdge(graph_map, node_i, data_i, 'r', move_test, name_node, line, column, depth_h);
            treeCreate(graph_map, node, players, depth_h);
        }
        if (data_i->board[(line)*10+(column)-1] == '-') {
            sprintf(name_node, "%d%s%d%d", depth_h, agnameof(node_i), line, (column)-1);
            sprintf(move_test, "%c m %d %d %d %d", 'r', line, column, line, (column)-1);
            node = createNodeEdge(graph_map, node_i, data_i, 'r', move_test, name_node, line, column, depth_h);
            treeCreate(graph_map, node, players, depth_h);
        }
        if (data_i->board[((line)+1)*10+(column)] == '-') {
            sprintf(name_node, "%d%s%d%d", depth_h, agnameof(node_i), (line)+1, column);
            sprintf(move_test, "%c m %d %d %d %d", 'r', line, column, (line)+1, column);
            node = createNodeEdge(graph_map, node_i, data_i, 'r', move_test, name_node, line, column, depth_h);
            treeCreate(graph_map, node, players, depth_h);
        }
        if (data_i->board[((line)-1)*10+(column)] == '-') {
            sprintf(name_node, "%d%s%d%d", depth_h, agnameof(node_i), (line)-1, column);
            sprintf(move_test, "%c m %d %d %d %d", 'r', line, column, (line)-1, column);
            node = createNodeEdge(graph_map, node_i, data_i, 'r', move_test, name_node, line, column, depth_h);
            treeCreate(graph_map, node, players, depth_h);
        }
        if (data_i->board[(line)*10+(column)+1] == 'g') {
			if (data_i->board[(line)*10+(column)+2] == '-') {
                sprintf(name_node, "%d%s%d%d", depth_h, agnameof(node_i), line, (column)+2);
                sprintf(move_test, "%c s %d %d %d %d", 'r', line, column, line, (column)+2);
                node = createNodeEdge(graph_map, node_i, data_i, 'r', move_test, name_node, line, column, depth_h);
                treeCreate(graph_map, node, players, depth_h);
            }
		}
		if (data_i->board[(line)*10+(column)-1] == 'g') {
			if (data_i->board[(line)*10+(column)-2] == '-') {
                sprintf(name_node, "%d%s%d%d", depth_h, agnameof(node_i), line, (column)-2);
                sprintf(move_test, "%c s %d %d %d %d", 'r', line, column, line, (column)-2);
                node = createNodeEdge(graph_map, node_i, data_i, 'r', move_test, name_node, line, column, depth_h);
                treeCreate(graph_map, node, players, depth_h);
            }
		}
		if (data_i->board[((line)+1)*10+(column)] == 'g') {
			if (data_i->board[((line)+2)*10+(column)] == '-') {
                sprintf(name_node, "%d%s%d%d", depth_h, agnameof(node_i), (line)+2, column);
                sprintf(move_test, "%c s %d %d %d %d", 'r', line, column, (line)+2, column);
                node = createNodeEdge(graph_map, node_i, data_i, 'r', move_test, name_node, line, column, depth_h);
                treeCreate(graph_map, node, players, depth_h);
            }
		}
		if (data_i->board[((line)-1)*10+(column)] == 'g') {
			if (data_i->board[((line)-2)*10+(column)] == '-') {
                sprintf(name_node, "%d%s%d%d", depth_h, agnameof(node_i), (line)-2, column);
                sprintf(move_test, "%c s %d %d %d %d", 'r', line, column, (line)-2, column);
                node = createNodeEdge(graph_map, node_i, data_i, 'r', move_test, name_node, line, column, depth_h);
                treeCreate(graph_map, node, players, depth_h);
            }
		}
    } else {
        for (line = 0; line < 9; line++) {
            for (column = 0; column < 9; column++) {
                if (data_i->board[line*10+column] == 'g') {
                    if (data_i->board[line*10+column+1] == '-') {
                        sprintf(name_node, "%d%s%d%d", depth_h, agnameof(node_i), line, (column)+1);
                        sprintf(move_test, "%c m %d %d %d %d", 'g', line, column, line, column+1);
                        node = createNodeEdge(graph_map, node_i, data_i, 'g', move_test, name_node, line, column, depth_h);
                        treeCreate(graph_map, node, players, depth_h);
                    }
                    if (data_i->board[line*10+column-1] == '-') {
                        sprintf(name_node, "%d%s%d%d", depth_h, agnameof(node_i), line, (column)-1);
                        sprintf(move_test, "%c m %d %d %d %d", 'g', line, column, line, (column)-1);
                        node = createNodeEdge(graph_map, node_i, data_i, 'g', move_test, name_node, line, column, depth_h);
                        treeCreate(graph_map, node, players, depth_h);
                    }
                    if (data_i->board[(line+1)*10+column] == '-') {
                        sprintf(name_node, "%d%s%d%d", depth_h, agnameof(node_i), (line)+1, column);
                        sprintf(move_test, "%c m %d %d %d %d", 'g', line, column, (line)+1, column);
                        node = createNodeEdge(graph_map, node_i, data_i, 'g', move_test, name_node, line, column, depth_h);
                        treeCreate(graph_map, node, players, depth_h);
                    }
                    if (data_i->board[(line-1)*10+column] == '-') {
                        sprintf(name_node, "%d%s%d%d", depth_h, agnameof(node_i), (line)-1, column);
                        sprintf(move_test, "%c m %d %d %d %d", 'g', line, column, (line)-1, column);
                        node = createNodeEdge(graph_map, node_i, data_i, 'g', move_test, name_node, line, column, depth_h);
                        treeCreate(graph_map, node, players, depth_h);
                    }
                }
            }
        }
    }
}

//=============================treeCreate=====================================//
// Cria a árvore de jogadas utilizando recursão.                              //
//============================================================================//
int treeCreate(Agraph_t *graph_map, Agnode_t *node_i, char players[2], int depth_h)
{
    if (depth_h < DEPTH-1)
        childCreate(graph_map, node_i, players, depth_h+1);

    return 1;
}
//============================================================================//
