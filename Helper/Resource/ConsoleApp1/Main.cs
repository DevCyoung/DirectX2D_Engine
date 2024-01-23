using System.Text;

// 2023 - 06 - 26 remove namespace
// TODO 유효성검사

public class MyProgram
{
    static string PRAGMA_ONCE = "#pragma once\r\n\r\n";
    static string SHARP_INCLUDE = "#include";
    static string BEGIN_ENGINE_NAMESPACE = ""; //"namespace engine\n{\n";
    static string END_ENGINE_NAMESPACE   = ""; //"}//namespace engine End";
    static string RESOURCE_PATH = "";

    static string RETURN_TYPE = "const wchar_t*";
    static string STRING_TYPE = "static constexpr const wchar_t*";

    //static List<string> allResourceFileNames = new List<string>();

    static void WriteLine(string str)
    {
        Console.WriteLine($"EnumResource: {str}");
    }

    static void WriteWarningLine(string str)
    {
        Console.WriteLine($"EnumResource: Warning: {str}");
    }

    static void WriteErrorLine(string str)
    {
        Console.WriteLine($"EnumResource: Error: {str}");
    }

    public static void Main(string[] args)
    {
        
        if (args.Length == 2)
        {
            WriteLine("Program Ready.....");
            //WriteLine("Input Check....");
            //WriteLine($"argc = {args.Length}");
            //WriteLine("args length is 2, ok! Program start");

            //WriteLine("###########Input Path############");
            foreach (string arg in args)
            {
                //WriteLine($"arg = {arg}");
            }
            //WriteLine("###########Input Path############");            

            string path = @"";
            string targetPath = @"";

            

            path += args[0];
            targetPath += args[1];

            


            RESOURCE_PATH = path;

            if (targetPath[targetPath.Length - 1] != '\\')
            {
                targetPath += '\\';
            }

            string resourcePath = path;

            string[] resourceDirectorys = Directory.GetDirectories(resourcePath);

            if (null == resourceDirectorys)
            {
                WriteErrorLine($"resourceDirectorys is null has directory? path({resourcePath})");
                return;
            }

            
            



            //WriteLine("###########Create Files############");
            foreach (string resDirectory in resourceDirectorys)
            {
                string enumType = GetFileName(resDirectory);


                List<string> enumNames = new List<string>();
                List<string> enumFilePath = new List<string>();

                MakeEnumNames(resDirectory, enumNames, enumFilePath, "");

                
                string depentdPath = Path.Combine(targetPath, enumType + "_" + "Res_dpend.diff");

                //여기서 유효성 검사를합니다. 통과했을때
                {
                    StreamReader depenReader = new StreamReader(new FileStream(depentdPath
                        , FileMode.OpenOrCreate), Encoding.UTF8);
                    string nameA = depenReader.ReadToEnd().Replace("\r\n", "");
                    string nameB = "";

                    foreach (string s in enumFilePath)
                    {
                        nameB += s;
                    }
                    nameB = nameB.Replace("\r\n", "");
                    depenReader.Close();

                    //바뀐게없다.
                    if (nameA == nameB)
                    {
                        continue;
                    }                    
                    WriteLine($"enumType = {enumType} is change");
                }


                //유하지않아서 다시적음
                {                    
                    StreamWriter depenWirter = new StreamWriter(new FileStream(depentdPath, 
                        FileMode.Create), Encoding.UTF8);

                    if (null == depenWirter)
                    {
                        WriteErrorLine("depenWirter is null");
                        return;
                    }

                    foreach (string s in enumFilePath)
                    {
                        depenWirter.WriteLine(s);
                    }

                    depenWirter.Close();
                }




                string enumHeader = MakeEnumNumHeader(enumType, enumNames);

                string enumHeaderPath =
                   targetPath + "EnumResourceType" + enumType + ".h";

                StreamWriter enumHearderWriter = new StreamWriter(
                new FileStream(enumHeaderPath
                , FileMode.Create)
                , Encoding.UTF8);


                if (null == enumHearderWriter)
                {
                    WriteErrorLine($"enumHearderWriter, check your enumHeaderPath... enumHeaderPath(Create fullPath) = " +
                        $"{enumHeaderPath} targetPath = {targetPath}");
                    return;
                }
                else
                {
                    enumHearderWriter.WriteLine(enumHeader);                    
                    enumHearderWriter.Close();
                    WriteLine($"CreateHeaderFile = {enumHeaderPath}");
                }              

                string enumCpp = MakeEnumCpp(enumType, enumFilePath);

                string enumCppPath =
                    targetPath + "EnumResourceType" + enumType + ".cpp";

                StreamWriter enumCppWirter = new StreamWriter(
                new FileStream(enumCppPath
                , FileMode.Create)
                , Encoding.UTF8);

                if (null == enumCppWirter)
                {
                    WriteErrorLine($"enumCppWirter, check your enumCppPath... enumCppPath(Create fullPath) = " +
                        $"{enumCppPath} targetPath = {targetPath}");                    
                }
                else
                {
                    enumCppWirter.WriteLine(enumCpp);                    
                    enumCppWirter.Close();
                    WriteLine($"CreateCppFile = {enumCppPath}");
                }                
            }


            //WriteLine("###########Create Files############");
            //WriteLine("Success End...");
        }
        else
        {
            if (args.Length == 3)
            {
                if (args[2] == "NO")
                {
                    WriteLine("OK! Not Execute Enum Program End");
                }
                else
                {
                    WriteErrorLine($"Check third argument... Please change \"{args[2]}\" -> \"NO\" and,  program not execute");
                }
            }
            else
            {
                WriteErrorLine("need 2 arguments, No Execute Enum Program End");
            }            
        }

    }

