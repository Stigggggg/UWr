using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Http;
using System.Text;

var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

app.MapGet("/", async context =>
{
    string error = context.Request.Query["error"];
    string html = $@"
        <html>
        <body>
            <h1>Prosty formularz</h1>
            {(string.IsNullOrEmpty(error) ? "" : $"<p style='color:red'>{error}</p>")}
            <form method='post' action='/submit'>
                Imie: <input type='text' name='name' /><br/>
                Wiek: <input type='text' name='age' /><br/>
                <input type='submit' value='Wyslij' />
            </form>
        </body>
        </html>";
    context.Response.ContentType = "text/html";
    await context.Response.WriteAsync(html);
});

app.MapPost("/submit", async context =>
{
    var form = await context.Request.ReadFormAsync();
    string name = form["name"];
    string ageText = form["age"];

    if (string.IsNullOrWhiteSpace(name))
    {
        context.Response.Redirect("/?error=Podaj imie!");
        return;
    }

    if (!int.TryParse(ageText, out int age) || age <= 0)
    {
        context.Response.Redirect("/?error=Wiek musi byc liczba wieksza od 0!");
        return;
    }

    context.Response.Redirect($"/print?name={Uri.EscapeDataString(name)}&age={age}");
});

app.MapGet("/print", async context =>
{
    string name = context.Request.Query["name"];
    string age = context.Request.Query["age"];

    string html = $@"
        <html>
        <body>
            <h1>Wynik formularza</h1>
            <p>Imie: {name}</p>
            <p>Wiek: {age}</p>
            <a href='/'>Powrot do formularza</a>
        </body>
        </html>";
    context.Response.ContentType = "text/html";
    await context.Response.WriteAsync(html);
});

app.Run();

