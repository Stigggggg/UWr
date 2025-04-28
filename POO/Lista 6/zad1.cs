using System;
using System.IO;

public interface ILogger
{
    void Log(string message);
}

public class ConsoleLogger : ILogger
{
    public void Log(string message)
    {
        Console.WriteLine(message);
    }
}

public class FileLogger : ILogger
{
    private readonly string filePath;

    public FileLogger(string path)
    {
        filePath = path;
    }

    public void Log(string message)
    {
        File.AppendAllText(filePath, message + Environment.NewLine);
    }
}

public class NullLogger : ILogger
{
    public void Log(string message)
    {

    }
}

public enum LogType
{
    None,
    Console,
    File
}

public class LoggerFactory
{
    private static readonly LoggerFactory instance = new LoggerFactory();

    private LoggerFactory() { }

    public static LoggerFactory Instance => instance;

    public ILogger GetLogger(LogType logType, string parameters = null)
    {
        switch (logType)
        {
            case LogType.Console:
                return new ConsoleLogger();
            case LogType.File:
                return new FileLogger(parameters);
            case LogType.None:
            default:
                return new NullLogger();
        }
    }
}

class Zad1
{
    public static void Main(string[] args)
    {
        ILogger logger1 = LoggerFactory.Instance.GetLogger(LogType.File, "foo.txt");
        logger1.Log("log do pliku"); 
        ILogger logger2 = LoggerFactory.Instance.GetLogger(LogType.Console);
        logger2.Log("log na konsoli");
    }
}
