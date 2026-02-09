#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

class PasswordAnalyzer {
private:
    string password;
    int strengthScore;
    
    bool hasUpperCase() {
        for(char c : password) {
            if(isupper(c)) return true;
        }
        return false;
    }
    
    bool hasLowerCase() {
        for(char c : password) {
            if(islower(c)) return true;
        }
        return false;
    }
    
    bool hasDigit() {
        for(char c : password) {
            if(isdigit(c)) return true;
        }
        return false;
    }
    
    bool hasSpecialChar() {
        string specialChars = "!@#$%^&*()_+-=[]{}|;:,.<>?";
        for(char c : password) {
            if(specialChars.find(c) != string::npos) return true;
        }
        return false;
    }

public:
    PasswordAnalyzer(string pwd) : password(pwd), strengthScore(0) {}
    
    void analyze() {
        cout << "\n=== Password Strength Analysis ===" << endl;
        cout << "Password: " << string(password.length(), '*') << endl;
        
        // Check criteria
        if(password.length() >= 8) {
            cout << "✓ Length: Good (8+ characters)" << endl;
            strengthScore += 2;
        } else {
            cout << "✗ Length: Too short (minimum 8 characters)" << endl;
        }
        
        if(hasUpperCase()) {
            cout << "✓ Contains uppercase letters" << endl;
            strengthScore++;
        } else {
            cout << "✗ Missing uppercase letters" << endl;
        }
        
        if(hasLowerCase()) {
            cout << "✓ Contains lowercase letters" << endl;
            strengthScore++;
        } else {
            cout << "✗ Missing lowercase letters" << endl;
        }
        
        if(hasDigit()) {
            cout << "✓ Contains numbers" << endl;
            strengthScore++;
        } else {
            cout << "✗ Missing numbers" << endl;
        }
        
        if(hasSpecialChar()) {
            cout << "✓ Contains special characters" << endl;
            strengthScore++;
        } else {
            cout << "✗ Missing special characters" << endl;
        }
        
        // Common password check (basic)
        string commonPasswords[] = {"password", "123456", "qwerty", "admin"};
        for(string common : commonPasswords) {
            if(password == common) {
                cout << "⚠ WARNING: This is a commonly used password!" << endl;
                strengthScore = 0;
                break;
            }
        }
        
        cout << "\n=== RESULT ===" << endl;
        cout << "Security Score: " << strengthScore << "/6" << endl;
        
        if(strengthScore >= 5) {
            cout << "Strength: VERY STRONG ✅" << endl;
        } else if(strengthScore >= 3) {
            cout << "Strength: MODERATE ⚠" << endl;
        } else {
            cout << "Strength: WEAK ❌ (Consider changing)" << endl;
        }
    }
    
    void saveToFile() {
        ofstream file("password_audit.txt", ios::app);
        if(file.is_open()) {
            file << "Password analyzed (masked): " << string(password.length(), '*') << endl;
            file << "Strength Score: " << strengthScore << "/6" << endl << endl;
            file.close();
            cout << "\nReport saved to 'password_audit.txt'" << endl;
        }
    }
};

int main() {
    string inputPassword;
    
    cout << "=== CYBERSECURITY PASSWORD CHECKER ===" << endl;
    cout << "Enter password to analyze: ";
    cin >> inputPassword;
    
    PasswordAnalyzer analyzer(inputPassword);
    analyzer.analyze();
    
    char saveChoice;
    cout << "\nSave analysis to file? (y/n): ";
    cin >> saveChoice;
    
    if(tolower(saveChoice) == 'y') {
        analyzer.saveToFile();
    }
    
    cout << "\n=== TIPS FOR STRONG PASSWORDS ===" << endl;
    cout << "1. Use at least 12 characters" << endl;
    cout << "2. Combine letters, numbers, and symbols" << endl;
    cout << "3. Avoid personal information" << endl;
    cout << "4. Use unique passwords for each account" << endl;
    
    return 0;
}
