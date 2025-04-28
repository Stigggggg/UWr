using System;
using System.IO;
using System.Net;
using System.Net.Mail;
using System.Text;

public class SmtpFacade
{
    private readonly string _smtpHost;
    private readonly int _smtpPort;
    private readonly string _username;
    private readonly string _password;
    private readonly bool _enableSsl;
    
    //konstruktor z istotnymi polami
    public SmtpFacade(string smtpHost, int smtpPort, string username, string password, bool enableSsl = true)
    {
        _smtpHost = smtpHost;
        _smtpPort = smtpPort;
        _username = username;
        _password = password;
        _enableSsl = enableSsl;
    }

    //właściwa implementacja send
    public void Send(string from, string to, string subject, string body, Stream attachment, string attachmentMimeType)
    {
        using (var message = new MailMessage(from, to, subject, body))
        {
            //obsługa ewentualnego załącznika
            if (attachment != null)
            {
                var mailAttachment = new Attachment(attachment, "attachment", attachmentMimeType);
                message.Attachments.Add(mailAttachment);
            }
            //łączenie za pomocą credentials
            using (var client = new SmtpClient(_smtpHost, _smtpPort))
            {
                client.Credentials = new NetworkCredential(_username, _password);
                client.EnableSsl = _enableSsl;
                client.Send(message);
            }
        }
    }
}

class Zad1
{
    //przykład użycia
    public static void Main()
    {
        var smtp = new SmtpFacade(
            smtpHost: "smtp.example.com",
            smtpPort: 587,
            username: "your_email@example.com",
            password: "your_password"
        );
        using (var stream = new MemoryStream(Encoding.UTF8.GetBytes("Tekst z załącznikiem")))
        {
            smtp.Send(
                from: "your_email@example.com",
                to: "recipient@example.com",
                subject: "Temat",
                body: "Treść",
                attachment: stream,
                attachmentMimeType: "text/plain"
            );
        }
        Console.WriteLine("Wysłano");
    }
}
