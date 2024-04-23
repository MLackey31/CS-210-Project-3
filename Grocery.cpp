#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;
/*Function call by callProcedure("xxxxxxx"")*/
/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}
/*Function call by callIntFunc("xxxxxxx"")*/


int CallFuncOneParam(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Python Interpreter 
	Py_Initialize();
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load Module
	pModule = PyImport_Import(pName);
	pDict = PyModule_GetDict(pModule);
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//Print
	Py_DECREF(pValue);
	Py_DECREF(pModule);
	Py_DECREF(pName);
	//Python Interpreter
	Py_Finalize();


	delete[] procname;
	delete[] paramval;

	return _PyLong_AsInt(presult);
}

// Verify User Input
void validateUserInput(int& userInput) {

	while (!(cin >> userInput)) {
		cin.clear();
		cin.ignore(123, '\n');
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "\t\t\t" << "UNKNOWN ENTRY!!! PLEASE TRY AGAIN." << endl;
		cout << "\t\t" << "PLEASE SELECT AN OPTION USING NUMBERS 1 THROUGH 4" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "1: DISPLAY A LIST OF ALL PRODUCTS PURCHASED AND THE QUANTITIES." << endl;
		cout << "2: DISPLAY THE TOTAL QUANTITY PURCHASED OF A SPECIFIC ITEM" << endl;
		cout << "3: DISPLAY HISTOGRAM OF ITEMS PURCHASED" << endl;
		cout << "4: EXIT" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << endl;

	}

}

//Get User Input 
void getUserInput(int& userInput) {

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "\t\t\t" << "WELCOME TO THE CORNER GROCER" << endl;
	cout << "\t\t\t" << "  PLEASE SELECT AN OPTION" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "1: DISPLAY A LIST OF ALL PRODUCTS PURCHASED AND THE QUANTITIES." << endl;
	cout << "2: DISPLAY THE TOTAL QUANTITY PURCHASED OF A SPECIFIC ITEM" << endl;
	cout << "3: DISPLAY HISTOGRAM OF ITEMS PURCHASED" << endl;
	cout << "4: EXIT" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << endl;
	validateUserInput(userInput);
	while (userInput <= 0 && userInput > 4) {
		'4'
			getUserInput(userInput);
	}

}

//Gets input to search from list
void userValue(string& userVal) {
	cout << "Enter an item to view the frequency it was purchased in a day:" << endl; //Print
	while (!(cin >> userVal)) {
		cin.clear();
		cin.ignore(123, '\n');
		cout << "Enter an item to view the frequency it was purchased in a day:" << endl;
	}

}

int main()
{
	//Vari
	int userInput = 0;
	ifstream inFS;
	string item;
	int quantity;

	//Waits for 4 if not exits
	while (userInput != 4) {

		getUserInput(userInput); //Welcome Display
		string userVal;

		if (userInput == 1) {
			CallProcedure("printItemCount");//Python To Print Item Count
		}
		else if (userInput == 2) {
			userValue(userVal);
			cout << endl;
			cout << "The quantity of " << userVal << " sold today is " << CallFuncOneParam("printCount", userVal) << "." << endl;
			cout << endl;
		}
		else if (userInput == 3) {
			CallFuncOneParam("createFile", "frequency.dat");
			inFS.open("frequency.dat"); //Opens frequency.dat
			if (!inFS.is_open()) {
				cout << "Could not open the frequency.dat file." << endl;
				break;
			}
			cout << endl;
			while (!inFS.eof()) {
				inFS >> item;
				inFS >> quantity;
				cout << item << ": ";
				for (int i = 0; i < quantity; ++i) {
					cout << "*";
				}
				cout << endl;
			}
			cout << endl;
			inFS.close(); //Ends File
		}

	}

}