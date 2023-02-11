#include <iostream>
#include "BST.h"
#include<string>
#include<fstream>

using namespace std;

int main() {

	//ignore BST.cpp (all methods defined in BST.h)

	BST tree;

	string tstCase;

	string firstInputFile; //use this name in ifstream

	string secondActionFile; //use this name in 2nd ifstream

	string outFileName; //use this name in output file ofstream

	ifstream initialFile; //name comes from firstInputFile string
	
	ifstream operationFile; //name comes from secondActionFile string

	ofstream outputFile; //Output file

	int number;

	//1-Dimensional Array!
	int operAmnt[4] = { 0, 0, 0, 0 }; //at index 0 = total Creation, at index 1= total insert, at index 2= total search, at index 3= total delete
	
	int comparisons; //store amount of comparisons/operations for each action
	 

	cout << "Hello! Please Enter test case name:" << endl;

	getline(cin, tstCase);

	cout << "Enter 1st input file name" << endl;

	cin >> firstInputFile;

	firstInputFile = firstInputFile + ".txt";

	cout << "Enter 2nd input (Action) file name" << endl;

	cin >> secondActionFile;

	secondActionFile = secondActionFile + ".txt";

	cout << "Enter output file name" << endl;

	cin >> outFileName;

	outFileName = outFileName + ".txt";

	
	
	initialFile.open(firstInputFile); //open input file //IT WORKS FINALLY
	outputFile.open(outFileName); //open output file
	
	if (!initialFile.is_open()) {

		 //terminate program if file fails to open

		cout << "Unable to open File" << endl;

		return 1;
	}
	
	if (!outputFile.is_open()) {
	
		//terminate program if file fails to open

		cout << "Unable to open output File" << endl;

		return 1;
	
	}

	//check if file is empty
	if (initialFile.peek() == EOF) { // IT WORKS :) //works for output file

		cout << "Empty File. Tree is empty" << endl;
		outputFile << "Empty File. Tree is empty" << endl;

	}
	else { //iterate each number in the initial file into the tree
	
		while (initialFile >> number) {
			comparisons = 0;

			cout << "Insert " << number << endl<<endl;
			outputFile << "Insert " << number << endl<<endl;

			tree.insert(number, comparisons);
			comparisons += 1; //ADD 1 TO COMPARISON TO ACCOUNT FOR INSERT ACTION (NOT JUST COMPARISON)

			tree.print(outputFile);
			cout << endl;
			cout << "Tree Height: " << tree.height() << endl;
			cout << "Comparisons/operations to insert " << number <<": " << comparisons;
			cout << endl<<endl;
			//print to outputfile
			outputFile << endl;
			outputFile<< "Tree Height: " << tree.height() << endl;
			outputFile << "Comparisons/operations to insert " << number << ": " << comparisons;
			outputFile << endl << endl;
			operAmnt[0] += comparisons;    //+= to calculate total comparisons for Tree Creation
		}
		
	}
	 //Done with first input file now close it
	initialFile.close();

	cout << endl<< "NOW ONTO THE OPERATION FILE :)" << endl<<endl;
	outputFile <<endl<< "NOW ONTO THE OPERATION FILE :)" << endl << endl; //to outputfile
	//Now Open 2nd input(action) file 

	operationFile.open(secondActionFile);

	if (!operationFile.is_open()) {

		//terminate program if file fails to open

		cout << "Unable to open File" << endl;

		return 1;
	}

	//Declare char variable that will hold actions and int that will hold numbers in operation file
	char Action;
	int ActionNum;
	
	//Check if operation(action) File is empty
	if (operationFile.peek() == EOF) { 

		cout << "Empty Action File. No actions will be performed" << endl;
		outputFile<< "Empty Action File. No actions will be performed" << endl;
	}
	else {
		while (operationFile >> Action >> ActionNum) { //CONTINUE HEREEEEEEEEE!!!!!!!
		
			switch (Action) {
			
			case 'S':
				comparisons = 0;
				cout << "Searching for " << ActionNum << endl<<endl;
				outputFile << "Searching for " << ActionNum << endl << endl;

				tree.print(outputFile);

				if (tree.search(ActionNum, comparisons)) {
				
					cout<< ActionNum<< " Found!"<<endl; 
					outputFile << ActionNum << " Found!" << endl;
				}
				else {
				
					cout << ActionNum << " Not Found!" << endl;
					outputFile << ActionNum << " Not Found!" << endl;
				}
				
				cout << "Tree Height: " << tree.height()<<endl;
				cout << "Comparisons/operations to search " << ActionNum << ": " << comparisons << endl<<endl;
				//output
				outputFile << "Tree Height: " << tree.height() << endl;
				outputFile << "Comparisons/operations to search " << ActionNum << ": " << comparisons << endl << endl;
				operAmnt[2] += comparisons; //index 2 = search
				break;
			
			case 'I':
				//reset comparisons integer
				comparisons = 0;

				cout << "Inserting " << ActionNum << endl<<endl;
				outputFile << "Inserting " << ActionNum << endl<<endl;

				tree.insert(ActionNum, comparisons);
				comparisons += 1; //ADD 1 TO COMPARISON TO ACCOUNT FOR INSERT ACTION (NOT JUST THE COMPARISONS DONE)

				tree.print(outputFile);
				cout << "Tree Height: " << tree.height()<<endl;
				cout << "Comparisons/operations to insert " << ActionNum << ": " << comparisons<<endl<<endl;
				//output
				outputFile << "Tree Height: " << tree.height() << endl;
				outputFile << "Comparisons/operations to insert " << ActionNum << ": " << comparisons << endl << endl;

				operAmnt[1] += comparisons; //index 1 = insert
				break;

			case 'D':
				comparisons = 0;
				int searchcheck; //to use in search, NOT IMPORTANT, JUST MADE IT SO I CAN CALL SEARCH
				cout << "Deleting " << ActionNum << endl<<endl;
				outputFile << "Deleting " << ActionNum << endl<<endl;

				//check if number is in tree (to account for actual delete action since my method doesnt increment if something is deleted, it just counts comparisons)
				if (tree.search(ActionNum, searchcheck)) { 
					comparisons += 1; //SEARCH FOR THE NUMBER, IF ITS IN TREE, ADD 1 TO DELETE COMPARISON COUNT TO ACCOUNT FOR THE ACTUAL DELETE ACTION
				}

				tree.deleteItem(ActionNum, comparisons);

				tree.print(outputFile);
				cout << "Tree Height: " << tree.height()<<endl;
				cout << "Comparisons/operations to delete " << ActionNum << ": " << comparisons << endl<<endl;
				//output
				outputFile << "Tree Height: " << tree.height() << endl;
				outputFile << "Comparisons/operations to delete " << ActionNum << ": " << comparisons << endl << endl;

				operAmnt[3] += comparisons; //index 3 = delete
				break;

			default:

				cout << "Invalid Action Code" << endl<<endl;
				outputFile << "Invalid Action Code" << endl << endl;
				

			}
			

		
		}
		
	
	
	}

	//then close the operationFile
	operationFile.close();

	//PRINT OUT RESULTS IN A SMALL TABLE

	cout << tstCase << endl;
	cout << "Operation/Comparison Count!" << endl<<endl;
	cout << "Creation\t" << operAmnt[0]<<endl;
	cout << "Search\t\t" << operAmnt[2]<<endl;
	cout << "Insert\t\t" << operAmnt[1] << endl;
	cout << "Delete\t\t" << operAmnt[3] << endl<<endl;
	cout << "Total\t\t" << operAmnt[0] + operAmnt[1] + operAmnt[2] + operAmnt[3] << endl;


	//PRINT AGAIN TO OUTPUT FILE!!!!
	outputFile << tstCase << endl;
	outputFile << "Operation/Comparison Count!" << endl << endl;
	outputFile << "Creation\t" << operAmnt[0] << endl;
	outputFile << "Search\t\t" << operAmnt[2] << endl;
	outputFile << "Insert\t\t" << operAmnt[1] << endl;
	outputFile << "Delete\t\t" << operAmnt[3] << endl<<endl;
	outputFile << "Total\t\t" << operAmnt[0] + operAmnt[1] + operAmnt[2] + operAmnt[3] << endl;

	/* SAVE CODE FOR LATER!!
		cout << boolalpha<< tree.search(10);
		the boolalpha changes the 1 to be true and 0 to be false!!!


	*/
	return 0;
}