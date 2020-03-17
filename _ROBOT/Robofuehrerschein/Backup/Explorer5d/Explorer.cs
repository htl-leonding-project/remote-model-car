// -------------------------------------------------------------------------------------
//
// Explorer.cs                                                   Ulrich Müller  26.05.08
//                                                               PCS1700 C# 2005 Express
// Klasse zum Betrieb des ROBO Explorers
// FishFace2005.DLL wird genutzt, Anwendung using FishFace40;
//
// -------------------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using FishFace40;

namespace Explorer5d
{
    public struct DatenEingaenge
    {
        public bool SpurL;
        public bool SpurR;
        public int Distance;
        public int Temperatur;
        public int Farbe;
        public int Helligkeit;
    }

    public struct Farben
    {
        public int blauMin;
        public int blauMax;
        public int gruenMin;
        public int gruenMax;
        public int rotMin;
        public int rotMax;
    }

    class Explorer
    {

        // --- private globale Variable ---------------

        public FishFace ft = new FishFace();
        Thread MessungEingaenge;
        Thread TemperaturMelder;
        Thread LichtSchaltung;
        Thread FarbErkennung;
        Thread SpurFahren;

        Speed geschwindigkeit = Speed.Full;
        DatenEingaenge messung = new DatenEingaenge();
        int heissMax = 400;
        int dunkelMin = 500;
        int disMin = 12;
        Farben grenzFarben = new Farben();
        bool aufSpur = true;
        bool tempStop = false;
        bool lichtStop = false;
        bool farbStop = false;
        bool spurStop = false;

        // --- Belegung des ROBO Interfaces an USB ------------

        const Out mLinks = Out.M2;
        const Out mRechts = Out.M1;
        const Dir cVor = Dir.Left;
        const Dir cRuck = Dir.Right;
        const Dir cOff = Dir.Off;

        const Out oLampeR = Out.O5;
        const Out oLampeL = Out.O6;
        const Out oLampeT = Out.O7;
        const Out oHupe = Out.M3;

        const Inp iImpulsL = Inp.I1;
        const Inp iSpurR = Inp.I3;
        const Inp iSpurL = Inp.I4;

        const Inp dUltra = Inp.D1;

        const Inp aLicht = Inp.AX;
        const Inp aTemp = Inp.AY;

        const Inp aFarbe = Inp.A1;

        public delegate void Messwerte(object sender, DatenEingaenge Werte);
        public event Messwerte WerteEingaenge;

        public void RotAn()
        {
            ft.SetLamp(oLampeT,Dir.On);
        }
        public void RotAus()
        {
            ft.SetLamp(oLampeT,Dir.Off);
        }

        public Explorer()
        {
            grenzFarben.blauMin = 240; grenzFarben.blauMax = 260;
            grenzFarben.gruenMin = 200; grenzFarben.gruenMax = 220;
            grenzFarben.rotMin = 170; grenzFarben.rotMax = 190;
        }

        public void OpenExplorer(IFTypen iTyp, int SerialNr)
        {
            ft.OpenInterface(iTyp, SerialNr);
            if (WerteEingaenge != null)
            {
                MessungEingaenge = new Thread(MessLoop);
                MessungEingaenge.IsBackground = true;
                MessungEingaenge.Start();
            }
        }
        public void OpenExplorer()
        {
            OpenExplorer(IFTypen.ftROBO_first_USB, 0);
        }
        public void CloseExplorer()
        {
            ft.NotHalt = true;
            if (WerteEingaenge != null) MessungEingaenge.Join();
            StopTemperaturUeberwachung();
            StopLichtUeberwachung();
            StopFarbUeberwachung();
            ft.CloseInterface();
        }

        // --- Eigenschaften -----

