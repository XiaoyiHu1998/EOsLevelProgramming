#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::cerr;

int main(int argc, char *argv[1]){
    int number;
    cin >> number;

    if(argc != 1){
    cerr << "Give 1 number between 0 and 99";
         return -1;
    }

    for(;;){
        cin >> number;

        if(cin.eof()){
            return 0;
        }

        int factor = 5;
        int output = number * factor;
        cout << output << "\n";
    }
}