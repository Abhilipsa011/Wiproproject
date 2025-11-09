#include <iostream>
using namespace std;
#include <filesystem>
#include <string>
#include <sys/stat.h>   
namespace fs=std::filesystem;
string getPermissions(const fs::path& path) 
{
    string perms;
    fs::perms p=fs::status(path).permissions();
    perms+=((p&fs::perms::owner_read)!=fs::perms::none?"r":"-");
    perms+=((p&fs::perms::owner_write)!=fs::perms::none?"w":"-");
    perms+=((p&fs::perms::owner_exec)!=fs::perms::none?"x":"-");
    perms+=((p&fs::perms::group_read)!=fs::perms::none?"r":"-");
    perms+=((p&fs::perms::group_write)!=fs::perms::none?"w":"-");
    perms+=((p&fs::perms::group_exec)!=fs::perms::none?"x":"-");
    perms+=((p&fs::perms::others_read)!=fs::perms::none?"r":"-");
    perms+=((p&fs::perms::others_write)!=fs::perms::none?"w":"-");
    perms+=((p&fs::perms::others_exec)!=fs::perms::none?"x":"-");
    return perms;
}

void setPermissions(const fs::path& file,mode_t mode) 
{
    if(chmod(file.string().c_str(),mode)==0)
        cout<<"Permissions updated successfully.\n";
    else
        perror("chmod");
}
int main() 
{
    string command,filename;
    fs::path currentPath=fs::current_path();
    cout<<"Permission Manager (Linux)\n";
    cout<<"Commands:\n";
    cout<<"  perms <filename>        - show permissions\n";
    cout<<"  chmod <filename> <mode> - set permissions (e.g. 755)\n";
    cout<<"  exit\n\n";
    while(true) 
    {
        cout<<"["<<currentPath<<"]$ ";
        getline(cin,command);
        if(command=="exit") 
           break;
        else if(command.rfind("perms ",0)==0) 
        {
            filename=command.substr(6);
            fs::path file=currentPath/filename;
            if(fs::exists(file))
                cout<<filename<<": "<<getPermissions(file)<<"\n";
            else
                cout<<"File not found!\n";
        } 
        else if(command.rfind("chmod ",0)==0) 
        {
            string modeStr;
            istringstream iss(command.substr(6));
            iss>>filename>>modeStr;
            if(filename.empty()||modeStr.empty()) 
            {
                cout<<"Usage: chmod <filename> <mode>\n";
                continue;
            }
            mode_t mode=std::stoi(modeStr,nullptr,8); 
            setPermissions(currentPath/filename,mode);
        }
        else 
            cout<<"Unknown command.\n";
        
    }
}