#include "headers\Headers.hpp"
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
			double percent;
			if (input == "1") {
				cout << "Enter image file name: ";
				cin >> image;
				cout << "Enter config file name: ";
				cin >> config;

				cout << "Enter percent blackness needed (0.0 - 1.0): ";
				cin >> percent;

				//New scan
				AnalyzeImage analyze(image, config, percent);
				vector<int> results = analyze.getAnswers();
				cout << "Results: " << endl;
				for (unsigned int i = 0; i < results.size(); i++) {
					cout << results[i] << endl;
				}
				cout << endl;

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