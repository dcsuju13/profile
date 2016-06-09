#ifndef _filedst
#define _filedst
#include <QtWidgets/QMainWindow>
extern QString g_filedst;
extern int offset;

typedef struct coor{
	float x;
	float y;
	float z;
}coor;//表示每个点的坐标

struct node;
struct edge;

struct node{
	float x, y, z;
	struct edge *edgef;
	int id;
	float n[3];
	float laplace[3];
};

struct edge{
	struct node *start;
	struct node *end;
	struct edge *next;
};

struct arraylist
{
	struct node *end;
	float l;
	struct arraylist *next;
};

#endif