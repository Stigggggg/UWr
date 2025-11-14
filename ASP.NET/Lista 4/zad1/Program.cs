using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Routing;
using Microsoft.AspNetCore.Routing.Matching;
using Microsoft.AspNetCore.Routing.Patterns;

var builder = WebApplication.CreateBuilder(args);
// zakomentować dla testów bez konfliktu, bo ma selektor
builder.Services.AddSingleton<EndpointSelector, CustomEndpointSelector>();
var app = builder.Build();

// ograniczenie typu
app.MapGet("/type/{id:int}", (int id) =>
{
    return $"Matched /type/{{id:int}} → value = {id}";
});

// ograniczenie długości
app.MapGet("/length/{name:length(5,10)}", (string name) =>
{
    return $"Matched /length/{{name:length(5,10)}} → value = {name}";
});

// ograniczenie wymagalności
app.MapGet("/required/{value:required}", (string value) =>
{
    return $"Matched /required/{{value:required}} → value = {value}";
});

// opisanie regexem
app.MapGet("/regex/{code:regex(^[A-Z]{{3}}[0-9]{{2}}$)}", (string code) =>
{
    return $"Matched /regex/{{{{code:regex}}}} → value = {code}";
});

// konflikt
app.MapGet("/conflict/{value}", (string value) =>
{
    return $"General match: {value}";
});

app.MapGet("/conflict/{value:int}", (int value) =>
{
    return $"Integer match: {value}";
});

app.Run();

// własny selektor punktów końcowych
class CustomEndpointSelector : EndpointSelector
{
    public override async Task SelectAsync(HttpContext httpContext, CandidateSet candidates)
    {
        CandidateState selectedCandidate = new CandidateState();

        for (var i = 0; i < candidates.Count; i++)
        {
            if (candidates.IsValidCandidate(i))
            {
                selectedCandidate = candidates[i];
                break;
            }
        }

        httpContext.SetEndpoint(selectedCandidate.Endpoint);
        httpContext.Request.RouteValues = selectedCandidate.Values;
    }
}



