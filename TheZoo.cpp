#include <iostream>
#include <jni.h>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

void GenerateData();
void AddAnimal();
void RemoveAnimal();
void LoadDataFromFile();
void SaveDataToFile();
void DisplayMenu();

struct animal {
	string trackNumber, name, type, subType, eggs, nurse;
};
vector<animal> animalList;

void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialisation options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }


     jvm->DestroyJavaVM();
     cin.get();
}

void AddAnimal()
{
	cout << endl << endl;

   string trackNumber, type, subType, name, eggs, nurse;
   bool valid = true;

   do { //loop until valid input
	   cout << "Enter the Track #: ";
	   cin >> trackNumber;
	   int temp;
	   try{
		   temp = stoi(trackNumber); // try to convert to integer
		   valid = true;
	   }
	   catch(exception) {
		   valid = false;
		   cout << "Enter a valid number! "; // user did not enter a number
	   }


	   if (valid == true) {
		   if(temp < 0) {
			   valid = false;
			   cout << "Enter a positive number! "; // user did not enter a positive number
		   }
		   else if(temp > 999999) {
			   cout << "Enter a number that is six digits or less! "; //user entered a number that was too large
			   valid = false;
		   }
		   else { // user entered a valid input
			   string tempString;

			   for(int i = trackNumber.length(); i < 6; i++ ) { //append zeros if number is less than 6 digits.
				   tempString += '0';
			   }
			   trackNumber = tempString + trackNumber;

			   bool found = false;
			   for(int i = 0; i < animalList.size(); i++) { //make sure the track# is unique
				   if(animalList[i].trackNumber == trackNumber)
					   found = true;
			   }
			   if (found == true) {
				   cout << "This track number already exists.  Please enter a unique track number! ";
				   valid = false;
			   }
		   }
	   }
   } while (valid == false);

   do{  //name
	   cout << "Enter the name: ";
	   cin >> name;

		if(name.length() > 15) {
			cout << "Enter a name that is less than 15 characters! ";
					valid = false;
		}
		else {
			valid = true;
		}
   } while (valid == false);

   do { //type
	   cout <<"Enter the type: ";
	   cin >> type;

	   if(type.length() > 15) {
		   cout << "Enter a type that is less than 15 characters! ";
		   	  	  valid = false;
	   }
	   else {
	   			valid = true;
	   }
   } while (valid == false);

   do { //subtype
  	   cout <<"Enter the Sub-type: ";
  	   cin >> subType;

  	   if(subType.length() > 15) {
  		   cout << "Enter a Sub-type that is less than 15 characters! ";
  		   	  	  valid = false;
  	   }
  	   else {
  	   			valid = true;
  	   }
     } while (valid == false);

   do { //eggs
	   cout << "Enter the number of eggs: ";
	   cin >> eggs;

	   try{
		   int tempEggs = stoi(eggs);
		   valid = true;

	   }
	   catch(exception) {
		   cout << "Enter a valid number! ";
		   valid = false;
	   }
   } while(valid == false);
   do { //nursing
	   cout << "Enter 1 if nursing 0 if not: ";
	   cin >> nurse;
	   try {
		   int tempNurse = stoi(nurse);
		   valid = true;
	   }
	   catch(exception) {
		   cout << "Enter a valid number! ";
		   valid = false;
	   }
	   if(valid == true) {
		   if(nurse != "0" && nurse != "1" ) {
			   cout << "Enter a valid option! ";
			   valid = false;
		   }
	   }
   } while (valid == false);
   cout << "Entered data: " << trackNumber <<  " " << name << " " << type
		   << " " << subType << " " << eggs << " " << nurse << "" << endl;

   string response;
   do{
	   cout << "Would you like to save this record? (Y/N): ";
	   cin >> response;
	   if(response == "Y" || response == "y") {
		   animal newAnimal; // create new instance of struct animal
		   newAnimal.trackNumber = trackNumber;
		   newAnimal.name = name;
		   newAnimal.type = type;
		   newAnimal.subType = subType;
		   newAnimal.eggs = eggs;
		   newAnimal.nurse = nurse;

		   animalList.push_back(newAnimal); //add new animal to the global vector

		   cout << "Record saved. ";
		   valid = true;
	   }
	   else if(response == "N" || response == "n") {
		   cout << "Record not saved. ";
		   valid = true;
	   }
	   else {
		   cout <<  "Enter a valid option! "; //user entered something besides y or n
		   valid = false;
	   }
   } while (valid == false);

	cout << endl << endl;


}

