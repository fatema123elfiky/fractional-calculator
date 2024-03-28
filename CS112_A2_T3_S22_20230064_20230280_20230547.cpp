// FCAI – Structured Programming – 2024 - Assignment 2
// Program Name: CS112_A2_T3_S22_20230064_20230280_20230547.cpp
// Program Description: the program subtracts , adds  , multiples and divides the fractional numbers and there is some validations for the inputs
// Last Modification Date: 18/03/2024
// Author1 and ID and Group: Alaa Tarek Mohamed Salah El-den Ahmed      ID:20230064     Group: B
// Author2 and ID and Group: Fatema Elzhraa Ahmed Mohamed El fiky       ID:20230280     Group: B
// Author3 and ID and Group: Mohamed Ehab Sabry Saber Kandil            ID:20230547     Group: B
// Teaching Assistant: Eng. Rana AbdelKader
// Who did what:
//              Validation and Subtraction function: Fatema Elzhraa
//              Addition function: Alaa Tarek
//              Multiplication and division: Mohamed Ehab
//
// Link to the algorithm file: https://drive.google.com/drive/folders/19OwlWzuVG3_fU0NBW7CLFc8WOClLh8wE?usp=sharing.
//E-mails:
//      fatmaelfeky922@gmail.com
//      Alaatarek2090@gmail.com
//      messk8@gmail.com



#include <iostream>
#include <regex>
#include <string>
#include <iomanip>
#include <numeric>

using namespace std;

