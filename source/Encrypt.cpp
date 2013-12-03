/*
	Authors: Jonathan McElroy, Aaron Salinas, Elise Brown
	FileName: Encrypt.cpp
	Description: The source file that implements the
	methods of the encrypt class from encrypt.h
	
	This File also has the implementation of our asmMain function which
	is our assembly language encrypt and decrypt function that is
	the main base for the Enigma encryption.  THe RotorUpdate function
	is also included in this file.  Rotor update is an assembly function
	that shifts the rotors according to the user's rotor settings. The asmToLower 
	function converts the user's string to all lowercase letters before encryption
	this eliminates the problem of having an uppercase letter encrypt to its 
	lowercase counterpart.
	
*/
#include "Encrypt.h"
#include <string>
#include <cstdlib>

using namespace std;


/****************************************
	Default Constructor
*****************************************/
Encrypt::Encrypt(){

	//Assign Plugboard default values
	for(int i = 0; i < 26; i++)
		plugboard[i] = i;


	//Assign Rotor 1 default values
	rotor1[0] = 7;
	rotor1[1] = 3;
	rotor1[2] = 23;
	rotor1[3] = 8;
	rotor1[4] = 25;
	rotor1[5] = 21;
	rotor1[6] = 4;
	rotor1[7] = 22;
	rotor1[8] = 6;
	rotor1[9] = 14;
	rotor1[10] = 10;
	rotor1[11] = 16;
	rotor1[12] = 19;
	rotor1[13] = 9;
	rotor1[14] = 12;
	rotor1[15] = 18;
	rotor1[16] = 20;
	rotor1[17] = 17;
	rotor1[18] = 1;
	rotor1[19] = 0;
	rotor1[20] = 15;
	rotor1[21] = 24;
	rotor1[22] = 2;
	rotor1[23] = 11;
	rotor1[24] = 13;
	rotor1[25] = 5;
	
	//Assign Rotor 2 default values
	rotor2[0] = 25;
	rotor2[1] = 19;
	rotor2[2] = 20;
	rotor2[3] = 18;
	rotor2[4] = 14;
	rotor2[5] = 4;
	rotor2[6] = 9;
	rotor2[7] = 23;
	rotor2[8] = 24;
	rotor2[9] = 8;
	rotor2[10] = 15;
	rotor2[11] = 13;
	rotor2[12] = 21;
	rotor2[13] = 2;
	rotor2[14] = 7;
	rotor2[15] = 3;
	rotor2[16] = 16;
	rotor2[17] = 22;
	rotor2[18] = 17;
	rotor2[19] = 12;
	rotor2[20] = 1;
	rotor2[21] = 0;
	rotor2[22] = 10;
	rotor2[23] = 6;
	rotor2[24] = 11;
	rotor2[25] = 5;

	//Assign Rotor 3 default values
	rotor3[0] = 23;
	rotor3[1] = 12;
	rotor3[2] = 21;
	rotor3[3] = 19;
	rotor3[4] = 10;
	rotor3[5] = 22;
	rotor3[6] = 8;
	rotor3[7] = 5;
	rotor3[8] = 15;
	rotor3[9] = 16;
	rotor3[10] = 17;
	rotor3[11] = 6;
	rotor3[12] = 2;
	rotor3[13] = 3;
	rotor3[14] = 1;
	rotor3[15] = 14;
	rotor3[16] = 7;
	rotor3[17] = 25;
	rotor3[18] = 9;
	rotor3[19] = 24;
	rotor3[20] = 18;
	rotor3[21] = 13;
	rotor3[22] = 20;
	rotor3[23] = 11;
	rotor3[24] = 4;
	rotor3[25] = 0;

	//Assign reflector default values
	reflector[0] = 14;
	reflector[1] = 12;
	reflector[2] = 23;
	reflector[3] = 4;
	reflector[4] = 3;
	reflector[5] = 11;
	reflector[6] = 24;
	reflector[7] = 17;
	reflector[8] = 25;
	reflector[9] = 16;
	reflector[10] = 19;
	reflector[11] = 5;
	reflector[12] = 1;
	reflector[13] = 15;
	reflector[14] = 0;
	reflector[15] = 13;
	reflector[16] = 9;
	reflector[17] = 7;
	reflector[18] = 21;
	reflector[19] = 10;
	reflector[20] = 22;
	reflector[21] = 18;
	reflector[22] = 20;
	reflector[23] = 2;
	reflector[24] = 6;
	reflector[25] = 8;
	
	//Assign default rotor settings
	setting1 = 0;
	setting2 = 0;
	setting3 = 0;

}


