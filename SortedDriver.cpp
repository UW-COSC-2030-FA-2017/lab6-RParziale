// SortedDriver.cpp

// tom bailey   1445  25 mar 2014
// Construct sorted sequences and call functions that 
//   process the sorted sequences.

//Ryan Parziale
//COSC2030
//Lab6
//10-30-2017
//Working with sorted collections

#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty; 
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double
mostIsolated(vector<double> & number)
{
	
	//most largest difference, difference between current number and previous number,
	//difference between current number and next number, and the most isolated number
	double biggestDif, prevDif, nextDif, mostIsolated;
	
	prevDif = 999;
	nextDif = 999;
	
	
	nextDif = number[0] - number[1];
	biggestDif = nextDif;
	mostIsolated = number[0];
	//Going through the list
	for (int i = 1; i < number.size() - 1; i++)
	{
		prevDif = nextDif;
		nextDif = number[i] - number[i + 1];
		
		if (abs(prevDif) < abs(nextDif))
		{
			if (abs(prevDif) > abs(biggestDif))
			{
				biggestDif = prevDif;
				mostIsolated = number[i];
			}
		}
		else
		{
			if (abs(nextDif) > abs(biggestDif))
			{
				biggestDif = nextDif;
				mostIsolated = number[i];
			}
		}
		

	}
	
	return mostIsolated;
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int
unmatched(list<string> & A, list<string> & B)
{
	//Number of elements from list A not contained in list B
	int notContained;
	notContained = 0;

	list<string>::iterator itA;
	list<string>::iterator itB;
	
	itB = B.begin();
	itA = A.begin();
	
	bool contained;
	
	//Going through list A
	for (itA = A.begin(); itA != A.end(); itA++)
	{
		contained = false;
		
		
		while (*itA > *itB && itB != B.end())
		{
			
			itB++;
		}
			
		if (*itA == *itB)
		{
			contained = true;
		}

		if (contained == false)
		{
			notContained++;
		}


		
		
	}
	
	return notContained;
}


int
main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}
