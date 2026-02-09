#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

class CaesarCipher {
private:
    int shiftKey;
    
    char encryptChar(char ch) {
        if(isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            return (ch - base + shiftKey) % 26 + base;
        }
        return ch; // Non-alphabetic unchanged
    }
    
    char decryptChar(char ch) {
        if(isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            return (ch - base - shiftKey + 26) % 26 + base;
        }
        return ch;
    }

public:
    CaesarCipher(int key = 3) : shiftKey(key % 26) {}
    
    string encrypt(string text) {
        string result = "";
        for(char ch : text) {
            result += encryptChar(ch);
        }
        return result;
    }
    
    string decrypt(string text) {
        string result = "";
        for(char ch : text) {
            result += decryptChar(ch);
        }
        return result;
    }
    
    void encryptFile(string inputFile, string outputFile) {
        ifstream inFile(inputFile);
        ofstream outFile(outputFile);
        
        if(!inFile) {
            cout << "Error: Cannot open input file!" << endl;
            return;
        }
        
        string line;
        while(getline(inFile, line)) {
            outFile << encrypt(line) << endl;
        }
        
        inFile.close();
        outFile.close();
        cout << "File encrypted successfully: " << outputFile << endl;
    }
    
    void decryptFile(string inputFile, string outputFile) {
        ifstream inFile(inputFile);
        ofstream outFile(outputFile);
        
        if(!inFile) {
            cout << "Error: Cannot open input file!" << endl;
            return;
        }
        
        string line;
        while(getline(inFile, line)) {
            outFile << decrypt(line) << endl;
        }
        
        inFile.close();
        outFile.close();
        cout << "File decrypted successfully: " << outputFile << endl;
    }
};

void displayMenu() {
    cout << "\n=== CAESAR CIPHER TOOL ===" << endl;
    cout << "1. Encrypt Text" << endl;
    cout << "2. Decrypt Text" << endl;
    cout << "3. Encrypt File" << endl;
    cout << "4. Decrypt File" << endl;
    cout << "5. Exit" << endl;
    cout << "==========================" << endl;
    cout << "Select option: ";
}

int main() {
    CaesarCipher cipher;
    int choice, key;
    string text, inputFile, outputFile;
    
    cout << "Enter shift key (1-25): ";
    cin >> key;
    cipher = CaesarCipher(key);
    
    do {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Clear buffer
        
        switch(choice) {
            case 1:
                cout << "Enter text to encrypt: ";
                getline(cin, text);
                cout << "Encrypted: " << cipher.encrypt(text) << endl;
                break;
                
            case 2:
                cout << "Enter text to decrypt: ";
                getline(cin, text);
                cout << "Decrypted: " << cipher.decrypt(text) << endl;
                break;
                
            case 3:
                cout << "Enter input filename: ";
                cin >> inputFile;
                cout << "Enter output filename: ";
                cin >> outputFile;
                cipher.encryptFile(inputFile, outputFile);
                break;
                
            case 4:
                cout << "Enter input filename: ";
                cin >> inputFile;
                cout << "Enter output filename: ";
                cin >> outputFile;
                cipher.decryptFile(inputFile, outputFile);
                break;
                
            case 5:
                cout << "Exiting..." << endl;
                break;
                
            default:
                cout << "Invalid choice!" << endl;
        }
        
    } while(choice != 5);
    
    return 0;
}
