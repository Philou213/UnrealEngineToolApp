# UnrealEngineToolApp

**Author:** Philippe St-Laurent-Recoura  

## About  

**UnrealEngineToolApp** is a tool designed to simplify and accelerate the process of building and packaging Unreal Engine projects. This project automates tasks to make the workflow more efficient, reducing manual steps and improving consistency across builds.  

## How to Use  

1. Open a terminal (**PowerShell** or **Command Prompt**) in the root of the Unreal Engine folder.  
2. Use the following commands to interact with the tool:  

---

### Commands  

#### 1. Show Project Info  
```sh
[PathToThisExecutable] [PathToUnrealProject] show-infos
```
Display infos about the project

#### 2. Build Project
```sh
[PathToThisExecutable] [PathToUnrealProject] build
```
Build the project with Unreal Build Tool (UBT)

#### 3. Package Project
```sh
[PathToThisExecutable] [PathToUnrealProject] package [PathToPackage]
```
Package the project with Unreal Automation Tool (UAT)