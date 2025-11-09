#include <iostream>
using namespace std;
#include <filesystem>
namespace fs=std::filesystem;

void listFiles(const string& path) 
{
    try 
    {
        for (const auto& entry : fs::directory_iterator(path)) 
        {
            cout<<(entry.is_directory() ? "[DIR]  " : "       ");
            cout<<entry.path().filename().string() << '\n';
        }
    } 
    catch (const exception& e) 
    {
        cerr << "Error: " << e.what() << '\n';
    }
}

int main() 
{
    string path = ".";
    cout << "Listing files in directory: " << fs::absolute(path) << "\n\n";
    listFiles(path);
    return 0;
}