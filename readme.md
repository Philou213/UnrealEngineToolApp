# UnrealEngineToolApp

**Author:** Philippe St-Laurent-Recoura  

## About  

**UnrealEngineToolApp** is a tool designed to simplify and accelerate the process of building and packaging Unreal Engine projects. This project automates tasks to make the workflow more efficient, reducing manual steps and improving consistency across builds.  

## How to use  

1. Open a terminal (Powershell or command prompt) in the root of the Unreal Engine folder
2. This a list of commands that you can execute :
   ***
   1. [PathToThisExecutable] [PathToUnrealProject] show-infos 
      Show infos about the project
   2. [PathToThisExecutable] [PathToUnrealProject] build
      Build the project with UBT
   3. [PathToThisExecutable] [PathToUnrealProject] package [PackagePath]
      Package the project with UAT
      **Warning** : The packagePath must be in double quote and the double quote in the package path must be changed for single quote