        public Speed Geschwindigkeit
        {
            get { return geschwindigkeit; }
            set
            {
                geschwindigkeit = value;
                if (up)
                {
                    this.Vorwaerts(this.geschwindigkeit);
                }
                else if (down)
                {
                    this.Rueckwaerts(this.geschwindigkeit);
                }
                else if (right)
                {
                    this.DrehenRechts(this.geschwindigkeit);
                }
                else if (left)
                {
                    this.DrehenLinks(this.geschwindigkeit);
                }
            }
        }
        public int MinimalDistance
        {
            get { return disMin; }
            set { disMin = value; }
        }
        public DatenEingaenge MessDaten
        {
            get
            {
                messung.Distance = ft.GetDistance(dUltra);
                messung.Farbe = ft.GetVoltage(aFarbe);
                messung.Helligkeit = ft.GetAnalog(aLicht);
                messung.SpurL = !ft.GetInput(iSpurL);
                messung.SpurR = !ft.GetInput(iSpurR);
                messung.Temperatur = ft.GetAnalog(aTemp);
                return messung;
            }
        }
        public int HeissMax
        {
            get { return heissMax; }
            set { heissMax = value; }
        }
        public int DunkelMin
        {
            get { return dunkelMin; }
            set { dunkelMin = value; }
        }
        public Farben FarbGrenzen
        {
            get { return grenzFarben; }
            set { grenzFarben = value; }
        }

        public bool LichtIstAn
        {
            get { return lichtistan; }
            set { lichtistan = value; }
        }


        // --- Methoden : Fahren ---

        private bool left = false, up = false, down = false, right = false;

        public void StoppUp()
        {
            up = false;
            if (down)
            {
                if (right)
                    DrehenLinks(this.geschwindigkeit);
                if (left)
                    DrehenRechts(this.geschwindigkeit);
                else
                    Rueckwaerts(this.geschwindigkeit);
            }
            else if (right)
            {
                DrehenRechts(this.geschwindigkeit);
            }
            else if (left)
            {
                DrehenLinks(this.geschwindigkeit);
            }
            else if (!down && !right && !left)
            {
                ft.SetMotor(mLinks, cOff);
                ft.SetMotor(mRechts, cOff);
            }
        }
        public void StoppDown()
        {
            down = false;
            if (up)
            {
                if (right)
                    DrehenRechts(this.geschwindigkeit);
                if (left)
                    DrehenLinks(this.geschwindigkeit);
                else
                    Vorwaerts(this.geschwindigkeit);
            }
            else if (right)
            {
                DrehenRechts(this.geschwindigkeit);
            }
            else if (left)
            {
                DrehenLinks(this.geschwindigkeit);
            }
            else if (!up && !right && !left)
            {
                ft.SetMotor(mLinks, cOff);
                ft.SetMotor(mRechts, cOff);
            }
        }
        public void StoppRechts(Speed Geschwindigkeit)
        {
            right = false;
            if (up)
            {
                if (right)
                    DrehenRechts(this.geschwindigkeit);
                if (left)
                    DrehenLinks(this.geschwindigkeit);
                else
                    Vorwaerts(this.geschwindigkeit);
            }else
                if (down)
                {
                    if (right)
                        DrehenLinks(this.geschwindigkeit);
                    if (left)
                        DrehenRechts(this.geschwindigkeit);
                    else
                        Rueckwaerts(this.geschwindigkeit);
                }
                else if (left)
                {
                    DrehenLinks(this.geschwindigkeit);
                }
                else if (!up && !down && !left)
                {
                    ft.SetMotor(mLinks, cOff);
                    ft.SetMotor(mRechts, cOff);
                }
        }
        public void StoppRechts()
        {
            StoppRechts(geschwindigkeit);
        }
        public void StoppLinks(Speed Geschwindigkeit)
        {
            left = false;
            if (up)
            {
                if (right)
                    DrehenRechts(this.geschwindigkeit);
                if (left)
                    DrehenLinks(this.geschwindigkeit);
                else
                    Vorwaerts(this.geschwindigkeit);
            }
            else if (down)
            {
                if (right)
                    DrehenLinks(this.geschwindigkeit);
                if (left)
                    DrehenRechts(this.geschwindigkeit);
                else
                    Rueckwaerts(this.geschwindigkeit);
            }
            else if (right)
            {
                DrehenRechts(this.geschwindigkeit);
            }
            else if (!up && !down && !right)
            {
                ft.SetMotor(mLinks, cOff);
                ft.SetMotor(mRechts, cOff);
            }
        }

        public void Finish()
        {
            int time = 0;
            while (time < 1000)
            {
                HupeEin();
                Thread.Sleep(150);
                HupeAus();
                Thread.Sleep(150);
                time += 300;
            }
        }

