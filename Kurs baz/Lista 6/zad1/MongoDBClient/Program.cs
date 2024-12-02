using MongoDB.Driver;

class zad1 {
    static void Main(string[] args) {
        var client = new MongoClient("mongodb://localhost:27017");
        var databases = client.ListDatabaseNames().ToList();
        databases.ForEach(Console.WriteLine);
    }
}