int main() {
    // ANSI escape codes for text formatting
    const string BOLD = "\033[1m";
    const string RED_FG = "\033[31m";
    const string BLUE_FG = "\033[34m";
    const string MAGENTA_FG = "\033[35m";
    const string RESET = "\033[0m";
    const string CYAN_BOLD = "\033[1;36m";

    // Display welcome message with formatting
    cout << CYAN_BOLD << right << setw(89) << setfill('-') << "Welcome to your advanced fraction calculator" << setw(45) << setfill('-') << RESET << endl;

    // Display instructions for using the calculator
    cout << BOLD << endl << "*Some instructions*\n" << RESET << setw(20) << setfill('-') << " " << "\n";
    cout << "(1) Only spaces around the operator are allowed\n(2) Negative in denominator not allowed too\n";
    cout << "If you want to exit the program, type 'exit'\n" << setw(45) << setfill('-') << " " << "\n\n";

    // Infinite loop for continuous calculations
    while (true) {
        string ques, number1 = "", number2 = "", numerat1 = "", denomen1 = "", numerat2 = "", denomen2 = "", operat = "";
        int sign1 = 1, sign2 = 1;

        // Prompt user for input
        cout << "Please enter the calculation you would like to do\n";
        getline(cin, ques);

        // Convert input to uppercase for case-insensitive comparison
        for (long long i = 0; i < ques.size(); i++) {
            ques[i] = toupper(ques[i]);
        }

        // Validate input format and handle user exit
        while (!(regex_match(ques, regex("[+-]?[0-9]+(/[0-9]+)?\\s+[+-/*]{1}\\s+[+-]?[0-9]+(/[0-9]+)?"))) && ques != "EXIT") {
            cout << "Please enter again according to the instructions\n";
            getline(cin, ques);
        }

        // Exit if user enters "EXIT"
        if (ques == "EXIT") {
            cout << "Thank you for using our program\n";
            break;
        }

        // Remove extra spaces in input
        long long i = 0;
        while (true) {
            if (isspace(ques[i]) && isspace(ques[i - 1])) {
                ques.erase(i, 1);
                i = 0;
                continue;
            }
            i++;
            if (i == ques.size()) {
                break;
            }
        }

        // Parse input into operands and operator
        while (true) {
            if (ques[0] != ' ') {
                number1 += ques[0];
                ques.erase(0, 1);
            } else {
                ques.erase(0, 1);
                operat += ques[0];
                ques.erase(0, 2);
                number2 += ques;
                break;
            }
        }

        // Handle signs and fractions in operands
        if (!isdigit(number1[0])) {
            if (number1[0] == '-')
                sign1 = -1;
            number1.erase(0, 1);
        }
        if (!isdigit(number2[0])) {
            if (number2[0] == '-')
                sign2 = -1;
            number2.erase(0, 1);
        }

        // Check if operands are fractions
        bool fraction1 = false, fraction2 = false;
        for (size_t i = 0; i < number1.size(); i++) {
            if (number1[i] == '/') {
                fraction1 = true;
                break;
            } else
                fraction1 = false;
        }
        for (size_t i = 0; i < number2.size(); i++) {
            if (number2[i] == '/') {
                fraction2 = true;
                break;
            } else
                fraction2 = false;
        }

        // Extract numerator and denominator for fraction operands
        while (true) {
            if (fraction1) {
                if (number1[0] != '/') {
                    numerat1 += number1[0];
                    number1.erase(0, 1);
                } else {
                    number1.erase(0, 1);
                    denomen1 += number1;
                    break;
                }
            } else {
                numerat1 = number1;
                denomen1 = "1";
                break;
            }
        }

        // Extract numerator and denominator for the second fraction operand
        while (true) {
            if (fraction2) {
                if (number2[0] != '/') {
                    numerat2 += number2[0];
                    number2.erase(0, 1);
                } else {
                    number2.erase(0, 1);
                    denomen2 += number2;
                    break;
                }
            } else {
                numerat2 = number2;
                denomen2 = "1";
                break;
            }
        }

        // Check if any denominator is zero, which is invalid
        if (denomen1 == "0" || denomen2 == "0") {
            cout << "\nZeros are not allowed in the denominator. Invalid input \n";
            continue; // Skip further processing and ask for input again
        }

        // Convert numerator and denominator strings to integers for calculations
        long long numerator1 = stoll(numerat1) * sign1, numerator2 = stoll(numerat2) * sign2, denom1 = stoll(denomen1), denom2 = stoll(denomen2);

        // Perform arithmetic operations based on the operator provided
        if (operat == "-") {
            // Calculate subtraction result
            long long down = denom1 * denom2, up = (denom2 * numerator1) - (denom1 * numerator2);
            cout << "Subtraction result is: " << MAGENTA_FG << BOLD << up << "/" << down << RESET << "\n";
        } else if (operat == "*") {
            // Calculate multiplication result
            long long full_num = (numerator1 * numerator2) / (denom1 * denom2);
            long long remainder = (numerator1 * numerator2) % (denom1 * denom2);

            if (full_num == 0) {
                cout << "Multiplication result is: " << MAGENTA_FG << BOLD << remainder << "/" << (denom1 * denom2) << RESET << endl;
            } else if (remainder == 0) {
                cout << "Multiplication result is: " << MAGENTA_FG << BOLD << full_num << RESET << endl;
            } else {
                cout << "Multiplication result is: " << MAGENTA_FG << BOLD << full_num << " " << remainder << "/" << (denom1 * denom2) << RESET << endl;
            }
        } else if (operat == "/") {
            // Calculate division result
            long long full_num = 1, remainder = 1;
            if (numerator2 * denom1 == 0) {
                cout << "Zeros are not allowed in the denominator. Invalid input \n";
                continue; // Skip further processing and ask for input again
            }
            full_num = (numerator1 * denom2) / (numerator2 * denom1);
            remainder = (numerator1 * denom2) % (numerator2 * denom1);

            if (full_num == 0) {
                cout << "Division result is: " << MAGENTA_FG << BOLD << remainder << "/" << (numerator2 * denom1) << RESET << endl;
            } else if (remainder == 0) {
                cout << "Division result is: " << MAGENTA_FG << BOLD << full_num << RESET << endl;
            } else {
                cout << "Division result is: " << MAGENTA_FG << BOLD << full_num << " " << remainder << "/" << (numerator2 * denom1) << RESET << endl;
            }
        } else if (operat == "+") {
            // Calculate addition result
            long long res1, res2;
            res1 = denom1 * numerator2 + denom2 * numerator1;
            res2 = denom1 * denom2;

            if (res1 == 0) {
                cout << "The result of summation = 0 \n";
            } else if (abs(res1) == abs(res2)) {
                cout << "The result of summation =  " << res1 / res2 << "\n";
            } else {
                cout << "The result of summation = " << res1 << " / " << res2 << "\n";
            }
        }
    }

    return 0;
}