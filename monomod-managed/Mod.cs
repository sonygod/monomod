using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;

namespace JHeidt.MonoMod
{
    public class Mod
    {
        private readonly Server _Server;

        /// <summary>
        /// Initializes a new instance of the <see cref="Mod"/> class.
        /// </summary>
        public Mod() 
        {
            Server.Console.WriteLine("Mod constructor");
            _Server = new Server();
            _Server.ClientDisconnect += Server_ClientDisconnect;
            _Server.ClientPutInServer += Server_ClientPutInServer;
        }

        /// <summary>
        /// Handles the ClientPutInServer event of the Server.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        void Server_ClientPutInServer(object sender, EventArgs e) {
            Server.Console.WriteLine("Server_ClientPutInServer");
        }

        /// <summary>
        /// Handles the ClientDisconnect event of the Server.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        void Server_ClientDisconnect(object sender, EventArgs e) {
            Server.Console.WriteLine("Server_ClientDisconnect");
        }

        /// <summary>
        /// Called when the mod is starting.
        /// </summary>
        public void OnStart() 
        {
            Server.Console.WriteLine("Mod.OnStart()");
        }

        /// <summary>
        /// Called when the mod is shutting down.
        /// </summary>
        public void OnShutdown() 
        {
            Server.Console.WriteLine("Mod.OnShutdown()");
        }
    }
}