        public void Stopp()
        {
            try
            {
                right = false;
                left = false;
                up = false;
                down = false;
                ft.SetMotor(mLinks, cOff);
                ft.SetMotor(mRechts, cOff);
            }
            catch (Exception) { }
        }
        public void StoppLinks()
        {
            StoppLinks(geschwindigkeit);
        }
        public void Vorwaerts(Speed Geschwindigkeit)
        {
            if (this.MessDaten.Distance < this.MinimalDistance)
                return;
            if (left && !right)
            {
                DrehenLinks(Geschwindigkeit);
            }
            else if (right && !left)
            {
                DrehenRechts(Geschwindigkeit);
            }
            else if (!down)
            {
                up = true;
                ft.SetMotor(mLinks, cRuck, Geschwindigkeit);
                ft.SetMotor(mRechts, cVor, Geschwindigkeit);
            }
            else
            {
                ft.SetMotor(mLinks, cOff);
                ft.SetMotor(mRechts, cOff);
            }
        }
        public void Vorwaerts()
        {
            Vorwaerts(geschwindigkeit);
        }
        public void Rueckwaerts(Speed Geschwindigkeit)
        {
            
            if (left && !right)
            {
                DrehenRechts(Geschwindigkeit);
            }
            else if (right && !left)
            {
                DrehenLinks(Geschwindigkeit);
            }
            else if (!up)
            {
                down = true;
                ft.SetMotor(mLinks, cVor, Geschwindigkeit);
                ft.SetMotor(mRechts, cRuck, Geschwindigkeit);
            }
            else
            {
                ft.SetMotor(mLinks, cOff);
                ft.SetMotor(mRechts, cOff);
            }
        }
        public void Rueckwaerts()
        {
            Rueckwaerts(geschwindigkeit);
        }
        public void DrehenLinks(Speed Geschwindigkeit)
        {
            left = true;
            ft.SetMotor(mLinks, cVor, Geschwindigkeit);
            ft.SetMotor(mRechts, cVor, Geschwindigkeit);
        }
        public void DrehenLinks()
        {
            left = true;
            DrehenLinks(geschwindigkeit);
        }
        public void DrehenRechts(Speed Geschwindigkeit)
        {
            right = true;
            ft.SetMotor(mLinks, cRuck, Geschwindigkeit);
            ft.SetMotor(mRechts, cRuck, Geschwindigkeit);
        }
        public void DrehenRechts()
        {
            right = true;
            DrehenRechts(geschwindigkeit);
        }

        // --- Methoden : Erweitertes Fahren -----

        //public bool HindernisErkennung()
        //{
        //    if (ft.GetDistance(dUltra) < disMin) return false;
        //    Stopp();
        //    ft.Pause(1000);
        //    Rueckwaerts(Speed.Half);
        //    ft.WaitForGreater(dUltra, disMin);
        //    Stopp();
        //    DrehenLinks(Speed.Half);
        //    ft.Pause(500);
        //    return true;
        //}
        //public void Spursuche()
        //{
        //    int Zahler;
        //    aufSpur = false;
        //    while (!ft.Finish())
        //    {
        //        Zahler = 52;
        //        DrehenLinks();
        //        do
        //        {
        //            if (!ft.GetInput(iSpurL) || !ft.GetInput(iSpurR))
        //            {
        //                Stopp(); aufSpur = true; return;
        //            }
        //            ft.WaitForHigh(iImpulsL);
        //            if (HindernisErkennung()) { Zahler = 52; DrehenLinks(); }
        //            else Zahler--;
        //        } while (Zahler > 0 && !ft.Finish());
        //        Zahler = 10;
        //        Vorwaerts(Speed.Half);
        //        do
        //        {
        //            if (!ft.GetInput(iSpurL) || !ft.GetInput(iSpurR))
        //            {
        //                Stopp(); aufSpur = true; return;
        //            }
        //            ft.WaitForHigh(iImpulsL);
        //            if (HindernisErkennung()) Zahler = 0;
        //            else Zahler--;
        //        } while (Zahler > 0 && !ft.Finish());
        //    }
        //}

