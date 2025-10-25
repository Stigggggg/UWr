using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Remoting.Contexts;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace WebApplication1
{
    public partial class WebForm1 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            string path = "C:\\Users\\mikid\\OneDrive\\Pulpit\\Studia\\UWr\\ASP.NET\\Lista 1\\zad4\\WebApplication1\\plik.txt";
            try
            {
                using (StreamReader sr = new StreamReader(path))
                {
                    string text = sr.ReadToEnd();
                    Response.Write("<h3>Odczytano plik:</h3><pre>" + text + "</pre>");
                }
            }
            catch (Exception ex)
            {
                Response.Write("<h3'>Błąd odczytu:</h3><pre>" + ex.Message + "</pre>");
            }
        }
    }
}