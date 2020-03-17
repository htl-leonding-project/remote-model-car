// --------------------------------------------------------------------------------------
//
// Ex5dMain.cs                                                    Ulrich Müller  27.05.08
//                                                                PCS1700 C# 2005 Express
// Explorer : Bedienoberfläche für den ROBO Explorer über das RF Datalink
//            Zusätzlich ein AUTOPILOT für das Fahren a la Explorer3
//            Genutzt wird die Klasse Explorer5
//            Basis ist die Assembly FishFace2005.DLL v4.3.75.2005
//
// --------------------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using FishFace40;

namespace Explorer5d
{
    public partial class Explorer5d : Form
    {
        Explorer ex = new Explorer();

        bool AufSpur;
        bool LichtAn = false;

        private void MessDaten(object sender, DatenEingaenge Werte)
        {
            lblAbstand.Text = Werte.Distance.ToString();
            //notaus
            //if (Werte.Distance < ex.MinimalDistance)
            //{
            //    ex.Stopp();
            //    ex.HupeEin();
            //    Thread.Sleep(100);
            //    ex.HupeAus();
            //    Thread.Sleep(100);
            //    ex.HupeEin();
            //    Thread.Sleep(100);
            //    ex.HupeAus();
            //    Thread.Sleep(100);
            //    ex.HupeEin();
            //    Thread.Sleep(100);
            //    ex.HupeAus();
            //}
            if (Werte.Helligkeit > 550)
            {
                if (!ex.LichtIstAn)
                    ex.LichtAn();
            }
            else
            {
                if (ex.LichtIstAn)
                    ex.LichtAus();
            }

            lblFarbwert.Text = Werte.Farbe.ToString();
            lblHelligkeit.Text = Werte.Helligkeit.ToString();
            lblTemperatur.Text = Werte.Temperatur.ToString();
            lblSpurL.Text = Werte.SpurL ? "F" : "T";
            lblSpurR.Text = Werte.SpurR ? "F" : "T";
        }

        private bool hupkonzert = false;

        private void CheckDistance()
        {
            while (checking)
            {
                if (ex.MessDaten.Distance < ex.MinimalDistance)
                {
                    ex.Stopp();
                    ex.HupeEin();
                    Thread.Sleep(150);
                    ex.HupeAus();
                    
                }
                Thread.Sleep(100);
            }
        }

        private void StartCheckDistance()
        {
            checking = true;
            new Thread(CheckDistance).Start();
        }

        private void StopCheckDistance()
        {
            checking = false;
        }

        private void HupKonzert()
        {
            while (hupkonzert)
            {
                //ex.HupeEin();
                Thread.Sleep(70);
                //ex.HupeAus();
                ex.RotAn();
                Thread.Sleep(70);
                ex.RotAus();
            }
        }

        private bool checking = false;

        private void CheckLine()
        {
            while (checking)
            {
                if (ex.MessDaten.Farbe > 250 && ex.MessDaten.Farbe < 310)
                {
                    if (!hupkonzert)
                        StartHupKonzert();
                }
                else
                {
                    StopHupKonzert();
                }
                Thread.Sleep(200);
            }
        }

        

        private void StartCheckLine()
        {
            checking = true;
            new Thread(CheckLine).Start();
        }

        private void StopCheckLine()
        {
            checking = false;
        }

        private void StartHupKonzert()
        {
            hupkonzert = true;
            new Thread(HupKonzert).Start();
        }

        private void StopHupKonzert()
        {
            hupkonzert = false;
        }

        #region --- Programm-Kontrolle ---
        public Explorer5d()
        {
            InitializeComponent();
            Label.CheckForIllegalCrossThreadCalls = false;
        }

        private void cmdAction_Click(object sender, EventArgs e)
        {
            try
            {
                ex.WerteEingaenge += new Explorer.Messwerte(MessDaten);
                ex.OpenExplorer(IFTypen.ftROBO_first_USB,0);
                cmdAction.Enabled = false;
                pnlDrive.Enabled = true;
                cmdEnde.Text = "HALT";
                StartCheckLine();
                StartCheckDistance();
                connected = true;
            }
            catch (FishFaceException eft)
            {
                connected = false;

                MessageBox.Show(eft.Source, this.Text,
                MessageBoxButtons.OK, MessageBoxIcon.Stop);
            }
        }

        private void cmdEnde_Click(object sender, EventArgs e)
        {
            if (cmdEnde.Text == "HALT")
            {
                StopCheckLine();
                StopCheckDistance();
                StopHupKonzert();
                connected = false;
                ex.CloseExplorer();
                cmdAction.Enabled = true;
                pnlDrive.Enabled = false;
                cmdEnde.Text = "ENDE";
                cmdAction.Focus();
            }
            else this.Close();
        }

        private void WinningMelody()
        {
            
        }

        private void formClosing(object sender, FormClosingEventArgs e)
        {
            if (cmdEnde.Text == "HALT") e.Cancel = true;
        }
        #endregion

        // --- Routinen Licht und Hupe Buttons --------------------



        // --- Starten / Beenden des AutoPilot Modes ----------------------

