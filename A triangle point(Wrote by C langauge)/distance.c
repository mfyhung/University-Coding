#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
int main() {
	int x1, x2, x3, y1, y2, y3;
	double sx, sy, lx, ly, ax, ay, d12, d23, d31;
	double check1x, check1y, check2x, check2y, dis = 0, disc;
	int counter = 0;
	printf("Distance Measurement\nThe following inputs are integers separated by whitespaces:\n");
	printf("Enter interest point 1 (x1 y1): ");
	scanf("%d%d", &x1, &y1);
	printf("Enter interest point 2 (x2 y2): ");
	scanf("%d%d", &x2, &y2);
	printf("Enter interest point 3 (x3 y3): ");
	scanf("%d%d", &x3, &y3);
	printf("checks:\n");
	printf("*** p1(%d, %d); p2(%d, %d); p3(%d, %d)\n", x1, y1, x2, y2, x3, y3);//print out the points
	printf("*** Smallest x = ");
	if ((x1 == x2&&x3>x1) || (x1 == x3&&x2>x1) || (x2 > x1&&x3 > x1)) {
		sx = x1;
	}
	else if ((x2 == x3&&x1>x2) || (x3 > x2&&x1 > x2)) {
		sx = x2;
	}
	else if ((x2 > x3&&x1 > x3) || (x2 == x1&&x1>x3)) {
		sx = x3;
	}
	else {
		sx = lx = x1;
	}
	//The different situation to find out the smallest x
	printf("%.0lf\n", sx);//print the smallest x 
	printf("***  Largest x = ");
	if ((x1 == x2&&x1>x3) || (x1 == x3&&x1>x2) || (x1 > x2&&x1 > x3)) {
		lx = x1;
	}
	else if ((x2 == x3&&x2>x1) || (x2 > x3&&x2 > x1)) {
		lx = x2;
	}
	else if ((x3 > x2&&x3 > x2) || (x2 == x1&&x3>x1)) {
		lx = x3;
	}
	//The different situation to find out the largest x
	printf("%.0lf\n", lx);//print the largest x 
	printf("*** Smallest y = ");
	if ((y1 == y2&&y3>y1) || (y1 == y3&&y2>y1) || (y2 > y1&&y3 > y1)) {
		sy = y1;
	}
	else if ((y2 == y3&&y1>y2) || (y3 > y2&&y1 > y2)) {
		sy = y2;
	}
	else if ((y2 > y3&&y1 > y3) || (y2 == y1&&y1>y3)) {
		sy = y3;
	}
	else {//when there are same y
		sy = ly = y1;
	}
	//The different situation to find out the smallest y
	printf("%.0lf\n", sy);//print the smallest y
	printf("***  Largest y = ");
	if ((y1 == y2&&y1>y3) || (y1 == y3&&y1>y2) || (y1 > y2&&y1 > y3)) {
		ly = y1;
	}
	else if ((y2 == y3&&y2>y1) || (y2 > y3&&y2 > y1)) {
		ly = y2;
	}
	else if ((y3 > y2&&y3 > y2) || (y2 == y1&&y3>y1)) {
		ly = y3;
	}
	//The different situation to find out the largest y
	printf("%.0lf\n", ly);//print the largest y
	ax = (x1 + x2 + x3) / 3.0;
	ay = (y1 + y2 + y3) / 3.0;
	printf("*** Centroid = (Avg x, Avg y) = (%lf, %lf)\n", ax, ay);
	d12 = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
	d23 = sqrt(pow((x3 - x2), 2) + pow((y3 - y2), 2));
	d31 = sqrt(pow((x3 - x1), 2) + pow((y3 - y1), 2));
	printf("*** Distance p1-p2 = %lf\n", d12);
	printf("*** Distance p2-p3 = %lf\n", d23);
	printf("*** Distance p3-p1 = %lf\n", d31);
	printf("Enter as many way points as you like until reaching the goal\nOur goal is to hit the centroid within an error of 1e-5\n");
	printf("The following inputs are doubles separated by white spaces:\n");
	do {
		counter++;
		printf("Enter way point %d (wx%d wy%d): ", counter, counter, counter);
		if (counter % 2 == 1) {
			scanf("%lf%lf", &check1x, &check1y);
			disc = sqrt(pow((check1x - ax), 2) + pow((check1y - ay), 2));
		}
		else {
			scanf("%lf%lf", &check2x, &check2y);
			disc = sqrt(pow((check2x - ax), 2) + pow((check2y - ay), 2));
		}

		printf("*** Distance of way point %d from centroid = %lf\n", counter, disc);
		if (counter == 1) {
			printf("*** Total distance travelled = 0.000000\n");
		}
		else {
			dis += sqrt(pow((check1x - check2x), 2) + pow((check1y - check2y), 2));
			printf("*** Total distance travelled = %lf\n", dis);
		}
	} while (disc > 0.00001);
	return 0;
}