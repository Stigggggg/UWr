using NUnit.Framework;
using System;
using zad2;

[TestFixture]
public class ShapeFactoryTests
{
    [Test]
    public void Factory_ShouldCreateSquare()
    {
        ShapeFactory factory = new ShapeFactory();
        factory.RegisterWorker(new SquareFactoryWorker());
        IShape shape = factory.CreateShape("Square", 5.0);
        Assert.That(shape, Is.InstanceOf<Square>());
        Assert.That(((Square)shape).Side, Is.EqualTo(5.0));
        Assert.That(shape.GetArea(), Is.EqualTo(25.0));
    }

    [Test]
    public void Factory_ShouldCreateRectangle()
    {
        ShapeFactory factory = new ShapeFactory();
        factory.RegisterWorker(new RectangleFactoryWorker());
        IShape shape = factory.CreateShape("Rectangle", 3.0, 5.0);
        Assert.That(shape, Is.InstanceOf<Rectangle>());
        Assert.That(((Rectangle)shape).Width, Is.EqualTo(3.0));
        Assert.That(((Rectangle)shape).Height, Is.EqualTo(5.0));
        Assert.That(shape.GetArea(), Is.EqualTo(15.0));
    }

    [Test]
    public void Factory_ShouldThrowExceptionForUnknownShape()
    {
        var factory = new ShapeFactory();
        Assert.Throws<ArgumentException>(() => factory.CreateShape("Triangle", 5.0));
    }

    [Test]
    public void Factory_ShouldThrowExceptionForInvalidParameters()
    {
        var factory = new ShapeFactory();
        factory.RegisterWorker(new SquareFactoryWorker());
        Assert.Throws<ArgumentException>(() => factory.CreateShape("Square", "wrong_param"));
    }
}