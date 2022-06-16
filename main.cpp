#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "AVL.h"
using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif		

int main(int argc, char* argv[]) {
	VS_MEM_CHECK	//implementing memory check

		if (argc < 3) {
			cerr << "Please provide name of input and output files";
			return 1;
		}
	cout << "Input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in) {
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	cout << "Output file: " << argv[2] << endl;
	ofstream out(argv[2]);
	if (!out) {
		in.close();
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}

	AVL<string> avlString;			//instantiations of BST objects with int, string, and copies of each
	AVL<string> avlStringCopy;
	AVL<int> avlInt;
	AVL<int> avlIntCopy;
	bool intVal = true;		//bool to determine if we are in int or string mode
	bool haveAdded = false;		//bool to determine if we have added to any tree yet

	for (string line; getline(in, line);) {		//parse through the file until the end
		string item1, stringItem;
		int intItem;
		if (line.size() == 0) continue;
		cout << endl << line;
		istringstream iss(line);
		iss >> item1;
		if (item1 == "INT") {		//if int is called, set the bool to int mode and mark that we have added 
			haveAdded = true;
			intVal = true;
			cout << " true";
		}
		else if (item1 == "STRING") {		//if string is called, set the bool to string mode by declaring false
			haveAdded = true;
			intVal = false;
			cout << " true";
		}
		else if (item1 == "add") {		//if add is called, check for which mode we are in, then add the node to the tree
			if (intVal == true) {
				iss >> intItem;
				if (avlInt.addNode(intItem) == true) {
					cout << " true";
				}
				else {
					cout << " false";
				}
				haveAdded = true;
			}
			else {
				iss >> stringItem;
				if (avlString.addNode(stringItem) == true) {
					cout << " true";
				}
				else {
					cout << " false";
				}
				haveAdded = true;
			}
		}
		else if (item1 == "print") {		//if print is called, check for which mode we are in, then call the toString for the respective tree
			if (haveAdded == true) {
				if (intVal == true) {
					cout << ":" << avlInt.toString();
				}
				else {
					cout << ":" << avlString.toString();
				}
			}
			else {
				cout << ": empty";
			}
		}
		else if (item1 == "find") {		//if find is called, check for which mode we are in, then call find on the respective object
			if (intVal == true) {
				iss >> intItem;
				if (avlInt.findValue(intItem) == true) {
					cout << " found";
				}
				else {
					cout << " not found";
				}
			}
			else {
				iss >> stringItem;
				if (avlString.findValue(stringItem) == true) {
					cout << " found";
				}
				else {
					cout << " not found";
				}
			}
		}
		else if (item1 == "size") {		//if size is called, check for which mode we are in and call for the size of the respective tree
			if (intVal == true) {
				cout << " " << avlInt.sizeTree();
			}
			else {
				cout << " " << avlString.sizeTree();
			}
		}
		else if (item1 == "clear") {		//if clear is called, check for which mode we are in and call clear for the respective tree
			if (intVal == true) {
				avlInt.clearTree();
			}
			else {
				avlString.clearTree();
			}
			cout << " true";
		}
		else if (item1 == "remove") {		//if remove is called, check for which mode we are in and call remove for the item in the respective tree
			if (intVal == true) {
				iss >> intItem;
				if (avlInt.findValue(intItem) == true) {
					avlInt.removeNode(intItem);
					cout << " true";
				}
				else {
					cout << " false";
				}
			}
			else {
				iss >> stringItem;
				if (avlString.findValue(stringItem) == true) {
					avlString.removeNode(stringItem);
					cout << " true";
				}
				else {
					cout << " false";
				}
			}
		}
	}

	in.close();
	return 0;
}
