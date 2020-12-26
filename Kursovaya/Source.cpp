#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

int main() {
	setlocale(LC_ALL, "RUSSIAN");
	const int n1 = 100;
	const int n2 = n1 * 3;



	long int k1 = 8;
	double n[4][n1];
	double xstl[4][4][n1];
	long int kstl[4][n1];

	ifstream fin("C:\\Users\\LENOVO\\Desktop\\курсовая работа\\oktaedr.stl");

	if (fin.is_open()) {
		for (int i = 1; i <= k1; i++) {
			fin >> n[1][i] >> n[2][i] >> n[3][i];
			fin >> xstl[1][1][i] >> xstl[2][1][i] >> xstl[3][1][i];
			fin >> xstl[1][2][i] >> xstl[2][2][i] >> xstl[3][2][i];
			fin >> xstl[1][3][i] >> xstl[2][3][i] >> xstl[3][3][i];
			kstl[1][i] = 0; kstl[2][i] = 0; kstl[3][i] = 0;
		}
		fin.close();
	}
	else
	{
		cout << "Файл не найден.";
	}

	kstl[1][1] = 1; kstl[2][1] = 2; kstl[3][1] = 3;
	long int k = 3;
	int i, j;
	int i1, j1;
	int i2, j2;
	int i3;
	double norma;

	for (i = 1; i < k1; i++) {
		for (j = 1; j <= 3; j++) {
			if (kstl[j][i] == 0) {
				k++;
				kstl[j][i] = k;
			}
			for (i1 = i + 1; i1 <= k1; i1++) {
				for (j1 = 1; j1 <= 3; j1++) {
					norma = abs(xstl[1][j][i] - xstl[1][j1][i1]) + abs(xstl[2][j][i] - xstl[2][j1][i1]) + abs(xstl[3][j][i] - xstl[3][j1][i1]);
					if (norma < 0.0001)
						kstl[j1][i1] = kstl[j][i];
				}
			}

		}

	}

	double x[4][n2];
	long int kod[4][n1], kod2[7][n1];

	for (i = 1; i <= k1; i++) {
		for (j = 1; j <= 3; j++) {
			x[1][kstl[j][i]] = xstl[1][j][i];
			x[2][kstl[j][i]] = xstl[2][j][i];
			x[3][kstl[j][i]] = xstl[3][j][i];
			kod[j][i] = kstl[j][i];
		}
	}

	int k2 = k;
	for (i = 1; i <= k2; i++) {
		kod2[0][i] = 0;
	}
	for (i = 1; i <= k1; i++) {
		for (j = 1; j <= 3; j++) {
			kod2[0][kstl[j][i]] += 1;
			kod2[kod2[0][kstl[j][i]]][kstl[j][i]] = i;
		}
	}

	//Печать кодов
	ofstream fout;
	fout.open("C:\\Users\\LENOVO\\Desktop\\курсовая работа\\kods_0.stl");

	fout << "Узлы:" << endl;
	for (i = 1; i <= k2; i++) {
		fout << x[1][i] << ' ' << x[2][i] << ' ' << x[3][i] << endl;
	}

	fout << "Грани:" << endl;
	for (i = 1; i <= k1; i++) {
		fout << kod[1][i] << ' ' << kod[2][i] << ' ' << kod[3][i] << endl;
	}

	fout << "Инцидентность узлов граням:" << endl;
	for (i = 1; i <= k2; i++) {
		fout << kod2[0][i] << ' ';
		for (j = 1; j <= kod2[0][i]; j++) {
			fout << kod2[j][i] << ' ';
		}
		fout << endl;
	}


	//Векторы нормали в узлах

	double nu[4][n2];
	for (i = 1; i <= k2; i++) {
		norma = sqrt(pow(x[1][i], 2) + pow(x[2][i], 2) + pow(x[3][i], 2));
		nu[1][i] = x[1][i] / norma;
		nu[2][i] = x[2][i] / norma;
		nu[3][i] = x[3][i] / norma;
	}


	//Центры граней 

	double xc[4][n1];
	for (i = 1; i <= k1; i++) {
		i1 = kod[1][i];
		i2 = kod[2][i];
		i3 = kod[3][i];
		xc[1][i] = (x[1][i1] + x[1][i2] + x[1][i3]) / 3;
		xc[2][i] = (x[2][i1] + x[2][i2] + x[2][i3]) / 3;
		xc[3][i] = (x[3][i1] + x[3][i2] + x[3][i3]) / 3;
	}
	fout << "Векторы нормали в узлах:" << endl;
	for (i = 1; i <= k2; i++) {
		fout << nu[1][i] << ' ' << nu[2][i] << ' ' << nu[3][i] << endl;
	}
	fout << "Центры граней:" << endl;
	for (i = 1; i <= k1; i++) {
		fout << xc[1][i] << ' ' << xc[2][i] << ' ' << xc[3][i] << endl;
	}

	//fout.close(); 




	//Работа с гранями

	double e1[4], e2[4], e3[4];
	double mat[4][4][n1];
	int m;
	double ee[4][4];
	float al[4][4][n1];

	for (i = 1; i <= k1; i++) {
		i1 = kod[1][i];
		i2 = kod[2][i];
		i3 = kod[3][i];

		//Базис

		e1[1] = x[1][i1] - xc[1][i];
		e1[2] = x[2][i1] - xc[2][i];
		e1[3] = x[3][i1] - xc[3][i];

		norma = sqrt(pow(e1[1], 2) + pow(e1[2], 2) + pow(e1[3], 2));
		e1[1] /= norma;
		e1[2] /= norma;
		e1[3] /= norma;
		e3[1] = n[1][i];
		e3[2] = n[2][i];
		e3[3] = n[3][i];
		e2[1] = e3[2] * e1[3] - e3[3] * e1[2];
		e2[2] = e3[3] * e1[1] - e3[1] * e1[3];
		e2[3] = e3[1] * e1[2] - e3[2] * e1[1];
		mat[1][1][i] = e1[1]; mat[2][1][i] = e1[2]; mat[3][1][i] = e1[3];
		mat[1][2][i] = e2[1]; mat[2][2][i] = e2[2]; mat[3][2][i] = e2[3];
		mat[1][3][i] = e3[1]; mat[2][3][i] = e3[2]; mat[3][3][i] = e3[3];

		//Координаты узлов в местном базисе


		ee[1][1] = x[1][i1] - xc[1][i]; ee[1][2] = x[2][i1] - xc[2][i]; ee[1][3] = x[3][i1] - xc[3][i];
		ee[2][1] = x[1][i2] - xc[1][i]; ee[2][2] = x[2][i2] - xc[2][i]; ee[2][3] = x[3][i2] - xc[3][i];
		ee[3][1] = x[1][i3] - xc[1][i]; ee[3][2] = x[2][i3] - xc[2][i]; ee[3][3] = x[3][i3] - xc[3][i];

		for (j = 1; j <= 3; j++) {
			for (k = 1; k <= 3; k++) {
				al[j][k][i] = 0;
				for (m = 1; m <= 3; m++) {
					al[j][k][i] += ee[j][m] * mat[m][k][i];
				}
			}
		}
			if (i == 1) {
				fout << "Векторы 1-й грани:" << endl;
				fout << ee[1][1] << ' ' << ee[1][2] << ' ' << ee[1][3] << endl;
				fout << ee[2][1] << ' ' << ee[2][2] << ' ' << ee[2][3] << endl;
				fout << ee[3][1] << ' ' << ee[3][2] << ' ' << ee[3][3] << endl;
			}
		
	}
	fout.precision(6);
	fout << "Матрицы" << endl;
	for (i = 1; i <= k1; i++) {
		fout << "Грань " << i << ':' << endl;
		fout << mat[1][1][i] << ' ' << mat[2][1][i] << ' ' << mat[3][1][i] << endl;
		fout << mat[1][2][i] << ' ' << mat[2][2][i] << ' ' << mat[3][2][i] << endl;
		fout << mat[1][3][i] << ' ' << mat[2][3][i] << ' ' << mat[3][3][i] << endl;
	}
	fout.precision(6);
	fout << "Вершины граней в местных системах координат:" << endl;
	for (i = 1; i <= k1; i++) {
		fout << "Грань " << i << ':' << endl;
		fout << al[1][1][i] << ' ' << al[2][1][i] << ' ' << al[3][1][i] << endl;
		fout << al[1][2][i] << ' ' << al[2][2][i] << ' ' << al[3][2][i] << endl;
		fout << al[1][3][i] << ' ' << al[2][3][i] << ' ' << al[3][3][i] << endl;
	}

	// Значения в точках

	double p[4][n1][n1];
	for (i = 1; i <= 8; i++) {
		p[1][1][i] = al[1][1][i]; p[1][2][i] = al[1][2][i]; p[1][3][i] = al[1][3][i];
		p[2][1][i] = al[2][1][i]; p[2][2][i] = al[2][2][i]; p[2][3][i] = al[2][3][i];
		p[3][1][i] = al[3][1][i]; p[3][2][i] = al[3][2][i]; p[3][3][i] = al[3][3][i];

		p[1][4][i] = (2 * al[1][1][i] + al[1][2][i]) / 3; 
		p[2][4][i] = (2 * al[2][1][i] + al[2][2][i]) / 3; 
		p[3][4][i] = (2 * al[3][1][i] + al[3][2][i]) / 3; 

		p[1][5][i] = (al[1][1][i] + 2 * al[1][2][i]) / 3; 
		p[2][5][i] = (al[2][1][i] + 2 * al[2][2][i]) / 3; 
		p[3][5][i] = (al[3][1][i] + 2 * al[3][2][i]) / 3; 


		p[1][6][i] = (2 * al[1][2][i] + al[1][3][i]) / 3;
		p[2][6][i] = (2 * al[2][2][i] + al[2][3][i]) / 3; 
		p[3][6][i] = (2 * al[3][2][i] + al[3][3][i]) / 3; 


		p[1][7][i] = (al[1][2][i] + 2 * al[1][3][i]) / 3; 
		p[2][7][i] = (al[2][2][i] + 2 * al[2][3][i]) / 3;
		p[3][7][i] = (al[3][2][i] + 2 * al[3][3][i]) / 3; 


		p[1][8][i] = (al[1][1][i] + 2 * al[1][3][i]) / 3;
		p[2][8][i] = (al[2][1][i] + 2 * al[2][3][i]) / 3; 
		p[3][8][i] = (al[3][1][i] + 2 * al[3][3][i]) / 3; 


		p[1][9][i] = (2 * al[1][1][i] + al[1][3][i]) / 3;
		p[2][9][i] = (2 * al[2][1][i] + al[2][3][i]) / 3; 
		p[3][9][i] = (2 * al[3][1][i] + al[3][3][i]) / 3;

		p[1][10][i] = (al[1][1][i] + al[1][2][i] + al[1][3][i]) / 3;
		p[2][10][i] = (al[2][1][i] + al[2][2][i] + al[2][3][i]) / 3;
		p[3][10][i] = (al[3][1][i] + al[3][2][i] + al[3][3][i]) / 3;
	}
	fout.precision(2);
	fout << "Значения в точках" << endl;
	for (i = 1; i <= k1; i++) {
		fout << "Грань " << i << ':' << endl;
		fout << p[1][1][i] << ' ' << p[2][1][i] << ' ' << p[3][1][i] << endl;
		fout << p[1][2][i] << ' ' << p[2][2][i] << ' ' << p[3][2][i] << endl;
		fout << p[1][3][i] << ' ' << p[2][3][i] << ' ' << p[3][3][i] << endl;
		fout << p[1][4][i] << ' ' << p[2][4][i] << ' ' << p[3][4][i] << endl;
		fout << p[1][5][i] << ' ' << p[2][5][i] << ' ' << p[3][5][i] << endl;
		fout << p[1][6][i] << ' ' << p[2][6][i] << ' ' << p[3][6][i] << endl;
		fout << p[1][7][i] << ' ' << p[2][7][i] << ' ' << p[3][7][i] << endl;
		fout << p[1][8][i] << ' ' << p[2][8][i] << ' ' << p[3][8][i] << endl;
		fout << p[1][9][i] << ' ' << p[2][9][i] << ' ' << p[3][9][i] << endl;
		fout << p[1][10][i] << ' ' << p[2][10][i] << ' ' << p[3][10][i] << endl;
	}

	// Производные в точках

	double u[11][9];

	for (i = 1; i <= 8; i++) {
		for (j = 1; j <= 3; j++) {
			u[j][i] = 0;
		}
	}

	


/*	fout << "Матрицы" << endl;
	for (i = 1; i <= k1; i++) {
		fout << "Грань " << i << ':' << endl;
		fout << mat[1][1][i] << ' ' << mat[1][2][i] << ' ' << mat[1][3][i] << endl;
		fout << mat[2][1][i] << ' ' << mat[2][2][i] << ' ' << mat[2][3][i] << endl;
		fout << mat[3][1][i] << ' ' << mat[3][2][i] << ' ' << mat[3][3][i] << endl;
    }

	fout << "Вершины граней в местных системах координат:" << endl;
	for (i = 1; i <= k1; i++) {
		fout << "Грань " << i << ':' << endl;
		fout << al[1][1][i] << ' ' << al[1][2][i] << ' ' << al[1][3][i] << endl;
		fout << al[2][1][i] << ' ' << al[2][2][i] << ' ' << al[2][3][i] << endl;
		fout << al[3][1][i] << ' ' << al[3][2][i] << ' ' << al[3][3][i] << endl;
	}
*/
	fout.close();


	system("pause");
	return 0;
}
