using System;
using System.Threading;

public interface IMathService
{
    int Divide(int a, int b);
}

public class RealMathService : IMathService
{
    public int Divide(int a, int b)
    {
        return a / b;
    }
}

public class RetryProxy : IMathService
{
    private readonly IMathService _inner;
    private readonly int _maxRetries;
    public RetryProxy(IMathService inner, int maxRetries = 3)
    {
        _inner = inner;
        _maxRetries = maxRetries;
    }
    public int Divide(int a, int b)
    {
        int attempt = 0;
        while (true)
        {
            try
            {
                return _inner.Divide(a, b);
            }
            catch (Exception ex)
            {
                attempt++;
                Console.WriteLine($"[RetryProxy] Próba {attempt}: {ex.Message}");
                if (attempt >= _maxRetries)
                    throw;
                Thread.Sleep(100);
            }
        }
    }
}

public class LoggingProxy : IMathService
{
    private readonly IMathService _inner;
    public LoggingProxy(IMathService inner)
    {
        _inner = inner;
    }
    public int Divide(int a, int b)
    {
        Console.WriteLine($"[LoggingProxy] {DateTime.Now}: Wywołanie Divide({a}, {b})");
        try
        {
            int result = _inner.Divide(a, b);
            Console.WriteLine($"[LoggingProxy] {DateTime.Now}: Wynik = {result}");
            return result;
        }
        catch (Exception ex)
        {
            Console.WriteLine($"[LoggingProxy] {DateTime.Now}: Wyjątek = {ex.Message}");
            throw;
        }
    }
}

public static class MathServiceFactory
{
    public static IMathService CreateWithLoggingAndRetry()
    {
        IMathService realService = new RealMathService();
        IMathService withRetry = new RetryProxy(realService, 3);
        IMathService withLogging = new LoggingProxy(withRetry);
        return withLogging;
    }
}

public class Zad5
{
    public static void Main()
    {
        var math = MathServiceFactory.CreateWithLoggingAndRetry();
        try
        {
            Console.WriteLine("Wynik: " + math.Divide(10, 2));
            Console.WriteLine("Wynik: " + math.Divide(10, 0));
        }
        catch (Exception ex)
        {
            Console.WriteLine("Operacja zakończona błędem: " + ex.Message);
        }
    }
}
