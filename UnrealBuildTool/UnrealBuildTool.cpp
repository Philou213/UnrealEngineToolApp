#include <fmt/core.h>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void ShowInfo(const std::string& projectPath);
void BuildProject(const std::string& projectPath);
void PackageProject(const std::string& projectPath, const std::string& packagePath);

std::vector<std::string> JsonRead(const std::string& projectPath);

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cout << "Usage: UnrealBuildTool.exe [UPROJECT_PATH] [COMMAND] [OPTIONAL_ARGUMENTS]\n";
        std::cout << "Example: UnrealBuildTool.exe c:\\projects\\MyProject.uproject show-infos\n";
        return 1;
    }

    std::string projectPath = argv[1]; // The .uproject file path
    std::string command = argv[2];     // The command to execute

    // Process commands
    if (command == "show-infos") {
        ShowInfo(projectPath);
    }
    else if (command == "build") {
        BuildProject(projectPath);
    }
    else if (command == "package") {
        if (argc < 4) {
            std::cout << "Missing package destination path for 'package' command.\n";
            return 1;
        }
        std::string packagePath = argv[3]; // Package destination path
        PackageProject(projectPath, packagePath);
    }
    else {
        std::cout << "Unknown command: " << command << "\n";
        return 1;
    }

    return 0;
}

void ShowInfo(const std::string& projectPath)
{
    std::cout << "\n";

    std::vector<std::string> projectInfos = JsonRead(projectPath);

    std::cout << "Project Name: " << projectInfos[0] << "\n";

    if (projectInfos[1].find("{") != std::string::npos)
    {
        std::cout << "Unreal Engine Version: " << "From Source" << "\n";
    }
    else
    {
        std::cout << "Unreal Engine Version: " << projectInfos[1] << "\n";
    }
    std::cout << "Plugins: " << projectInfos[2] << "\n";
    std::cout << "\n";
}

void BuildProject(const std::string& projectPath)
{
    std::cout << "Building project: " << projectPath << "\n";

    std::string buildPath = "./Engine/Build/BatchFiles/Build.bat";
    std::string projectName = "BuildToolTest";
    std::string target = "Win64";
    std::string optimisation = "Development";

    const std::string open = "open";
    std::wstring wideOpen(open.begin(), open.end());

    const std::string filePath = buildPath + " " + projectName + " " + target + " " + optimisation + " " + projectPath + " -waitmutex";
    std::wstring wideFilePath(filePath.begin(), filePath.end());

    //ShellExecute(NULL, wideOpen.c_str(), wideFilePath.c_str(), NULL, NULL, SW_SHOWMINIMIZED);
}

void PackageProject(const std::string& projectPath, const std::string& packagePath)
{
    std::cout << "Packaging project: " << projectPath << " to " << packagePath << "\n";
    // Implement your packaging logic here
}

std::vector<std::string> JsonRead(const std::string& projectPath)
{
    std::vector<std::string> projectInfos;

    std::ifstream file(projectPath);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << projectPath << "\n";
    }

    // Parse the .uproject file as JSON
    json projectData;
    try {
        file >> projectData;
    }
    catch (const std::exception& e) {
        std::cerr << "Error reading the JSON data: " << e.what() << "\n";
    }

    // Access the data from the JSON object
    try {
        // Get project name from FileDescription
        std::string projectName = projectData["Modules"][0]["Name"];
		projectInfos.push_back(projectName);

        std::string unrealVersion = projectData["EngineAssociation"];
		projectInfos.push_back(unrealVersion);

        // Access and display the plugins
        if (projectData.contains("Plugins")) {
            std::string pluginNames;
            for (const auto& plugin : projectData["Plugins"]) {
                pluginNames += plugin["Name"].get<std::string>() + ", ";
            }
            if (!pluginNames.empty()) {
                pluginNames.pop_back();
                pluginNames.pop_back();
            }
            projectInfos.push_back(pluginNames);
        }
        else {
            projectInfos.push_back("No plugins found.");
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error accessing JSON data: " << e.what() << "\n";
    }
	return projectInfos;
}
