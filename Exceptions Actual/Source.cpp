#include <iostream>
#include <string>
#include <fstream>
//inclusions

//Prototype Functions
bool Banking(); // function for introduction
void NewAccount(); // makes the new account
void LogIn(); // Logs the old accounts in
void SaveFiles(); // saves files
void LoadFiles(); // Loads files
void DumpFiles(); // Dumps files to screen

//public usernames and passwords - array format
const int MAXARRAY = 5;
std::string Users[MAXARRAY];
std::string Passwords[MAXARRAY];
// now save and load to the Files

int main() // Main function
{
	LoadFiles(); // loads the array up with previously saved data
	for (int i = 0; i < MAXARRAY; i++) { Users[i] == ""; Passwords[i] == ""; } // INIT arrays for use
	std::cout << "\n\n\t *** Exception Actual and saved data showcase *** \n\n " << std::endl;
	//std::cout << " This is a Showcase of Programmed Exceptions, as well as other Functions\n" << std::endl; // commented out for beauty sake
	while (!Banking()) {} // Loops Banking function until retun = true
	return 0;
}

bool Banking()// Begining Function
{
	std::string Selection (""); // Inting an empty string

	std::cout << "\n\n Welcome to the United States Federal Banking Service, How may We assist you today?\n" << std::endl;
	std::cout << "Are you here to make a [New Account]? Or [Log In] to an existing one? Or, Would you like to [Exit] the Program? \n" << std::endl;
	std::cout << "If you are an admin, Please use [Dump] to show all file data \n\n" << std::endl;
	std::getline(std::cin, Selection);
	
	// std::cout << Selection << std::endl; << Debugging line
	try
	{
		if (!Selection.compare("New Account")) { NewAccount(); } // if the selection matches the string input, It would move to making a new account
		else if (!Selection.compare("Log In")) { LogIn(); } // If the selection matches, Moves onto the Log In screen
		else if (!Selection.compare("Exit")) { return true; } // if Exit is input, it willexit the program in its entireity 
		else if (!Selection.compare("Dump")) { DumpFiles(); } // Dumps files to screen
		else { throw 11; } // if somthing dosnt match, it will throw Exception 11
	}
	catch (int error_code) // catches an int error
	{

		if (error_code == 11)
		{ 
			std::cout << "\n ERROR CODE 11";
			std::cout << "\n This is not an option great Customer! please, try again" << std::endl;

		}
		else if (error_code == 22)
		{
			std::cout << "\n ERROR CODE 22";
			std::cout << "\n That Username Already Exists, Please try again!" << std::endl;
		}

	}
	catch (std::string error_string) // catches a string error
	{
		std::cout << "\n There was an error!!! Error = " << error_string << std::endl;
		
	}
	catch (...) // catches any unknown errors
	{
		std::cout << "UNKNOWN ERROR" << std::endl; 
		
	}

	return false; // if it returns false, it loops the program
}

void NewAccount() // 
{

	std::string Username(""); // empty string
	std::cout << "\n This is a new account \n" << std::endl; 
	std::cout << "Please Enter an account Username : ";
	std::getline(std::cin, Username); // gets the line for string
	for (int i = 0; i < MAXARRAY; i++) // a for loop!
	{

		if (!Username.compare(Users[i])) // Compares the input, If it matches one that already exists, Throws an error
		{
			throw 22;
		}
		else if (!Users[i].compare("")) // compares input, and if it dosnt match anything, it moves to the next step
		{
			Users[i] = Username; // sets the blank area as the new username

				std::cout << "Please Enter an account Password : ";
				std::getline(std::cin, Passwords[i]); // this will set the password to the same line in the password area
				SaveFiles(); // saves the username and password for future use
				LogIn(); // forces the running of the log in set
				break; // breaks the loop
		}
	}
}

void LogIn()
{
	std::string Username("");// empty string for input
	std::string Password("");// empty string for input
	std::cout << "\n Logging in \n" << std::endl;
	std::cout << " Please Input your Username : ";
	std::getline(std::cin, Username);

	for (int i = 0; i < MAXARRAY; i++) // for loop for Logging in
	{
		if (!Username.compare(Users[i])) //  Checks the username, and when it passes, it will move to the password
		{
			std::cout << "Please Enter an account Password : ";
			std::getline(std::cin, Password);

			if (!Password.compare(Passwords[i])) // checks the password, than logs them in
			{
				std::cout << "\n\n Sucessfully Logged in!";
				break;
			}
			else // unknown password error
			{
				std::string ERROR_WRONG_PASSWORD(" This is the Incorrect Password ");
				throw ERROR_WRONG_PASSWORD;
			}
		}
		else if (!Users[i].compare("")) // string error for an unknown username
		{
			std::string USER_NOT_FOUND(" There is no user with that username ");
				throw USER_NOT_FOUND;
		}
	}
}

void SaveFiles() // saves all input data into an array
{
	std::ofstream UsernameFile("UserNames.txt"), PasswordFile("PassWords.txt");

	if (UsernameFile.is_open() && PasswordFile.is_open()) // checks if the file is open before saving
	{
		for (int i = 0; i < MAXARRAY; i++) // the arrays for loop, makes sure that it reads all data and saves it into the files
		{

			UsernameFile << Users[i] << ("\n"); // saves the Username to the file
			PasswordFile << Passwords[i] << ("\n"); // Saves the Password to the file

		}
	}
	UsernameFile.close(); // closes the file(s)
	PasswordFile.close();
}

void LoadFiles() // Loads and inits the data into the array
{
	std::ifstream UsernameFile("UserNames.txt"), PasswordFile("PassWords.txt"); // checks if the files are open before loading from them
	if (UsernameFile.is_open() && PasswordFile.is_open())

	{
		for (int i = 0; i < MAXARRAY; i++) // the arrays for loop, makes sure that it reads all data and loads it into the array
		{
			std::getline(UsernameFile, Users[i]); // loads up the User Array
			std::getline(PasswordFile, Passwords[i]); // Loads up the passwords Array
		}
	}
	UsernameFile.close(); // closes the file(s)
	PasswordFile.close();
}

void DumpFiles() // Program to dump file contents to screen
{
	std::string DisplayFile1; // Display string 1
	std::string DisplayFile2; // Display string 2

	std::ifstream UsernameFile("UserNames.txt"), PasswordFile("PassWords.txt");  // inits the files fo use

	std::cout << "These are all current users of Program : \n ---------------------------- \n"; // breaker

	while (std::getline(UsernameFile, DisplayFile1)) // While there is content, it will print
	{
		std::cout << DisplayFile1 << ("\n");
	}

	std::cout << "\n ---------------------------- \nThese are all current Passwords of Program :\n ---------------------------- \n"; // breaker 2

	while (std::getline(PasswordFile, DisplayFile2))// while there is content, it will print
	{
		std::cout << DisplayFile2 << ("\n");
	}
}
