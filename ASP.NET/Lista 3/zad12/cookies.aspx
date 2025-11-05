<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="cookies.aspx.cs" Inherits="zad12.cookies" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <h3>Dodawanie ciastka</h3>
            <div>
                <asp:TextBox ID="cookie_name" runat="server" placeholder="Nazwa ciastka"></asp:TextBox>
            </div>
            <div>
                <asp:TextBox ID="cookie_value" runat="server" placeholder="Wartość ciastka"></asp:TextBox>
            </div>
            <div>
                <asp:Button ID="add_cookie" runat="server" Text="Dodaj ciastko" OnClick="add_cookie_click" />
            </div>

            <h3>Wyświetlanie ciastka</h3>
            <div>
                <asp:TextBox ID="cookie_rname" runat="server" placeholder="Nazwa ciastka"></asp:TextBox>
            </div>
            <div>
                <asp:Button ID="show_cookie" runat="server" Text="Pokaż ciastko" OnClick="show_cookie_click" />
            </div>
            <asp:Label ID="cookie_val" runat="server" Text=""></asp:Label>

            <h3>Usuwanie ciastka</h3>
            <div>
                <asp:TextBox ID="cookie_name_to_remove" runat="server" placeholder="Nazwa ciastka"></asp:TextBox>
            </div>
            <div>
                <asp:Button ID="remove_cookie" runat="server" Text="Usuń ciastko" OnClick="remove_cookie_click" />
            </div>

            
        </div>
    </form>
</body>
</html>
