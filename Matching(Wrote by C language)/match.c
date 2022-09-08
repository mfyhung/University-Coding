/*I declare that the assignment here submitted is original
* except for source material explicitly acknowledged,
*and that the same or closely related material has not been
* previously submitted for another course.
* I also acknowledge that I am aware of University policy and
* regulations on honesty in academic work, and of the disciplinary
* guidelines and procedures applicable to breaches of such
* policy and regulations, as contained in the website.
*
* University Guideline on Academic Honesty :
*http ://www.cuhk.edu.hk/policy/academichonesty/
	*
	* Student Name : Hung Fan Yan
	* Student ID : 1155083147
	* Class / Section :ENGG1110B 
	* Date : 2/11/2016
	*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

void findMin(double k[], int n, char w) {//the function find the min, from the input value of the n(the number of the array),w(the "P"character), and the array)
	int i;
	double minV;
	minV = k[1];
	for (i = 1; i <= n; i++) {//to check the value, if the value is smaller than the orginal one , the minvalue treansfer.
		if (minV >= k[i])
			minV = k[i];
	}
	printf("*** Smallest %c = %f\n", w, minV);//print out the value 
}

void findMax(double k[], int n, char w) {//the function find the max, from the input value of the n(the number of the array),w(the "P"character), and the array)
	int i;
	double maxV;
	maxV = k[1];
	for (i = 1; i <= n; i++) {//to check the value, if the value is latger than the orginal one , the maxvalue treansfer.
		if (maxV <= k[i])
			maxV = k[i];
	}
	printf("***  Largest %c = %f\n", w, maxV);
}
void printTable(double k[], double p[], int n) {//the function that print out table
	int i, j, t[20] = { 0 }, check, amount = 0;
	double dis;
	printf("***Distance Table");//the distance table word.
	for (i = 1;i <= n;i++) {
		printf("|      p%d", i);//print out the P1-20
	}
	printf("\n");
	printf("-----------------");
	for (i = 0;i < n;i++) {
		printf("+--------");//print out the ------- by a loop
	}
	printf("\n");
	for (i = 1;i <= n;i++) {
		printf("p%d (%+5.1lf, %+5.1lf)", i, k[i], p[i]);//print and calcate the value.
		for (j = 1;j <= n;j++) {
			dis = sqrt(pow((k[i] - k[j]), 2.0) + pow((p[i] - p[j]), 2.0));//the distance measurement 
			printf("|%8.3lf", dis);
		}
		printf("\n");

	}
	printf("Enter a list of points to be shortlisted [1-%d], other int to end: ", n);
	for (i = 1;i <= n;i++) {
		scanf("%d", &check);//ask for the input
		if (check >= 1 && check <= n) {//check the input is that larger than n or smaller than 1
			t[i] = check;
			amount++;
		}
		else
			break;
	}
	printf("***%d Shortlisted points:", amount);
	for (i = 1;i <= amount;i++) {
		printf(" p%d", t[i]);
	}
	printf("\n***Distance Table");
	for (i = 1;i <= amount;i++) {
		printf("|      p%d", t[i]);
	}
	printf("\n");
	printf("-----------------");
	for (i = 0;i < amount;i++) {
		printf("+--------");
	}
	printf("\n");
	for (i = 1;i <= amount;i++) {
		printf("p%d (%+5.1lf, %+5.1lf)", t[i], k[t[i]], p[t[i]]);
		for (j = 1;j <= amount;j++) {
			dis = sqrt(pow((k[t[i]] - k[t[j]]), 2.0) + pow((p[t[i]] - p[t[j]]), 2.0));//call back the X,Y array by a new array call t
			printf("|%8.3lf", dis);
		}
		printf("\n");
	}

}
int main() {
	double X[21] = { 0 }, Y[21] = { 0 }, check_x, check_y;//the variable 
	int n, i;
	printf("Point Matching\n");
	printf("The following inputs are integers separated by whitespaces:\n");
	printf("How many points [1-20]: ");
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		printf("Enter interest point %d (x%d y%d):", i, i, i);
		scanf("%lf%lf", &check_x, &check_y);//ask for the user input 
		if (check_x > 99.999999 || check_x<-99.999999 || check_y>99.999999 || check_y < -99.999999) {//a checking that if the input value is wrong
			i--;//reset the i value
			printf("Invalid Input\n");
			continue;
		}
		X[i] = check_x;
		Y[i] = check_y;
	}
	printf("Checks:\n");
	for (i = 1; i <= n; i++) {
		printf("*** p%d (%+5.1lf, %+5.1lf)\n", i, X[i], Y[i]);
	}
	findMin(X, n, 'x');
	findMax(X, n, 'x');
	findMin(Y, n, 'y');
	findMax(Y, n, 'y');
	printTable(X, Y, n);
	return 0;
}