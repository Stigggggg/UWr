using System;
using System.IO;

class CaesarStream : Stream
{
    private Stream _stream;
    private int _shift;
    public CaesarStream(Stream stream, int shift)
    {
        _stream = stream ?? throw new ArgumentNullException(nameof(stream));
        _shift = shift;
    }
    public override int Read(byte[] buffer, int offset, int count) //funkcja czytająca
    {
        int bytesRead = _stream.Read(buffer, offset, count);
        for (int i = 0; i < bytesRead; i++)
        {
            buffer[i] = (byte)(buffer[i] - _shift);
        }
        return bytesRead;
    }
    public override void Write(byte[] buffer, int offset, int count) //funkcja wypisująca
    {
        for (int i = 0; i < count; i++)
        {
            buffer[i] = (byte)(buffer[i] - _shift);
        }
        _stream.Write(buffer, offset, count);
    }
    //override funkcji FileStream z System.IO
    public override bool CanRead => _stream.CanRead;
    public override bool CanSeek => _stream.CanSeek;
    public override bool CanWrite => _stream.CanWrite;
    public override long Length => _stream.Length;
    public override long Position { get => _stream.Position; set => _stream.Position = value; }
    public override void Flush() => _stream.Flush();
    public override long Seek(long offset, SeekOrigin origin) => _stream.Seek(offset, origin);
    public override void SetLength(long value) => _stream.SetLength(value);
}

class Zad2 
{
    public static void Main() 
    {
        //piszemy do pliku zaszyfrowaną wiadomość
        FileStream fileToWrite = new FileStream("plik.txt", FileMode.Create);
        CaesarStream caeToWrite = new CaesarStream(fileToWrite, 5);
        using (StreamWriter writer = new StreamWriter(caeToWrite))
        {
            writer.WriteLine("ghijklmn");
        }
        fileToWrite.Close();
        //czytamy i wypisujemy na standardowe wyjście odszyfrowaną
        FileStream fileToRead = new FileStream("plik.txt", FileMode.Open);
        CaesarStream caeToRead = new CaesarStream(fileToRead, -5);
        using (StreamReader reader = new StreamReader(caeToRead))
        {
            Console.WriteLine(reader.ReadToEnd());
        }
        fileToRead.Close();
    }
}