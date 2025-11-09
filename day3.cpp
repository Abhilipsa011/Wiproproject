#include <iostream>
using namespace std;
#include <filesystem>
#include <fstream>
namespace fs=std::filesystem;

void copyFile(const fs::path& src, const fs::path& dest) 
{
    fs::copy(src,dest,fs::copy_options::overwrite_existing);
}
void moveFile(const fs::path& src, const fs::path& dest) 
{
    fs::rename(src,dest);
}
void deleteFile(const fs::path& target) 
{
    fs::remove(target);
}
void createFile(const fs::path& target) 
{
    ofstream file(target);
    file.close();
}
int main() 
{
    fs::path currentPath=fs::current_path();
    string command,arg1,arg2;
    while (true) 
    {
        cout<<"\n["<<currentPath<<"]$ ";
        getline(std::cin,command);
        if(command=="exit") 
          break;
        else if(command=="ls") 
        {
            for(auto& p : fs::directory_iterator(currentPath))
                cout<<p.path().filename().string() << "\n";
        } 
        else if(command.rfind("copy ",0)==0) 
        {
            istringstream iss(command.substr(5));
            iss>>arg1>>arg2;
            copyFile(currentPath/arg1,currentPath/arg2);
        } 
        else if(command.rfind("move ",0)==0) 
        {
            istringstream iss(command.substr(5));
            iss>>arg1>>arg2;
            moveFile(currentPath/arg1,currentPath/arg2);
        } 
        else if(command.rfind("del ",0)==0) 
        {
            arg1=command.substr(4);
            deleteFile(currentPath/arg1);
        } 
        else if(command.rfind("touch ",0)==0) 
        {
            arg1=command.substr(6);
            createFile(currentPath/arg1);
        }
    }
}