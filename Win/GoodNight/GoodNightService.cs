using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Linq;
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
            NtpClient.NtpConnection ntpConnection = new NtpClient.NtpConnection("pool.ntp.org");
            DateTime utc = ntpConnection.GetUtc();
            TimeZoneInfo tst = TimeZoneInfo.FindSystemTimeZoneById(
                                                                "Central European Standard Time");
            DateTime european = TimeZoneInfo.ConvertTime(utc, TimeZoneInfo.Utc, tst);
            if (european.Hour >= 22 && european.Minute >= 30)
            {
                Process.Start("shutdown.exe",
                    "/s /t 300 /c \"Your PC will shutdown in 5 minutes. Good Night!\"");
            }
        }
    }
}
