
using System;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using UnityEngine;

public class TCPManager : Singleton<TCPManager>
{
    private TcpClient connection;
    private Thread recvThread;
    private int headerLength = 4;
    private int maxDataLength = 512;


    void Start()
    {
        ConnectToServer();
    }


    private void ConnectToServer()
    {
        try
        {
            string serverHost = "127.0.0.1";
            int port = 9404;
            connection = new TcpClient(serverHost, port);
            recvThread = new Thread(new ThreadStart(ReadDataThread))
            {
                IsBackground = true
            };
            recvThread.Start();
        }
        catch (Exception e)
        {
            Debug.LogError("connect server error " + e);
        }
    }

    private void ReadDataThread()
    {
        try
        {
            Byte[] bytes = new Byte[headerLength + maxDataLength];
            while (true)
            {
                using (NetworkStream stream = connection.GetStream())
                {
                    int length;
                    while ((length = stream.Read(bytes, 0, bytes.Length)) != 0)
                    {
                        var data = new byte[length];
                        Array.Copy(bytes, 0, data, 0, length);
                        String serverMessage = Encoding.ASCII.GetString(data);
                        Debug.Log(serverMessage);
                    }
                }
            }
        }
        catch (SocketException e)
        {
            Debug.Log("read error " + e);
        }
    }

    // Endian Change
    byte[] INT2LE(int data)
    {
        byte[] b = new byte[4];
        b[0] = (byte)data;
        b[1] = (byte)(((uint)data >> 8) & 0xFF);
        b[2] = (byte)(((uint)data >> 16) & 0xFF);
        b[3] = (byte)(((uint)data >> 24) & 0xFF);
        return b;
    }
    byte[] INT2BE(int data)
    {
        byte[] b = new byte[4];
        b[3] = (byte)data;
        b[2] = (byte)(((uint)data >> 8) & 0xFF);
        b[1] = (byte)(((uint)data >> 16) & 0xFF);
        b[0] = (byte)(((uint)data >> 24) & 0xFF);
        return b;
    }

    public void EnqueueToSendData()
    {
        try
        {
            NetworkStream stream = connection.GetStream();
            if (stream.CanWrite)
            {
                string clientMessage = "ThisisAMESSAGE";
                byte[] clientMessageAsByteArray = Encoding.ASCII.GetBytes(clientMessage);
                byte[] buffer = new byte[clientMessageAsByteArray.Length + 4];
                int curLen = clientMessageAsByteArray.Length;
                for (int i = 3; i >= 0; i--)
                {
                    if (curLen == 0)
                    {
                        buffer[i] = 32;
                        continue;
                    }
                    buffer[i] = (byte)(curLen % 10 + 48);
                    curLen /= 10;
                }
                clientMessageAsByteArray.CopyTo(buffer, 4);
                stream.BeginWrite(buffer, 0, buffer.Length, (IAsyncResult ar) =>
                {

                }, this);

            }
        }
        catch (SocketException socketException)
        {
            Debug.Log("Socket exception: " + socketException);
        }
    }

    private void Update()
    {
        // Test
        if (Input.GetKeyUp(KeyCode.UpArrow))
        {
            EnqueueToSendData();
        }
    }
}