void RemoveAnimal()
{
	cout << endl << endl;

	cout <<"Available track numbers: ";
    for(int i=0;i<animalList.size();i++){
        cout << animalList[i].trackNumber << " ";
    }
    cout << endl;

	string option;
	bool valid = true;
	do {
		 cout << "Enter the track number you would like to remove, or C to cancel: ";
		 cin >> option;

		 if (option == "C" || option == "c") {
			 return;
		 }
		try{
			int temp = stoi(option); //test for integer
			valid = true;
		}
		catch(exception){
			valid = false;
			cout << "Please enter a valid number! ";
		}
		if(valid == true) {
			   int found = -1;
			   for(int i = 0; i < animalList.size(); i++) {
				   if(animalList[i].trackNumber == option) //search user input
					   found = i;
			   }
			   if(found != -1) {
				   animalList.erase(animalList.begin()+found);
				   cout << "Animal successfully deleted!";
				   valid = true;
			   }
			   else {
				   string tempString;

				   for(int i = option.length(); i < 6; i++ ) { //append zeros if number is less than 6 digits.
					   tempString += '0';
				   }
				   option = tempString + option;
				   for(int i = 0; i < animalList.size(); i++) { //search user input with zeros added.
					   if(animalList[i].trackNumber == option)
						   found = i;
				   }
				   if(found != -1) {
					   animalList.erase(animalList.begin()+found); // remove item from vector
					   valid = true;
					   cout << "Animal successfully deleted!";
				   }
				   else {
					   cout << "Not found. ";
					   valid = false;
				   }
			   }
		}
	} while (valid == false);
	cout << endl << endl;

}

void LoadDataFromFile()
{
	cout << endl << endl;

	string temp;
	vector<string> lineList;

	//column headers
	cout << "Track #:  ";
	cout << "Name:            ";
	cout << "Type:            ";
	cout << "Subtype:         ";
	cout << "Eggs:  ";
	cout << "Nursing: ";
	cout << endl;

	ifstream animalFile;
	animalFile.open("zoodata.txt");

	char line[200];
	while(animalFile.good()){ // add string to the vector for each line in file
		animalFile.getline(line, 200);
		lineList.push_back(line);
	}

	for (int i = 0; i < lineList.size() - 1; i++) {
		temp = lineList[i].substr(0, 6); //track#
		cout << temp << "    ";
		temp = lineList[i].substr(6, 15); //name
		cout << temp << "  ";
		temp = lineList[i].substr(21, 15); //type
		cout  << temp << "  ";
		temp = lineList[i].substr(36, 15); //subtype
		cout << temp << "  ";

		temp = "";
		int j = 51;

		while(!(isspace(lineList[i][j]))) { //since eggs doesn't have a set size we have to keep going until we find white space.
			temp += lineList[i][j]; //eggs
			j++;
		}
		cout << temp;
		int x = 7 - temp.length();
		for (int k = 0; k < x; ++k) {
			cout << " ";
		}

		j++;
		temp = lineList[i].substr(j, 1); //nurse
		if (temp == "0") {
			cout << "No";
		}

		else {
			cout << "Yes";
		}
		cout << endl;
	}

	animalFile.close();

	cout << endl << endl;
}
void SaveDataToFile()
{
	cout << endl << endl;

	string response;
	bool valid = true;

	do{
		cout << "Would you like to save your data? (Y/N)";
		cin >> response;
		if(response == "Y" || response == "y") {
			ofstream file;
			file.open("zoodata.txt");
			for(int i = 0; i < animalList.size(); i++) { //loops once per item in the vector
				file << animalList[i].trackNumber;
				file << animalList[i].name;
				for (int j = animalList[i].name.size(); j < 15; j++) { //ensures the field takes up 15 characters
					file << " ";
				}
				file << animalList[i].type;
				for (int j = animalList[i].type.size(); j < 15; j++) {
					file << " ";
				}
				file << animalList[i].subType;
				for (int j = animalList[i].subType.size(); j < 15; j++) {
					file << " ";
				}
				file << animalList[i].eggs << " ";
				file << animalList[i].nurse << endl;
			}
			cout << "Save successfully completed" << endl;
		}
		else if(response == "N" || response == "n") {
			return;
		}
		else {
			cout << "Choose a valid option! "; //user entered something besides y or n
		}
	} while(valid == false);
	cout << endl << endl;

}

void DisplayMenu()
{
	bool valid = true;
	string userOption;
	do {
		if (valid == false){
			cout << "Please enter a number between 1 and 6!!!!!!" << endl;
		}

		cout << "Select an option:" << endl;
		cout << "1: Generate Data" << endl;
		cout << "2: Display Animal Data" << endl;
		cout << "3: Add Record" << endl;
		cout << "4: Delete Record" << endl;
		cout << "5: Save Animal Data" << endl;
		cout << "6: Quit" << endl;


		cin >> userOption;

		int option;

		try{
			option = stoi(userOption); // try to convert user input to int
		}
		catch (exception){
			option = 0; //the switch will catch this as invalid input
		}

		switch (option) {
			case 1: {
				valid = true;
				GenerateData();
				break;
			}
			case 2: {
				valid = true;
				LoadDataFromFile();
				break;
			}
			case 3: {
				valid = true;
				AddAnimal();
				break;
			}
			case 4: {
				valid = true;
				RemoveAnimal();
				break;
			}
			case 5: {
				valid = true;
				SaveDataToFile();
				break;
			}
			case 6: {
				return;
			}
			default:
				valid = false;
		}
	} while(valid != true || userOption != "6"); //continue loop until user selects '6'
}

int main()
{
	DisplayMenu(); //replaced previous code so that we can call display menu.

	return 1;
}
