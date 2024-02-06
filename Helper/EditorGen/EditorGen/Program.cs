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
    public string headAllRead;
    public Node()
    {
        mParent = null;
        mChild = new List<Node>();
        filePath = "";
        className = "";
        headAllRead = "";
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

    public static string GetParentClassName(string headerAllRead, string className)
    {
        StringBuilder sb = new StringBuilder(headerAllRead.Length);
        foreach (char c in headerAllRead)
        {
            if (false == char.IsWhiteSpace(c))
            {
                sb.Append(c);
            }
        }
        headerAllRead = sb.ToString();

        string strstr = $"class{className}:public";
        int index = headerAllRead.IndexOf(strstr);

        if (-1 == index)
        {
            return "";
        }

        string parentClassName = "";
        index += strstr.Length;

        for (int i = index; i < headerAllRead.Length; ++i)
        {
            if ('{' == headerAllRead[i])
            {
                break;
            }

            parentClassName += headerAllRead[i];

        }

        return parentClassName;
    }

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

            if (null != node.mParent)
            {
                uiCpp += $"class {node.mParent.className};\r\n";
                uiCpp += $"void {node.mParent.className}UI({node.mParent.className}* component);\r\n";
            }

            uiCpp += "\r\n\r\n";
            uiCpp += $"void {node.className}UI({node.className}* component)\r\n";
            uiCpp += "{\r\n";

            if (null != node.mParent)
            {
                uiCpp += $"\t{node.mParent.className}UI(component);\r\n";
            }
            
            uiCpp += "\r\n";
            uiCpp += "}\r\n";

            string uiPath = PATH_TARGET_DIRECTORT + "\\" + node.className + "UI.cpp";
                
            if (false == File.Exists(uiPath))
            {
                StreamWriter scriptCppReader = new StreamWriter(new FileStream(uiPath, FileMode.OpenOrCreate), Encoding.UTF8);
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
    public static void CreateComponentUIRender(string headerPath, string rootClassName)
    {
        string[] headerPaths = Directory.GetFiles(headerPath, "*.h", System.IO.SearchOption.TopDirectoryOnly);

        //탐색용해쉬
        Node componentNode = new Node();
        componentNode.className = rootClassName;
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

            string className = Path.GetFileNameWithoutExtension(path);            
            string headerAllRead = scriptCppReader.ReadToEnd();

            if (rootClassName == className)
            {
                continue;
            }
            

            Node newNode = new Node();
            newNode.mParent = null;
            newNode.filePath = path;
            newNode.className = className;
            newNode.headAllRead = headerAllRead;
            
            dictionary.Add(newNode.className, newNode);

            scriptCppReader.Close();
        }

        WriteLine("hello");

        foreach (KeyValuePair<string, Node> kv in dictionary)
        {
            Node node = kv.Value;

            string parentClassName = GetParentClassName(node.headAllRead, node.className);

            Node? parentNode2 = null;
            if (dictionary.TryGetValue(parentClassName, out parentNode2))
            {
                node.mParent = parentNode2;
                parentNode2.mChild.Add(node);
            }
        }  

        //header
        string componentWriteCpp = "";

        componentWriteCpp += "#include \"pch.h\"\r\n";
        componentWriteCpp += "#include \"ComponentUIRender.h\"\r\n";        
        componentWriteCpp += "#include <Engine/ScriptComponent.h>\r\n";
        componentWriteCpp += "#include <Engine/EnumComponent.h>\r\n";
        componentWriteCpp += "#include <Content/EnumScriptComponent.h>\r\n";

        RecHeader(componentNode, rootClassName, ref componentWriteCpp);
        componentWriteCpp += "\r\n";

        componentWriteCpp += $"void {rootClassName}UIRender({componentNode.className}* component)\r\n";        
        componentWriteCpp += "{\r\n";

        if (rootClassName == "Component")
        {
            componentWriteCpp += "\tswitch (component->GetType())\r\n";
        }
        else
        {
            componentWriteCpp += "\tswitch (component->GetScriptType())\r\n";
        }
        

        componentWriteCpp += "\t{\r\n";


        RecSwitch(componentNode, rootClassName, ref componentWriteCpp);        

        componentWriteCpp += "\t}\r\n";
        componentWriteCpp += "}\r\n";

        string path3 = PATH_TARGET_DIRECTORT + $"\\{rootClassName}UIRender.cpp";
        StreamWriter scriptCppReader2 = new StreamWriter(new FileStream(path3, FileMode.OpenOrCreate    ), Encoding.UTF8);
        scriptCppReader2.WriteLine(componentWriteCpp);
        scriptCppReader2.Close();
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

        //WriteLine("-----------------------------------");
        CreateComponentUIRender(path1, "Component");
        WriteLine("-----------------------------------");
        CreateComponentUIRender(path2, "ScriptComponent");
    }
}
