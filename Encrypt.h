// Jonathan McElroy, Aaron Salinas
// encrypt.h

#ifndef ADD_H_GUARD
#define ADD_H_GUARD
#include <string>

using namespace std;
/*
	This class was created to hold the rotors and
	rotor settings for better collaboration between
	the asm encrypt/decrypt and the GUI
*/
class Encrypt{
	
	/*
		The plugboard, rotors and reflector are stored as private members in this class
		this is important because it allows the rotate rotor function to easily recieve
		the arguments.
	*/
	private:
		char plugboard[26];
		char rotor1[26];
		char rotor2[26];
		char rotor3[26];
		char reflector[26];
		
		int setting1,	//rotor 1 setting
		setting2,	//rotor 2 setting
		setting3;	//rotor 3 setting
		
 
			
	public:
		/*
			Name: Default Constructor
			Description: Initializes the Rotors,plugboard, and reflector 
			to their default settings
		*/
		Encrypt();		

		//These functions return the current settings of the rotors
		string getSetting1(){ return string(1, char(setting1+'A'));	}
		string getSetting2(){ return string(1, char(setting2+'A'));	}
		string getSetting3(){ return string(1, char(setting3+'A'));	}

		//These functions set the current settings of the rotors
		void setSetting1(char c);
		void setSetting2(char c);
		void setSetting3(char c);
		
		/*
			Name: EncryptString
			Description: This is a wrapper function that takes the 
			user's string converts it to a c_string and then calls
			the asmToLower and asmmain functions that encrypt the 
			string
			Arguments: string
		*/
		string encryptString(string);
		
		/*
			Name: setPlugboard
			Description: Allows the user to determine what they want the
			plugboard settings to be
			Arguments: char1 and char2 represent the two indexes to
			be switched in the plugboard
		*/
		int setPlugboard(char, char);		//set plugboard settings
		
		/*
			Name: unsetPlugboard
			Description: Allows the user to revert the plugboard to its
			previous state
			Arguments: char1 and char2 are the two indexes to revert
		*/
		void unsetPlugboard(char, char);	//unset plugboard settings

};


		void asmMain(char[], const char[], const char[], const char[], const char[], const char[], int&, int&, int&);
		void rotorUpdate(int&, int&, int&);
		void reflectStr(char[], int&);
		void asmToLower(char[]);

#endif
