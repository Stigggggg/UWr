<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="print.aspx.cs" Inherits="zad4.Print" %>

<!DOCTYPE html>
<html>
<head runat="server">
    <title>Formularz wydruku</title>
    <style>
        table {
            border-collapse: collapse;
            width: 50%;
        }
        td, th {
            border: 1px solid #333;
            padding: 8px;
        }
    </style>
</head>
<body>
    <h2>Pasek zgłoszenia zadań – podgląd wydruku</h2>
    <form id="form1" runat="server">
        <asp:Literal ID="litOutput" runat="server"></asp:Literal>
    </form>
</body>
</html>