//These functions set the current settings of the rotors
void Encrypt::setSetting1(char c){
	int i;
	i = c - 'A';	//Convert from ASCII
	setting1 = i;	//Assign settings
}

void Encrypt::setSetting2(char c){
	int i;
	i = c - 'A'; 	//Convert from ASCII
	setting2 = i;	//Assign settings
}

void Encrypt::setSetting3(char c){
	int i;
	i = c - 'A'; 	//Convert from ASCII
	setting3 = i;	//Assign settings
}



/***************************************
	encrypt string
	This function calls the asm function
	to encrypt a string
***************************************/
string Encrypt::encryptString(string s){

	char *encryptString;		//create new character array based on original
	
	encryptString = new char[(s.size() + 1)];	// create new char array 
	strcpy(encryptString, s.c_str());			// copy original into new string
	asmToLower(encryptString);						// set lowercase default

	asmMain(encryptString, plugboard, rotor1, rotor2, rotor3, reflector, setting1, setting2, setting3);



	return string(encryptString);
}


int Encrypt::setPlugboard(char ch1, char ch2){
	int n = 0;
	int index1, index2;
	
	asmToLower(&ch1);	//change case of character
	asmToLower(&ch1);	//change case of character
	
	index1 = ch1 - 'a';	//assign corresponding index
	index2 = ch2 - 'a';
	
	//store characters in 4 bytes
	n = plugboard[index1] + 'a';	// place first character in n (low bits)
	n = n << 8;						// shift first character over (high bits)
	n += plugboard[index2] + 'a';	// place second character in low bits
	
	//swap plugboard elements based on plugboard settings
	swap(plugboard[index1], plugboard[plugboard[index1]]);

	swap(plugboard[index2], plugboard[plugboard[index2]]);

	swap(plugboard[index1], plugboard[index2]);

	return n;
}

void Encrypt::unsetPlugboard(char ch1, char ch2){

	int index;
	
	asmToLower(&ch1);
	asmToLower(&ch2);
		
	index = ch1 - 'a';		//Convert ASCII to index
	plugboard[index] = index;	//reassign default index value

	index = ch2 - 'a';		//Convert ASCII to index
	plugboard[index] = index;	//reassign default index value

}

