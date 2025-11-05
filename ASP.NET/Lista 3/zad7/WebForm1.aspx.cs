using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Xml.Linq;
using System.Xml.Schema;

namespace zad7
{
    public partial class WebForm1 : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void ButtonUpload_Click(object sender, EventArgs e)
        {
            if (FileUpload1.HasFile)
            {
                string name = FileUpload1.FileName;
                int size = FileUpload1.PostedFile.ContentLength;
                byte[] bytes = FileUpload1.FileBytes;
                int mod = bytes.Sum(b => (int)b) % 0xFFFF;
                XDocument xml = new XDocument(
                    new XElement("opis",
                        new XElement("nazwa", name),
                        new XElement("rozmiar", size.ToString()),
                        new XElement("sygnatura", mod.ToString())
                    )
                );
                string xmlstr = xml.ToString();
                Response.Clear();
                Response.ContentType = "application/xml";
                string encoded = Uri.EscapeDataString(name); // RFC5987
                string header = $"attachment; filename=\"{name}\"; filename*=UTF-8''{encoded}"; // attachment - załącznik, inline - otwierany wewnątrz przeglądarki, np. PDF
                Response.AddHeader("Content-Disposition", header); // mówimy, że to plik do pobrania, nie do wyświetlenia
                Response.Write(xmlstr);
                Response.End();
            }
            else
            {
                Response.Write("Nie podano pliku.");
            }
        }
    }
}