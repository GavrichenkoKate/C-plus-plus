#include <iostream>
#include <cstdlib>
#include <ctime>

void enter_params(int& program_num) {
	std::cout << "Enter the number of pragram: " << std::endl;
	std::cin >> program_num;

}

void set_dislocations_1(int num0, int size, int square[], int disloc[], int neighbors_name[]) {
	int coord_i = 0;

	for (int i = 0; i < num0; i++) {

		do {
			coord_i = rand() % (size);
		} while (square[coord_i] != 0);

		disloc[i] = coord_i;
		square[disloc[i]] = neighbors_name[0];
	}
}

void set_dislocations_2(int num0, int size, int square[], int disloc[], int neighbors_name[]) {
	int coord_i = 0;
	int coord_x_i = 0;
	int coord_y_i = 0;

	for (int i = 0; i < num0; i++) {

		do {
			coord_i = rand() % (size * size);
			coord_x_i = coord_i % size;
			coord_y_i = coord_i / size;
		} while (square[coord_y_i * size + coord_x_i] != 0);

		disloc[i] = coord_y_i * size + coord_x_i;
		square[disloc[i]] = neighbors_name[0];
	}
}

void disloc_deactiv(int& num_moved, int disloc_moved[], int square[], int neighbors_name[], int i) {
	int tmp_disloc = 0;

	if (num_moved > 1) {
		tmp_disloc = disloc_moved[num_moved - 1];
		disloc_moved[num_moved - 1] = disloc_moved[i];
		disloc_moved[i] = tmp_disloc;

		if (square[disloc_moved[num_moved - 1]] == neighbors_name[0]){
			square[disloc_moved[num_moved - 1]] = neighbors_name[1];
		}
		if (square[disloc_moved[num_moved - 1]] == neighbors_name[2]) {
			square[disloc_moved[num_moved - 1]] = neighbors_name[3];
		}
		if (square[disloc_moved[num_moved - 1]] == neighbors_name[4]) {
			square[disloc_moved[num_moved - 1]] = neighbors_name[5];
		}

		num_moved--;
	}
	else {
		if (num_moved = 1) {
			if (square[disloc_moved[num_moved - 1]] == neighbors_name[0]) {
				square[disloc_moved[num_moved - 1]] = neighbors_name[1];
			}
			if (square[disloc_moved[num_moved - 1]] == neighbors_name[2]) {
				square[disloc_moved[num_moved - 1]] = neighbors_name[3];
			}
			if (square[disloc_moved[num_moved - 1]] == neighbors_name[4]) {
				square[disloc_moved[num_moved - 1]] = neighbors_name[5];
			}
			num_moved--;
		}
	}
}

bool check_clear(int direction_point, int neighbors_name[]) {
	bool clear = true;
	for (int k = 0; k < 6; k++) {
		if (direction_point == neighbors_name[k]) {
			clear = false;
			break;
		}
	}
	return clear;
}

void change_disloc(int direction_point, int prev_point, int &moved_point, int neighbors_name[], int neighbors_name_sec[], int square[]){

	if (square[prev_point] == neighbors_name[0]) {
		if (square[direction_point] == 0) {
			square[prev_point] = 0;
			moved_point = direction_point;
			square[moved_point] = neighbors_name[0];
		}
		if (square[direction_point] == neighbors_name_sec[0]) {
			square[prev_point] = 0;
			moved_point = direction_point;
			square[moved_point] = neighbors_name[2];
		}
		if (square[direction_point] == neighbors_name_sec[1]) {
			square[prev_point] = 0;
			moved_point = direction_point;
			square[moved_point] = neighbors_name[4];
		}
	}

	if (square[prev_point] == neighbors_name[2]) {
		if (square[direction_point] == 0) {
			square[prev_point] = neighbors_name_sec[0];
			moved_point = direction_point;
			square[moved_point] = neighbors_name[0];
		}
		if (square[direction_point] == neighbors_name_sec[0]) {
			square[prev_point] = neighbors_name_sec[0];
			moved_point = direction_point;
			square[moved_point] = neighbors_name[2];
		}
		if (square[direction_point] == neighbors_name_sec[1]) {
			square[prev_point] = neighbors_name_sec[0];
			moved_point = direction_point;
			square[moved_point] = neighbors_name[4];
		}
	}

	if (square[prev_point] == neighbors_name[4]) {
		if (square[direction_point] == 0) {
			square[prev_point] = neighbors_name_sec[1];
			moved_point = direction_point;
			square[moved_point] = neighbors_name[0];
		}
		if (square[direction_point] == neighbors_name_sec[0]) {
			square[prev_point] = neighbors_name_sec[1];
			moved_point = direction_point;
			square[moved_point] = neighbors_name[2];
		}
		if (square[direction_point] == neighbors_name_sec[1]) {
			square[prev_point] = neighbors_name_sec[1];
			moved_point = direction_point;
			square[moved_point] = neighbors_name[4];
		}
	}
}

