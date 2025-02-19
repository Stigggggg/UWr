using Neo4j.Driver;

class Program
{
    private static async Task Main(string[] args)
    {
        var driver = GraphDatabase.Driver("neo4j+s://cb849312.databases.neo4j.io", AuthTokens.Basic("neo4j", "msFLVEDvMp8J2yb4yLiur6-riwV65FuM7FRNPFhkQMc"));
        var session = driver.AsyncSession();

        try
        {
            var result = await session.RunAsync("MATCH (p:Person) RETURN p.name AS Name");
            var people = await result.ToListAsync(record => new
            {
                name = record["Name"].As<string>(),
            });
            foreach (var person in people)
            {
                Console.WriteLine($"Name: {person.name}");
            }
        }
        finally
        {
            await session.CloseAsync();
            await driver.CloseAsync();
        }
    }
}