using System;
using System.Threading;

namespace zad1
{
    public sealed class ProcessSingleton
    {
        private static readonly ProcessSingleton _instance = new ProcessSingleton();
        public static ProcessSingleton Instance => _instance;
        private ProcessSingleton() { }
    }

    public sealed class ThreadSingleton
    {
        private static readonly ThreadLocal<ThreadSingleton> _instance = new(() => new ThreadSingleton());

        public static ThreadSingleton Instance => _instance.Value;

        private ThreadSingleton() { }
    }

    public sealed class TimedSingleton
    {
        private static TimedSingleton _instance;
        private static DateTime _creationTime;
        private static readonly object _lock = new();

        private TimedSingleton()
        {
            _creationTime = DateTime.UtcNow;
        }
        
        public static TimedSingleton Instance
        {
            get
            {
                lock (_lock)
                {
                    if (_instance == null || (DateTime.UtcNow - _creationTime).TotalSeconds > 5)
                    {
                        _instance = new TimedSingleton();
                    }
                    return _instance;
                }
            }
        }
    }
}


