using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace zad1
{
    public class CustomHttpHandler : IHttpHandler
    {
        public bool IsReusable
        {
            get
            {
                return false;
            }
        }

        public void ProcessRequest(HttpContext context)
        {
            context.Response.ContentType = "text/html";

            // 1 kropka - pełny adres żądania
            string fullUrl = context.Request.Url.ToString();
            context.Response.Write("<b>Pełny adres żądania:</b>" + fullUrl + "<br><br>");

            // 2 kropka - nagłówki
            context.Response.Write("<b>Nagłówki HTTP:</b><br>");
            foreach (string header in context.Request.Headers)
            {
                string value = context.Request.Headers[header];
                context.Response.Write(header + ": " + value + "<br>");
            }
            context.Response.Write("<br>");

            // 3 kropka - żądanie
            string verb = context.Request.HttpMethod;
            context.Response.Write("<b>HTTP verb:</b> " + verb + "<br>");

            // 4 kropka - treść POST
            if (verb == "POST" && context.Request.InputStream.Length > 0) 
            {
                context.Request.InputStream.Position = 0;
                using (var reader = new System.IO.StreamReader(context.Request.InputStream))
                {
                    string requestBody = reader.ReadToEnd();
                    if (!string.IsNullOrEmpty(requestBody))
                    {
                        context.Response.Write("<b>Treść żądania POST:</b><br>" + System.Web.HttpUtility.HtmlEncode(requestBody));
                    }
                }
            }
            else
            {
                context.Response.Write("<br>Żądanie nie było POST, więc nie ma treści");
            }
        }
    }
}