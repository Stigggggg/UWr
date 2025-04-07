//Dependency Inversion Principle - moduły wyższego poziomu zależą od abstrakcji, nie od implementacji

using System;

public interface IDataProvider {
    string GetData();
}

public interface IDocumentFormatter {
    string FormatDocument(string data);
}

public interface IReportPrinter {
    void PrintReport(string formattedDocument);
}

public class DatabaseDataProvider : IDataProvider {
    public string GetData() {
        return "Jakieś dane";
    }
}

public class JsonDocumentFormatter : IDocumentFormatter {
    public string FormatDocument(string data) {
        return $"{{ \"Raport\": \"{data}\" }}";
    }
}

public class ConsoleReportPrinter : IReportPrinter {
    public void PrintReport(string formattedDocument) {
        Console.WriteLine("Drukowanie raportu: " + formattedDocument);
    }
}

public class ReportComposer {
    private readonly IDataProvider _dataProvider;
    private readonly IDocumentFormatter _documentFormatter;
    private readonly IReportPrinter _reportPrinter;

    public ReportComposer(IDataProvider dataProvider, IDocumentFormatter documentFormatter, IReportPrinter reportPrinter) {
        _dataProvider = dataProvider;
        _documentFormatter = documentFormatter;
        _reportPrinter = reportPrinter;
    }

    public void GenerateReport() {
        string data = _dataProvider.GetData();
        string formattedDocument = _documentFormatter.FormatDocument(data);
        _reportPrinter.PrintReport(formattedDocument);
    }
}

class Zad7 {
    static void Main() {
        var dataProvider = new DatabaseDataProvider();
        var formatter = new JsonDocumentFormatter();
        var printer = new ConsoleReportPrinter();
        var reportComposer = new ReportComposer(dataProvider, formatter, printer);
        reportComposer.GenerateReport();
    }
}

//Czemu to działa? Bo ReportComposer nie zależy od konkretnych implementacji tylko od abstrakcji.
//Można dodać nowy typ danych albo metodę drukowania