#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int process_rotation(int* current_value, int rotate_pivot, bool is_left_rotate) {
	int original = *current_value;
	if (is_left_rotate) {
		*current_value = (*current_value - rotate_pivot) % 100;
		if (*current_value < 0) {
			*current_value = 100 + *current_value;
		}
		return rotate_pivot >= original && original != 0 ? 
			abs(original - rotate_pivot) / 100 + 1 : 
			abs(original - rotate_pivot) / 100;
	}
	*current_value = (*current_value + rotate_pivot) % 100;
	return (original + rotate_pivot) / 100;
}

int main() {
	clock_t start, end;
	double cpu_time_used;

	start = clock();

	int current_value = 50;

	FILE* fptr;
	fptr = fopen("puzzle_input.txt", "r");

	if (fptr == NULL) {
		printf("Error: file did not open");
		return 1;
	}

	bool is_left_rotate = 0;

	char* rotation_pivot = (char*)malloc(20 * sizeof(char));
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
				int value = process_rotation(&current_value, rotation_pivot_int, is_left_rotate);
				sum += value;
			}

			cur_len = 0;
			rotation_pivot[0] = '\0';

		} else {
			printf("Error: invalid input. can only be L, R or numeric");
			return 1;

		}

		chr = fgetc(fptr);
	}
	
	// do same processing as \n for the last element
	if (cur_len != 0) {
		int rotation_pivot_int = atoi(rotation_pivot);
		int value = process_rotation(&current_value, rotation_pivot_int, is_left_rotate);
		sum += value;
	}

	cur_len = 0;
	rotation_pivot[0] = '\0';

	free(rotation_pivot);

	int result = fclose(fptr);
	if (result != 0) {
		printf("Error: file could not close, res: %d\n", result);
		return 1;
	}

	printf("Total times it passes 0 is %d", sum);

	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Time taken to run this code: %f seconds.\n", cpu_time_used);
	
	fptr = fopen("runtime_info.txt", "w");
	fprintf(fptr, "Time taken to run this code: %.16f seconds.\n", cpu_time_used);
	fclose(fptr);

	return 0;
}

