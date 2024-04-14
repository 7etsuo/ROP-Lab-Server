/**
 * @file my_tcp.c
 * A simple TCP socket interface using the Winsock library.
 * This file implements the necessary operations for TCP communication,
 * including initializing the Winsock library, creating and binding sockets,
 * listening for connections, accepting client connections, receiving data, and
 * closing the connection. These operations facilitate the setup of a TCP
 * server ready to handle client connections and data exchange.
 *
 * Social Media Links:
 * - Twitter: https://twitter.com/7etsuo
 * - GitHub: https://github.com/7etsuo
 * - YouTube: https://www.youtube.com/@snowcrash-
 *
 * Author: 7etsuo, 2024
 */

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "my_tcp.h"

void
InitWinsock (void)
{
  WSADATA wsaData;
  if (WSAStartup (MAKEWORD (2, 2), &wsaData) != 0)
    {
      printf ("WSAStartup failed. Error: %d\n", WSAGetLastError ());
      return 1;
    }
}

SOCKET
CreateSocket (void)
{
  SOCKET listenSocket = INVALID_SOCKET;
  listenSocket = socket (AF_INET, SOCK_STREAM, 0);
  if (listenSocket == INVALID_SOCKET)
    {
      printf ("Socket creation failed. Error: %d\n", WSAGetLastError ());
      WSACleanup ();
      return NULL;
    }

  return listenSocket;
}

int
BindSocket (SOCKET listenSocket)
{
  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons (PORT);

  if (bind (listenSocket, (struct sockaddr *)&serverAddr, sizeof (serverAddr))
      == SOCKET_ERROR)
    {
      printf ("Bind failed. Error: %d\n", WSAGetLastError ());
      closesocket (listenSocket);
      WSACleanup ();
      return 0;
    }

  return 1;
}

int
DoListen (SOCKET listenSocket, int port)
{
  printf ("Listening on port %d...\n", port);

  if (listen (listenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
      printf ("Listen failed. Error: %d\n", WSAGetLastError ());
      closesocket (listenSocket);
      WSACleanup ();
      return 0;
    }

  return 1;
}

SOCKET
AcceptClientConnection (SOCKET listenSocket)
{
  SOCKET clientSocket = INVALID_SOCKET;
  clientSocket = accept (listenSocket, NULL, NULL);
  if (clientSocket == INVALID_SOCKET)
    {
      printf ("Accept failed. Error: %d\n", WSAGetLastError ());
      closesocket (listenSocket);
      WSACleanup ();
      return NULL;
    }

  return clientSocket;
}

int
RecvData (CLIENT_CONNECTION_T *client, SIZE_T max_read)
{
  client->client_data->n_read
      = recv (client->sockets->clientSocket, client->client_data->data,
              max_read - 1, 0);
  if (client->client_data->n_read == SOCKET_ERROR)
    {
      printf ("Recv failed. Error: %d\n", WSAGetLastError ());
      closesocket (client->sockets->clientSocket);
      closesocket (client->sockets->listenSocket);
      WSACleanup ();
      return 0;
    }
  client->client_data->data[client->client_data->n_read] = '\0';
  return 1;
}

void
CloseWinsock (CLIENT_CONNECTION_T *client)
{
  if (client->sockets->clientSocket)
    closesocket (client->sockets->clientSocket);
  if (client->sockets->listenSocket)
    closesocket (client->sockets->listenSocket);
  WSACleanup ();
}
