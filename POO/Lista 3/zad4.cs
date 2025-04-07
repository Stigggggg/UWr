//Liskov Substitution Principle - obiekt klasy powinien być zastępowalny przez obiekt klasy potomnej
//Problem polega na tym, że Square zmusza zmienną rect do dostosowania width = height

using System;

//Rozwiązanie: stosujemy abstrakcyjną klasę, z której mogą osobno dziedziczyć Rectangle i Square
//W ten sposób nie wpływają na siebie
public abstract class Shape {
    public abstract int CalculateArea();
}

public class Rectangle : Shape {
    public int Width { get; set; }
    public int Height { get; set; }
    public override int CalculateArea() {
        return Width * Height;
    }
}

public class Square : Shape {
    public int Side { get; set; }
    public override int CalculateArea() {
        return Side * Side;
    }
}

public class Zad4 {
    public static void Main() {
        Shape rect = new Rectangle { Width = 4, Height = 5 };
        Shape square = new Square { Side = 4 };
        Console.WriteLine("Pole prostokąta: " + rect.CalculateArea());
        Console.WriteLine("Pole kwadratu: " + square.CalculateArea());
    }
}