void move_dislocations(int program_num, int& num, int num0, int size, int square[], int disloc[], int disloc_moved[], int neighbors_name[], int neighbors_name_sec[], int direction[]) {

	int bord_vert_i;
	int bord_hor_i;
	int size_all = 0;

	int neighbors_i[4] = {};
	int num_moved;

	if (program_num == 1 || program_num == 3) {
		size_all = size;
	}
	if (program_num == 2 || program_num == 4) {
		size_all = size * size;
	}

	num = 0;


	for (int i = 0; i < size_all; i++) {
		if (square[i] == neighbors_name[0] || square[i] == neighbors_name[2] || square[i] == neighbors_name[4]) {
			num++;
			disloc[num - 1] = i;
			disloc_moved[num - 1] = i;
		}
	}

	num_moved = num;

	for (int i = 0; i < num; i++) {
		direction[i] = rand() % 4;

		if ((disloc[i] - size >= 0) && (direction[i] == 0) && (check_clear(square[disloc[i] - size], neighbors_name))) {
			change_disloc((disloc[i] - size), disloc[i], disloc_moved[i], neighbors_name, neighbors_name_sec, square);
		}
		if (((disloc[i] + 1) % size != size - 1) && direction[i] == 1 && check_clear(square[disloc[i] + 1], neighbors_name)) {
			change_disloc((disloc[i] + 1), disloc[i], disloc_moved[i], neighbors_name, neighbors_name_sec, square);
		}
		if ((disloc[i] + size < size_all) && direction[i] == 2 && check_clear(square[disloc[i] + size], neighbors_name)) {
			change_disloc((disloc[i] + size), disloc[i], disloc_moved[i], neighbors_name, neighbors_name_sec, square);
		}
		if (((disloc[i] - 1) % size != 0) && direction[i] == 3 && check_clear(square[disloc[i] - 1], neighbors_name)) {
			change_disloc((disloc[i] - 1), disloc[i], disloc_moved[i], neighbors_name, neighbors_name_sec, square);
		}
	}

	for (int i = 0; i < num; i++) {
		bord_vert_i = disloc[i] % size;
		bord_hor_i = disloc[i] / size;

		if ((bord_vert_i == 0 && direction[i] == 3) || (bord_vert_i == size - 1 && direction[i] == 1) || (bord_hor_i == 0 && direction[i] == 0) || (bord_hor_i == size - 1 && direction[i] == 2)) {
			disloc_moved[i] = disloc[i];
			disloc_deactiv(num_moved, disloc_moved, square, neighbors_name, i);
		}
	}

	num = num_moved;

	for (int i = 0; i < num; i++) {
		bord_vert_i = disloc_moved[i] % size;
		int neighbors_i[4] = { disloc_moved[i] - 1, disloc_moved[i] - size, disloc_moved[i] + size, disloc_moved[i] + 1 };

		if (bord_vert_i == size - 1) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 6; k++) {
					if (square[neighbors_i[j]] == neighbors_name[k]) {
						disloc_deactiv(num_moved, disloc_moved, square, neighbors_name, i);
						break;
					}
				}
			}
		}
		else {
			if (bord_vert_i == 0) {
				for (int j = 1; j < 4; j++) {
					for (int k = 0; k < 6; k++) {
						if (square[neighbors_i[j]] == neighbors_name[k]) {
							disloc_deactiv(num_moved, disloc_moved, square, neighbors_name, i);
							break;
						}
					}
				}
			}
			else {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 6; k++) {
						if (square[neighbors_i[j]] == neighbors_name[k]) {
							disloc_deactiv(num_moved, disloc_moved, square, neighbors_name, i);
							break;
						}
					}
				}
			}
		}
	}
}

