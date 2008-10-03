using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Runtime.CompilerServices;
using System.Diagnostics;

namespace JHeidt.MonoMod {

    public class Server
    {
        public event EventHandler<EventArgs> ClientPutInServer;
        public event EventHandler<EventArgs> ClientDisconnect;

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private extern static string _Log(string entry);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        private extern static string _Print(string message);

        /// <summary>
        /// Called when a client is put in the server.
        /// </summary>
        protected void OnClientPutInServer() {
            if (ClientPutInServer != null) {
                ClientPutInServer(this, null);
            }
        }

        /// <summary>
        /// Called when a client disconnects.
        /// </summary>
        protected void OnClientDisconnect() {
            if (ClientDisconnect != null) {
                ClientDisconnect(this, null);
            }
        }

        /// <summary>
        /// Provides access to the SRCDS log
        /// </summary>
        public static class Log {
            /// <summary>
            /// Writes the specified message to the server log, which always appends a line.
            /// </summary>
            /// <param name="message">The message.</param>
            public static void WriteLine(string message) {
                _Log(message);
            }
        }

        /// <summary>
        /// Provides methods for interaction with the SRCDS console.
        /// </summary>
        public static class Console {

            /// <summary>
            /// Writes the specified message to the server console.
            /// </summary>
            /// <param name="message">The message.</param>
            public static void Write(string message) {
                _Print(message);
            }

            /// <summary>
            /// Writes the specified message to the server console, and appends a new line.
            /// </summary>
            /// <param name="message">The message.</param>
            public static void WriteLine(string message) {
                _Print(String.Format("{0}{1}", message, Environment.NewLine));
            }
        }
    }

}
