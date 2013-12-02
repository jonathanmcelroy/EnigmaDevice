#ifndef ADD_H_GUARD
#define ADD_H_GUARD
#include <string>

using namespace std;

class Encrypt{

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
		Encrypt();		//Default Constructor

		//These functions return the current settings of the rotors
		string getSetting1(){ return string(1, char(setting1+'A'));	}
		string getSetting2(){ return string(1, char(setting2+'A'));	}
		string getSetting3(){ return string(1, char(setting3+'A'));	}

		//These functions set the current settings of the rotors
		void setSetting1(char c);
		void setSetting2(char c);
		void setSetting3(char c);

		string encryptString(string);

		int setPlugboard(char, char);		//set plugboard settings
		void unsetPlugboard(char, char);	//unset plugboard settings

};


		void asmMain(char[], const char[], const char[], const char[], const char[], const char[], int&, int&, int&);
		void rotorUpdate(int&, int&, int&);
		void reflectStr(char[], int&);
		void asmToLower(char[]);

#endif