// UnrealBuildTool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <regex>
#include <string>
#include <windows.h>

void ProcessCommand(const std::string& command);
void ShowInfos(const std::string& path);
void Compile(const std::string& path);
void Package(const std::string& path, const std::string& packagePath);

std::string GetProjectNameFromPath(const std::string& projectPath);

int main()
{
	std::string command;
    std::cout << "Welcome in the Unreal Build Tool!\n";
    std::cout << "By Philippe St-Laurent-Recoura\n\n";
	std::cout << "There are 4 commands :\n";
    std::cout << "  MyTool [CHEMIN DU UPROJECT] show-infos\n";
    std::cout << "  MyTool [CHEMIN DU UPROJECT] build\n";
    std::cout << "  MyTool [CHEMIN DU UPROJECT] package [CHEMIN_DU_PACKAGE]\n";
    std::cout << "  exit\n\n";

    while (true) {
        std::cout << "Type the command line\n";
        std::getline(std::cin, command);

        // Check for exit command
        if (command == "exit") {
            std::cout << "Goodbye!\n";
            break;
        }

        // Process the command
        ProcessCommand(command);
		std::cout << "\n";
    }
}

// Process commands
void ProcessCommand(const std::string& command)
{
    std::regex showInfosRegex(R"(MyTool\s+(\S+)\s+show-infos)");
    std::regex buildRegex(R"(MyTool\s+(\S+)\s+build)");
    std::regex packageRegex(R"(MyTool\s+(\S+)\s+package\s+(\S+))");
    std::smatch match;

    if (std::regex_match(command, match, showInfosRegex)) {
        std::string path = match[1].str();
		ShowInfos(path);
    }
    else if (std::regex_match(command, match, buildRegex)) {
        std::string path = match[1].str();
        std::cout << "Building the specified .uproject file " << path << "\n";
    }
    else if (std::regex_match(command, match, packageRegex)) {
        std::string path = match[1].str();
		std::string packagePath = match[2].str();
        std::cout << "Packaging the .uproject  " << path << "\n";
    }
}

void ShowInfos(const std::string& path)
{
    std::cout << "Project name: " << path << "\n";
    std::cout << "Unreal version: " << path << "\n";
    std::cout << "Plugins: " << path << "\n";
}

void Compile(const std::string& path)
{
    std::string uePath = "./Engine/Build/BatchFiles/Build.bat";
    std::string projectName = "TestProject";
    std::string platform = "Win64";
    std::string configuration = "Development";

    const std::string open = "open";
    std::wstring wideOpen(open.begin(), open.end());

    const std::string filePath = "\"" + uePath + "\" " + projectName + " " + platform + " " + configuration + " -waitmutex";
    std::wstring wideFilePath(filePath.begin(), filePath.end());

	std::cout << "Compiling the specified .uproject file " << path << "\n";
    ShellExecute(NULL, wideOpen.c_str(), wideFilePath.c_str(), NULL, NULL, SW_SHOWMINIMIZED);
}

void Package(const std::string& path, const std::string& packagePath)
{
}
