#include "Route.h"

int *CreateRoute(Map map, int src, int dest) {
	int x, y, i, bad, start_x, start_y, end_x, end_y, temp_length, last_pos;
	srand(time(NULL));
	start_x = src % map.x;
	start_y = src / map.x;
	end_x = dest % map.x;
	end_y = dest / map.x;
	int *path = (int *)malloc(sizeof(int)*100);

	last_pos = -1;
	temp_length = 0;
	x = start_x;
	y = start_y;
	
	while((x != end_x || y != end_y)){
		printf("x: %d y: %d\n", x, y);
		if(map.x*y + x == last_pos) {
			printf("\nit breaks here\n");
			break;
		}
		last_pos = map.x*y + x;
		if(x != end_x){
			bad = 0;
			if(x+1 <= end_x && map.arr[map.x*y + x + 1] != 'L') {
				if(y < end_y) {
					for (i = y; i < end_y; i++) {
						if(map.arr[map.x*i + end_x] == 'L') {
							bad = 1;
							break;
						}
					}
				}
				if(y > end_y) {
					for (i = y; i > end_y; i--) {
						if(map.arr[map.x*i + end_x] == 'L') {
							bad = 1;
							break;
						}
					}
				}
				if(!bad) {
					path[temp_length++] = map.x*y + ++x;
				}
			}
			if(x-1 >= end_x && map.arr[map.x*y + x -1] != 'L') {
				if(y < end_y) {
					for (i = y; i < end_y; i++) {
						if(map.arr[map.x*i + end_x] == 'L') {
							bad = 1;
							break;
						}
					}
				}
				if(y > end_y) {
					for (i = y; i > end_y; i--) {
						if(map.arr[map.x*i + end_x] == 'L') {
							bad = 1;
							break;
						}
					}
				}
				if(!bad) {
					path[temp_length++] = map.x*y + --x;
				}
			}
		}
		if(y != end_y){
			bad = 0;
			if(y+1 <= end_y && map.arr[map.x*(y+1) + x] != 'L') {
				if(x < end_x) {
					for (i = x; i < end_x; i++) {
						if(map.arr[map.x*(end_y) + i] == 'L') {
							bad = 1;
							break;
						}
					}
				}
				if(x > end_x) {
					for (i = x; i > end_x; i--) {
						if(map.arr[map.x*(end_y) + i] == 'L') {
							bad = 1;
							break;
						}
					}
				}
				if(!bad) {
					path[temp_length++] = map.x*++y + x;
				}
			}
			if(y-1 >= end_y && map.arr[map.x*(y-1) + x] != 'L') {
				if(x < end_x) {
					for (i = x; i < end_x; i++) {
						if(map.arr[map.x*(end_y) + i] == 'L') {
							bad = 1;
							break;
						}
					}
				}
				if(x > end_x) {
					for (i = x; i > end_x; i--) {
						if(map.arr[map.x*(end_y) + i] == 'L') {
							bad = 1;
							break;
						}
					}
				}
				if(!bad) {
					path[temp_length++] = map.x*--y + x;
				}
			}
		}
		if(map.x*y + x == last_pos) {
			if(x == 5) {
				
			}
		}
	}
	
	return path;
}









