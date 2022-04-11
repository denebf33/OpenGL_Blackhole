// Support Code written by Michael D. Shah
// Last Updated: 1/21/17
// Please do not redistribute without asking permission.

// Functionality that we created
#include "SDLGraphicsProgram.hpp"
#include <iostream>
int main(int argc, char** argv){
	// Warn the user they need to specify at least one argument
    // We detect this by checking the size of the argument count (argc)

    // The first or 0th agument is the program name
    // Now I'll convert the filepath to a string, and you can use
    // as needed.

	// Create an instance of an object for a SDLGraphicsProgram
	SDLGraphicsProgram mySDLGraphicsProgram(840, 472);
	// Run our program forever
	mySDLGraphicsProgram.Loop();
	// When our program ends, it will exit scope, the
	// destructor will then be called and clean up the program.
	return 0;
}
