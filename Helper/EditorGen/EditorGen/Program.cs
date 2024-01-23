using System;
using System.Collections;
using System.IO;
using System.Linq;
using System.Linq.Expressions;
using System.Reflection.PortableExecutable;
using System.Text;
using System.Xml;
using System.Xml.Linq;

public class Node
{

    public Node mParent;
    public List<Node> mChild;
    public string filePath;
    public string className;
    public string type;

    public Node()
    {
        mParent = null;
        mChild = new List<Node>();
        filePath = "";
        className = "";
    }
}

public class MyProgram
{
    //EnumScript.h
    static string? PATH_TARGET_DIRECTORT = null;
    static string? PATH_ENUM_SCRIPT_H = null; // target
    static string? PATH_ENUM_SCRIPT_CPP = null; // target
    static string? ENUM_NAME = null;
    static string? IS_MESSAGE = null;

    static bool IS_MESSAGE_BOOL = false;
    static bool IS_NAME_SPACE = false;


    static void WriteLine(string str)
    {
        //if (IS_MESSAGE_BOOL)
            Console.WriteLine($"EditorGen: {str}");
    }

    static void WriteWarningLine(string str)
    {
        Console.WriteLine($"EditorGen: Warning: {str}");
    }

    static void WriteErrorLine(string str)
    {

        Console.WriteLine($"EditorGen: Error: {str}");
    }

    static string RemoveWhiteSpace(string str)
    {
        StringBuilder sb = new StringBuilder(str.Length);
        foreach (char c in str)
        {
            if (!char.IsWhiteSpace(c))
            {
                sb.Append(c);
            }
        }

        return sb.ToString();
    }

    public static string GetParentClassName(string header, string className)
    {
        StringBuilder sb = new StringBuilder(header.Length);
        foreach (char c in header)
        {
            if (false == char.IsWhiteSpace(c))
            {
                sb.Append(c);
            }
        }
        header = sb.ToString();

        string strstr = $"class{className}:public";
        int index = header.IndexOf(strstr);

        if (-1 == index)
        {
            return "";
        }

        string parentClassName = "";
        index += strstr.Length;

        for (int i = index; i < header.Length; ++i)
        {
            if ('{' == header[i])
            {
                break;
            }

            parentClassName += header[i];

        }

        return parentClassName;
    }

    //public static IsParent(string header, string className, string parentName)
    //{
    //    string parent = GetParentClassName(header, className);
    //}


    public static void RecHeader(Node node, string type, ref string header)
    {
        //header += $"#include \"{node.className}UI.h\"\r\n";
        header += $"class {node.className};\r\n";
        header += $"void {node.className}UI({node.className}* component);\r\n";

        //Create h, cpp
        //string uiHeader = "";
        //# include "pch.h"
        //# include "ComponentUI.h"
        {
            string uiCpp = "";
            uiCpp += "# include \"pch.h\"\r\n";
            //uiCpp += $"class {node.className};\r\n";

            if (node.filePath.Contains("\\Engine") || node.mParent == null)
            {
                uiCpp += $"#include <Engine/{node.className}.h>\r\n";
            }
            else
            {
                uiCpp += $"#include <Content/{node.className}.h>\r\n";
            }


            uiCpp += "\r\n\r\n";
            uiCpp += $"void {node.className}UI({node.className}* component)\r\n";
            uiCpp += "{\r\n";
            uiCpp += "\r\n";
            uiCpp += "}\r\n";

            string uiPath = PATH_TARGET_DIRECTORT + "\\" + node.className + "UI.cpp";

            if (false == File.Exists(uiPath))
            {
                StreamWriter scriptCppReader = new StreamWriter(new FileStream(uiPath, FileMode.Open), Encoding.UTF8);
                scriptCppReader.Write(uiCpp);
                scriptCppReader.Close();
            }
        } 
        foreach (Node item in node.mChild)
        {
            RecHeader(item, type, ref header);
        }
    }

