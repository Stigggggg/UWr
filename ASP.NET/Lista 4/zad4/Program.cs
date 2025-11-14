using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Options;
using Microsoft.Extensions.DependencyInjection;

var builder = WebApplication.CreateBuilder(args);
builder.Configuration
    .AddJsonFile("appsettings2.json", optional: true, reloadOnChange: true)
    .AddXmlFile("appsettings.xml", optional: true, reloadOnChange: true);
builder.Services.AddOptions<AppSettingsConfig>().Bind(builder.Configuration.GetSection("AppSettings"));
var app = builder.Build();

// indeksery
app.MapGet("/config",
    (IConfiguration config) =>
    {
        var fooSetting = config["foo"];
        var barSetting = config["foo2:bar2"];
        var fooSettingxml = config["foo3"];
        var barSettingxml = config["foo4:bar4"];
        return $"FooSetting: {fooSetting}, BarSetting: {barSetting} \n  FooSettingxml: {fooSettingxml}, BarSettingxml: {barSettingxml}";
    });

// GetSection
app.MapGet("/section",
    (IConfiguration config) =>
    {
        var settings = config.GetSection("AppSettings").Get<AppSettingsConfig>();
        return $"Settings: {string.Join(", ", settings.Settings.Select(s => $"{s.Key}={s.Value}"))}";

    });

// IOptions
app.MapGet("/options",
    (IOptions<AppSettingsConfig> options) =>
    {
        var settings = options.Value.Settings;
        return $"Settings (via IOptions): {string.Join(", ", settings.Select(s => $"{s.Key}={s.Value}"))}";
    });

app.Run();


public class AppSettingsConfig
{
    public KeyValueConfig[] Settings { get; set; } = [];
}


public class KeyValueConfig
{
    public string? Key { get; set; }
    public string? Value { get; set; }
}
