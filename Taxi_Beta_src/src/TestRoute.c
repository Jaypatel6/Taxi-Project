#include "Route.h"

int main() {
	Map map;
	map = Reader(map);
	/* (0, 0), (10, 0), (10, 0), (20, 0), (20, 0), (35, 14)  */
	int src_arr[6] = {0, 10, 10, 20, 20, 623};
	/* (2, 19), (13, 14), (24, 16), (2, 19), (23, 21), (26, 14) */
	int dest_arr[6] = {800, 601, 696, 800, 905, 614};
	int optimal_length[6] = { 21, 17, 30, 37, 24, 19};
	int i, j, start_x, start_y, end_x, end_y;
	
	
	int *path;
	for(i = 0; i < 6; i++) {
		start_x = src_arr[i] % map.x;
		start_y = src_arr[i] / map.x;
		end_x = dest_arr[i] % map.x;
		end_y = dest_arr[i] / map.x;
		path = CreateRoute(map, src_arr[i], dest_arr[i]);
		for ( j = 0; j < 100; j++) {
			printf( "%d ", path[j]);
			if(path[j] == dest_arr[i]) {
				printf("\nl expect: %d l actual: %d\n", optimal_length[i], j+1);
				printf("x expect: %d x actual: %d\n", end_x, path[j] % map.x);
				printf("y expect: %d y actual: %d\n\n", end_y, path[j] / map.x);
				break;
			}
		}
	}
	
	return 0;
}