/**
 * @file main.c
 * This file uses the Winsock library to set up a TCP server, accepts client
 * connections, and processes received data in a way that is deliberately
 * insecure, specifically by demonstrating a buffer overflow vulnerability.
 *
 * The application includes:
 * - A vulnerable function that performs an unsafe memory copy.
 * - TCP server setup and teardown using a simplified socket handling
 * interface.
 * - ROP Gadgets to be used in a WriteProcessMemory() DEP bypass.
 *
 * This setup serves as an educational tool for studying the exploitation of
 * buffer overflows and the application of Return-Oriented Programming (ROP)
 * techniques.
 *
 * Social Media Links:
 * - Twitter: https://twitter.com/7etsuo
 * - GitHub: https://github.com/7etsuo
 * - YouTube: https://www.youtube.com/@snowcrash-
 *
 * Author: 7etsuo, 2024
 */

#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "gadgets.h"
#include "my_tcp.h"

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 4996
#endif // _CRT_SECURE_NO_WARNINGS

#pragma warning(disable : _CRT_SECURE_NO_WARNINGS)
#pragma comment(lib, "Ws2_32.lib")

/**
 * Copies data from a user-provided buffer to a local buffer of fixed size,
 * demonstrating a classic buffer overflow vulnerability if sz_buf exceeds 28
 * bytes.
 * @param buf Pointer to the buffer containing data to copy.
 * @param sz_buf Size of data to copy from buf.
 */
void
vulnerable (char *buf, size_t sz_buf)
{
  char dst[28];
  memcpy (dst, buf, sz_buf);
  return;
}

int
main (int argc, char **argv)
{
  RCV_DATA_T data;
  SOCKET_T sock;
  CLIENT_CONNECTION_T client = { &data, &sock };

#pragma warning(push)
#pragma warning(disable : 6387)
  (void)WriteProcessMemory ((HANDLE)-1, 0, 0, 0, 0);
#pragma warning(pop)

  InitWinsock ();

  client.sockets->listenSocket = CreateSocket ();
  if (!client.sockets->listenSocket)
    goto err;

  if (!BindSocket (client.sockets->listenSocket))
    goto err;

  if (!DoListen (client.sockets->listenSocket, PORT))
    goto err;

  client.sockets->clientSocket
      = AcceptClientConnection (client.sockets->listenSocket);
  if (!client.sockets->clientSocket)
    goto err;

  RecvData (&client, BUFFER_SIZE);
  vulnerable (client.client_data->data, client.client_data->n_read);

  CloseWinsock (&client);

  return 0;
err:
  return 1;
}