/**********************************************
	asmMain Function
	This function encrypts a string
Function Arguments:
char[]	 : character array to encrypt (+8)
const char[]: Plugboard (+12)
const char[]: Rotor 1 array (+16)
const char[]: Rotor 2 array (+20)
const char[]: Rotor 3 array (+24)
const char[]: Reflector (+28)
int	 : Rotor 1 Setting (+32)
int	 : Rotor 2 Setting (+36)
int	 : Rotor 3 Setting (+40)
**********************************************/
void __declspec(naked) asmMain(char[], const char[], const char[], const char[], const char[], const char[], int&, int&, int&){
__asm{
			push ebp	 //establish stack frame
			mov ebp, esp	 //move the stack pointer to the base pointer
			push eax	 //store eax on stack
			push ebx	 //store ebx on stack
			push ecx	 //store ecx on stack
			push edx	 //store edx on stack

			//clear registers for use
			xor eax, eax	  
			xor ebx, ebx
			xor ecx, ecx
			xor edx, edx

			sub esp, 4	 //local variable


			mov ebx, [ebp+8]	 // get the char array address
			TOP:	 mov al, BYTE PTR[ebx]	 // get the current character

			cmp al, '\0'	 // if the first char is NULL, finish
			je DONE

			cmp al, ' '
			jne ENCRYPT
			inc ebx
			jmp top

			cmp al, 'z'	 // if the char is greater than 'z',
			jng ENCRYPT	 // continue
			inc ebx
			jmp top

			cmp al, 'a'		// if the char is less than 'a',
			jnl ENCRYPT		// continue
			inc ebx
			jmp top


ENCRYPT:	sub al, 'a'	 // get the index in the alphabet of the letter
			mov edx, [ebp+12]	 // get the address of the plugboard
			mov al, [edx+eax]	 // move the encryption of the letter into al

			mov edx, [ebp+16]	 // get the address of the first rotor
			mov ecx, [ebp+32]	 // get rotor setting assign to ecx
			mov ecx, DWORD PTR[ecx]	 // assign offset from current rotor 1 setting
			add ecx, eax
			cmp ecx, 26
			jl ENCRYPT1
			sub ecx, 26
ENCRYPT1:	mov al, [edx+ecx]	 // move the encryption of the letter into al

			mov edx, [ebp+20]	 // get the address of the second rotor
			mov ecx, [ebp+36]	 // get rotor setting assign to ecx
			mov ecx, DWORD PTR[ecx]	 // assign offset from current rotor 1 setting
			add ecx, eax
			cmp ecx, 26
			jl ENCRYPT2
			sub ecx, 26
ENCRYPT2:	mov al, [edx+ecx]	 // move the encryption of the letter into al


			mov edx, [ebp+24]	 // get the address of the Third rotor
			mov ecx, [ebp+40]	 // get rotor setting assign to ecx
			mov ecx, DWORD PTR[ecx]	 // assign offset from current rotor 1 setting
			add ecx, eax
			cmp ecx, 26
			jl ENCRYPT3
			sub ecx, 26
ENCRYPT3:	mov al, [edx+ecx]	 // move the encryption of the letter into al



REFLECT:	mov edx, [ebp+28]	 // get the address of the reflector
			mov al, [edx+eax]	 // Move the encryption of the letter into al

REVERSE:	mov edx,[ebp+24]	 // get address of the third rotor	
			mov [esp], eax	 // copy current index into local variable
			push esp	 // push current index (local Variable)
			push edx	 // push address to rotor 3
			call reflectStr	 // reverse encrypt the character with the 3rd rotor
			add esp, 8	 // clean up stack
			mov ecx,[ebp+40]	 // get rotor setting 3	
			mov eax, [esp]	 // copy next index into eax
			sub eax, DWORD PTR[ecx]
			cmp eax, 0
			jge REVERSE3
			add eax, 26
REVERSE3:	

			mov edx,[ebp+20]	 // get address of the second rotor
			mov [esp], eax	 // copy current index to local variable
			push esp	 // push current index (local variable)
			push edx	 // push address to rotor 2
			call reflectStr	 // reverse encrypt the character with the 2nd rotor
			add esp, 8	 // clean up stack
			mov eax, [esp]	 // copy next index to eax
			mov ecx,[ebp+36]	 // get rotor setting 2
			sub eax, DWORD PTR[ecx]
			cmp eax, 0
			jge REVERSE2
			add eax, 26
REVERSE2:	

			mov edx,[ebp+16]	 // get address of the first rotor
			mov [esp], eax	 // copy current index to local variable
			push esp	 // push current index
			push edx	 // push address to rotor 1
			call reflectStr	 // reverse encrypt the character with the 1st rotor
			add esp, 8
			mov eax, [esp]
			mov ecx,[ebp+32]	 // get rotor setting 1
			sub eax, DWORD PTR[ecx]
			cmp eax, 0
			jge REVERSE1
			add eax, 26
REVERSE1:	

			//plugboard
			mov edx,[ebp+12]	 // get address of the plugboard
			mov [esp], eax	 // copy current index to local variable
			push esp	 // push current index
			push edx	 // push address to rotor 1
			call reflectStr	 // reverse encrypt the character with the 1st rotor
			add esp, 8
			mov eax, [esp]

ROTATE:		push [ebp+40]	 // push rotor setting 3
			push [ebp+36]	 // push rotor setiing 2
			push [ebp+32]	 // push rotor setting 1
			call rotorUpdate	 // call rotor update fuction
			add esp, 12	 // clean up stack

CONTINUE:	add al, 'a'
			mov BYTE PTR[ebx], al
			inc ebx

			jmp TOP



DONE:		sub esp, 12	//mov esp to pushed registers
			pop edx	 //restore edx
			pop ecx	 //restore ecx
			pop ebx	 //restore ebx
			pop eax	 //restore eax
			mov esp, ebp
			pop ebp
			ret

}

}

