#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	// rbtree *t = new_rbtree();
	// node_t *p = rbtree_insert(t, 1024);
	
	// delete_rbtree(t);

	rbtree *t = NULL;
	node_t *temp;

	printf("1: Create a RB-tree.\n");
	printf("2: Insert to the RB-tree.\n");
	printf("3: Find node from the RB-tree.\n");
	printf("4: Erase node from the RB-tree.\n");
	printf("0: Delete the RB-tree and Quit;\n");

	int i, c = 1;

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/4/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			t = new_rbtree();
			printf("One empty RB-tree is successfully created.");
			break;
		case 2:
			printf("Input an integer that you want to add to the RB-tree: ");
			scanf("%d", &i);
			rbtree_insert(t, i);
			printTree(t, t->root);
			break;
		case 3:
			printf("Input an integer that you want to find in the RB-tree: ");
			scanf("%d", &i);
			temp = rbtree_find(t, i);
			printf("The node's color : (%d), key : %d", temp->color, temp->key);
			break;
		case 4:
			printf("Input an integer that you want to erase in the RB-tree: ");
			scanf("%d", &i);
			temp = rbtree_find(t, i);
			rbtree_erase(t, temp);
			printf("Result tree: ");
			printTree(t, t->root);
			break;
		case 0:
			delete_rbtree(t);
			break;
		default:
			printf("Choice unknown:\n");
			break;
		}
	}

	return 0;
}
