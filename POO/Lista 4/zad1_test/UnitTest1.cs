using NUnit.Framework;
using System;
using System.Threading;
using zad1;

[TestFixture]
public class SingletonTests
{
    [Test]
    public void ProcessSingleton_ShouldReturnSameInstance()
    {
        var instance1 = ProcessSingleton.Instance;
        var instance2 = ProcessSingleton.Instance;
        Assert.That(instance1, Is.SameAs(instance2));
    }

    [Test]
    public void ThreadSingleton_ShouldReturnDifferentInstancesForDifferentThreads()
    {
        ThreadSingleton? instance1 = null;
        ThreadSingleton? instance2 = null;
        var thread1 = new Thread(() => instance1 = ThreadSingleton.Instance);
        var thread2 = new Thread(() => instance2 = ThreadSingleton.Instance);
        thread1.Start();
        thread2.Start();
        thread1.Join();
        thread2.Join();
        Assert.That(instance1, Is.Not.SameAs(instance2));
    }

    [Test]
    public void TimedSingleton_ShouldReturnSameInstanceWithin5Seconds()
    {
        var instance1 = TimedSingleton.Instance;
        Thread.Sleep(3000); 
        var instance2 = TimedSingleton.Instance;
        Assert.That(instance1, Is.SameAs(instance2));
    }

    [Test]
    public void TimedSingleton_ShouldCreateNewInstanceAfter5Seconds()
    {
        var instance1 = TimedSingleton.Instance;
        Thread.Sleep(6000); 
        var instance2 = TimedSingleton.Instance;
        Assert.That(instance1, Is.Not.SameAs(instance2));
    }
}