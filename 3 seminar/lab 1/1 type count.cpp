#include <iostream>
#include <cstdlib>
#include <ctime>

void enter_params(int &program_num) {
	std::cout << "Enter the number of pragram: " << std::endl;
	std::cin >> program_num;
}

void set_dislocations_1(int num0, int size, int square[], int disloc[], int disloc_moved[]) {
	int coord_i = 0;

	for (int i = 0; i < num0; i++) {

		do {
			coord_i = rand() % (size);
		} while (square[coord_i] == 1);

		disloc[i] = coord_i;
		square[disloc[i]] = 1;

	}
}

void set_dislocations_2(int num0, int size, int square[], int disloc[], int disloc_moved[]) {
	int coord_i = 0;
	int coord_x_i = 0;
	int coord_y_i = 0;

	for (int i = 0; i < num0; i++) {

		do {
			coord_i = rand() % (size * size);
			coord_x_i = coord_i % size;
			coord_y_i = coord_i / size;
		} while (square[coord_y_i * size + coord_x_i] == 1);

		disloc[i] = coord_y_i * size + coord_x_i;
		square[disloc[i]] = 1;

	}
}

void disloc_deactiv(int& num_moved, int disloc_moved[], int square[], int i) {
	int tmp_disloc;
	if (num_moved > 1) {
		tmp_disloc = disloc_moved[num_moved - 1];
		disloc_moved[num_moved - 1] = disloc_moved[i];
		disloc_moved[i] = tmp_disloc;
		square[disloc_moved[num_moved - 1]] = 2;
		num_moved--;
	}
	else {
		if (num_moved = 1) {
			square[disloc_moved[i]] = 2;
			num_moved--;
		}
	}
}