    public static string[] GetDirectories(string resourcePath)
    {
        string[] directorys = Directory.GetDirectories(resourcePath);

        foreach (string directory in directorys)
        {
            GetDirectories(directory);
        }

        string[] fileNames = Directory.GetFiles(resourcePath);

        return directorys;
    }

    public static string GetFileName(string path)
    {
        string[] split = path.Split('\\');
        string fileName = split[split.Length - 1];

        return fileName;
    }

    public static void MakeEnumNames(string resDirectory,
        List<string> enumNames,
        List<string> enumFilePath,
        string recursiveEnumName)
    {
        string[] directorys = Directory.GetDirectories(resDirectory);

        foreach (string directory in directorys)
        {
            string prev = recursiveEnumName;

            recursiveEnumName += GetFileName(directory) + "_";
            MakeEnumNames(directory, enumNames, enumFilePath, recursiveEnumName);

            recursiveEnumName = prev;
        }

        string[] fileNames = Directory.GetFiles(resDirectory);




        foreach (string fileName in fileNames)
        {
            

            string perfactEnumName = recursiveEnumName + Path.GetFileNameWithoutExtension(
                GetFileName(fileName));
            enumNames.Add(perfactEnumName);

            string resourceBaseFileName = fileName.Replace(resDirectory, "");
            resourceBaseFileName = resourceBaseFileName.Replace("\\", "\\\\");
            enumFilePath.Add(fileName.Replace(RESOURCE_PATH, "").Replace("\\", "\\\\"));

        }
    }


    public static string MakeEnumNumHeader(string enumType, List<string> enumNames)
    {
        string header = "";

        header += PRAGMA_ONCE;

        header += BEGIN_ENGINE_NAMESPACE;
        {
            header += "enum class " + "eRes" + enumType + "\r\n";
            header += "{\r\n";

            foreach (string enumName in enumNames)
            {
                header += "\t" + enumName + ",\r\n";
            }
            header += "" + "\tEnd\r\n";
            header += "};\r\n\r\n";

            if (enumNames.Count > 0)
            {
                header += $"{RETURN_TYPE} EnumResourcePath(eRes{enumType} type);\r\n";
            }

        }
        header += END_ENGINE_NAMESPACE;

        return header;
    }

    //enum to Path
    public static string MakeEnumCpp(string enumType, List<string> relativePaths)
    {
        string cpp = "";
        string eResEnumType = $"eRes{enumType}";
        string enumResourcePathArray = $"{eResEnumType}Path";


        cpp += $"{SHARP_INCLUDE} \"pch.h\"\r\n";
        cpp += $"{SHARP_INCLUDE} \"EnumResourceType{enumType}.h\"\r\n\r\n";

        cpp += BEGIN_ENGINE_NAMESPACE;
        {
            //const wchar
            if (relativePaths.Count > 0)
            {
                cpp += $"{STRING_TYPE} {enumResourcePathArray}[static_cast<UINT>({eResEnumType}::End)]\r\n";
                cpp += "{\r\n";

                foreach (string relativePath in relativePaths)
                {
                    //리소스 하위로가져온다.
                    cpp += $"\tL\"{relativePath}\",\r\n";
                }
                cpp += "};\r\n";
                cpp += "\r\n";
                cpp += $"{RETURN_TYPE} EnumResourcePath(eRes{enumType} type)\r\n";
                cpp += "{\r\n";
                cpp += $"\treturn {enumResourcePathArray}[static_cast<UINT>(type)];\r\n";
                cpp += "}\r\n";
            }
        }
        cpp += END_ENGINE_NAMESPACE;

        return cpp;
    }
}