/**********************************************
	rotorUpdate function
	This function updates the settings of the
	rotors
**********************************************/

void __declspec(naked) rotorUpdate(int&, int&, int&){

	__asm{
				push ebp	 //establish stack frame
				mov ebp, esp	//move the stack pointer to the base pointer
				push eax	 //store eax on stack
				push ebx	 //store ebx on stack
				push ecx	 //store ecx on stack
				pushfd	 //store EFLAGS

				//zero out all of the registers
		SETUP:	mov eax, DWORD PTR[ebp+8]	// eax->rotor1 setting
				mov ebx, DWORD PTR[ebp+12]	// ebx->rotor2 setting
				mov ecx, DWORD PTR[ebp+16]	// ecx->rotor3 setting

		TOP:	

				/*this set of code updates the current rotor settings as each encrypt letter
				goes through one entire cycle*/

		SHIFT:	

				cmp [eax], 26	//counter < 26; Rotor setting 1
				jl NEXT	 //jmp if counter < 26

				and [eax], 0	 //reset counter to 0; Rotor setting 1
				inc [ebx]	 //update second rotor; Rotor setting 2
				cmp [ebx], 26	//R2 counter < 26?; Rotor setting 2
				jl NEXT	 //jmp if counter < 26

				and [ebx], 0	 //reset R2 counter; Rotor setting 2
				inc [ecx]	 //incriment R3 counter; Rotor setting 
				cmp [ecx], 26	//R3 counter < 26?; Rotor setting 3
				jl NEXT

				and [ecx], 0	 //reset R3 counter

		NEXT:	inc [eax]	//update first rotor counter


		DONE:	popfd
				pop ecx	 //restore ecx
				pop ebx	 //restore ebx
				pop eax	 //restore eax
				mov esp, ebp
				pop ebp
				ret
	}

}


// The value in al needs to be changed so we are not pushing eax in this function
// instead we are going to directly manipulate eax
void __declspec(naked) reflectStr(char[], int&){
	__asm{

		START:
				push ebp	 //establish stackframe
				mov  ebp,esp	
				push eax
				push edi	 //push edi, store rotor array
				push ecx	 //push ecx, counter

				mov edi, [ebp+8]	//edi->array
				mov ecx, 26	 //initiallize counter

		TOP:	
				repne scasb	 //search for key in rotor array
				mov eax, [ebp+12]
				mov   [eax], cl	 //copy counter (index) into next index
				neg   [eax]	
				add   [eax], 26
				dec	  [eax]

		DONE:	
				pop ecx	 //restore stack frame
				pop edi
				pop eax
				mov esp,ebp
				pop ebp
				ret
	}	
}


/******************************************************************
Function Argument: 
char[]: character array that is going to be
modified, lower all character cases
Function Description:
asm function takes a character array and changes the case
of any uppercase alphabet letters to lower case. Ignores
any non-alphabetic characters
*******************************************************************/
void __declspec(naked) asmToLower(char[]) {
__asm {
     START:  push ebp        // store the base pointer to the stack
             mov ebp, esp    // move the stack pointer to the base pointer
             push ebx        // store ebx on stack

             mov ebx, [ebp+8]    // get the char array address

             cmp BYTE PTR[ebx], '\0' // if the first char is NULL, finish
             je DONE

           
     TOP:    cmp BYTE PTR[ebx], 'Z'  // if the char is greater than 'Z',
                                     // continue
             jg CONTINUE
             cmp BYTE PTR[ebx], 'A'  // if the char is less than 'A',
                                     // continue
             jl CONTINUE

     UPPERTEST:
             or BYTE PTR[ebx], 00100000b  // add the diference between lower and
                                     // upper to char
     CONTINUE:
             inc ebx                 // increment the char index
             cmp BYTE PTR[ebx], '\0' // if the char is not NULL, loop
             jne TOP

     DONE:   pop ebx // get the ebx back
             pop ebp // get the ebp back
             ret     // return control to the calling function
}
}





