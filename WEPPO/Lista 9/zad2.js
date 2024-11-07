var mssql=require('mssql');

async function main() 
{
    var conn=new mssql.ConnectionPool('server=localhost,1433;database=WEPPO;trustServerCertificate=true;user id=foo;password=foo');
    try 
    {
        await conn.connect();
        var request=new mssql.Request(conn);
        var result=await request.query('select * from dbo.Osoba_v2');
        result.recordset.forEach(r=>{
            console.log(`${r.ID} ${r.Imię}`);
        });
        await conn.close();
    }
    catch(err) 
    {
        if(conn.connected)
            conn.close();
        console.log(err);
    }
}
main();
console.log("abcd");