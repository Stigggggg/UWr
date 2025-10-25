using System;
using System.Data.SqlClient;
using System.Web.UI.WebControls;
using System.Xml.Linq;

namespace zad4
{
    public partial class start : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                tasks.DataSource = new int[10]; // 10 pól na zadania
                tasks.DataBind();
            }
        }

        protected void btnSubmit_Click(object sender, EventArgs e)
        {
            label.Text = "";

            // 1) Walidacja pól
            if (string.IsNullOrWhiteSpace(name.Text))
            {
                label.Text = "Pole 'Imię i nazwisko' nie może być puste.";
                return;
            }

            if (!DateTime.TryParse(date.Text, out _))
            {
                label.Text = "Pole 'Data' musi być poprawną datą (np. 2025-01-15).";
                return;
            }

            // 2) Walidacja punktów
            string[] taskPoints = new string[tasks.Items.Count];
            for (int i = 0; i < tasks.Items.Count; i++)
            {
                TextBox txt = tasks.Items[i].FindControl("points") as TextBox;
                string val = txt.Text.Trim();
                if (val == "") val = "0";

                if (!int.TryParse(val, out int pts) || pts < 0)
                {
                    label.Text = $"Nieprawidłowa liczba punktów w zadaniu {i + 1}.";
                    return;
                }
                taskPoints[i] = val;
            }

            string pointsCsv = string.Join(",", taskPoints);

            // 3) Przekierowanie z danymi w QueryString
            string url = $"print.aspx?name={Server.UrlEncode(name.Text)}" +
                         $"&date={Server.UrlEncode(date.Text)}" +
                         $"&course={Server.UrlEncode(course.Text)}" +
                         $"&set={Server.UrlEncode(set.Text)}" +
                         $"&points={Server.UrlEncode(pointsCsv)}";

            Response.Redirect(url, false);
        }
    }
}