        public static string path()
        {
            string[] pfad = Environment.CurrentDirectory.Split('\\');
            string path = "";
            for (int i = 0; i < pfad.Length - 2; i++)
            {
                path += pfad[i] + "\\";
            }
            return path;
        }

        private bool connected = false;

        Image gearup2 = Image.FromFile(@""+path()+"\\Resources\\fast_forward.jpg");
        Image gearup = Image.FromFile(@""+path()+"\\Resources\\fast_forward2.jpg");
        Image rewind2 = Image.FromFile(@""+path()+"\\Resources\\rewind.jpg");
        Image rewind = Image.FromFile(@""+path()+"\\Resources\\rewind2.jpg");
        Image left = Image.FromFile(@""+path()+"\\Resources\\Arrow_Left.jpg");
        Image left2 = Image.FromFile(@""+path()+"\\Resources\\previous.jpg");
        Image right = Image.FromFile(@""+path()+"\\Resources\\Arrow_Right.jpg");
        Image right2 = Image.FromFile(@""+path()+"\\Resources\\next.jpg");
        Image up = Image.FromFile(@""+path()+"\\Resources\\Arrow_Up.jpg");
        Image up2 = Image.FromFile(@""+path()+"\\Resources\\up_red.jpg");
        Image down = Image.FromFile(@""+path()+"\\Resources\\Arrow_Down.jpg");
        Image down2 = Image.FromFile(@""+path()+"\\Resources\\down_red.jpg");
        Image horn = Image.FromFile(@""+path()+"\\Resources\\sound.jpg");
        Image horn2 = Image.FromFile(@""+path()+"\\Resources\\sound_on.jpg");
        Image light = Image.FromFile(@""+path()+"\\Resources\\weather-clear-night.jpg");
        Image light2 = Image.FromFile(@""+path()+"\\Resources\\weather-clear.jpg");

        private void Explorer5d_KeyDown(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.W:
                    cmdVor.BackgroundImage = up2;
                    if (connected)
                        ex.DrehenRechts((Speed)Int32.Parse(label_gear.Text));
                    break;
                case Keys.S:
                    cmdZuruck.BackgroundImage = down2;
                    if (connected)
                        ex.DrehenLinks((Speed)Int32.Parse(label_gear.Text));
                    break;
                case Keys.A:
                    cmdLinks.BackgroundImage = left2;
                    if (connected)
                        ex.Rueckwaerts((Speed)Int32.Parse(label_gear.Text));
                    break;
                case Keys.D:
                    cmdRechts.BackgroundImage = right2;
                    if (connected)
                        ex.Vorwaerts((Speed)Int32.Parse(label_gear.Text));
                    break;
                case Keys.H:
                    cmdHupe.BackgroundImage = horn2;
                    if (connected)
                        ex.HupeEin();
                    break;
                case Keys.E:
                    button_gearup.BackgroundImage = gearup2;
                    if (Int32.Parse(label_gear.Text) != (Int32)Speed.Full)
                    {
                        label_gear.Text = (Int32.Parse(label_gear.Text) + 1).ToString();
                        ex.Geschwindigkeit++;
                    }
                    break;
                case Keys.Q:
                    button_geardown.BackgroundImage = rewind2;
                    if (Int32.Parse(label_gear.Text) != (Int32)Speed.L1)
                    {
                        label_gear.Text = (Int32.Parse(label_gear.Text) - 1).ToString();
                        ex.Geschwindigkeit--;
                    }
                    break;
            }
        }

        private void Explorer5d_KeyUp(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.W:
                    cmdVor.BackgroundImage = up;
                    if (connected)
                        ex.StoppRechts((Speed)Int32.Parse(label_gear.Text));
                    break;
                case Keys.S:
                    cmdZuruck.BackgroundImage = down;
                    if (connected)
                        ex.StoppLinks((Speed)Int32.Parse(label_gear.Text));
                    break;
                case Keys.A:
                    cmdLinks.BackgroundImage = left;
                    if (connected)
                        ex.StoppDown();
                    break;
                case Keys.D:
                    cmdRechts.BackgroundImage = right;
                    if (connected)
                        ex.StoppUp();
                    break;
                case Keys.H:
                    cmdHupe.BackgroundImage = horn;
                    if (connected)
                        ex.HupeAus();
                    break;
                case Keys.E:
                    button_gearup.BackgroundImage = gearup;
                    break;
                case Keys.Q:
                    button_geardown.BackgroundImage = rewind;
                    break;
            }
        }

        private void Explorer5d_KeyPress(object sender, KeyPressEventArgs e)
        {
            switch (e.KeyChar)
            {
                case 'l':
                    if (ex.LichtIstAn)
                    {
                        cmdLicht.BackgroundImage = light;
                        ex.LichtIstAn = false;
                        if (connected)
                            ex.LichtAus();
                    }
                    else
                    {
                        cmdLicht.BackgroundImage = light2;
                        ex.LichtIstAn = true;
                        if (connected)
                            ex.LichtAn();
                    }
                    break;
                case 'k':
                    cmdHupe.BackgroundImage = horn2;
                    if (connected)
                    {
                        ex.HupenKonzert();
                        cmdHupe.BackgroundImage = horn;
                    }
                    break;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            ex.Stopp();
        }
    }
}