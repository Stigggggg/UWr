using System;
using System.Text;
using System.Web.UI;

namespace zad4
{
    public partial class Print : Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            string name = Request.QueryString["name"];
            string date = Request.QueryString["date"];
            string course = Request.QueryString["course"];
            string setNumber = Request.QueryString["set"];
            string points = Request.QueryString["points"];

            if (string.IsNullOrEmpty(name))
            {
                litOutput.Text = "<p style='color:red;'>Brak danych do wyświetlenia.</p>";
                return;
            }

            StringBuilder html = new StringBuilder();
            html.Append("<table>");
            html.Append($"<tr><th>Imię i nazwisko</th><td>{name}</td></tr>");
            html.Append($"<tr><th>Data</th><td>{date}</td></tr>");
            html.Append($"<tr><th>Nazwa zajęć</th><td>{course}</td></tr>");
            html.Append($"<tr><th>Numer zestawu</th><td>{setNumber}</td></tr>");
            html.Append("<tr><th colspan='2'>Wyniki zadań</th></tr>");

            if (!string.IsNullOrEmpty(points))
            {
                var arr = points.Split(',');
                for (int i = 0; i < arr.Length; i++)
                {
                    html.Append($"<tr><td>Zadanie {i + 1}</td><td>{arr[i]}</td></tr>");
                }
            }

            html.Append("</table>");
            litOutput.Text = html.ToString();
        }
    }
}
