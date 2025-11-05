<%@ Page Language="C#" AutoEventWireup="true" CodeFile="start.aspx.cs" Inherits="zad4.start" %>

<!DOCTYPE html>
<html>
<head runat="server">
    <title>Deklaracja</title>
</head>
<body>
    <form id="form1" runat="server">
        <h2>Deklaracja rozwiązanych zadań</h2>

        <asp:Label ID="label" runat="server" ForeColor="Red"></asp:Label><br><br>

        Imię i nazwisko: <asp:TextBox ID="name" runat="server"></asp:TextBox><br><br>
        Data: <asp:TextBox ID="date" runat="server"></asp:TextBox><br><br>
        Przedmiot: <asp:TextBox ID="course" runat="server"></asp:TextBox><br><br>
        Lista: <asp:TextBox ID="set" runat="server"></asp:TextBox><br><br>

        <h3>Punkty za zadania:</h3>
        <asp:Repeater ID="tasks" runat="server">
            <ItemTemplate>
                Zadanie <%# Container.ItemIndex + 1 %>:
                <asp:TextBox ID="points" runat="server"></asp:TextBox><br /><br />
            </ItemTemplate>
        </asp:Repeater>

        <asp:Button ID="submit" runat="server" Text="Zatwierdź" OnClick="btnSubmit_Click" />
    </form>
</body>
</html>

