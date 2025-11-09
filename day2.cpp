#include <iostream>
using namespace std;
#include <filesystem>
#include <string>
namespace fs=std::filesystem;

void listFiles(const fs::path& path) 
{
    for (const auto& entry:fs::directory_iterator(path)) 
    {
       cout<<(entry.is_directory() ? "[DIR]  " : "       ");
       cout<<entry.path().filename().string() << '\n';
    }
}

int main() 
{
    fs::path currentPath=fs::current_path();
    string command;
    while (true) 
    {
        cout<<"\nCurrent Directory: " << currentPath << "\n";
        cout<<"Commands: ls | cd <dir> | exit\n> ";
        getline(std::cin, command);
        if(command == "ls") 
            listFiles(currentPath);
        else if(command.rfind("cd ",0)==0) 
        {
            fs::path newPath= currentPath/command.substr(3);
            if(fs::exists(newPath)&&fs::is_directory(newPath)) 
                currentPath=fs::canonical(newPath);
            else 
                std::cout << "Directory not found!\n";
            
        } 
        else if(command=="exit") 
            break;
        else
            cout<<"Unknown command!\n";
        
    }
}