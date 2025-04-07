using NUnit.Framework;
using System;
using zad3;

[TestFixture]
public class ObjectPoolTests
{
    [Test]
    public void InvalidSize()
    {
        Assert.Throws<ArgumentException>(() => new ObjectPool(0));
    }

    [Test]
    public void ValidSize()
    {
        var pool = new ObjectPool(1);
        var reusable = pool.AcqureReusable();
        Assert.IsNotNull(reusable);
    }

    [Test]
    public void CapacityDepleted()
    {
        var pool = new ObjectPool(1);
        var reusable = pool.AcqureReusable();
        Assert.Throws<ArgumentException>(() => pool.AcqureReusable());
    }

    [Test]
    public void ReusedInstance()
    {
        var pool = new ObjectPool(1);
        var reusable = pool.AcqureReusable();
        pool.ReleaseReusable(reusable);
        var reusable2 = pool.AcqureReusable();
        Assert.That(reusable, Is.EqualTo(reusable2));
    }

    [Test]
    public void ReleaseInvalidInstance()
    {
        var pool = new ObjectPool(1);
        var reusable = new Reusable();
        Assert.Throws<ArgumentException>(() => pool.ReleaseReusable(reusable));
    }
}

[TestFixture]
public class BetterReusableTests
{
    [Test]
    public void UsingReleasedObjectThrowsException()
    {
        var reusable = new BetterReusable();
        reusable.Release();
        Assert.Throws<InvalidOperationException>(() => reusable.DoWork());
    }
}
