#include "shell.hh"
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

struct userInput{
    string inputFile;
    string outputFile;
    int offset;
};

struct ioFileDescriptors{
    int in;
    int out;
};

userInput getUserInput(userInput & input){
    userInput input;
    string fileNameIn;
    string fileNameOut;
    int indexOffset = -1;

    cout << "Give the name of the file to shuffle: ";
    std::getline(cin, input.inputFile);
    cout << "Give a positive number: ";
    while(indexOffset < 0){
        getline(cin, input.offset);
        if(indexOffset < 0){
            cout << "give a postive number: ";
        }
    }
    cout << "Give a name for the outputfile: ";
    getline(cin, input.file);

    return input;
}

IOFileDescriptors getFD(IOFileDescriptors & fd){
    fd.in = open(input.inputFile, O_RDONLY);
    fd.out = open(input.outputFile, O_WRONLY);

    return fd;
}

int getCharCount(const userInput & input){
    int charCount = 0;
    while(!fd.in.eof()){
        charCount++;
    }

    return charCount;
}

void writeOutput(const userInput & input,const ioFileDescriptors & fd, int charCount){
    int index = input.offset;
    char[1] charArray;
    int startfd = lseek(input.in, 0, SEEK_SET);

    read(input.in, charArray, 1);
    write(fd.out, charArray, 4094);

    while(read(input.in, charArray, 1)){

        if(lseek(input.in, index, SEEK_SET) != startfd){
            write(fd.out, charArray, 4094);
            index += input.offset;

            if(index > charCount){
                index -= charCount;
            }
        }
        else{
            break;
        }
        
    }
    
}

void closeFD(ioFileDescriptors & fd){
    close(fd.in);
    close(fd.out);
}

int main(){
    userinput input = getUserInput();
    IOFileDescriptors fd = getFD(input);
    int charCount = getCharCount(input);
    writeOutput(input, fd, charCount);
    closeFD(fd);
}