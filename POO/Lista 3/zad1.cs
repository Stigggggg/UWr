using System;

//Controller - centralizowanie obsługi żądań
//Który z obiektów odbiera żądania i kontroluje wykonanie?

public class OrderService {
    public void Process(int order_id) {
        Console.WriteLine($"Przetwarzam zamówienie {order_id}...");
    }
}

public class OrderController {
    private readonly OrderService os;
    public OrderController(OrderService o) {
        os = o;
    }
    public void ProcessOrder(int order_id) {
        os.Process(order_id);
    }
}

//Polymorphism - unikanie instrukcji warunkowych przez wykorzystanie polimofrizmu
//Przydzielamy zobowiązania za pomocą polimorfizmu

public abstract class Payment {
    public abstract void Process();
}

public class CreditCardPayment : Payment {
    public override void Process() {
        Console.WriteLine("Przetwarzanie płatności kartą...");
    } 
}

public class BlikPayment : Payment {
    public override void Process() {
        Console.WriteLine("Przetwarzanie płatności blikiem...");
    }
}

public class Zad1 {
    public static void Main() {
        //Controller
        var os = new OrderService();
        var controller = new OrderController(os);
        controller.ProcessOrder(123);
        //Polimofrizm
        Payment p = new BlikPayment();
        p.Process();
    }
}