    public static void RecRender(Node node, string type, ref string header)
    {


        foreach (Node item in node.mChild)
        {
            RecSwitch(item, type, ref header);
        }
    }


    public static void RecSwitch(Node node, string type, ref string switchCase)
    {             
        if (null != node.mParent)          
        {
            switchCase += $"\tcase e{type}Type::{node.className}:\r\n";
            switchCase += $"\t\t{node.className}UI(({node.className}*)component);\r\n";
            switchCase += "\t\tbreak;\r\n";
        }        

        foreach (Node item in node.mChild)
        {
            RecSwitch(item, type, ref switchCase);
        }        
    }

    //Component, ScriptComponent
    public static void CreateComponentUIRender(string headerPath, string rootType)
    {
        string[] headerPaths = Directory.GetFiles(headerPath, "*.h", System.IO.SearchOption.TopDirectoryOnly);

        //탐색용해쉬
        Node componentNode = new Node();
        componentNode.className = rootType;
        Dictionary<string, Node> dictionary = new Dictionary<string, Node>();

        dictionary.Add(componentNode.className, componentNode);

        foreach (string path in headerPaths)
        {
            StreamReader scriptCppReader = new StreamReader(new FileStream(path, FileMode.Open), Encoding.UTF8);
            if (null == scriptCppReader)
            {
                WriteErrorLine($"{scriptCppReader} is invalid");
                return;
            }

            //부모클래스이름 추출
            string myName = Path.GetFileNameWithoutExtension(path);
            string header = scriptCppReader.ReadToEnd();

            string parentName = GetParentClassName(header, myName);

            if (parentName == "")
            {
                continue;
            }

            //부모가있었다.
            Node parentNode = null;
            if (dictionary.TryGetValue(parentName, out parentNode))
            {
                //부모가있으나 나도있는지 확인해야함
                Node myNode = null;
                if (dictionary.TryGetValue(myName, out myNode))
                {
                    //나도있으니 패쓰 누군가가 만들어줬다
                    parentNode.mChild.Add(myNode);
                }
                else
                {
                    //부모가있으나 내꺼새로만듬

                    myNode = new Node();
                    myNode.className = myName;
                    myNode.filePath = path;
                    myNode.mParent = parentNode;

                    parentNode.mChild.Add(myNode);
                    dictionary.Add(myNode.className, myNode);
                }
            }
            else //부모가없었다
            {
                //부모만듬                
                parentNode = new Node();
                parentNode.className = parentName;

                Node myNode = null;
                if (dictionary.TryGetValue(myName, out myNode))
                {
                    //나도있으니 패쓰 누군가가 만들어줬다
                    parentNode.mChild.Add(myNode);
                }
                else
                {
                    myNode = new Node();
                    myNode.className = myName;
                    myNode.filePath = path;
                    myNode.mParent = parentNode;

                    parentNode.mChild.Add(myNode);
                    dictionary.Add(myNode.className, myNode);
                }
            }

            scriptCppReader.Close();
        }


        //완전탐색
        //RecPrint(componentNode, rootType);

        //cpp        

        //header
        string componentWriteCpp = "";

        componentWriteCpp += "#include \"pch.h\"\r\n";
        componentWriteCpp += "#include \"ComponentUIRender.h\"\r\n";        
        componentWriteCpp += "#include <Engine/ScriptComponent.h>\r\n";
        componentWriteCpp += "#include <Engine/EnumComponent.h>\r\n";
        componentWriteCpp += "#include <Content/EnumScriptComponent.h>\r\n";

        RecHeader(componentNode, rootType, ref componentWriteCpp);
        componentWriteCpp += "\r\n";

        componentWriteCpp += $"void {rootType}UIRender({componentNode.className}* component)\r\n";        
        componentWriteCpp += "{\r\n";

        if (rootType == "Component")
        {
            componentWriteCpp += "\tswitch (component->GetType())\r\n";
        }
        else
        {
            componentWriteCpp += "\tswitch (component->GetScriptType())\r\n";
        }
        

        componentWriteCpp += "\t{\r\n";


        RecSwitch(componentNode, rootType, ref componentWriteCpp);        

        componentWriteCpp += "\t}\r\n";
        componentWriteCpp += "}\r\n";

        string path3 = PATH_TARGET_DIRECTORT + $"\\{rootType}UIRender.cpp";
        StreamWriter scriptCppReader2 = new StreamWriter(new FileStream(path3, FileMode.OpenOrCreate    ), Encoding.UTF8);
        scriptCppReader2.WriteLine(componentWriteCpp);
        scriptCppReader2.Close();
        //WriteLine(componentWriteCpp);
    }

