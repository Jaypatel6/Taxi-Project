#include "Reader.h"

Map Reader(Map map){
 FILE *stream = fopen("NewIrvine.map", "r");
 size_t len = 0;
 ssize_t read;
 int x = 0, y = 0;
 char *finder = NULL, *line = NULL, *line2 = NULL;
 int i, j, xstart, xend, ystart, yend, sum, str_len;
 map.num_taxis = 0;
 if(stream == NULL){
  exit(EXIT_FAILURE);
 }
 
 while((read = getline(&line, &len, stream)) != -1){
	xstart = xend = ystart = yend = sum = 0;
	finder = strstr(line, "GRID");
	if(finder)
	{
		line2 = strtok(line, " ");
		line2 = strtok(NULL, " ");
		str_len = strlen(line2);
		for(i=0; i<str_len; i++){
			y = y * 10 + ( line2[i] - '0' );
		}
		map.y = y;
		line2 = strtok(NULL, " ");
		str_len = strlen(line2);
		for(i=0; i<str_len-1; i++){
			x = x * 10 + ( line2[i] - '0' );
		}
		map.x = x;
		map.x_names = (char *)malloc(sizeof(char)*map.x*80);
		map.y_names = (char *)malloc(sizeof(char)*map.y*80);
		map.arr = (char *)malloc(sizeof(char)*map.x*map.y);
		for(i = 0; i < map.y; i++){
			for(j = 0; j < map.x; j++){
				map.arr[i*x + j] = 'X';
			}
		}
	}
 
 	finder = strstr(line, "STREET_NAMES_EAST_WEST");
	if(finder){
		line2 = strtok(line, " ");
		line2 = strtok(NULL, ",");
		strcpy(map.y_names, line2);
		strcat(map.y_names, ",");
		int i = map.y;
		while(i > 1) {
			line2 = strtok(NULL, ",\n");
			strcat(map.y_names, line2);
			strcat(map.y_names, ",");
			i--;	
		}
	}

	finder = strstr(line, "STREET_NAMES_NORTH_SOUTH");
	if(finder){
		line2 = strtok(line, " ");
		line2 = strtok(NULL, ",");
		strcpy(map.x_names, line2);
		strcat(map.x_names, ",");
		int i = map.x;
		while(i > 1) {
			line2 = strtok(NULL, ",\n");
			strcat(map.x_names, line2);
			strcat(map.x_names, ",");
			i--;	
		}
	}
	
	finder = strstr(line, "LANDMARK");
	if(finder){
		finder = strstr(line, "(");
		if(finder){
			line2 = strtok(line, " ");
			line2 = strtok(NULL, " ");
			i = 0;
			while(line2[i] != '('){
				i++;
			}
			ystart = line2[++i] - 'A';
			i++;
			while(line2[i] >= '0' && line2[i] <= '9'){
				xstart = xstart * 10 + ( line2[i] - '0' );
				i++;
			}
			yend = line2[++i] - 'A';
			i++;
			while(line2[i] >= '0' && line2[i] <= '9'){
				xend = xend * 10 + ( line2[i] - '0' );
				i++;
			}
			for(j = ystart+1; j < yend; j++){
				for(i = xstart; i < xend-1; i++){
					map.arr[j*map.x + i] = 'L';
				}
			}
		}
	}
	finder = strstr(line, "TAXI_STAND");
	if(finder){
		line2 = strtok(line, " ");
		line2 = strtok(NULL, " ");
		ystart = line2[0] - 'A';
		i = 1;
		while(line2[i] >= '0' && line2[i] <= '9'){
				xstart = xstart * 10 + ( line2[i] - '0' );
				i++;
		}
		i++;
		while(line2[i] >= '0' && line2[i] <= '9'){
				sum = sum * 10 + ( line2[i] - '0' );
				i++;
		}
		map.num_taxis += sum;
		map.arr[ystart*map.x + xstart-1] = sum + 48;
	}
	
  finder = NULL;
	}
 fclose(stream);
 return map;
}
