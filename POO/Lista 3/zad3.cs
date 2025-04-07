//Open Responsibility Principle - otwartość na rozszerzenia, zamknięcie na modyfikacje
//Czemu CashRegister nie spełnia OCP?
//Ma 2 odpowiedzialności, obliczanie podatków i drukowanie rachunku
//Więc gdybyśmy chcieli dodać nową wartość podatku albo nowy sposób drukowania, musielibyśmy rozszerzać

using System;
using System.Linq;

public class Item {
    public string Name { get; set; }
    public decimal Price { get; set; }
}

//Interfejs pozwala nam dodawać kolejne wartości bez modyfikacji istniejących
public interface ITaxCalculator {
    decimal CalculateTax(decimal price);
}

public class StandardTaxCalculator : ITaxCalculator {
    public decimal CalculateTax(decimal price) {
        return price * 0.22m;
    }
}

public class ReducedTaxCalculator : ITaxCalculator {
    public decimal CalculateTax(decimal price) {
        return price * 0.05m;
    }
}

//Tak samo z rachunkiem
public interface IBillPrinter {
    void PrintBill(Item[] items, ITaxCalculator taxCalculator);
}

public class DefaultBillPrinter : IBillPrinter {
    public void PrintBill(Item[] items, ITaxCalculator taxCalculator) {
        foreach (var item in items)
            Console.WriteLine("{0}: cena {1} + podatek {2}", item.Name, item.Price, taxCalculator.CalculateTax(item.Price));
    }
}

public class AlphabeticalBillPrinter : IBillPrinter {
    public void PrintBill(Item[] items, ITaxCalculator taxCalculator) {
        var sortedItems = items.OrderBy(i => i.Name).ToArray();
        foreach (var item in sortedItems)
            Console.WriteLine("{0}: cena {1} + podatek {2}", item.Name, item.Price, taxCalculator.CalculateTax(item.Price));
    }
}

//Teraz CashRegister działa z każdym kalkulatorem i printerem
public class CashRegister {
    private readonly ITaxCalculator _taxCalculator;
    private readonly IBillPrinter _billPrinter;
    public CashRegister(ITaxCalculator taxCalculator, IBillPrinter billPrinter) {
        _taxCalculator = taxCalculator;
        _billPrinter = billPrinter;
    }
    public decimal CalculatePrice(Item[] items) {
        decimal totalPrice = 0;
        foreach (Item item in items) {
            totalPrice += item.Price + _taxCalculator.CalculateTax(item.Price);
        }
        return totalPrice;
    }
    public void PrintBill(Item[] items) {
        _billPrinter.PrintBill(items, _taxCalculator);
    }
}

public class Zad3 {
    public static void Main() {
        var items = new[] {
            new Item { Name = "Laptop", Price = 3000 },
            new Item { Name = "Myszka", Price = 100 }
        };
        var taxCalculator = new StandardTaxCalculator(); 
        var billPrinter = new AlphabeticalBillPrinter();
        var cashRegister = new CashRegister(taxCalculator, billPrinter);
        Console.WriteLine("Całkowita cena: " + cashRegister.CalculatePrice(items));
        cashRegister.PrintBill(items);
    }
}