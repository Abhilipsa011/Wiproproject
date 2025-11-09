#include <iostream>
using namespace std;
#include <filesystem>
namespace fs = std::filesystem;

void searchFiles(const fs::path& path,const std::string& filename) 
{
    for(const auto& entry:fs::recursive_directory_iterator(path)) 
    {
        if(entry.path().filename().string().find(filename)!=string::npos)
            cout<<entry.path()<<'\n';
    }
}
int main() 
{
    string term;
    cout<<"Enter file name to search: ";
    getline(cin,term);
    searchFiles(fs::current_path(),term);
}