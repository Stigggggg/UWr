namespace zad2
{
    public interface IShape
    {
        double GetArea();
    }

    public class Square : IShape
    {
        public double Side { get; }

        public Square(double side)
        {
            Side = side;
        }

        public double GetArea()
        {
            return Side * Side;
        }
    }

    public class Rectangle : IShape
    {
        public double Width { get; }
        public double Height { get; }

        public Rectangle(double width, double height)
        {
            Width = width;
            Height = height;
        }

        public double GetArea()
        {
            return Width * Height;
        }
    }

    public interface IShapeFactoryWorker
    {
        string ShapeName { get; }
        IShape CreateShape(params object[] parameters);
    }

    public class SquareFactoryWorker : IShapeFactoryWorker
    {
        public string ShapeName => "Square";

        public IShape CreateShape(params object[] parameters)
        {
            if (parameters.Length != 1 || parameters[0] is not double side)
            {
                throw new ArgumentException("Square requires one double parameter (side length)");
            }
            return new Square(side);
        }
    }

    public class RectangleFactoryWorker : IShapeFactoryWorker
    {
        public string ShapeName => "Rectangle";

        public IShape CreateShape(params object[] parameters)
        {
            if (parameters.Length != 2 || parameters[0] is not double width || parameters[1] is not double height)
            {
                throw new ArgumentException("Rectangle requires two double parameters (width, height)");
            }
            return new Rectangle(width, height);
        }
    }

    public class ShapeFactory
    {
        private readonly Dictionary<string, IShapeFactoryWorker> _workers = new();

        public void RegisterWorker(IShapeFactoryWorker worker)
        {
            _workers[worker.ShapeName] = worker;
        }

        public IShape CreateShape(string shapeName, params object[] parameters)
        {
            if (!_workers.TryGetValue(shapeName, out var worker))
            {
                throw new ArgumentException($"No factory worker registered for shape: {shapeName}");
            }
            return worker.CreateShape(parameters);
        }
    }
}
