#include<stdio.h>
#include<stdlib.h>


int process_rotation(int current_value, int rotate_pivot, bool is_left_rotate) {
	return is_left_rotate ? (current_value - rotate_pivot) % 100 : (current_value + rotate_pivot) % 100;	
}

int main() {
	int current_value = 50;

	FILE* fptr;
	fptr = fopen("puzzle_input.txt", "r");

	if (fptr == NULL) {
		printf("Error: file did not open");
		return 1;
	}

	bool is_left_rotate = 0;

	char* rotation_pivot = (char*) malloc(20*sizeof(char));
	rotation_pivot[0] = '\0';
	int cur_len = 0;

	int chr = fgetc(fptr);

	int sum = 0;

	while (chr != EOF) {
		if (chr == 'L') {
			is_left_rotate = true;

		} else if (chr == 'R') {
			is_left_rotate = false;

		} else if (chr >= '0' && chr <= '9') {
			rotation_pivot[cur_len] = chr;
			cur_len++;
			rotation_pivot[cur_len] = '\0';

		} else if (chr == '\n') {
			if (cur_len != 0) {
				int rotation_pivot_int = atoi(rotation_pivot);
				current_value = process_rotation(current_value, rotation_pivot_int, is_left_rotate);
				if (current_value == 0) {
					sum ++;	
				}
			}

			cur_len = 0;
			rotation_pivot[0] = '\0';

		} else {
			printf("Error: invalid input. can only be L, R or numeric");
			return 1;

		}

		chr = fgetc(fptr);
	}

	free(rotation_pivot);

	int result = fclose(fptr);
	if (result != 0) {
		printf("Error: file could not close, res: %d\n", result);
		return 1;
	}

	printf("Total times it reaches 0 is %d", sum);

	return 0;

}

