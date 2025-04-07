using System;

//Single Responsibility Principle - każda klasa ma tylko jedną funkcjonalność
//Tu ma 3
public class Report {
    public string GetData() {
        return "Jakieś dane";
    }
    public void Format() {
        Console.WriteLine("Formatowanie...");
    }
    public void Print() {
        Console.WriteLine("Drukowanie...");
    }
}

//Tu dzielimy powyższą klasę z 3 metodami na 3 podklasy, każda z 1 funkcjonalnością
public class Report2 {
    public string GetData() {
        return "Jakieś dane";
    }
}

public class ReportFormat {
    public string Format(string data) {
        return $"Sformatowane dane: {data}";
    }
}

public class ReportPrint {
    public void Print(string data) {
        Console.WriteLine($"Drukowanie danych: {data}");
    }
}

public class Zad2 {
    public static void Main() {
        var data = new Report2();
        var format = new ReportFormat();
        var print = new ReportPrint();
        string sth = data.GetData();
        string form = format.Format(sth);
        print.Print(form);
    }
}