#include <iostream>
#include <fstream>
#include <pthread.h>
#include <vector>
#include <cstdlib> // for atoi()
#include <cmath> // for sqrt(num)
#include <mutex>

using namespace std;

int numOfPrime = 0;
int numOfPalindrome = 0;
int numOfPalindromicPrime = 0;
int totalNums = 0;

vector<int> PrimeList;
vector<int> PalindromeList;
vector<int> PalindromicPrimeList;

mutex lockPrint;
mutex lockTotalNums;
mutex lockCount;

struct threadsInfo {
	int threadID;
	int startNum;
	int endNum;
	bool TisWorking = true;
};

void* threadsFun(void* arg) {
	threadsInfo* threadsArg = (threadsInfo*)arg;

	if (!threadsArg->TisWorking) {
		lockPrint.lock();
		cout << "threadID=" << threadsArg->threadID
			<< ", I have nothing to do!\n";
		lockPrint.unlock();
	}
	else {
		lockPrint.lock();
		cout << "threadID=" << threadsArg->threadID
			<< ", startNum=" << threadsArg->startNum
			<< ", endNum=" << threadsArg->endNum << endl;
		lockPrint.unlock();

		for (int num = threadsArg->startNum; num < threadsArg->endNum; num++) {

			lockTotalNums.lock();
			totalNums++;
			lockTotalNums.unlock();

			// check if prime
			bool primeCheck = true;
			if (num <= 1)
				primeCheck = false;
			else {
				for (int i = 2; i <= sqrt(num); i++) {
					if (num % i == 0) {
						primeCheck = false;
						break;
					}
				}
			}

			// check if palindrome
			bool palindromeCheck;
			int orgNum = num;
			int revNum = 0;
			while (orgNum > 0) {
				int digit = orgNum % 10;
				revNum = (revNum * 10) + digit;
				orgNum /= 10;
			}
			palindromeCheck = (num == revNum);

			if (primeCheck) {
				lockCount.lock();
				PrimeList.push_back(num);
				numOfPrime++;
				lockCount.unlock();
			}
			if (palindromeCheck) {
				lockCount.lock();
				PalindromeList.push_back(num);
				numOfPalindrome++;
				lockCount.unlock();
			}
			if (primeCheck && palindromeCheck) {
				lockCount.lock();
				PalindromicPrimeList.push_back(num);
				numOfPalindromicPrime++;
				lockCount.unlock();
			}
		}
	}
	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {

	// store the number of threads (T)
	if (argc != 2 || atoi(argv[1]) <= 0) {
		cerr << "Unaccepted number of threads!\n";
		return 1;
	}
	int T = atoi(argv[1]); // ASCII to int

	// read the range of numbers
	int rangeStart, rangeEnd;
	ifstream infile("in.txt");
	if (!infile) {
		cerr << "Input file couldn't open.\n";
		return 1;
	}
	infile >> rangeStart >> rangeEnd;
	infile.close();

	// divide the range over threads
	int rangeSize = rangeEnd - rangeStart;
	int newT = T;
	if (rangeSize % T == 0) {
		rangeSize /= T;
	}
	else { // if (T > rangeSize)
		newT = rangeSize;
		rangeSize = 1;
	}

	// create worker threads
	pthread_t* threads = new pthread_t[T];
	threadsInfo* threadsArg = new threadsInfo[T];
	for (int i = 0; i < T; i++) {
		threadsArg[i].threadID = i;

		if (i < newT) {
			threadsArg[i].startNum = rangeStart + (i * rangeSize);
			threadsArg[i].endNum = threadsArg[i].startNum + rangeSize;
		}
		else // if(i > newT)
			threadsArg[i].TisWorking = false;

		pthread_create(&threads[i], NULL, threadsFun, (void*)&threadsArg[i]);
	}

	// make main wait until all threads finish
	for (int i = 0; i < T; i++) {
		pthread_join(threads[i], NULL);
	}

	// main thread will print
	cout << "totalNums=" << totalNums
		<< ", numOfPrime=" << numOfPrime
		<< ", numOfPalindrome=" << numOfPalindrome
		<< ", numOfPalindromicPrime=" << numOfPalindromicPrime << endl;

	// store arrays of numbers
	ofstream outfile("out.txt");
	if (!outfile) {
		cerr << "Output file couldn't open.\n";
		return 1;
	}

	outfile << "The prime numbers are:\n";
	for (int i = 0; i < numOfPrime; ++i) {
		outfile << PrimeList[i] << endl;
	}
	outfile << "The palindrome numbers are:\n";
	for (int i = 0; i < numOfPalindrome; ++i) {
		outfile << PalindromeList[i] << endl;
	}
	outfile << "The palindromicPrime numbers are:\n";
	for (int i = 0; i < numOfPalindromicPrime; ++i) {
		outfile << PalindromicPrimeList[i] << endl;
	}

	return 0;
}
