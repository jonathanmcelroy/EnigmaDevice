#include <iostream>
#include <cstring>
#include <string>

using namespace std;

/*
* Arguments:
*   char[] : string to encrypt, ending with a NULL char
*   char[] : string describing the plugboard configuration
*   char[] : string describing rotor 1's configuration
*   int    : index to start from
*   char[] : string describing rotor 2's configuration
*   int    : index to start from
*   char[] : string describing rotor 3's configuration
*   int    : index to start from
*   char[] : string describing the reflectors configuration
*/
void __declspec(naked) encryptStr(char[], char[], char[], int, char[], int, char[], int, char[]) {
  __asm {
    START:  push ebp                // store the base pointer to the stack
            mov ebp, esp            // move the stack pointer to the base pointer
              
            push eax                // store eax on stack
            push ebx                // store ebx on stack
            push ecx                // store ecx on stack
            push edx                // store edx on stack

            mov ebx, [ebp+8]        // get the char array address
            mov al, BYTE PTR[ebx]   // get the current character
            xor eax, eax            //clear out eax

            cmp al, '\0'            // if the first char is NULL, finish
            je DONE

    TOP:    cmp al, 'z'             // if the char is greater than 'z',
                                    // continue
            jg CONTINUE

            cmp al, 'a'             // if the char is less than 'a',
                                    // continue
            jl CONTINUE

    ENCRPTLP:
            sub al, 'a'             // get the index in the alphabet of the letter
            mov edx, [ebp+12]       // get the address of the plugboard

            mov al, [edx+eax]       // move the encryption of the letter into al
            mov edx, [ebp+16]       // get the address of the first rotor
            mov al, [edx+eax]       // move the encryption of the letter into al
            mov edx, [ebp+20]       // get the address of the second rotor
            mov al, [edx+eax]       // move the encryption of the letter into al
            mov edx, [ebp+24]       // get the address of the third rotor
            mov al, [edx+eax]       // move the encryption of the letter into al
            mov edx, [ebp+28]       // get the address of the reflector
            mov al, [edx+eax]       // move the encryption of the letter into al

              /*
                  ENCRPTLP:           char = plugboard[char]
              //                      char = rotor1[char]
              //                      char = rotor2[char]
              //                      char = rotor3[char]
              //                      char = reflection[char]
              //                      push char
              //                      push rotor3 ptr
              //                      call reflect_encrypt
              //                      add ESP, 8
              //                      push char (eax)
              //                      push rotor2 ptr
              //                      call reflect_encrypt
              //                      add ESP, 8
              //                      push char (eax)
              //                      push rotor1 ptr
              //                      call reflect_encrypt
              //                      add ESP, 8
              //                      change letter in string[index] to char
              //                      rotate rotors

              */

    CONTINUE:
            mov BYTE PTR[ebx], al
            inc ebx                 // increment the char index
            mov al, BYTE PTR[ebx]   // get the current character
            cmp BYTE PTR[ebx], '\0' // if the char is not NULL, loop
            jne TOP

    DONE:   pop edx                 // get the ebx back
            pop ecx
            pop ebx
            pop eax

            mov esp,ebp
            pop ebp                 // get the ebp back
            ret                     // return control to the calling function

  }

}

/* 
* Arguments:
*	char  : character to reflect encrypt
*	char[]: character array to use
*/
void __declspec(naked) reflect_encrypt(char&, char[]) {
	__asm {
		START:	push	ebp			// set the stack frame
				mov		ebp, esp
		ret
	}
}

void __declspec(naked) toLower(char[]) {
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

int main1() {


  char plugboard[26];
  char rotor1[26];
  char rotor2[26];
  char rotor3[26];
  char reflector[26];
  for (int i=0; i<26; i++) {
      plugboard[i] = i;
      rotor1[i] = i;
      rotor2[i] = i;
      rotor3[i] = i;
      reflector[i] = i;
  }

  string str;
  cout << "String: " << endl;
  getline(cin, str);

  char* c_str = new char [str.size() + 1];
  strcpy(c_str, str.c_str());

  toLower(c_str);
  encryptStr(c_str, plugboard, rotor1, 0, rotor2, 0, rotor3, 0, reflector);

  return 0;
}