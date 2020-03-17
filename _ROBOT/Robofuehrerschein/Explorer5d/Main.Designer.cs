namespace Explorer5d {
  partial class Explorer5d {
    /// <summary>
    /// Erforderliche Designervariable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    /// Verwendete Ressourcen bereinigen.
    /// </summary>
    /// <param name="disposing">True, wenn verwaltete Ressourcen gelöscht werden sollen; andernfalls False.</param>
    protected override void Dispose(bool disposing) {
      if (disposing && (components != null)) {
        components.Dispose();
      }
      base.Dispose(disposing);
    }

    #region Vom Windows Form-Designer generierter Code

    /// <summary>
    /// Erforderliche Methode für die Designerunterstützung.
    /// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
    /// </summary>
    private void InitializeComponent() {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Explorer5d));
            this.cmdAction = new System.Windows.Forms.Button();
            this.cmdEnde = new System.Windows.Forms.Button();
            this.pnlDrive = new System.Windows.Forms.Panel();
            this.button_gearup = new System.Windows.Forms.Button();
            this.button_geardown = new System.Windows.Forms.Button();
            this.cmdZuruck = new System.Windows.Forms.Button();
            this.cmdRechts = new System.Windows.Forms.Button();
            this.cmdLinks = new System.Windows.Forms.Button();
            this.cmdVor = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.lblAbstand = new System.Windows.Forms.Label();
            this.lblHelligkeit = new System.Windows.Forms.Label();
            this.lblFarbwert = new System.Windows.Forms.Label();
            this.lblTemperatur = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.lblSpurR = new System.Windows.Forms.Label();
            this.lblSpurL = new System.Windows.Forms.Label();
            this.cmdHupe = new System.Windows.Forms.Button();
            this.cmdLicht = new System.Windows.Forms.Button();
            this.label_gear = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.pnlDrive.SuspendLayout();
            this.SuspendLayout();
            // 
            // cmdAction
            // 
            this.cmdAction.Font = new System.Drawing.Font("Tahoma", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cmdAction.Location = new System.Drawing.Point(321, 247);
            this.cmdAction.Name = "cmdAction";
            this.cmdAction.Size = new System.Drawing.Size(120, 28);
            this.cmdAction.TabIndex = 1;
            this.cmdAction.Text = "ACTION";
            this.cmdAction.UseVisualStyleBackColor = true;
            this.cmdAction.Click += new System.EventHandler(this.cmdAction_Click);
            // 
            // cmdEnde
            // 
            this.cmdEnde.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cmdEnde.Font = new System.Drawing.Font("Tahoma", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cmdEnde.Location = new System.Drawing.Point(321, 202);
            this.cmdEnde.Name = "cmdEnde";
            this.cmdEnde.Size = new System.Drawing.Size(119, 27);
            this.cmdEnde.TabIndex = 2;
            this.cmdEnde.Text = "A&bbrechen";
            this.cmdEnde.UseVisualStyleBackColor = true;
            this.cmdEnde.Click += new System.EventHandler(this.cmdEnde_Click);
            // 
            // pnlDrive
            // 
            this.pnlDrive.BackColor = System.Drawing.Color.White;
            this.pnlDrive.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.pnlDrive.Controls.Add(this.button_gearup);
            this.pnlDrive.Controls.Add(this.button_geardown);
            this.pnlDrive.Controls.Add(this.cmdZuruck);
            this.pnlDrive.Controls.Add(this.cmdRechts);
            this.pnlDrive.Controls.Add(this.cmdLinks);
            this.pnlDrive.Controls.Add(this.cmdVor);
            this.pnlDrive.Enabled = false;
            this.pnlDrive.Location = new System.Drawing.Point(24, 65);
            this.pnlDrive.Name = "pnlDrive";
            this.pnlDrive.Size = new System.Drawing.Size(220, 188);
            this.pnlDrive.TabIndex = 5;
            // 
            // button_gearup
            // 
            this.button_gearup.BackgroundImage = global::Explorer5d.Properties.Resources.fast_forward2;
            this.button_gearup.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.button_gearup.FlatAppearance.BorderSize = 0;
            this.button_gearup.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button_gearup.Location = new System.Drawing.Point(130, 50);
            this.button_gearup.Name = "button_gearup";
            this.button_gearup.Size = new System.Drawing.Size(40, 40);
            this.button_gearup.TabIndex = 16;
            this.button_gearup.UseVisualStyleBackColor = true;
            // 
            // button_geardown
            // 
            this.button_geardown.BackgroundImage = global::Explorer5d.Properties.Resources.rewind2;
            this.button_geardown.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.button_geardown.FlatAppearance.BorderSize = 0;
            this.button_geardown.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button_geardown.Location = new System.Drawing.Point(50, 50);
            this.button_geardown.Name = "button_geardown";
            this.button_geardown.Size = new System.Drawing.Size(40, 40);
            this.button_geardown.TabIndex = 15;
            this.button_geardown.UseVisualStyleBackColor = true;
            // 
            // cmdZuruck
            // 
            this.cmdZuruck.BackColor = System.Drawing.Color.Transparent;
            this.cmdZuruck.BackgroundImage = global::Explorer5d.Properties.Resources.Arrow_Down;
            this.cmdZuruck.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.cmdZuruck.FlatAppearance.BorderSize = 0;
            this.cmdZuruck.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.cmdZuruck.Location = new System.Drawing.Point(90, 90);
            this.cmdZuruck.Name = "cmdZuruck";
            this.cmdZuruck.Size = new System.Drawing.Size(40, 40);
            this.cmdZuruck.TabIndex = 3;
            this.cmdZuruck.TabStop = false;
            this.cmdZuruck.UseVisualStyleBackColor = false;
            // 
            // cmdRechts
            // 
            this.cmdRechts.BackColor = System.Drawing.Color.Transparent;
            this.cmdRechts.BackgroundImage = global::Explorer5d.Properties.Resources.Arrow_Right;
            this.cmdRechts.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.cmdRechts.FlatAppearance.BorderSize = 0;
            this.cmdRechts.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.cmdRechts.Location = new System.Drawing.Point(130, 90);
            this.cmdRechts.Name = "cmdRechts";
            this.cmdRechts.Size = new System.Drawing.Size(40, 40);
            this.cmdRechts.TabIndex = 2;
            this.cmdRechts.TabStop = false;
            this.cmdRechts.UseVisualStyleBackColor = false;
            // 
            // cmdLinks
            // 
            this.cmdLinks.BackColor = System.Drawing.Color.Transparent;
            this.cmdLinks.BackgroundImage = global::Explorer5d.Properties.Resources.Arrow_Left;
            this.cmdLinks.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.cmdLinks.FlatAppearance.BorderSize = 0;
            this.cmdLinks.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.cmdLinks.Location = new System.Drawing.Point(50, 90);
            this.cmdLinks.Name = "cmdLinks";
            this.cmdLinks.Size = new System.Drawing.Size(40, 40);
            this.cmdLinks.TabIndex = 1;
            this.cmdLinks.TabStop = false;
            this.cmdLinks.UseVisualStyleBackColor = false;
            // 
            // cmdVor
            // 
            this.cmdVor.BackColor = System.Drawing.Color.Transparent;
            this.cmdVor.BackgroundImage = global::Explorer5d.Properties.Resources.Arrow_Up;
            this.cmdVor.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.cmdVor.FlatAppearance.BorderSize = 0;
            this.cmdVor.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.cmdVor.Location = new System.Drawing.Point(90, 50);
            this.cmdVor.Name = "cmdVor";
            this.cmdVor.Size = new System.Drawing.Size(40, 40);
            this.cmdVor.TabIndex = 0;
            this.cmdVor.TabStop = false;
            this.cmdVor.UseVisualStyleBackColor = false;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(272, 147);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(51, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "Farbwert";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(272, 116);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(63, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "Temperatur";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(272, 88);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(49, 13);
            this.label4.TabIndex = 9;
            this.label4.Text = "Helligkeit";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(272, 60);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(47, 13);
            this.label5.TabIndex = 10;
            this.label5.Text = "Abstand";
            // 
            // lblAbstand
            // 
            this.lblAbstand.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.lblAbstand.Location = new System.Drawing.Point(370, 60);
            this.lblAbstand.Name = "lblAbstand";
            this.lblAbstand.Size = new System.Drawing.Size(58, 18);
            this.lblAbstand.TabIndex = 14;
            this.lblAbstand.Text = "0";
            this.lblAbstand.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lblHelligkeit
            // 
            this.lblHelligkeit.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.lblHelligkeit.Location = new System.Drawing.Point(370, 88);
            this.lblHelligkeit.Name = "lblHelligkeit";
            this.lblHelligkeit.Size = new System.Drawing.Size(58, 18);
            this.lblHelligkeit.TabIndex = 15;
            this.lblHelligkeit.Text = "0";
            this.lblHelligkeit.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lblFarbwert
            // 
            this.lblFarbwert.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.lblFarbwert.Location = new System.Drawing.Point(370, 144);
            this.lblFarbwert.Name = "lblFarbwert";
            this.lblFarbwert.Size = new System.Drawing.Size(58, 18);
            this.lblFarbwert.TabIndex = 16;
            this.lblFarbwert.Text = "0";
            this.lblFarbwert.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lblTemperatur
            // 
            this.lblTemperatur.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.lblTemperatur.Location = new System.Drawing.Point(370, 116);
            this.lblTemperatur.Name = "lblTemperatur";
            this.lblTemperatur.Size = new System.Drawing.Size(58, 18);
            this.lblTemperatur.TabIndex = 17;
            this.lblTemperatur.Text = "0";
            this.lblTemperatur.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(272, 174);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(61, 13);
            this.label6.TabIndex = 18;
            this.label6.Text = "Spursensor";
            // 
            // lblSpurR
            // 
            this.lblSpurR.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.lblSpurR.Location = new System.Drawing.Point(410, 171);
            this.lblSpurR.Name = "lblSpurR";
            this.lblSpurR.Size = new System.Drawing.Size(18, 18);
            this.lblSpurR.TabIndex = 19;
            this.lblSpurR.Text = "0";
            this.lblSpurR.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lblSpurL
            // 
            this.lblSpurL.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.lblSpurL.Location = new System.Drawing.Point(370, 171);
            this.lblSpurL.Name = "lblSpurL";
            this.lblSpurL.Size = new System.Drawing.Size(20, 18);
            this.lblSpurL.TabIndex = 20;
            this.lblSpurL.Text = "0";
            this.lblSpurL.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // cmdHupe
            // 
            this.cmdHupe.BackColor = System.Drawing.Color.Transparent;
            this.cmdHupe.BackgroundImage = global::Explorer5d.Properties.Resources.sound;
            this.cmdHupe.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.cmdHupe.FlatAppearance.BorderSize = 0;
            this.cmdHupe.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.cmdHupe.Location = new System.Drawing.Point(204, 22);
            this.cmdHupe.Name = "cmdHupe";
            this.cmdHupe.Size = new System.Drawing.Size(40, 40);
            this.cmdHupe.TabIndex = 14;
            this.cmdHupe.TabStop = false;
            this.cmdHupe.UseVisualStyleBackColor = false;
            // 
            // cmdLicht
            // 
            this.cmdLicht.BackColor = System.Drawing.Color.Transparent;
            this.cmdLicht.BackgroundImage = global::Explorer5d.Properties.Resources.weather_clear_night;
            this.cmdLicht.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.cmdLicht.FlatAppearance.BorderSize = 0;
            this.cmdLicht.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.cmdLicht.Location = new System.Drawing.Point(24, 22);
            this.cmdLicht.Name = "cmdLicht";
            this.cmdLicht.Size = new System.Drawing.Size(40, 40);
            this.cmdLicht.TabIndex = 13;
            this.cmdLicht.UseVisualStyleBackColor = false;
            // 
            // label_gear
            // 
            this.label_gear.AutoSize = true;
            this.label_gear.Enabled = false;
            this.label_gear.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label_gear.Font = new System.Drawing.Font("Tahoma", 25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_gear.ForeColor = System.Drawing.Color.Red;
            this.label_gear.Location = new System.Drawing.Point(117, 21);
            this.label_gear.Margin = new System.Windows.Forms.Padding(0);
            this.label_gear.Name = "label_gear";
            this.label_gear.Size = new System.Drawing.Size(40, 41);
            this.label_gear.TabIndex = 22;
            this.label_gear.Text = "7";
            this.label_gear.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(357, 21);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 23;
            this.button1.Text = "reset";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // Explorer5d
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cmdEnde;
            this.ClientSize = new System.Drawing.Size(463, 295);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label_gear);
            this.Controls.Add(this.cmdLicht);
            this.Controls.Add(this.cmdHupe);
            this.Controls.Add(this.lblSpurL);
            this.Controls.Add(this.lblSpurR);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.lblTemperatur);
            this.Controls.Add(this.lblFarbwert);
            this.Controls.Add(this.lblHelligkeit);
            this.Controls.Add(this.lblAbstand);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.pnlDrive);
            this.Controls.Add(this.cmdEnde);
            this.Controls.Add(this.cmdAction);
            this.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.KeyPreview = true;
            this.MaximizeBox = false;
            this.Name = "Explorer5d";
            this.Text = "ROBO Explorer : Fernsteuerung und Autopilot";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.formClosing);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Explorer5d_KeyDown);
            this.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.Explorer5d_KeyPress);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.Explorer5d_KeyUp);
            this.pnlDrive.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.Button cmdAction;
    private System.Windows.Forms.Button cmdEnde;
    private System.Windows.Forms.Panel pnlDrive;
    private System.Windows.Forms.Button cmdZuruck;
    private System.Windows.Forms.Button cmdRechts;
    private System.Windows.Forms.Button cmdLinks;
    private System.Windows.Forms.Button cmdVor;
    private System.Windows.Forms.Label label2;
    private System.Windows.Forms.Label label3;
    private System.Windows.Forms.Label label4;
    private System.Windows.Forms.Label label5;
    private System.Windows.Forms.Label lblAbstand;
    private System.Windows.Forms.Label lblHelligkeit;
    private System.Windows.Forms.Label lblFarbwert;
    private System.Windows.Forms.Label lblTemperatur;
    private System.Windows.Forms.Label label6;
    private System.Windows.Forms.Label lblSpurR;
    private System.Windows.Forms.Label lblSpurL;
    private System.Windows.Forms.Button cmdHupe;
    private System.Windows.Forms.Button cmdLicht;
    private System.Windows.Forms.Button button_gearup;
    private System.Windows.Forms.Button button_geardown;
    private System.Windows.Forms.Label label_gear;
    private System.Windows.Forms.Button button1;
  }
}

