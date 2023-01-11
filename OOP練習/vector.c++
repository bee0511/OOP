#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#define INF 10000000

class PrimeFactorization {
private:
	int num1, num2;
	vector<int> num1_factor, num2_factor, prime;
	vector<bool> is_prime;

public:
	PrimeFactorization() {
		//TO_DO: initial constructor
		this->num1 = 0;
		this->num2 = 0;
	}
	PrimeFactorization(int _a, int _b) {
		//TO_DO: _a means the first integer and _b means the second integer
		this->num1 = _a;
		this->num2 = _b;
		is_prime.resize(INF, 1);
		is_prime[0] = is_prime[1] = 0;  //Make 0 and 1 not prime number.
		for (int i = 2; i < INF; i++) { //Find all the prime numbers that are smaller than 10^7.
			if (is_prime[i] == true) {
				prime.push_back(i);
				for (int j = 2 * i; j < INF; j += i) {
					is_prime[j] = false;
				}
			}
		}
	}
	void Get_Prime_Factorization() {
		//TO_DO: Prime factorization num1 and num2, push result to the num1_factor and num2_factor.
		for (int i = 0; i * i <= num1; i++) {
			while (num1 % prime[i] == 0) {
				num1 /= prime[i];
				num1_factor.push_back(prime[i]);
			}
			if (is_prime[num1] == true) { //In the end, num1 may be prime number, so we need to check whether it is prime number.
				num1_factor.push_back(num1);
				break;
			}
		}

		for (int i = 0; i * i <= num2; i++) {
			while (num2 % prime[i] == 0) {
				num2 /= prime[i];
				num2_factor.push_back(prime[i]);
			}
			if (is_prime[num2] == true) { //In the end, num2 may be prime number, so we need to check whether it is prime number.
				num2_factor.push_back(num2);
				break;
			}
		}
	}

	void Print_Prime_Factorization() {
		//TO_DO: Print num1_factor and num2_factor.
		cout << "num1_Prime_factor : \" ";
		for (int i = 0; i < num1_factor.size(); i++) {
			cout << num1_factor[i] << " ";
		}
		cout << "\"" << endl;
		cout << "num2_Prime_factor : \" ";
		for (int i = 0; i < num2_factor.size(); i++) {
			cout << num2_factor[i] << " ";
		}
		cout << "\"" << endl;
	}

	void Print_GCD() {
		//TO_DO: Use num1_factor and num2_factor to find GCD and print the result.
	}

	void Print_LCM() {
		//TO_DO: Use num1, num2, and GCD to find LCM and print the result.
	}

};

int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;

		cout << "num1 = " << a << endl;
		cout << "num2 = " << b << endl;

		PrimeFactorization PF(a, b);

		PF.Get_Prime_Factorization();
		PF.Print_Prime_Factorization();
		PF.Print_GCD();
		PF.Print_LCM();

		cout << endl;

	}

	system("PAUSE");
	return 0;
}
