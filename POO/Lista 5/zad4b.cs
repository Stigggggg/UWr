using System;
using System.Collections.Generic;

//Wersja 2 - na odwrót
public class Person
{
    public string Name { get; set; }
    public override string ToString() => Name;
}

public interface IPersonNotifier
{
    void Notify(Person person);
}

public class EmailNotifier : IPersonNotifier
{
    public void Notify(Person person)
    {
        Console.WriteLine($"[EMAIL] Wysyłanie e-maila do {person.Name}");
    }
}

public class SmsNotifier : IPersonNotifier
{
    public void Notify(Person person)
    {
        Console.WriteLine($"[SMS] Wysyłanie SMS do {person.Name}");
    }
}

public abstract class PersonRegistryReversed
{
    protected IPersonNotifier notifier;
    public PersonRegistryReversed(IPersonNotifier notifier)
    {
        this.notifier = notifier;
    }
    public abstract List<Person> GetPersons();
    public void NotifyPersons()
    {
        foreach (var person in GetPersons())
        {
            notifier.Notify(person);
        }
    }
}

public class XmlRegistryReversed : PersonRegistryReversed
{
    public XmlRegistryReversed(IPersonNotifier notifier) : base(notifier) { }

    public override List<Person> GetPersons()
    {
        return new List<Person>
        {
            new Person { Name = "XMLName1" },
            new Person { Name = "XMLName2" }
        };
    }
}


public class DbRegistryReversed : PersonRegistryReversed
{
    public DbRegistryReversed(IPersonNotifier notifier) : base(notifier) { }

    public override List<Person> GetPersons()
    {
        return new List<Person>
        {
            new Person { Name = "DBName1" },
            new Person { Name = "DBName2" }
        };
    }
}

public class Zad4b
{
    public static void Main()
    {
        PersonRegistryReversed registry1 = new XmlRegistryReversed(new EmailNotifier());
        registry1.NotifyPersons();
        PersonRegistryReversed registry2 = new DbRegistryReversed(new SmsNotifier());
        registry2.NotifyPersons();
    }
}
