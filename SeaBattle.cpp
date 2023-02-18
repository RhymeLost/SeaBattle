#include <iostream>
#include<time.h>
#include <windows.h>

using namespace std;

void zap_point(char pole[][10]);
void vivod(char pole[][10]);
void zap_boat(char pole[10][10]);
void zap_boat_user(char pole[10][10]);
void punch_user(char pole[10][10],char show[10][10],short*p);
void punch_comp(char pole[10][10],short*p);
void check_comp(char pole[10][10], int* win);
void check_user(char pole[10][10], int* win);

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	char pole_comp[10][10];
	char pole_user[10][10];
	char show_comp[10][10];
	zap_point(pole_user);
	zap_point(pole_comp);
	zap_point(show_comp);
	zap_boat(pole_comp);
	short c, p=1;
	cout << "Random filling (1) or hand filling (2): ";
	cin >> c;
	int win = 0;
	do {
		if (c == 1) { zap_boat(pole_user); }
		if(c==2) { zap_boat_user(pole_user); }
		if(c!=1&&c!=2) {
			cout<< "\nInvalid value!";
		}
	} while (c != 1&& c != 2);
	
	while(!win){
		p = 1;
		while (p) {
			cout << "___________________Comp's field______________________\n";
			punch_user(pole_comp, show_comp, &p);
			vivod(show_comp);
			check_comp(pole_comp, &win);
			if (win == 1) {
				cout << "\nCondrates! You win!\n\n";
			}
		}
		p=1;
		while (p) {
			cout << "____________________Your field_______________________\n\n";
			punch_comp(pole_user, &p);
			vivod(pole_user);
			check_comp(pole_user, &win);
			if (win == 2) {
				cout << "\nCondrates! You lose!\n\n";
			}
		}
	}
}

void vivod(char pole[][10]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << pole[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void zap_point(char pole[][10]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			pole[i][j] = '.';
		}
	}
}

void zap_boat(char pole[10][10]) {
	for (int i = 0; i < 6; i++) {
		int r, r1;
		do {
			r = rand() % 10;
			r1 = rand() % 10;
			if (pole[r1 - 1][r - 1] != 'П' && pole[r1][r - 1] != 'П' && pole[r1 + 1][r - 1] != 'П'\
				&& pole[r1 - 1][r] != 'П' && pole[r1 + 1][r] != 'П' && pole[r1 - 1][r + 1] != 'П' && \
				pole[r1][r + 1] != 'П' && pole[r1 + 1][r + 1] != 'П' && pole[r1][r] != 'П')
			{
				pole[r1][r] = 'П';
			}
		} while (pole[r1][r] != 'П');
		int u = 0;
		do {
			int t = rand() % 4;
			switch (t) {

				case (0):
				if (pole[r1 + 1][r] == '.' && pole[r1 + 2][r - 1] != 'П'\
					&& pole[r1 + 2][r] != 'П' && pole[r1 + 2][r + 1] != 'П') {
					pole[r1 + 1][r] = 'П';
					u = 1; //вниз
				}
				break;
				case (1):
				if (pole[r1 - 1][r] == '.' && pole[r1 - 2][r - 1] != 'П'\
					&& pole[r1 - 2][r] != 'П' && pole[r1 - 2][r + 1]!= 'П') {
					pole[r1 - 1][r] = 'П';
					u = 1;//вверх
				}
				break;
				case(2):
			    if (pole[r1][r + 1] == '.' && pole[r1 - 1][r + 2] != 'П'\
					&& pole[r1][r + 2] != 'П' && pole[r1 + 1][r + 2]!= 'П' && r != 9) {
					pole[r1][r + 1] = 'П';
					u = 1;//вправо
				}
				break;
				case (3):
				if (pole[r1][r - 1] == '.' && pole[r1 - 1][r - 2] != 'П'\
					&& pole[r1][r - 2] != 'П' && pole[r1 + 1][r - 2] != 'П' && r != 9) {
					pole[r1][r - 1] = 'П';
					u = 1;//влево
				}
				break;
			}
			t = 0;
		} while (!u);
		r1 = 0;
		r = 0;
	}
}

void zap_boat_user(char pole[10][10]) {
	for (int i = 0; i < 6;) {
		int r, r1;
		do {
			cout << "\nChoose point by coordinantes:\n";
			cin >> r >> r1;
			if (r1 >= 0 && r >= 0 && r1 <= 9 && r <= 9) {
				if (pole[r1][r] == '.')
				{
					pole[r1][r] = 'П';
					vivod(pole);
				}
				else {
					cout << "\nInvalid value!";
				}
			}
			else {
				cout << "\nInvalid value!";
			}
		} while (pole[r1][r] != 'П');
		int u = 0;
		do {
			int t = 0;
			cout << "\nChoose direction (1-down,2-up,3-right,4-left): ";
			cin >> t;
			switch (t) {

			case (1):
				if (pole[r1 + 1][r] == '.') {
					pole[r1 + 1][r] = 'П';
					u = 1;
					i++;
					vivod(pole);//вниз
				}
				break;
			case (2):
				if (pole[r1 - 1][r] == '.') {
					pole[r1 - 1][r] = 'П';
					u = 1;
					i++;
					vivod(pole);//вверх
				}
				break;
			case(3):
				if (pole[r1][r + 1] == '.') {
					pole[r1][r + 1] = 'П';
					u = 1;
					i++;
					vivod(pole);//вправо
				}
				break;
			case (4):
				if (pole[r1][r - 1] == '.') {
					pole[r1][r - 1] = 'П';
					u = 1;
					i++;
					vivod(pole);//влево
				}
				break;
			default:
				cout << "Invalid value!";
			}
			t = 0;
		} while (!u);
		r1 = 0;
		r = 0;
	}
}

void punch_comp(char pole[10][10],short *p) {
	int r, r1;
	bool b = 0;
	do {
		r = rand() % 10;
		r1 = rand() % 10;
		if (pole[r1][r] == '.'){
			pole[r1][r] = 'o';
			*p = 0;
			b = 1;
		}
		if (pole[r1][r] == 'П') {
			pole[r1][r] = 'X';
			*p = 1;
			b = 1;
		}
	} while (!b);
}

void punch_user(char pole[10][10], char show[10][10],short*p) {
	int r, r1;
	bool b = 0;
	do {
		cout << "\nChoose point to punch by coordinantes:\n";
		cin >> r>> r1;
		if (pole[r1][r] == '.'){
			pole[r1][r] = 'o';
			show[r1][r] = 'o';
			*p = 0;
			b = 1;
		}
		if (pole[r1][r] == 'П') {
			pole[r1][r] = 'X';
			show[r1][r] = 'X';
			*p = 1;
			b = 1;
		}
		if(r1<0||r<0||r1>9||r>9){
			cout << "\nInvalid value!";
		}
	} while (!b);
}

void check_comp(char pole[10][10],int *win) {
	int temp=0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (pole[i][j] != 'П') {
				temp++;
			}

		}
	}
	temp == 100 ? *win = 1 : 0;
}

void check_user(char pole[10][10], int* win) {
	int temp = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (pole[i][j] != 'П') {
				temp++;
			}

		}
	}
	temp == 100 ? *win = 2 : 0;
}