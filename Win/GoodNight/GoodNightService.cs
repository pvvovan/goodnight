using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.ServiceProcess;
using System.Text;
using System.Threading.Tasks;

namespace GoodNight
{
    public partial class GoodNightService : ServiceBase
    {
        public GoodNightService()
        {
            InitializeComponent();
        }

        private System.Threading.Timer timer;

        protected override void OnStart(string[] args)
        {
            timer = new System.Threading.Timer(OnTimerCallback);
            timer.Change(300_000, 300_000);
        }

        protected override void OnStop()
        {
            timer.Change(System.Threading.Timeout.Infinite, System.Threading.Timeout.Infinite);
            timer.Dispose();
            timer = null;
        }

        private void OnTimerCallback(object state)
        {
            DateTime utc = GetUtc();
            TimeZoneInfo tst = TimeZoneInfo.FindSystemTimeZoneById(
                                                                "Central European Standard Time");
            DateTime european = TimeZoneInfo.ConvertTime(utc, TimeZoneInfo.Utc, tst);
            if (european.Hour >= 22 && european.Minute >= 45)
            {
                Process.Start("shutdown.exe",
                    "/s /t 300 /c \"Your PC will shutdown in 5 minutes. Good Night!\"");
            }
        }

        private DateTime GetUtc()
        {
            var ntpData = new byte[48];
            ntpData[0] = 0x1B;

            var addresses = Dns.GetHostEntry("pool.ntp.org").AddressList;
            var ipEndPoint = new IPEndPoint(addresses[0], 123);
            var socket = new Socket(
                AddressFamily.InterNetwork,
                SocketType.Dgram,
                ProtocolType.Udp)
            {
                ReceiveTimeout = 3000
            };

            socket.Connect(ipEndPoint);
            socket.Send(ntpData);
            socket.Receive(ntpData);
            socket.Close();

            var intPart = ((ulong)ntpData[40] << 24) |
                            ((ulong)ntpData[41] << 16) |
                            ((ulong)ntpData[42] << 8) |
                            ntpData[43];

            var fractPart = ((ulong)ntpData[44] << 24) |
                            ((ulong)ntpData[45] << 16) |
                            ((ulong)ntpData[46] << 8) |
                            ntpData[47];

            var milliseconds = intPart * 1000 + fractPart * 1000 / 0x100000000L;
            var networkDateTime = new DateTime(1900, 1, 1).AddMilliseconds((long)milliseconds);

            return networkDateTime;
        }
    }
}