void null_array(int array[], int lenth) {
	for (int i = 0; i < lenth; i++) {
		array[i] = 0;
	}
}

void program_1(int program_num, int& num1, int& num2, int &num_all, int square[], int disloc1[], int disloc2[], int disloc_moved1[], int disloc_moved2[], int neighbors_name1[], int neighbors_name2[], int direction1[], int direction2[]) {
	double array_1dis[20] = { 0 };
	int size = 0;
	int num01 = 1;
	int num02 = 1;
	int counter = 0;

	

	for (int i = 0; i < 20; i++) {
		int counter_all = 0;
		size = i + 2;


		for (int k = 1; k <= 100; k++) {
			counter = 0;
			num1 = num01;
			num2 = num02;
			num_all = num1 + num2;
			set_dislocations_1(num01, size, square, disloc1, neighbors_name1);
			set_dislocations_1(num02, size, square, disloc2, neighbors_name2);

			while (num_all > 0) {
				move_dislocations(program_num, num1, num01, size, square, disloc1, disloc_moved1, neighbors_name1, neighbors_name2, direction1);
				move_dislocations(program_num, num2, num02, size, square, disloc2, disloc_moved2, neighbors_name2, neighbors_name1, direction2);
				num_all = num1 + num2;
				//std::cout << "NUM " << num_all << std::endl;
				counter++;

			}
			counter_all += counter;
			null_array(disloc1, 100);
			null_array(disloc_moved1, 100);
			null_array(disloc2, 100);
			null_array(disloc_moved2, 100);
			null_array(square, 100);
			//std::cout << "COUNTER " << counter_all << std::endl;

		}
		array_1dis[i] = double(counter_all * 0.01);
	}

	for (int i = 0; i < 20; i++) {
		std::cout << array_1dis[i] << "," << std::endl;
	}
}


void program_2(int program_num, int& num1, int& num2, int& num_all, int square[], int disloc1[], int disloc2[], int disloc_moved1[], int disloc_moved2[], int neighbors_name1[], int neighbors_name2[], int direction1[], int direction2[]) {

	double array_1dis[10] = { 0 };
	int size = 0;
	int num01 = 1;
	int num02 = 1;
	int counter = 0;

	for (int i = 0; i < 10; i++) {
		int counter_all = 0;
		size = i + 2;

		for (int k = 1; k <= 1000; k++) {
			counter = 0;
			num1 = num01;
			num2 = num02;
			num_all = num1 + num2;
			set_dislocations_2(num01, size, square, disloc1, neighbors_name1);
			set_dislocations_2(num02, size, square, disloc2, neighbors_name2);
			while (num_all > 0) {
				move_dislocations(program_num, num1, num01, size, square, disloc1, disloc_moved1, neighbors_name1, neighbors_name2, direction1);
				move_dislocations(program_num, num2, num02, size, square, disloc2, disloc_moved2, neighbors_name2, neighbors_name1, direction2);
				num_all = num1 + num2;
				counter++;
			}
			counter_all += counter;
			null_array(disloc1, 100);
			null_array(disloc_moved1, 100);
			null_array(disloc2, 100);
			null_array(disloc_moved2, 100);
			null_array(square, 100);

		}
		array_1dis[i] = double(counter_all * 0.001);
	}

	for (int i = 0; i < 10; i++) {
		std::cout << array_1dis[i] << "," << std::endl;
	}
}

