// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
public class SimpleMySQL : ModuleRules
{
    public string ProjectDirectory
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ModuleDirectory,"../../../../"));  //项目路径
        }
    }

    private void CopyToProjectBinaries(string FilePathName, ReadOnlyTargetRules Target)
    {
        string BineriesDirectory = Path.Combine(ProjectDirectory, "Binaries", Target.Platform.ToString());
        string Filename = Path.GetFileName(FilePathName);

        if (!Directory.Exists(BineriesDirectory))
        {
            Directory.CreateDirectory(BineriesDirectory);
        }

        string ProjectFileFullName = Path.Combine(BineriesDirectory, Filename);
        if (!File.Exists(ProjectFileFullName))
        {
            File.Copy(FilePathName, ProjectFileFullName, true);
        }

        RuntimeDependencies.Add(ProjectFileFullName);
    }

    public SimpleMySQL(ReadOnlyTargetRules Target) : base(Target)
	{
        //https://blog.csdn.net/u010385624/article/details/102638449
        //包含第三方库时，有可能出现预处理器没有定义的情况，在库的头文件中使用预处理器进行某些判断时，会报错，解决方法
        bEnableUndefinedIdentifierWarnings = false;

        PublicDefinitions.Add("NTDDI_WIN7SP1"); //定义windows版本 

        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        string PluginsDirectory = Path.GetFullPath(Path.Combine(ModuleDirectory, "..", ".."));//路径
        string SQLLibDirectory = Path.Combine(PluginsDirectory, "MySQL"); //MySQL路径
        string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";

        string MysqlPath = Path.Combine(SQLLibDirectory, PlatformString);

        PublicIncludePaths.Add(MysqlPath);

        RuntimeDependencies.Add(Path.Combine(MysqlPath, "libmysql.dll"));   //动态链接
        PublicAdditionalLibraries.Add(Path.Combine(MysqlPath, "libmysql.lib")); //静态链接

        CopyToProjectBinaries(Path.Combine(MysqlPath, "libmysql.dll"), Target);
        CopyToProjectBinaries(Path.Combine(MysqlPath, "libmysql.lib"), Target);


        PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
