namespace GoodNight
{
    partial class ProjectInstaller
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.serviceProcessInstallerGn = new System.ServiceProcess.ServiceProcessInstaller();
            this.serviceInstallerGn = new System.ServiceProcess.ServiceInstaller();
            // 
            // serviceProcessInstallerGn
            // 
            this.serviceProcessInstallerGn.Account = System.ServiceProcess.ServiceAccount.LocalSystem;
            this.serviceProcessInstallerGn.Password = null;
            this.serviceProcessInstallerGn.Username = null;
            // 
            // serviceInstallerGn
            // 
            this.serviceInstallerGn.Description = "Sleep well!";
            this.serviceInstallerGn.DisplayName = "GoodNight";
            this.serviceInstallerGn.ServiceName = "ServiceGN";
            // 
            // ProjectInstaller
            // 
            this.Installers.AddRange(new System.Configuration.Install.Installer[] {
            this.serviceProcessInstallerGn,
            this.serviceInstallerGn});

        }

        #endregion

        private System.ServiceProcess.ServiceProcessInstaller serviceProcessInstallerGn;
        private System.ServiceProcess.ServiceInstaller serviceInstallerGn;
    }
}