    public static void Main(string[] args)
    {
        //0 ContentPath
        if (args.Length < 3) 
        {
            WriteErrorLine("<path1> <path2> <targetDirectory>");
            WriteErrorLine("args need 3");
            return;
        }

        string path1 = args[0];
        string path2 = args[1];
        PATH_TARGET_DIRECTORT = args[2];

        //Component 상속받은 자식Component모음
        //Check Script Files
        //string[] headerPath1 = Directory.GetFiles(path1, "*.h", System.IO.SearchOption.TopDirectoryOnly);
        //string[] headerPath2 = Directory.GetFiles(path2, "*.h", System.IO.SearchOption.TopDirectoryOnly);

        //배열합침
        CreateComponentUIRender(path1, "Component");
        WriteLine("-----------------------------------");
        CreateComponentUIRender(path2, "ScriptComponent");


        string componentWrite = "";
        string componentScriptWrite = "";

        componentWrite += "eComponentType GetParentComponentOrNull(eComponentType componentType)\r\n";
        componentScriptWrite += "eScriptComponent GetParentScriptComponentOrNull(eScriptComponent scriptComponentType)\r\n";        


        componentWrite += "}\r\n";
        componentScriptWrite += "}\r\n";

        componentWrite += "\tswitch (componentType)\r\n";
        componentScriptWrite += "\tswitch (componentType)\r\n";

        componentWrite += "\t{";




        componentScriptWrite += "\t}";

        componentWrite += "{\r\n";
        componentScriptWrite += "{\r\n";


        //WriteErrorLine("ScriptGen Start");
        //WriteErrorLine("ScriptGen Start");


        //const string DEPENDENCY_FILE_NAME = "dpend.diff";
        //const string RETURN_VALUE = "const wchar_t*";
        //const string CONST = "const";
        //string NAMESPACE_NAME = "";
        //string IGNORE_FILE_NAME = "";                         //ignore.txt

        //ENUM_NAME = args[0];                   //"Script"
        //PATH_TARGET_DIRECTION = args[1];       //@"C:\Users\tkdlq\Desktop\assort\DirectX2D_Engine\Project\Content\";
        //PATH_ENUM_SCRIPT_H = args[2];          //@$"{PATH_CONTENT_DIRECTION}EnumScript.h";
        //PATH_ENUM_SCRIPT_CPP = args[3];        //@$"{PATH_CONTENT_DIRECTION}EnumScript.cpp";
        //IS_MESSAGE = args[4];                  //true or false

        //bool IS_IGNORE = false;
        ////제외


        //if (IS_MESSAGE == "TRUE")
        //{
        //    IS_MESSAGE_BOOL = true;
        //}

        //if (args.Length > 5 && args[5].Length > 2)
        //{
        //    NAMESPACE_NAME = args[5];
        //    IS_NAME_SPACE = true;
        //}
        //if (args.Length > 6)
        //{
        //    IGNORE_FILE_NAME = args[6];
        //    IS_IGNORE = true;
        //}

        //string LOWER_ENUM_NAME = ENUM_NAME.ToLower();
        //string UPER_ENUM_NAME = ENUM_NAME.ToUpper();
        //string E_ENUM_NAME_Type = $"e{ENUM_NAME}Type";

        //string CREATE_NAME_BY_ENUM = $"Create{ENUM_NAME}ByEnum";
        //string GET_ENUM_NAME_NAME = $"Get{ENUM_NAME}Name";
        //string ENUM_NAME_NAMES = $"{ENUM_NAME}Names";

        //string REGISTER_ENUM_NAME_TYPE = $"REGISTER_{UPER_ENUM_NAME}_TYPE";
        //string GET_NAME_BY_SOMEONE = $"{ENUM_NAME}* Create{ENUM_NAME}ByName(const std::wstring& {LOWER_ENUM_NAME}Name)";
        ////get all .cppfile path

        //List<string> enumClassNames = new List<string>();



        ////Check Script Files
        //string[] cppFilePths = Directory.GetFiles(PATH_TARGET_DIRECTION, "*.h", System.IO.SearchOption.AllDirectories);
        //foreach (string cppPath in cppFilePths)
        //{
        //    StreamReader scriptCppReader = new StreamReader(new FileStream(cppPath, FileMode.Open), Encoding.UTF8);

        //    if (null == scriptCppReader)
        //    {
        //        WriteErrorLine($"{LOWER_ENUM_NAME}CppReader is null");
        //        return;
        //    }
        //    string className = Path.GetFileNameWithoutExtension(cppPath);
        //    string scriptCpp = scriptCppReader.ReadToEnd();
        //    string scirptForamt = $"{REGISTER_ENUM_NAME_TYPE}({className})";


        //    StringBuilder sb = new StringBuilder(scriptCpp.Length);
        //    foreach (char c in scriptCpp)
        //    {
        //        if (!char.IsWhiteSpace(c))
        //        {
        //            sb.Append(c);
        //        }
        //    }
        //    scriptCpp = sb.ToString();

        //    //Test();virtual~Test();
        //    if (scriptCpp.Contains(scirptForamt) && scriptCpp.Contains($"{className}();virtual~{className}();"))
        //    {
        //        enumClassNames.Add(className);
        //    }

        //    scriptCppReader.Close();
        //}

        ////순서대로
        //List<string> NewClassNames = new List<string>();
        //{
        //    string configPath = Path.Combine(PATH_TARGET_DIRECTION, "component.priority");

        //    StreamReader config = new StreamReader(new FileStream(configPath, FileMode.OpenOrCreate), Encoding.UTF8);
        //    string configText = config.ReadToEnd();

        //    string[] configTexts = configText.Split("\r\n", StringSplitOptions.RemoveEmptyEntries);

        //    foreach (string cn in configTexts)
        //    {
        //        //cn 의 화이트 스페이스 제거                
        //        string name = cn.Replace("\r", "").Replace("\n", "").Replace("\t", "").Replace(" ", "");

        //        if (name.Length == 0)
        //            continue;



        //        if (enumClassNames.Contains(name))
        //        {
        //            NewClassNames.Add(name);
        //            enumClassNames.Remove(name);
        //        }
        //        else
        //        {
        //            WriteErrorLine($"check: component.prioriey Not found Component {name}$");
        //        }
        //    }


        //    foreach (string className in enumClassNames)
        //    {
        //        NewClassNames.Add(className);
        //    }

        //    enumClassNames = NewClassNames;
        //}



        ////의존성 검사 return 
        //{
        //    string depentdPath = Path.Combine(PATH_TARGET_DIRECTION, DEPENDENCY_FILE_NAME);
        //    WriteLine("check dependency");
        //    StreamReader depenWirter = new StreamReader(new FileStream(depentdPath, FileMode.OpenOrCreate), Encoding.UTF8);

        //    if (null != depentdPath)
        //    {
        //        //a
        //        string a = depenWirter.ReadToEnd().Replace("\r\n", "");

        //        string b = "";
        //        foreach (string item in enumClassNames)
        //        {
        //            b += item;
        //        }

        //        if (a == b)
        //        {
        //            WriteLine($"OK! Not Execute {ENUM_NAME}Gen Program End File No Change :)");
        //            depenWirter.Close();
        //            return;
        //        }
        //    }

        //    depenWirter.Close();
        //}

        ////Header
        //{
        //    StreamWriter enumHWirter = new StreamWriter(new FileStream(PATH_ENUM_SCRIPT_H, FileMode.Create), Encoding.UTF8);
        //    if (null == enumHWirter)
        //    {
        //        WriteErrorLine("enumHWirter is null");
        //        return;
        //    }

        //    string enumH = "";
        //    enumH += "#pragma once\n";
        //    enumH += "#include <string>\n\n";
        //    enumH += $"class {ENUM_NAME};\n\n";
        //    //start
        //    if (IS_NAME_SPACE)
        //    {
        //        enumH += $"namespace {NAMESPACE_NAME}\n";
        //        enumH += "{\n";
        //    }

        //    enumH += $"enum class {E_ENUM_NAME_Type} \n";
        //    enumH += "{\n";

        //    foreach (string item in enumClassNames)
        //    {
        //        if (IS_IGNORE)
        //        {
        //            if (IGNORE_FILE_NAME == item)
        //            {
        //                continue;
        //            }
        //        }

        //        enumH += $"\t{item},\n";
        //    }

        //    if (IS_IGNORE)
        //    {
        //        enumH += $"\tEnd,\n";
        //        enumH += $"\t{IGNORE_FILE_NAME}\n";
        //    }
        //    else
        //    {
        //        enumH += $"\tEnd\n";
        //    }

        //    enumH += "};\n\n";
        //    enumH += $"{RETURN_VALUE} {GET_ENUM_NAME_NAME}({CONST} {E_ENUM_NAME_Type} type);\n";
        //    enumH += $"{GET_NAME_BY_SOMEONE};\n";
        //    enumH += $"{ENUM_NAME} * {CREATE_NAME_BY_ENUM}({CONST} {E_ENUM_NAME_Type} type);\n";

        //    if (IS_NAME_SPACE)
        //    {
        //        enumH += "}\n";
        //    }

        //    enumHWirter.WriteLine(enumH);
        //    enumHWirter.Close();




        //    //end

        //}

        ////enumCppWirter Open
        //StreamWriter enumCppWirter = new StreamWriter(new FileStream(PATH_ENUM_SCRIPT_CPP, FileMode.Create), Encoding.UTF8);
        //{

        //    if (null == enumCppWirter)
        //    {
        //        WriteErrorLine("enumCppWirter is null");
        //        return;
        //    }



        //    string enumCpp = "";
        //    enumCpp += "#include \"pch.h\"\n";
        //    enumCpp += $"#include \"{Path.GetFileName(PATH_ENUM_SCRIPT_H)}\"\n\n";

        //    //all script header
        //    foreach (string item in enumClassNames)
        //    {
        //        enumCpp += $"#include \"{item}.h\"\n";
        //    }
        //    enumCpp += "\n";



        //    //start
        //    if (IS_NAME_SPACE)
        //    {
        //        enumCpp += $"namespace {NAMESPACE_NAME}\n";
        //        enumCpp += "{\n";
        //    }



        //    //const wchar_t* GetComponentName(const eScriptType type)
        //    enumCpp += $"static constexpr {RETURN_VALUE} const {ENUM_NAME_NAMES}[static_cast<UINT>({E_ENUM_NAME_Type}::End)]\n";
        //    enumCpp += "{\n";
        //    foreach (string item in enumClassNames)
        //    {
        //        enumCpp += $"\tL\"{item}\",\n";
        //    }
        //    enumCpp += "};\n\n";
        //    enumCpp += $"{RETURN_VALUE} {GET_ENUM_NAME_NAME}({CONST} {E_ENUM_NAME_Type} type)\n";
        //    enumCpp += "{\n";
        //    enumCpp += $"\tassert(static_cast<UINT>(type) < static_cast<UINT>({E_ENUM_NAME_Type}::End));\n";
        //    enumCpp += $"\treturn {ENUM_NAME_NAMES}[static_cast<UINT>(type)];\n";
        //    enumCpp += "}\n";
        //    enumCppWirter.WriteLine(enumCpp);


        //    //Script* GetScriptByName(const std::wstring& scriptName)
        //    string GetComponentScript = "";
        //    GetComponentScript += $"{GET_NAME_BY_SOMEONE}\n";
        //    GetComponentScript += "{\n";
        //    GetComponentScript += $"\t{ENUM_NAME}* {LOWER_ENUM_NAME} = nullptr;\n\n";
        //    if (enumClassNames.Count != 0)
        //    {
        //        GetComponentScript += $"\tif (L\"{enumClassNames[0]}\" == {LOWER_ENUM_NAME}Name)\n";
        //        GetComponentScript += $"\t\t{LOWER_ENUM_NAME} = new {enumClassNames[0]};\n";
        //    }
        //    for (int i = 1; i < enumClassNames.Count; i++)
        //    {
        //        GetComponentScript += $"\telse if (L\"{enumClassNames[i]}\" == {LOWER_ENUM_NAME}Name)\n";
        //        GetComponentScript += $"\t\t{LOWER_ENUM_NAME} = new {enumClassNames[i]};\n";
        //    }
        //    GetComponentScript += "\telse\n";
        //    GetComponentScript += "\t\tassert(false);\n";
        //    GetComponentScript += $"\treturn {LOWER_ENUM_NAME};\n";
        //    GetComponentScript += "}\n";
        //    enumCppWirter.WriteLine(GetComponentScript);


        //    //GetComponentScript enum
        //    GetComponentScript = "";

        //    GetComponentScript += $"{ENUM_NAME}* {CREATE_NAME_BY_ENUM}({CONST} {E_ENUM_NAME_Type} type)\n";
        //    GetComponentScript += "{\n";
        //    GetComponentScript += $"\t{ENUM_NAME}* {LOWER_ENUM_NAME} = nullptr;\n\n";
        //    GetComponentScript += "\tswitch (type)\n";
        //    GetComponentScript += "\t{\n";
        //    foreach (string item in enumClassNames)
        //    {
        //        GetComponentScript += $"\tcase {E_ENUM_NAME_Type}::{item}:\n";
        //        GetComponentScript += $"\t\t{LOWER_ENUM_NAME} = new {item};\n";
        //        GetComponentScript += $"\t\tbreak;\n";
        //    }
        //    GetComponentScript += "\tdefault:\n";
        //    GetComponentScript += "\t\tassert(false);\n";
        //    GetComponentScript += "\t\tbreak;\n";
        //    GetComponentScript += "\t}\n";

        //    GetComponentScript += $"\treturn {LOWER_ENUM_NAME};\n";
        //    GetComponentScript += "}\n";

        //    if (IS_NAME_SPACE)
        //    {
        //        GetComponentScript += "}\n";
        //    }

        //    enumCppWirter.WriteLine(GetComponentScript);
        //}
        //enumCppWirter.Close();


        ////의존성 파일 생성
        //{
        //    string depentdPath = Path.Combine(PATH_TARGET_DIRECTION, DEPENDENCY_FILE_NAME);
        //    StreamWriter depenWirter = new StreamWriter(new FileStream(depentdPath, FileMode.Create), Encoding.UTF8);
        //    if (null == depenWirter)
        //    {
        //        WriteErrorLine("depenWirter is null");
        //        return;
        //    }

        //    foreach (string s in enumClassNames)
        //    {
        //        depenWirter.WriteLine(s);
        //    }
        //    depenWirter.Close();
        //}

    }
}
