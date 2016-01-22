#include "Headers.h"

using namespace std;

int main()
{
	//Command Line Demo
	string input = "";
	while (input != "q" && input != "quit" && input != "0") {
		
		//Menu
		//1. New Scan
		//2. Current results
		//3. Load Template
		//0. Quit (q or quit)
		cout << "Welcome to ZopperScan's Command Line Demonstration" << endl;
		cout << "1. New Scan" << endl;
		cout << "0. Quit (q or quit)" << endl;

		cin >> input;

		if (input != "q" && input != "quit") {

			string image, config;
			int thres;
			double percent;
			if (input == "1") {
				cout << "Enter image file name: ";
				cin >> image;
				cout << "Enter config file name: ";
				cin >> config;

				//New scan
				AnalyzeImage analyze(image, config);

				cout << "Enter blackness threshold (0-255): ";
				cin >> thres;
				cout << "Enter percent blackness needed (0.0 - 1.0): ";
				cin >> percent;

				analyze.calculate(thres, percent);
				vector<bool> results = analyze.getResults();
				vector<double> blacks = analyze.getBlacks();
				int n;
				cout << "Enter line size: ";
				cin >> n;
				cout << "Results: " << endl;
				cout << (0 / n) + 1 << ": ";
				for (unsigned int i = 0, j = 0; i < results.size(); i++, j++) {
					if (j == n) {
						cout << endl << (i / n) + 1 << ": ";
						j = 0;
					}
					cout << results[i] << " ";
				}
				cout << endl;

				cout << "Print results to file? (Y/N) ";
				cin >> input;

				if (input == "Y" || input == "y") {
					cout << "Enter filename: ";
					cin >> input;
					analyze.writeResults(input, n);
				}

				cout << "Press any key to continue" << endl;
				getline(cin, input);
			}
			else {
				cerr << "Invalid input." << endl;
				return 1;
			}
			
		}
		else {
			return 0;
		}
	}
	
	return 0;
}