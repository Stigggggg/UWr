using System;
using System.Collections.Generic;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.DependencyInjection;

var builder = WebApplication.CreateBuilder(args);
builder.Services.AddScoped<IDapperRepository, DapperRepository>();
var app = builder.Build();

app.MapGet("/", (IDapperRepository repository) =>
{
    var names = repository.GetAllNames();
    return $"Names: {string.Join(", ", names)}";
});

app.Run();

public interface IDapperRepository : IDisposable
{
    IEnumerable<string> GetAllNames();
}

public class DapperRepository : IDapperRepository
{
    private bool _disposed = false;
    private readonly List<string> _data = new() { "Alice", "Bob", "Charlie" };

    public IEnumerable<string> GetAllNames()
    {
        if (_disposed) throw new ObjectDisposedException(nameof(DapperRepository));
        return _data;
    }

    public void Dispose()
    {
        if (!_disposed)
        {
            Console.WriteLine("DapperRepository disposed");
            _disposed = true;
        }
    }
}