        // --- Methoden : Licht, Hupe ---

        private bool lichtistan = false;

        public void LichtAn()
        {
            lichtistan = true;
            ft.SetLamp(oLampeL, Dir.On);
            ft.SetLamp(oLampeR, Dir.On);
        }
        public void LichtAus()
        {
            lichtistan = false;
            ft.SetLamp(oLampeL, Dir.Off);
            ft.SetLamp(oLampeR, Dir.Off);
        }
        public void HupeEin() { ft.SetMotor(oHupe, Dir.On); }
        public void HupeAus() { ft.SetMotor(oHupe, Dir.Off); }
        public void Hupen(int nMal, int Dauer)
        {
            for (int i = 0; i < nMal; i++)
            {
                HupeEin();
                ft.Pause(Dauer);
                HupeAus();
                ft.Pause(Dauer);
            }
        }
        public void HupenKonzert()
        {
            HupeEin();
            ft.Pause(150);
            HupeAus();
            ft.Pause(100); 
            
            HupeEin();
            ft.Pause(200);
            HupeAus();
            ft.Pause(150); 
            
            HupeEin();
            ft.Pause(100);
            HupeAus();
            ft.Pause(100);

            HupeEin();
            ft.Pause(250);
            HupeAus();
            ft.Pause(150);

            HupeEin();
            ft.Pause(100);
            HupeAus();
            ft.Pause(200);

            HupeEin();
            ft.Pause(250);
            HupeAus();
            ft.Pause(100);
        }

        // --- Thread Routinen ---

        private void MessLoop()
        {
            while (!ft.Finish())
            {
                WerteEingaenge(this, MessDaten);
                ft.Pause(111);
            }
        }
        public void StartTemperaturUeberwachung()
        {
            TemperaturMelder = new Thread(TempLoop);
            TemperaturMelder.IsBackground = true;
            tempStop = false;
            TemperaturMelder.Start();
        }
        public void StopTemperaturUeberwachung()
        {
            if (TemperaturMelder != null)
            {
                tempStop = true;
                TemperaturMelder.Join();
            }
        }
        private void TempLoop()
        {
            while (!tempStop && !ft.Finish())
            {
                if ((ft.GetAnalog(aTemp)) < heissMax)
                {
                    ft.SetLamp(oLampeT, Dir.On);
                    ft.Pause(100);
                    ft.SetLamp(oLampeT, Dir.Off);
                    ft.Pause(600);
                }
            }
        }
        public void StartLichtUeberwachung()
        {
            LichtSchaltung = new Thread(LichtLoop);
            LichtSchaltung.IsBackground = true;
            lichtStop = false;
            LichtSchaltung.Start();
        }
        public void StopLichtUeberwachung()
        {
            if (LichtSchaltung != null)
            {
                lichtStop = true;
                LichtSchaltung.Join();
            }
        }
        private void LichtLoop()
        {
            while (!lichtStop && !ft.Finish())
            {
                if (ft.GetAnalog(aLicht) > dunkelMin) LichtAn();
                else LichtAus();
            }
        }
        public void StartFarbUeberwachung()
        {
            FarbErkennung = new Thread(FarbLoop);
            FarbErkennung.IsBackground = true;
            farbStop = false;
            FarbErkennung.Start();
        }
        public void StopFarbUeberwachung()
        {
            if (FarbErkennung != null)
            {
                farbStop = true;
                FarbErkennung.Join();
            }
        }
        private void FarbLoop()
        {
            int farbe;
            while (!farbStop && !ft.Finish())
            {
                if (aufSpur)
                {
                    farbe = ft.GetVoltage(aFarbe);
                    if (farbe > grenzFarben.blauMin && farbe < grenzFarben.blauMax)
                        Hupen(4, 100);
                    if (farbe > grenzFarben.gruenMin && farbe < grenzFarben.gruenMax)
                        Hupen(3, 300);
                    if (farbe > grenzFarben.rotMin && farbe < grenzFarben.rotMax)
                        Hupen(2, 600);
                }
            }
        }
        public void StopSpurfahren()
        {
            if (SpurFahren != null)
            {
                spurStop = true;
                SpurFahren.Join();
            }
        }

    }
}