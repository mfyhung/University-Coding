#include<iostream>
#include <cmath>
using namespace std;

int main() {
	/*
	Assignment: 1
	Student ID: 1155083147
	Name      : Hung Fan Yan
	E-mail    : 1155083147@link.cuhk.edu.hk
	*/
	long long input;
	long long odd, odd_sum , even_sum , num, sum , check_num, counter;//The variables
	do {
		counter = 0,odd_sum=0,even_sum=0,sum=0;//reset the sum and variables
		cout << "Enter a 15-digit partial card num: ";
		cin >> input;
		if (input < 0) {//The input checking
			cout << "Bye!"<<endl;
			break;//Break the do while loop
		}
		else {
			for (int i = 15; i > 0; i--) {
				num = ((long long)(input / pow(10, i - 1))) % 10;//seperate the num from the input
				if (i % 2 == 1) {//Check the position of the input
					odd = num;
					odd *= 2;
					if (odd >= 10) {
						odd_sum += ((odd / 10) + (odd % 10));
					}
					else {
						odd_sum += odd;//sum to the odd sum
					}
				}
				else {
					even_sum += num;//sum to the even sum
				}
			}
			sum = odd_sum + even_sum;//sum up together
			sum *= 9;
			check_num=sum % 10;//Find out the check num
			cout << "Full card num is: ";
			for (int j = 15; j > 0; j--,counter++) {
				if (counter % 4 == 0&&counter!=0)//To find out the situation need to cout the "-"
					cout << "-";
				cout<< ((long long)(input / pow(10, j - 1))) % 10;
			}
			cout << check_num << endl;//cout the check number
		}
	} while (input > 0);
	return 0;
}