void program_3(int program_num, int& num1, int& num2, int& num_all, int square[], int disloc1[], int disloc2[], int disloc_moved1[], int disloc_moved2[], int neighbors_name1[], int neighbors_name2[], int direction1[], int direction2[]) {

	double array_1size[20] = { 0 };
	int size = 100;
	int num01 = 0;
	int num02 = 0;
	int counter = 0;


	for (int i = 0; i < 20; i++) {
		int counter_all = 0;
		num01 = i + 1;
		num02 = i + 1;

		for (int k = 1; k <= 1000; k++) {
			counter = 0;
			num1 = num01;
			num2 = num02;
			num_all = num1 + num2;
			set_dislocations_1(num01, size, square, disloc1, neighbors_name1);
			set_dislocations_1(num02, size, square, disloc2, neighbors_name2);
			while (num_all > 0) {
				move_dislocations(program_num, num1, num01, size, square, disloc1, disloc_moved1, neighbors_name1, neighbors_name2, direction1);
				move_dislocations(program_num, num2, num02, size, square, disloc2, disloc_moved2, neighbors_name2, neighbors_name1, direction2);
				num_all = num1 + num2;
				counter++;
			}
			counter_all += counter;
			null_array(disloc1, 100);
			null_array(disloc_moved1, 100);
			null_array(disloc2, 100);
			null_array(disloc_moved2, 100);
			null_array(square, 100);

		}
		array_1size[i] = double(counter_all * 0.001);
	}

	for (int i = 0; i < 20; i++) {
		std::cout << array_1size[i] << "," << std::endl;
	}
}

void program_4(int program_num, int& num1, int& num2, int& num_all, int square[], int disloc1[], int disloc2[], int disloc_moved1[], int disloc_moved2[], int neighbors_name1[], int neighbors_name2[], int direction1[], int direction2[]) {

	double array_1size[40] = { 0 };
	int size = 10;
	int num01 = 0;
	int num02 = 0;
	int counter = 0;


	for (int i = 0; i < 40; i++) {
		int counter_all = 0;
		num01 = i + 1;
		num02 = i + 1;

		for (int k = 1; k <= 1000; k++) {
			counter = 0;
			num1 = num01;
			num2 = num02;
			num_all = num1 + num2;
			set_dislocations_2(num01, size, square, disloc1, neighbors_name1);
			set_dislocations_2(num02, size, square, disloc2, neighbors_name2);
			while (num_all > 0) {
				move_dislocations(program_num, num1, num01, size, square, disloc1, disloc_moved1, neighbors_name1, neighbors_name2, direction1);
				move_dislocations(program_num, num2, num02, size, square, disloc2, disloc_moved2, neighbors_name2, neighbors_name1, direction2);
				num_all = num1 + num2;
				counter++;
			}
			counter_all += counter;
			null_array(disloc1, 100);
			null_array(disloc_moved1, 100);
			null_array(disloc2, 100);
			null_array(disloc_moved2, 100);
			null_array(square, 100);

		}
		array_1size[i] = double(counter_all * 0.001);
	}

	for (int i = 0; i < 40; i++) {
		std::cout << array_1size[i] << "," << std::endl;
	}
}

int main() {
	const int big_size = 100;
	const int neighbors_quant = 6;
	int program_num = 0;
	int num1 = 0;
	int num2 = 0;
	int num_all = num1 + num2;
	int square[big_size] = { 0 };
	int disloc1[big_size] = { 0 };
	int disloc_moved1[big_size] = { 0 };
	int disloc2[big_size] = { 0 };
	int disloc_moved2[big_size] = { 0 };
	int direction1[big_size] = { 0 };
	int direction2[big_size] = { 0 };
	int neighbors_name1[neighbors_quant] = { 1, 3, 5, 7, 6, 8 };
	int neighbors_name2[neighbors_quant] = { 2, 4, 5, 6, 7, 8 };

	srand(static_cast<unsigned int> (time(0)));

	enter_params(program_num);

	if (program_num == 1) {
		program_1(program_num, num1, num2, num_all, square, disloc1, disloc2, disloc_moved1, disloc_moved2, neighbors_name1, neighbors_name2, direction1, direction2);
	}
	if (program_num == 2) {
		program_2(program_num, num1, num2, num_all, square, disloc1, disloc2, disloc_moved1, disloc_moved2, neighbors_name1, neighbors_name2, direction1, direction2);
	}
	if (program_num == 3) {
		program_3(program_num, num1, num2, num_all, square, disloc1, disloc2, disloc_moved1, disloc_moved2, neighbors_name1, neighbors_name2, direction1, direction2);
	}
	if (program_num == 4) {
		program_4(program_num, num1, num2, num_all, square, disloc1, disloc2, disloc_moved1, disloc_moved2, neighbors_name1, neighbors_name2, direction1, direction2);
	}
	return 0;
}