void move_dislocations(int program_num, int& num, int num0, int size, int& counter, int square[], int disloc[], int disloc_moved[], int direction[]) {

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
	counter++;


	for (int i = 0; i < size_all; i++) {
		if (square[i] == 1) {
			num++;
			disloc[num - 1] = i;
			disloc_moved[num - 1] = i;
		}
	}

	num_moved = num;

	for (int i = 0; i < num; i++) {
		direction[i] = rand() % 4;
		if ((disloc[i] - size >= 0) && (direction[i] == 0) && (square[disloc[i] - size] == 0)) {
			square[disloc[i]] = 0;
			disloc_moved[i] = disloc[i] - size;
			square[disloc_moved[i]] = 1;
		}
		if (((disloc[i] + 1) % size != size - 1) && direction[i] == 1 && square[disloc[i] + 1] == 0) {
			square[disloc[i]] = 0;
			disloc_moved[i] = disloc[i] + 1;
			square[disloc_moved[i]] = 1;
		}
		if ((disloc[i] + size < size_all) && direction[i] == 2 && square[disloc[i] + size] == 0) {
			square[disloc[i]] = 0;
			disloc_moved[i] = disloc[i] + size;
			square[disloc_moved[i]] = 1;
		}
		if (((disloc[i] - 1) % size != 0) && direction[i] == 3 && square[disloc[i] - 1] == 0) {
			square[disloc[i]] = 0;
			disloc_moved[i] = disloc[i] - 1;
			square[disloc_moved[i]] = 1;
		}
	}

	for (int i = 0; i < num; i++) {
		bord_vert_i = disloc[i] % size;
		bord_hor_i = disloc[i] / size;

		if ((bord_vert_i == 0 && direction[i] == 3) || (bord_vert_i == size - 1 && direction[i] == 1) || (bord_hor_i == 0 && direction[i] == 0) || (bord_hor_i == size - 1 && direction[i] == 2)) {
			disloc_moved[i] = disloc[i];
			disloc_deactiv(num_moved, disloc_moved, square, i);
		}
	}

	num = num_moved;

	for (int i = 0; i < num; i++) {
		bord_vert_i = disloc_moved[i] % size;
		int neighbors_i[4] = { disloc_moved[i] - 1, disloc_moved[i] - size, disloc_moved[i] + size, disloc_moved[i] + 1 };

		if (bord_vert_i == size - 1) {
			for (int j = 0; j < 3; j++) {
				if (square[neighbors_i[j]] != 0) {
					disloc_deactiv(num_moved, disloc_moved, square, i);
					break;
				}
			}
		}
		else {
			if (bord_vert_i == 0) {
				for (int j = 1; j < 4; j++) {
					if (square[neighbors_i[j]] != 0) {
						disloc_deactiv(num_moved, disloc_moved, square, i);
						break;
					}
				}
			}
			else {
				for (int j = 0; j < 4; j++) {
					if (square[neighbors_i[j]] == 1 || square[neighbors_i[j]] == 2) {
						disloc_deactiv(num_moved, disloc_moved, square, i);
						break;
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

void program_1(int program_num, int& num, int square[], int disloc[], int disloc_moved[], int direction[]) {

	double array_1dis[20] = { 0 };
	int size = 0;
	int num0 = 1;
	int counter = 0;

	for (int i = 0; i < 20; i++) {
		int counter_all = 0;
		size = i + 1;

		for (int k = 1; k <= 1000; k++) {
			counter = 0;
			num = num0;
			set_dislocations_1(num0, size, square, disloc, disloc_moved);
			while (num > 0) {
				move_dislocations(program_num, num, num0, size, counter, square, disloc, disloc_moved, direction);
				counter++;;
			}
			counter_all += counter;
			null_array(disloc, 100);
			null_array(disloc_moved, 100);
			null_array(square, 100);

		}
		array_1dis[i] = double(counter_all * 0.001);
	}

	for (int i = 0; i < 20; i++) {
		std::cout << array_1dis[i] << "," << std::endl;
	}

}

void program_2(int program_num, int& num, int square[], int disloc[], int disloc_moved[], int direction[]){
	
	double array_1dis[10] = { 0 };
	int size = 0;
	int num0 = 1;
	int counter = 0;

	for (int i = 0; i < 10; i++) {
		int counter_all = 0;
		size = i + 1;

		for (int k = 1; k <= 1000; k++) {
			counter = 0;
			num = num0;
			set_dislocations_2(num0, size, square, disloc, disloc_moved);
			while (num > 0) {
				move_dislocations(program_num, num, num0, size, counter, square, disloc, disloc_moved, direction);
				counter++;;
			}
			counter_all += counter;
			null_array(disloc, 100);
			null_array(disloc_moved, 100);
			null_array(square, 100);

		}
		array_1dis[i] = double(counter_all * 0.001);
	}

	for (int i = 0; i < 10; i++) {
		std::cout << array_1dis[i] << "," << std::endl;
	}

}

void program_3(int program_num, int& num, int square[], int disloc[], int disloc_moved[], int direction[]) {
	
	double array_1size[20] = { 0 };
	int size = 100;
	int num0 = 0;
	int counter = 0;


	for (int i = 0; i < 20; i++) {
		int counter_all = 0;
		num0 = i + 1;

		for (int k = 1; k <= 1000; k++) {
			counter = 0;
			num = num0;
			set_dislocations_1(num0, size, square, disloc, disloc_moved);
			while (num > 0) {
				move_dislocations(program_num, num, num0, size, counter, square, disloc, disloc_moved, direction);
				counter++;;
			}
			counter_all += counter;
			null_array(disloc, 100);
			null_array(disloc_moved, 100);
			null_array(square, 100);

		}
		array_1size[i] = double(counter_all * 0.001);
	}

	for (int i = 0; i < 20; i++) {
		std::cout << array_1size[i] << "," << std::endl;
	}

}

void program_4(int program_num, int& num, int square[], int disloc[], int disloc_moved[], int direction[]) {
	
	double array_1size[40] = { 0 };
	int size = 10;
	int num0 = 0;
	int counter = 0;


	for (int i = 0; i < 40; i++) {
		int counter_all = 0;
		num0 = i + 1;

		for (int k = 1; k <= 1000; k++) {
			counter = 0;
			num = num0;
			set_dislocations_2(num0, size, square, disloc, disloc_moved);
			while (num > 0) {
				move_dislocations(program_num, num, num0, size, counter, square, disloc, disloc_moved, direction);
				counter++;;
			}
			counter_all += counter;
			null_array(disloc, 100);
			null_array(disloc_moved, 100);
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
	int program_num = 0;
	int num = 0;

	int square[big_size] = { 0 };
	int disloc[big_size] = { 0 };
	int disloc_moved[big_size] = {0};
	int direction[big_size] = { 0 };


	srand(static_cast<unsigned int> (time(0)));

	enter_params(program_num);

	if (program_num == 1) {
		program_1(program_num, num, square, disloc, disloc_moved, direction);
	}
	if (program_num == 2) {
		program_2(program_num, num, square, disloc, disloc_moved, direction);
	}
	if (program_num == 3) {
		program_3(program_num, num, square, disloc, disloc_moved, direction);
	}
	if (program_num == 4) {
		program_4(program_num, num, square, disloc, disloc_moved, direction);
	}
	return 0;
}
