#include "shell.hh"
#include <fstream>

using std::ifstream;
using std::ofstream;

int main(){
    std::string input;
    char buf[2];

    int fd = open("promptInput.txt", O_RDONLY);
    if(fd == -1){
        cout << "Error reading promptInput.txt";
        exit(1);
    }

    std::string prompt = read(fd, buf, 1);
    close(fd);


    while(true){

        std::cout << prompt;                   // Print het prompt
        std::getline(std::cin, input);         // Lees een regel
        if (input == "new_file") new_file();   // Kies de functie
        else if (input == "ls") list();        //   op basis van
        else if (input == "src") src();        //   de invoer
        else if (input == "find") find();
        else if (input == "python") python();
        else if (input == "exit") return 0;
        else if (input == "quit") return 0;
        else if (input == "error") return 1;

        if (std::cin.eof()) return 0; }

}      // EOF is een exit

void new_file(){
    std::string fileName;
    std::string fileContent;
    

    std::cout << "Give name for new file: ";
    std::getline(cin, fileName);
    std::cout << "Give a string for new file: ";
    std::getline(std::cin, fileContent);

    creat("newFileOutput", S_IRUSR|S_IWUSR);
    int newfileFD = open(fileName, O_RDWR);
    if(newFileFD == -1){
        cout << "Error opening " << fileName;
        exit(1);
    }
    write(newfileFD, fileContent, 1024);
    
    close(newFileFD);
}

void list(){
    int pid = fork();
    if(pid == -1){
        std::cout << "Error pid:-1";
        exit(1);
    }
    else if(pid == 0){
        char *args[] = {"/bin/ls", "-la", char( *) 0};
        execv("bin/ls", args);
    }
    else{
        int exit_status;
        wait(&exit_status);
    }
}

void find(){
    std::string searchString;
    std::cout << "Please give the string you are searching for: ";
    getline(std::cin, searchString);
    
    int findGrepPipe[2];
    int stringFindPipe[2];
    pipe(findGrepPipe);
    pipe(stringFindPipe);

    dup2(stringFindPipe[1],1);
    close(1);

    std::out << searchString;
    int pid = fork();
    if(pid == -1){
        std::cout << "Error pid:-1";
        exit(1);
    }
    else if(pid == 0){

        int pid =fork();
        if(pid == -1){
            std::cout << "Error pid:-1";
            exit(1);
        }
        else if(pid == 0){
            dup2(stringFindPipe[0], 0);
            dup2(findGrepPipe[1],1);
            close(1);
            close(0);
            close(findGrepPipe[0]);
            close(stringFindPipe[1]);

            char *args[] = {"/bin/find", char( *) 0};
            execv("bin/find", args);
        }
        else{
            dup2(findGrepPipe[0], 0);
            close(0);
            close(findGrepPipe[1]);

            int exit_status;
            wait(&exit_status);

            char *args[] = {"/bin/grep", char( *) 0};
            execv("/bin/grep", args);
        }
        
    }else{
        int exit_status;
        wait(&exit_status);
    }
}

void python(){
    int pid = fork();
    if(pid == -1){
        cout << "Error pid:-1";
        exit(1);
    }
    else if(pid == 0){
        execv("/usr/bin/python3", char( *) 0);
    }
    else{
        int exit_Status;
        wait(&exit_status);
    }
}

void src() // Voorbeeld: Gebruikt SYS_open en SYS_read om de source van de shell (shell.cc) te printen.
{ int fd = syscall(SYS_open, "shell.cc", O_RDONLY, 0755); // Gebruik de SYS_open call om een bestand te openen.
  char byte[1];                                           // 0755 zorgt dat het bestand de juiste rechten krijgt (leesbaar is).
  while(syscall(SYS_read, fd, byte, 1))                   // Blijf SYS_read herhalen tot het bestand geheel gelezen is,
    std::cout << byte; }                                  //   zet de gelezen byte in "byte" zodat deze geschreven kan worden.
