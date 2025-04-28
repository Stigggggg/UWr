using System;
using System.Collections.Generic;

public class Person
{
    public string Name { get; set; }
    public override string ToString() => Name;
}

public interface IPersonSource
{
    List<Person> GetPersons();
}

//1 stopień swobody - różne wczytywanie
public class XmlPersonSource : IPersonSource
{
    public List<Person> GetPersons()
    {
        return new List<Person>
        {
            new Person { Name = "XMLName1" },
            new Person { Name = "XMLName2" }
        };
    }
}

public class DbPersonSource : IPersonSource
{
    public List<Person> GetPersons()
    {
        return new List<Person>
        {
            new Person { Name = "DBName1" },
            new Person { Name = "DBName2" }
        };
    }
}

public abstract class PersonRegistry
{
    protected IPersonSource personSource;
    public PersonRegistry(IPersonSource personSource)
    {
        this.personSource = personSource;
    }
     public abstract void NotifyPersons();
}

//2 stopień swobody - różne powiadamianie/użycie
public class EmailRegistry : PersonRegistry
{
    public EmailRegistry(IPersonSource personSource) : base(personSource) { }
    public override void NotifyPersons()
    {
        foreach (var person in personSource.GetPersons())
        {
            Console.WriteLine($"[EMAIL] Wysyłanie e-maila do {person.Name}");
        }
    }
}

public class SmsRegistry : PersonRegistry
{
    public SmsRegistry(IPersonSource personSource) : base(personSource) { }
    public override void NotifyPersons()
    {
        foreach (var person in personSource.GetPersons())
        {
            Console.WriteLine($"[SMS] Wysyłanie SMS do {person.Name}");
        }
    }
}

public class Zad4
{
    public static void Main()
    {
        PersonRegistry registry1 = new EmailRegistry(new XmlPersonSource());
        registry1.NotifyPersons();
        PersonRegistry registry2 = new SmsRegistry(new DbPersonSource());
        registry2.NotifyPersons();
    }
}
