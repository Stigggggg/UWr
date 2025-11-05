<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="reverse.aspx.cs" Inherits="zad12.WebForm1" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title></title>
</head>
<body>
    <!-- pobieramy dokument, wywołujemy submit, co wysyła formularz na adres określony w action, return false zapobiega działaniu linka -->
    <a href="$" onclick="document.getElementById('form1').submit(); return false;">POST</a>

    <form id="form1" method="post" action="reverse.aspx">
        <input type="hidden" name="p1" value="v1" />
        <input type="hidden" name="p2" value="v2" />
    </form>

    <input type="button" value="GET request" onclick="document.location.href = 'reverse.aspx?p1=v1&p2=v2'" />
</body>
</html>
