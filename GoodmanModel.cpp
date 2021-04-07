/*	GoodmanModel.cpp : 	
	Программа позволяет оценивать среднюю продолжительность
	существования популяции по модели Гудмена, а также находить
	численность популяции необходимый для обеспечения заданной
	продолжительности существования.
*/
#include <iostream>
#include <locale.h>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
string answer1, answer2;
double T;
double V;
double R;

/* Ф-ция вычисления T по заданному N */
double Calculation(int n) {	 
   double x1 = 0;
   double x2 = 0;
   double x3 = 0;
   double t1 = 0;
   double t2 = 0;
   double t3 = 0;
   int N = n;

   if (N > 20) {
      t1 = 1.644;
   }
   else {
      for (int i = 1; i < N + 1; i++) {
         t1 = (1 / pow(i, 2)) + t1;
      }
   }
   x1 = ((V + R) / (V - R)) * (t1 / (R * (V - R)));

   for (int i = 1; i < N + 1; i++) {
      x2 = x2 + 1 / (i * (i * V - R));
   }
   x2 = x2 / R;

   for (int i = 2; i < N + 1; i++) {
      x3 = x3 + 1 / ((((i - 1) * V) - R) * ((i * V) - R));
   }
   t2 = (2 * V) / (V - R);
   x3 = x3 * t1 * t2;
   t3 = (x1 - x2 - x3) * ((N - 1) * V - R);
   return (t3);
}

/* Ф-ция ввода начальных данных */
int Input() {
   system("cls");
   cout << " N-численность популяции\n";
   cout << " T-продолжительность сущ-ния популяции\n"
   cout << " R-средняя удельная скорость роста числ-ти\n";
   cout << " V-дисперсия скорости роста (R)\n";
   cout << "\nЧтобы найти (N) обеспечивающий ожидаемую (T) введите 1";
   cout << "\nЧтобы найти (T) задавая (N) введите 2\n";
   cout << "\nЧто вы выберите?: ";
   cin >> answer1;

   while ((answer1 != "1") && (answer1 != "2")) {
      cout << "\nОШИБКА! Повторите выбор ('1' или '2'): ";
      cin >> answer1;
   }

   cout << "\nКаков темп роста (R)?: ";
   cin >> R;
   cout << "Какова дисперсия R (V)?: ";
   cin >> V;
   return (0);
}

/* Ф-ция вывода результатов вычислений */
int Output(int n, double t) {
   printf("\n------------------------------\n");
   printf("   Результаты вычислений     \n");
   printf("------------------------------\n");
   printf("   R = %10.5f                \n", R);
   printf("------------------------------\n");
   printf("   V = %10.5f                \n", V);
   printf("------------------------------\n");
   printf("   N = %i                 \n", n);
   printf("------------------------------\n");
   printf("   T = %10.5f                \n", t);
   printf("------------------------------\n");
   return (0);
}

int main() {
   setlocale(LC_ALL, "RUS");
	
   bool tryAgain = false;
   while (tryAgain != true) {
      double t = 0;
      Input();
      if (answer1 == "1") {
	    int n1, n2;

	    cout << "Ожидаемое время сохранения популяции (T): ";
	    cin >> T;
	    cout << "Предположение для нижней границы (N1): ";
	    cin >> n1;
	    cout << "Предположение для верхней границы (N2): ";
	    cin >> n2;

	    int f = 1;
	    int i = n1;
	    while ((i <= n2) && (f > 0)) {
	       t = Calculation(i);

	       if (abs(t - T) < 0.001 * T) {
		    f = 0;
		    Output(i, t);
	       }
	       if (t > T) {
	          if (i == n1) {
		        i = n1 - 1;
		        cout << "\nВведите меньшее значение для (N1):";
		        cin >> n1;
		     }
		     if (i < n2) {
		        f = 0;
		        Output(i, t);
	          }
	       }
	       if ((t < T) && (i == n2)) {
	          i = n2 - 1;
	          cout << "\nВведите большее значение для (N2):";
	          cin >> n2;
	       }
	       i++;
          }
       }
       if (answer1 == "2") {
          int N;
	     cout << "Введите численность популяции (N): ";
	     cin >> N;
	     t = Calculation(N);
	     Output(N, t);
       }
       cout << "\nДля выполнения новых расчетов введите '1' : ";
       cin >> answer2;
       if (answer2 != "1") {
          tryAgain = true;
       }
    }
    return (0);
}
