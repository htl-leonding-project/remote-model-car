using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Explorer5d {
  static class Program {
    /// <summary>
    /// Der Haupteinstiegspunkt für die Anwendung.
    /// </summary>
    [STAThread]
    static void Main() {
      Application.EnableVisualStyles();
      Application.SetCompatibleTextRenderingDefault(false);
      Application.Run(new Explorer5d());
    }
  }
}